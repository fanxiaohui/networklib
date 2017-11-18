#include <sys/time.h>
#include "vinvoker.h"

namespace vapi
{

using namespace std;

VConnectionPool VInvoker::m_vcpool;

VIResult VInvoker::Invoke(const char *txdata, int txlen,
                          char *rxdata, int rxlen,
                          PacketCheckFunc checker, void *ctx)
{
    VIResult viresult;
    int retry = m_retry;
    if (retry <= 0) retry = 1;
    for (int i = 0; i <= retry; i++) {
        viresult = DoInvoke(txdata, txlen, rxdata, rxlen, checker, ctx);
        if (viresult.code == 0) {//if failed,we try again
            break;
        }
    }

    return viresult;
}

VIResult VInvoker::DoInvoke(const char *txdata, int txlen,
                          char *rxdata, int rxlen,
                          PacketCheckFunc checker, void *ctx)
{
    // get IP and port from L5 or host array
    VIResult viresult;
    string ip;
    unsigned short port;

	InvokeCtx* pstCtx = NULL;
	if (ctx) pstCtx = (InvokeCtx*)ctx;

    int ret = m_router.GetRoute(ip, port);
    if (ret != 0) {
        viresult.code = ret;
        viresult.what = m_router.Error();
        return viresult;
    }
    viresult.ip = ip;
    viresult.port = port;

    // get connection from pool
    VConnection *conn = m_vcpool.GetConnection(ip, port, m_proto, m_timeout);
    if (conn == NULL) {
        viresult.code = E_GETCONN;
        viresult.what = "get connection failed!";
        return viresult;
    }

	//save ctx 
	if (pstCtx)
	{
		pstCtx->ip = ip;
		pstCtx->port = port;
		pstCtx->m_proto = m_proto;
		pstCtx->m_atype = m_atype;
	}

    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);

    //重新利用该ip建连的次数；
    int iReConTryTimes = 2;

    do {
        //所有异常或者成功就break
        iReConTryTimes--;

        ret = conn->Connect();
        if (ret < 0) {
            break;
        }
        
        ret = conn->Send(txdata, txlen);
        if (ret < 0) {
            break;
        }
        viresult.txlen = ret;

        ret = conn->Recv(rxdata, rxlen, checker, ctx);
        if (ret < 0) {
            //这是合理的，长链被对端关闭，可能是闲置时间太长等原因导致，
            //如果放在外层重试，可能再选择一个ip，仍然出现该问题，导致业务失败
            if (ret == E_SOCK_CLOSE_R )
            {
                //仅仅关闭当前的socket；
                conn->Close();
            }
            else
            {
                break;
            }
        }
        else
        {
            viresult.rxlen = ret;
            break;
        }
    } while (iReConTryTimes > 0);

    // report route
    gettimeofday(&end, NULL);
    viresult.cost = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    viresult.code = (ret < 0 ? ret : 0);
    viresult.what = (ret < 0 ? conn->Error() : "success");
    m_router.EndRoute(ip, port, (ret < 0) ? -1 : 0, viresult.cost);

    // close and remove connection if needed
    if (m_atype != ATYPE_LONG || ret < 0) {
        m_vcpool.RemoveConnection(ip, port, m_proto);
    }

    return viresult;
}

int  VInvoker::ClearConnCtx(void* ctx)
{
	InvokeCtx* pstCtx = NULL;

	if (ctx) 
	{
		pstCtx = (InvokeCtx*)ctx;

		// close and remove connection if needed
		if (pstCtx->ip.length() >= 1 && pstCtx->port > 0) 
		{
			m_vcpool.RemoveConnection(pstCtx->ip, pstCtx->port, pstCtx->m_proto);
		}
	}

	return 0;
}

}

