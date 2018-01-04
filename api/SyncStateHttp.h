#pragma once

#include "syncStateBase.h"
#include "httpClient.h"

class SyncStateHttp : public SyncStateBase {
public:
    virtual ~SyncStateHttp() {}


    /**
    * @return
    * =0: 成功
    * <0: 失败
    *
    */
    virtual int pack(std::string& sendBuf,
        SyncSessionBase *pSessionBase) {
        return httpClientApi.encodeHttpPack(req, sendBuf);
    }

    /**
    * @return
    * >0: 返回完整响应包大小
    * =0: 响应包还不完整
    * <0: 出错
    */
    virtual int checkPack(
        const char *buf,
        int len,
        SyncSessionBase *pSessionBase) {
        return httpClientApi.check_http_packet(pSessionBase, buf, len);
    }
    virtual int unpack(
        const char *buf,
        int len,
        SyncSessionBase *pSessionBase) {
        return httpClientApi.decodeHttpPack(buf, len, rsp);
    }

    STHttpReq& getReq() {
        return req;
    }

    STHttpRsp& getRsp() {
        return rsp;
    }

private:
    STHttpReq req;
    STHttpRsp rsp;
    HttpClientApi httpClientApi;
};


