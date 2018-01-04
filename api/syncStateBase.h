#pragma once

class SyncSessionBase;

class SyncStateBase {
public:
    SyncStateBase() {
        retcode = 0;
    }
    virtual ~SyncStateBase() {}


    /**
    * @return
    * =0: 成功
    * <0: 失败
    *
    */
    virtual int pack(std::string& sendBuf,
        SyncSessionBase *pSessionBase) = 0;

    /**
    * @return 
    * >0: 返回完整响应包大小
    * =0: 响应包还不完整
    * <0: 出错
    */
    virtual int checkPack(
        const char *buf,
        int len,
        SyncSessionBase *pSessionBase) = 0;
    virtual int unpack(
        const char *buf,
        int len,
        SyncSessionBase *pSessionBase) = 0;

    int getRetcode() {
        return retcode;
    }

    NetCtx& getNetCtx() {
        return netCtx;
    }

private:
    NetCtx netCtx;
    int retcode;

};
