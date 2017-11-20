/*
 * netClient.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef NETCLIENT_H_
#define NETCLIENT_H_

#include <sys/time.h> /* for gettimeofday */
#include <string>
#include "netConnectPool.h"
#include "netRouter.h"
#include "timehelp.h"
/*
 * 网络通信结果
 */
struct NetResult {
	NetResult();
	NetResult(int _code, const char *_msg = NULL);
	void init();
	bool operator !() const;
	operator bool() const;

	int code;
	std::string msg;
	std::string ip;
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
	unsigned short port;
	NetActionType m_atype;
	NetProtoType m_proto;
	std::string ip;
} NetCtx;

class NetClient {
public:

public:
	NetClient();
	void setRoute(const std::string& domain);
	void setRoute(const std::vector<RouterInfo>& routeList);
	void setProto(NetProtoType proto);
	void setActionType(NetActionType atype);
	void setTimeout(int timeout);
	void setRetryTimes(int retryTimes);

	NetResult rpc(const char *txdata, int txlen, char *rxdata, int rxlen,
		PacketCheckFunc checker, void *ctx);
	int clearConnCtx(void* ctx);
private:
	NetResult realrpc(const char *txdata, int txlen, char *rxdata, int rxlen,
		PacketCheckFunc checker, void *ctx);
protected:
	NetConnectPool m_vcpool;
	NetRouter m_router;
	NetProtoType m_proto;
	NetActionType m_atype;
	int m_timeout;  // unit: millisecond
	int m_retry;    // retry times
};

#endif /* NETCLIENT_H_ */
