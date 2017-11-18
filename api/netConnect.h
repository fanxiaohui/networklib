/*
 * netConnect.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef NETCONNECT_H_
#define NETCONNECT_H_

#include <stdio.h>       /* for snprintf */
#include <string.h>      /* for bzero  */
#include <string>
#include <sys/socket.h>  /* for socket, setsockopt, connect */
#include <netinet/in.h>  /* for htons  */
#include <arpa/inet.h>   /* for inet_pton  */
#include "fdhelp.h"

enum NetProto {
	NET_PROTO_TCP = 0, NET_PROTO_UDP = 1
};

enum NetActionType {
	NET_ATYPE_SHORT = 0, NET_ATYPE_LONG = 1
};

typedef int (*PacketCheckFunc)(void *ctx, char *data, int len);

class NetConnect {
public:
	NetConnect(const std::string &ip, int port, NetProto proto, int timeout) {
		m_ip = ip;
		m_port = port;
		m_proto = proto;
		m_timeout = timeout;
		m_err[0] = 0;
	}
	~NetConnect() {
	}

	int netConnect() {
		if (fdHelp.fd() > 0) {
			m_err[0] = 0;
			return 0;
		}
		fdHelp.reset();
		int& m_sockfd = fdHelp.fd();

		if (m_proto == NET_PROTO_TCP) {
			m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		} else if (m_proto == NET_PROTO_UDP) {
			m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		} else {
			return __LINE__;
		}

		if (m_sockfd < 0) {
			snprintf(m_err, sizeof(m_err), "socket() return %d, errno=%d",
					m_sockfd, errno);
			return __LINE__;
		}

		struct sockaddr_in m_addr;
		bzero(&m_addr, sizeof(m_addr));
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(m_port);
		int ret = inet_pton(AF_INET, m_ip.c_str(), (void*) &(m_addr.sin_addr));
		if (ret <= 0) {
			snprintf(m_err, sizeof(m_err), "inet_pton() return %d, ip=%s", ret,
					m_ip.c_str());
			return __LINE__;
		}

		// set timeout of send and recv
		struct timeval tv;
		tv.tv_sec = m_timeout / 1000;
		tv.tv_usec = (m_timeout % 1000) * 1000;
		ret = setsockopt(m_sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*) &tv,
				sizeof(tv));
		if (ret < 0) {
			snprintf(m_err, sizeof(m_err),
					"setsockopt(SO_RCVTIMEO) return %d, errno=%d", ret, errno);
			return __LINE__;
		}
		ret = setsockopt(m_sockfd, SOL_SOCKET, SO_SNDTIMEO, (char*) &tv,
				sizeof(tv));
		if (ret < 0) {
			snprintf(m_err, sizeof(m_err),
					"setsockopt(SO_SNDTIMEO) return %d, errno=%d", ret, errno);
			return __LINE__;
		}

		// set linger
		struct linger lingers;
		/*
		 *  l_onoff: 0, 忽略l_linger。 close后，缓冲区数据继续发送给对方。 默认选项。
		 *  l_onoff: 1, l_linger: 0。 close后，如果缓冲区有内容将丢弃，并回复对方RST。这样可以避免TIME_WAIT
		 *  l_onoff: 1, l_linger: 1。 close后，系统决定如何处理。默认阻塞一会。
		 */
		lingers.l_onoff = 1;
		lingers.l_linger = 0;
		setsockopt(m_sockfd, SOL_SOCKET, SO_LINGER, &lingers, sizeof(lingers));

		ret = connect(m_sockfd, (struct sockaddr*) &m_addr, sizeof(m_addr));
		if (ret < 0) {
			snprintf(m_err, sizeof(m_err),
					"connect() return %d, errno=%d, addr=%s:%d", ret, errno,
					m_ip.c_str(), m_port);
			return __LINE__;
		}

