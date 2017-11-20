#include "netClient.h"


NetResult::NetResult() {
	init();
}
NetResult::NetResult(int _code, const char *_msg) {
	init();
	if (_msg != NULL) {
		msg.assign(_msg);
	}
}
void NetResult::init() {
	code = 0;
	port = 0;
	txlen = 0;
	rxlen = 0;
	cost = 0;
	msg.clear();
	ip.clear();
}

bool NetResult::operator !() const {
	return code != 0;
}

NetResult::operator bool() const {
	return code == 0;
}

NetClient::NetClient() {
	m_proto = NET_PROTO_TYPE_TCP;
	m_atype = NET_ATYPE_TYPE_SHORT;
	m_timeout = 1000;
	m_retry = 0;
}

void NetClient::setRoute(const std::string& domain) {
	m_router.init(domain);
}

void NetClient::setRoute(const std::vector<RouterInfo>& routeList) {
	m_router.init(routeList);
}

void NetClient::setProto(NetProtoType proto) {
	m_proto = proto;
}

void NetClient::setActionType(NetActionType atype) {
	m_atype = atype;
}

void NetClient::setTimeout(int timeout) {
	m_timeout = timeout;
}

void NetClient::setRetryTimes(int retryTimes) {
	m_retry = retryTimes;
}

NetResult NetClient::rpc(const char *txdata, int txlen, char *rxdata, int rxlen,
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
int NetClient::clearConnCtx(void* ctx) {
	NetCtx* pstCtx = NULL;

	if (ctx) {
		pstCtx = (NetCtx*)ctx;

		// close and remove connection if needed
		if (pstCtx->ip.length() >= 1 && pstCtx->port > 0) {
			m_vcpool.removeConnection(pstCtx->ip, pstCtx->port,
				pstCtx->m_proto);
		}
	}

	return 0;
}
NetResult NetClient::realrpc(const char *txdata, int txlen, char *rxdata, int rxlen,
	PacketCheckFunc checker, void *ctx) {
	// get IP and port from L5 or host array
	NetResult netResult;
	std::string ip;
	unsigned short port;

	NetCtx* pstCtx = NULL;
	if (ctx) {
		pstCtx = (NetCtx*)ctx;
	}

	int ret = m_router.get(ip, port);
	if (ret != 0) {
		netResult.code = ret;
		netResult.msg = m_router.error();
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

	TimeHelp timehelp;

	timehelp.start();

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
			if (ret < 0) {
				//仅仅关闭当前的socket；
				conn->netClose();
			}
			else {
				break;
			}
		}
		else {
			netResult.rxlen = ret;
			break;
		}
	} while (iReConTryTimes > 0);

	// report route
	timehelp.end();
	netResult.cost = timehelp.cost();
	netResult.code = (ret < 0 ? ret : 0);
	netResult.msg = (ret < 0 ? conn->error() : "success");
	m_router.report(ip, port, (ret < 0) ? -1 : 0, netResult.cost);

	// close and remove connection if needed
	if (m_atype != NET_ATYPE_TYPE_LONG || ret < 0) {
		m_vcpool.removeConnection(ip, port, m_proto);
	}

	return netResult;
}