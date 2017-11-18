#ifndef __VINVOKER_H__
#define __VINVOKER_H__

#include <vector>
#include "vdefine.h"
#include "vconnection.h"
#include "vinvoker.h"
#include "vrouter.h"

namespace vapi
{

using namespace std;

struct VIResult
{
    VIResult() : code(0), port(0), txlen(0), rxlen(0), cost(0) {}
    VIResult(int _code, const char *_msg = NULL)
        : code(_code), port(0), txlen(0), rxlen(0), cost(0)
    {
        if (_msg != NULL) {
            what.assign(_msg);
        }
        else {
            what = "";
        }
    }
        
    inline bool operator !() const
    {
        return code != 0;
    }

    inline operator bool() const
    {
        return code == 0;
    }        

    int code;
    string what;
    string ip;
    unsigned short port;
    int txlen;
    int rxlen;
    int cost;
};

//ִ�и������������
typedef struct {
	uint64_t ddwSeqNum; //����ִ�д˴���������к�
    string ip;			//����ɹ�ִ�д˴����� ip
    unsigned short port; //����ɹ�ִ�д˴�����port
	VActionType m_atype; //m_atype, ATYPE_LONG
    VProto m_proto;
}InvokeCtx;

class VInvoker
{
public:
    VInvoker() : m_proto(PROTO_TCP), m_atype(ATYPE_SHORT), m_timeout(1000) {}

    inline void SetRoute(int mod, int cmd, float timeout = 0.5)
    {
        m_router.Init(mod, cmd, timeout);
    }

    inline void SetRoute(vector<string> &hosts, unsigned short port)
    {
        m_router.Init(hosts, port);
    }

    inline void SetProto(VProto proto)
    {
        m_proto = proto;
    }

    inline void SetActionType(VActionType atype)
    {
        m_atype = atype;
    }

    inline void SetTimeout(int timeout)
    {
        m_timeout = timeout;
    }

    inline void SetRetryTimes(int retryTimes)
    {
        m_retry = retryTimes;
    }

    /*
    * Invoke() ���͵��÷�ָ�������ݣ���������Ӧ���ݷ�����÷�ָ���ĵ�ַ��
    * �ڷ��ͺͽ�������ǰ��Invoke() �Ḻ�𵽷���˵�·��ѡ������ӹ���
    * �ڽ������ݹ����У�Invoke() ��ص����÷�ָ���ĺ�����������������ݡ�
    *
    * ����˵��:
    *   txdata: ���������ݵĴ�ŵ�ַ
    *   txlen: ���������ݵĳ���
    *   rxdata: ��Ž������ݵĻ�������ַ���ɵ��÷�������ͷ�
    *   rxlen: ��Ž������ݵĻ��������ȣ�Invoke()��������ʱ���ܳ����ó���
    *   checker: ���������ݵĻص�����ָ�룬�ɵ��÷�ָ������Invoke()�ص�
    *       checker()����<0��ʾУ�����Invoke()Ӧ�ö���������
    *       checker()����0��ʾ������δ����������Invoke()Ӧ�ü�����������
    *       checker()����>0��ʾ�����ѽ�������������ֵ��Ϊ�����յ����ݰ�����
    *   ctx: checker()У������ʱ�����������ָ�룬����seq����Ϣ��
    *       Invoke()��ctx͸����checker()
    *
    * ����ֵ˵��:
    *   VIResult.code: �����룬0��ʾ�ɹ�����0��ʾʧ��
    *   VIResult.what: ������Ϣ
    *   VIResult.ip: ����������ķ����IP
    *   VIResult.port: ����������ķ���˶˿�
    *   VIResult.txlen: ���������������͵����ݳ���
    *   VIResult.rxlen: ���������������յ����ݳ���
    *   VIResult.cost: ��������ĺ�ʱ
    */
    VIResult Invoke(const char *txdata, int txlen, char *rxdata, int rxlen,
        PacketCheckFunc checker, void *ctx);

    /**************************************************************
	 * �������ӵ������ģ���������Ӧ����Ч���߷���ʱ����Ҫ����
	 * ************************************************************/
	int ClearConnCtx(void* ctx);

private:
    VIResult DoInvoke(const char *txdata, int txlen, char *rxdata, int rxlen,
        PacketCheckFunc checker, void *ctx);

protected:
    static VConnectionPool m_vcpool;
    VRouter m_router;
    VProto m_proto;
    VActionType m_atype;
    int m_timeout;  // unit: millisecond
    int m_retry;    // retry times
};

}

#endif

