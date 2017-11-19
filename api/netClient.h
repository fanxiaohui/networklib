/*
 * netClient.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef NETCLIENT_H_
#define NETCLIENT_H_

#include "netConnectPool.h"
#include "netRouter.h"
/*
 * 网络通信结果
 */
struct NetResult {
	NetResult() {
		init();
	}
	NetResult(int _code, const char *_msg = NULL) {
		init();
		if (_msg != NULL) {
			msg.assign(_msg);
		}
	}
	void init() {
		code = 0;
		port = 0;
		txlen = 0;
		rxlen = 0;
		cost = 0;
		msg.clear();
		ip.clear();
	}

	bool operator !() const {
		return code != 0;
	}

	operator bool() const {
		return code == 0;
	}

	int code;
	string msg;
	string ip;
	unsigned short port;
	int txlen;
	int rxlen;
	int cost;
};

/*
 * 通信的上下文
 * 业务可以继承这个上下文
 * 在检查包函数中可以使用这个数据结构
 */
typedef struct {
	uint64_t ddwSeqNum;
	string ip;
	unsigned short port;
	NetActionType m_atype;
	NetProtoType m_proto;
} NetCtx;

class NetClient {
public:

public:
	NetClient() {
		m_proto = NET_PROTO_TYPE_TCP;
		m_atype = NET_ATYPE_TYPE_SHORT;
		m_timeout = 1000;
		m_retry = 0;
	}

	void setRoute(const std::string& domain) {
		m_router.init(domain);
	}

	void setRoute(const std::vector<RouterInfo>& routeList) {
		m_router.init(routeList);
	}

	void setProto(NetProtoType proto) {
		m_proto = proto;
	}

	void setActionType(NetActionType atype) {
		m_atype = atype;
	}

	void setTimeout(int timeout) {
		m_timeout = timeout;
	}

	void setRetryTimes(int retryTimes) {
		m_retry = retryTimes;
	}

	NetResult rpc(const char *txdata, int txlen, char *rxdata, int rxlen,
			PacketCheckFunc checker, void *ctx) {
		NetResult netResult;
		int retry = m_retry;
		if (retry <= 0) {
			retry = 1;
		}
		while (retry--) {
			netResult = realrpc(txdata, txlen, rxdata, rxlen, checker, ctx);

			//if failed,we try again
			if (netResult.code == 0) {
				break;
			}
		}

		return netResult;
	}
	int clearConnCtx(void* ctx) {
		NetCtx* pstCtx = NULL;

		if (ctx) {
			pstCtx = (NetCtx*) ctx;

			// close and remove connection if needed
			if (pstCtx->ip.length() >= 1 && pstCtx->port > 0) {
				m_vcpool.removeConnection(pstCtx->ip, pstCtx->port,
						pstCtx->m_proto);
			}
		}

		return 0;
	}
private:
	NetResult realrpc(const char *txdata, int txlen, char *rxdata, int rxlen,
			PacketCheckFunc checker, void *ctx) {
		// get IP and port from L5 or host array
		NetResult netResult;
		std::string ip;
		unsigned short port;

		NetCtx* pstCtx = NULL;
		if (ctx) {
			pstCtx = (NetCtx*) ctx;
		}

		int ret = m_router.get(ip, port);
		if (ret != 0) {
			netResult.code = ret;
			netResult.msg = m_router.Error();
			return netResult;
		}
		netResult.ip = ip;
		netResult.port = port;

		// get connection from pool
		NetConnect *conn = m_vcpool.getConnection(ip, port, m_proto, m_timeout);
		if (conn == NULL) {
			netResult.code = __LINE__;
			netResult.msg = "get connection failed!";
			return netResult;
		}

		//save ctx
		if (pstCtx) {
			pstCtx->ip = ip;
			pstCtx->port = port;
			pstCtx->m_proto = m_proto;
			pstCtx->m_atype = m_atype;
		}

		struct timeval start;
		struct timeval end;
		gettimeofday(&start, NULL);

		//重新利用该ip建连的次数；
		int iReConTryTimes = 2;

		do {
			//所有异常或者成功就break
			iReConTryTimes--;

			ret = conn->netConnect();
			if (ret < 0) {
				break;
			}

			ret = conn->netSend(txdata, txlen);
			if (ret < 0) {
				break;
			}
			netResult.txlen = ret;

			ret = conn->netRecv(rxdata, rxlen, checker, ctx);
			if (ret < 0) {
				//这是合理的，长链被对端关闭，可能是闲置时间太长等原因导致，
				//如果放在外层重试，可能再选择一个ip，仍然出现该问题，导致业务失败
				if (ret == E_SOCK_CLOSE_R) {
					//仅仅关闭当前的socket；
					conn->netClose();
				} else {
					break;
				}
			} else {
				netResult.rxlen = ret;
				break;
			}
		} while (iReConTryTimes > 0);

		// report route
		gettimeofday(&end, NULL);
		netResult.cost = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec
				- start.tv_usec;
		netResult.code = (ret < 0 ? ret : 0);
		netResult.msg = (ret < 0 ? conn->Error() : "success");
		m_router.report(ip, port, (ret < 0) ? -1 : 0, viresult.cost);

		// close and remove connection if needed
		if (m_atype != NET_ATYPE_TYPE_LONG || ret < 0) {
			m_vcpool.removeConnection(ip, port, m_proto);
		}

		return netResult;
	}

protected:
	NetConnectPool m_vcpool;
	NetRouter m_router;
	NetProtoType m_proto;
	NetActionType m_atype;
	int m_timeout;  // unit: millisecond
	int m_retry;    // retry times
};

#endif /* NETCLIENT_H_ */
