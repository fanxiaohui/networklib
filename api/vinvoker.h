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

//执行该请求的上下文
typedef struct {
	uint64_t ddwSeqNum; //保存执行此次请求的序列号
    string ip;			//保存成功执行此次请求 ip
    unsigned short port; //保存成功执行此次请求port
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
    * Invoke() 发送调用方指定的数据，并接收响应数据放入调用方指定的地址。
    * 在发送和接收数据前后，Invoke() 会负责到服务端的路由选择和连接管理。
    * 在接收数据过程中，Invoke() 会回调调用方指定的函数来检测所接收数据。
    *
    * 参数说明:
    *   txdata: 待发送数据的存放地址
    *   txlen: 待发送数据的长度
    *   rxdata: 存放接收数据的缓冲区地址，由调用方分配和释放
    *   rxlen: 存放接收数据的缓冲区长度，Invoke()接收数据时不能超过该长度
    *   checker: 检测接收数据的回调函数指针，由调用方指定、由Invoke()回调
    *       checker()返回<0表示校验出错，Invoke()应该丢弃该数据
    *       checker()返回0表示数据尚未接收完整，Invoke()应该继续接收数据
    *       checker()返回>0表示数据已接收完整，返回值即为所接收的数据包长度
    *   ctx: checker()校验数据时所需的上下文指针，例如seq等信息，
    *       Invoke()将ctx透传给checker()
    *
    * 返回值说明:
    *   VIResult.code: 返回码，0表示成功，非0表示失败
    *   VIResult.what: 返回信息
    *   VIResult.ip: 本次所请求的服务端IP
    *   VIResult.port: 本次所请求的服务端端口
    *   VIResult.txlen: 本次所请求所发送的数据长度
    *   VIResult.rxlen: 本次所请求所接收的数据长度
    *   VIResult.cost: 本次请求的耗时
    */
    VIResult Invoke(const char *txdata, int txlen, char *rxdata, int rxlen,
        PacketCheckFunc checker, void *ctx);

    /**************************************************************
	 * 清理连接的上下文，当该连接应该无效或者废弃时，需要调用
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

