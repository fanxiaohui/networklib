/*
 * httpClient.h
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_

#include "netClient.h"
#include "seqhelp.h"

struct STHttpReq {
	std::string eType;
	std::string strUrl;
	std::string strHost;
	std::string strContent;
	std::map<std::string, std::string> mapHead;
	void output() {
		printf("eType[%d] = %s\n", (int)eType.size(), eType.c_str());
		printf("strUrl[%d] = %s\n", (int)strUrl.size(), strUrl.c_str());
		printf("strHost[%d] = %s\n", (int)strHost.size(), strHost.c_str());
		printf("strContent[%d] = %s\n", (int)strContent.size(), strContent.c_str());
	}
};

struct STHttpRsp {
	int iStatus;
	std::string strHead;
	std::string strContent;
	void clear() {
		iStatus = 0;
		strHead = "";
		strContent = "";
	}
	void output() {
		printf("iStatus[%d]\n", iStatus);
		printf("strHead[%d] = %s\n", (int)strHead.size(), strHead.c_str());
		printf("strContent[%d] = %s\n", (int)strContent.size(), strContent.c_str());
	}
};

class HttpClientApi: public NetClient {
public:
	HttpClientApi();

	~HttpClientApi();
	const char *GetErrMsg();
public:
	int httpRpc(STHttpReq &req, STHttpRsp &rsp, uint64_t ddwSeqNum = 0);

private:
	int encodeHttpPack(STHttpReq& stReq, std::string& pack);

	int parseChunkedData(const char* buf, int len, std::string& strContent);

	int decodeHttpPack(const char * buf, int len, STHttpRsp& stRsp);

	static int check_http_packet(void *ctx, const char *buf, int len);

private:
	char m_err[256];
	SeqGenerator seqObj;

};

#endif /* HTTPCLIENT_H_ */
