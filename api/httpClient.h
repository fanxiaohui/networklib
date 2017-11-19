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
};

struct STHttpRsp {
	int iStatus;
	string strHead;
	string strContent;
	void clear() {
		iStatus = 0;
		strHead = "";
		strContent = "";
	}
};

class HttpClientApi: public NetClient {
public:
	HttpClientApi() {

	}

	~HttpClientApi() {

	}
	const char *GetErrMsg() {
		return m_err;
	}
public:
	int httpRpc(STHttpReq &req, STHttpRsp &rsp, uint64_t ddwSeqNum = 0) {
		int iRet = 0;
		std::string pack;
		static char buf[128 * 1024];
		rsp.clear();

		iRet = encodeHttpPack(req, pack);
		if (0 != iRet) {
			return iRet;
		}

		int len = sizeof(buf);

		NetResult stRet = Invoke((const char *) (pack.c_str()),
				(int) pack.length(), buf, len, check_http_packet,
				NULL);

		if (stRet.code == 0) {
			iRet = decodeHttpPack(buf, len, rsp);
		}

		return iRet;
	}

private:
	int encodeHttpPack(STHttpReq& stReq, std::string& pack) {
		pack = stReq.eType + " " + stReq.strUrl + " HTTP/1.1\r\n";
		if (!stReq.strHost.empty()) {
			pack.append("HOST: ");
			pack.append(stReq.strHost);
		}
		pack.append("\r\n");

		map<string, string>::const_iterator iter;
		for (iter = stReq.mapHead.begin(); iter != stReq.mapHead.end();
				++iter) {
			pack.append(iter->first);
			pack.append(": ");
			pack.append(iter->second);
			pack.append("\r\n");
		}

		char szTemp[64] = { 0 };
		snprintf(szTemp, sizeof(szTemp) - 1, "Content-Length: %u\r\n\r\n",
				(unsigned int) stReq.strContent.length());
		pack.append(szTemp);

		pack.append(stReq.strContent);

		return 0;
	}

	int parseChunkedData(const char* buf, int len, string& strContent) {
		string strData = string(buf, len);
		size_t sPos1 = 0;
		while (1) {
			size_t sPos2 = strData.find("\r\n", sPos1);
			if (sPos2 == string::npos) {
				break;
			}
			int iLen = strtoll(strData.substr(sPos1, sPos2 - sPos1).c_str(), 0,
					16);
			if (iLen <= 0) {
				break;
			}
			if (sPos2 + 2 + iLen > strData.size()) {
				break;
			}
			strContent.append(strData, sPos2 + 2, iLen);
			sPos1 = sPos2 + 2 + iLen + 2;
		}

		return 0;
	}

	int decodeHttpPack(const char * buf, int len, STHttpRsp& stRsp) {
		int iRet = 0;

		string strRsp(buf, len);
		size_t sPos = strRsp.find("\r\n\r\n");
		sPos += 4;
		stRsp.strHead = strRsp.substr(0, sPos);
		stRsp.iStatus = atoi(stRsp.strHead.substr(9, 3).c_str());

		if (strRsp.find("Transfer-Encoding: chunked") == string::npos) {
			//not trunk data..
			stRsp.strContent = strRsp.substr(sPos);
		} else {
			//trunked data.
			iRet = parseChunkedData(strRsp.c_str() + sPos, strRsp.size() - sPos,
					stRsp.strContent);
		}
		return iRet;
	}

	int check_http_packet(void *ctx, const char *buf, uint32_t len) {
		std::string strHeader;
		std::string strRsp((char*) buf, len);

		if (strRsp.size() >= 4 && strRsp.find("HTTP") == string::npos) {
			return -1;
		}

		size_t sPosHead = strRsp.find("\r\n\r\n");
		if (sPosHead == string::npos) {
			return 0;
		}

		sPosHead += 4;

		size_t sPosLen = strRsp.find("Content-Length: ");
		if (sPosLen == string::npos) {
			sPosLen = strRsp.find("content-length: ");
		}

		if (sPosLen == string::npos) {
			//no Content-length.cheeck if trunked.
			sPosLen = strRsp.find("Transfer-Encoding: chunked");
			if (sPosLen == string::npos) {
				sPosLen = strRsp.find("transfer-encoding: ");
			}

			if (sPosLen == string::npos) {
				return sPosHead;
			} else {
				size_t sPosEnd = strRsp.find("\r\n0\r\n\r\n", sPosHead);
				if (sPosEnd == string::npos) {
					return 0;
				} else {
					return (sPosEnd + 7);
				}
			}
		} else {
			//get content- length ,get len.
			int iLen = atoll(strRsp.c_str() + sPosLen + 16);
			if (iLen <= 0) {
				return sPosHead;
			}
			if (strRsp.size() < (sPosHead + iLen)) {
				return 0;
			} else {
				return sPosHead + iLen;
			}
		}
	}

private:
	char m_err[256];
	SeqGenerator seqObj;

};

#endif /* HTTPCLIENT_H_ */
