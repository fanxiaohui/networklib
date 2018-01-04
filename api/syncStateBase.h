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
    * =0: �ɹ�
    * <0: ʧ��
    *
    */
    virtual int pack(std::string& sendBuf,
        SyncSessionBase *pSessionBase) = 0;

    /**
    * @return 
    * >0: ����������Ӧ����С
    * =0: ��Ӧ����������
    * <0: ����
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
