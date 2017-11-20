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
#include "lockhelp.h"

enum NetProtoType {
	NET_PROTO_TYPE_TCP = 0, //
	NET_PROTO_TYPE_UDP = 1
};

enum NetActionType {
	NET_ATYPE_TYPE_SHORT = 0, //
	NET_ATYPE_TYPE_LONG = 1
};

/*
 * 检查包函数
 * 由于网络操作是流式的，这里需要业务提供一个函数来检查包的完整性
 * 返回值定义如下：
 * 大于0： 包收完了，值为包的长度
 * 等于0：包还没有收完
 * 小于0：包非法，停止收包
 *
 */
typedef int (*PacketCheckFunc)(void *ctx, const char *data, int len);

class NetConnect {
public:
	NetConnect(const std::string &ip, int port, NetProtoType proto,
			int timeout);
	~NetConnect();

public:
	int netConnect();

	int netSend(const char *data, int len);
	int netRecv(char *data, int len, PacketCheckFunc checker, void *ctx);
	void netClose();

public:
	std::string getIP();
	int getPort();

	NetProtoType getProto();

	const char* error();

private:
	FdHelp fdHelp;
	struct sockaddr_in m_addr;

	std::string m_ip;
	int m_port;
	NetProtoType m_proto;
	int m_timeout;  // unit: millisecond
	char m_err[1024];
};

#endif /* NETCONNECT_H_ */