		m_err[0] = 0;
		return 0;
	}

	int netSend(const char *data, int len) {
		//before we send,we have to judge if fd can writable
		int ret = 0;
		short wSelectTime = 0;

		fd_set wfds;
		struct timeval tv;

		do {
			//On error, -1 is returned, and errno is set appropriately; the sets and timeout become undefined, so do not rely on their contents after an error
			//please see man select

			wSelectTime++;
			if (wSelectTime >= 2) {
				break;
			}

			tv.tv_sec = 0;
			tv.tv_usec = 0;

			//only check
			FD_ZERO(&wfds);
			FD_SET(m_sockfd, &wfds);
			ret = select(m_sockfd + 1, NULL, &wfds, NULL, &tv);
		} while (ret < 0 && errno == EINTR);

		if (ret == 0) {
			snprintf(m_err, sizeof(m_err),
					"select before send timeout,errno=%d,data=%p,len=%d,addr=%s:%d",
					errno, data, len, m_ip.c_str(), m_port);
			return E_SOCK_CLOSE_W;
		}

		if (ret == -1) {
			snprintf(m_err, sizeof(m_err),
					"select error before send errno=%d,msg=%s,data=%p,len=%d,addr=%s:%d",
					errno, strerror(errno), data, len, m_ip.c_str(), m_port);

			return E_SOCK_CLOSE_W;
		}

		if (ret > 0) {
			if (FD_ISSET(m_sockfd, &wfds))            //can write
					{
				ret = send(m_sockfd, data, len, 0);
				if (ret < 0) {
					snprintf(m_err, sizeof(m_err),
							"send() return %d, errno=%d, data=%p, len=%d, addr=%s:%d",
							ret, errno, data, len, m_ip.c_str(), m_port);
					return E_SEND;
				}
			} else {
				snprintf(m_err, sizeof(m_err),
						"select m_sockfd=%d is not in wfds errno=%d,msg=%s,data=%p,len=%d,addr=%s:%d",
						m_sockfd, errno, strerror(errno), data, len,
						m_ip.c_str(), m_port);

				return E_SEND;

			}
		}

		m_err[0] = 0;
		return ret;
	}
	int netRecv(char *data, int len, PacketCheckFunc checker, void *ctx) {
		int n = 0;
		while (n < len) {
			int ret = recv(m_sockfd, data + n, len - n, 0);
			if (ret < 0) {
				snprintf(m_err, sizeof(m_err),
						"recv() return %d, errno=%d, data=%p, len=%d, addr=%s:%d",
						ret, errno, data, len, m_ip.c_str(), m_port);
				return E_RECV;
			}

			n += ret;
			// EOF
			if (n == 0) {
				snprintf(m_err, sizeof(m_err),
						"recv() return EOF, data=%p, len=%d, addr=%s:%d", data,
						len, m_ip.c_str(), m_port);
				return E_SOCK_CLOSE_R;
			}

			// check received data with the passed-in "checker"
			int result = checker(ctx, data, n);
			if (result < 0) {
				// invalid data, need to return error
				snprintf(m_err, sizeof(m_err),
						"check data failed! result=%d, data=%p, len=%d", result,
						data, n);
				return E_CHECKPKG;
			} else if (result == 0) {
				// incomplete data, continue to recv
				continue;
			} else {
				m_err[0] = 0;
				return n;
			}
		}

		snprintf(m_err, sizeof(m_err), "not enough buffer! data=%p, len=%d",
				data, n);
		return E_BUFFER;
	}
	void netClose() {
		fdHelp.closefd();
	}

	std::string GetIP() {
		return m_ip;
	}

	int GetPort() {
		return m_port;
	}

	NetProto GetProto() {
		return m_proto;
	}

	const char* Error() {
		return m_err;
	}

private:
	FdHelp fdHelp;
	struct sockaddr_in m_addr;

	std::string m_ip;
	int m_port;
	NetProto m_proto;
	int m_timeout;  // unit: millisecond
	char m_err[1024];
};

#endif /* NETCONNECT_H_ */
