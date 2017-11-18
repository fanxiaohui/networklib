/*
 * =====================================================================================
 *
 *       Filename:  vjceapi.h
 *
 *    Description: implementation of rpc based on jce protocal 
 *
 *        Version:  1.0
 *        Created:  08/10/14 11:25:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (sdalinluo)
 *					搞一个不包含模调的32位版本
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __V__JCE__API__H__
#define __V__JCE__API__H__

#include "vinvoker.h" //include header file of network actions which written by keaneliu 
#include "video_packet.h"  //include header file of jce and video pack protocal
#include <stdint.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//default buffer size of recv pack,invoker can change this if he likes!!
//but it is useless to enlarge this buffer size,beause the max pack len of 
//CVideoPacket is 100KB at this mement.
#define MAX_RECV_BUF_LEN 128*1024 

namespace vapi
{
	enum ERR_CODE
	{
		JCE_ENCODE_EXCEPTION = 1000,
		VIDEO_PACK_ENCODE_ERR = 10001,
		VIDEO_PACK_ENCODE_EXCEPTION = 10002,
		NET_WORK_LEVEL_ERR = 10003,
		VIDEO_PACK_DECODE_ERR = 10004,
		VIDEO_PACK_DECODE_EXCEPTION = 10005,
		SEQ_NOT_EQUAL = 10006,
		NON_ZERO_CODE_FROM_SVR = 10007,
		JCE_DECODE_EXCEPTION = 10008
	};

	class SeqGenerator
	{
	public:
		SeqGenerator()
		{
			fd_rand = -1;
		}

		~SeqGenerator()
		{
			if(fd_rand != -1)
			{
				close(fd_rand);
			}
		}

		uint64_t GetSeq()
		{
			struct timeval tv; 
			uint64_t ticks;
			uint64_t r;

			gettimeofday(&tv, NULL);
			ticks = tv.tv_sec * 1000000 + tv.tv_usec;

			if(fd_rand == -1)//只打开一次
			{   
				fd_rand = open ("/dev/urandom", O_RDONLY);
			}   

			if (fd_rand > 0)
			{
				read(fd_rand, &r, sizeof (r));
			}

			return ((ticks + r) & 0xFFFFFFFF);
		}

	private:
		int fd_rand;

	};

	inline int CheckVideoPack(void *ctx,char *data,int len)
	{
		return CVideoPacket::checkPacket((const char *)data,(uint32_t)len);
	}

	//jce api class,it is not thread saft.
	class ApiBasedOnJce: public VInvoker
	{
	public:

		ApiBasedOnJce()
		{

		}


		~ApiBasedOnJce()
		{

		}

		//init info of network
		//we use short connection of tcp ,and time out is 1000ms in default 
		//see functions in vinvoker.h header file please

		/*
		 * input:
		 * wCmdId: the cmd id of svr protocal
		 * stReq: the struct of request
		 * stVideoHeader:the pack header of CVideoPacket,you should set some necessary fields 
		 * ddwSeqNum: seqnum,if caller do not send to us,then we make it by ourself,else we use
		 *			  what caller send to us.
		 *
		 * output:
		 * stRsq: the struct of respones data
		 *
		 * return value:
		 * 0:suc;
		 * <0 failed,please reference from ERR_CODE and you can get error msg from GetErrMsg function
		 */
		template<typename TReq,typename TRsp>
			int DoJceRpc(uint16_t wCmdId,TReq &stReq,TRsp &stRsq,videocomm::VideoCommHeader *stVideoHeader = NULL,uint64_t ddwSeqNum = 0)
			{
				CVideoPacket video_packet;
				InvokeCtx stCtx;
				int ret = 0;

				video_packet.setCommand(wCmdId);//set command

				if(ddwSeqNum == 0)//caller do not send seqnum to us
				{
					stCtx.ddwSeqNum = seqObj.GetSeq();
				}
				else
				{
					stCtx.ddwSeqNum = ddwSeqNum;
				}

				video_packet.setSeqId(stCtx.ddwSeqNum);//set seq num

				//encode here
				taf::JceOutputStream<taf::BufferWriter> osBody;
				try
				{
					stReq.writeTo(osBody);
				}
				catch(exception &e)
				{
					snprintf(m_err,sizeof(m_err),"jce encode catch exception,msg[%s]",e.what());
					return -JCE_ENCODE_EXCEPTION;
				}

				//we handle pack header data here
				if(stVideoHeader)
				{
					//dirty code to set header fields
					video_packet.setReqUin(stVideoHeader->BasicInfo.ReqUin);
					video_packet.setServiceType(stVideoHeader->BasicInfo.ServiceType);
					video_packet.setVersion(stVideoHeader->BasicInfo.version);
					video_packet.setResult(stVideoHeader->BasicInfo.Result);
					video_packet.setCallerID(stVideoHeader->BasicInfo.CallerID);
					//video_packet.setSubCmd(stVideoHeader->BasicInfo.SubCmd);
					//video_packet.setBodyFlag(stVideoHeader->BasicInfo.BodyFlag);


					video_packet.setProxyIP(stVideoHeader->AccessInfo.ProxyIP);
					video_packet.setServerIP(stVideoHeader->AccessInfo.ServerIP);
					video_packet.setClientIP(stVideoHeader->AccessInfo.ClientIP);
					video_packet.setClientPort(stVideoHeader->AccessInfo.ClientPort);
					video_packet.setServiceTime(stVideoHeader->AccessInfo.ServiceTime);
					video_packet.setServiceName(stVideoHeader->AccessInfo.ServiceName);
					video_packet.setRtxName(stVideoHeader->AccessInfo.RtxName);
					video_packet.setFileName(stVideoHeader->AccessInfo.FileName);
					video_packet.setFuncName(stVideoHeader->AccessInfo.FuncName);
					video_packet.setLine(stVideoHeader->AccessInfo.Line);
					video_packet.setCgiProcId(stVideoHeader->AccessInfo.CgiProcId);
					video_packet.setFromInfo(stVideoHeader->AccessInfo.FromInfo);
					video_packet.setAccIP(stVideoHeader->AccessInfo.AccIP);
					video_packet.setAccPort(stVideoHeader->AccessInfo.AccPort);
					video_packet.setAccId(stVideoHeader->AccessInfo.AccId);
					video_packet.setClientID(stVideoHeader->AccessInfo.ClientID);


					video_packet.setLoginToken(stVideoHeader->LoginTokens);
					//video_packet.setAccCmdBody(stVideoHeader->AccCmdBody);

				}

				video_packet.setBody((const char *)osBody.getBuffer(),osBody.getLength());

				try
				{
					ret = video_packet.encode();
					if(ret != 0)
					{
						snprintf(m_err,sizeof(m_err),"CVideoPacket encode error,ret[%d]",ret);
						return -VIDEO_PACK_ENCODE_ERR;
					}
				}
				catch(exception &e)
				{
					snprintf(m_err,sizeof(m_err),"CVideoPacket encode catch exception,msg[%s]",e.what());
					return -VIDEO_PACK_ENCODE_EXCEPTION;
				}

				VIResult stRet = Invoke((const char *)video_packet.getPacket(),(int)video_packet.getPacketLen(),recv_buf,(int)sizeof(recv_buf),CheckVideoPack,(void *)&stCtx); 

				if(stRet.code  == 0)//we recv network pack suc
				{
					video_packet.set_packet((uint8_t *)recv_buf,(uint32_t)stRet.rxlen);

					try
					{
						ret = video_packet.decode();
						if(ret != 0)
						{
							snprintf(m_err,sizeof(m_err),"CVideoPacket decode error,ret[%d]",ret);
							return -VIDEO_PACK_DECODE_ERR;
						}
					}
					catch(exception &e)
					{
						snprintf(m_err,sizeof(m_err),"CVideoPacket decode catch exception,msg[%s]",e.what());
						return -VIDEO_PACK_DECODE_EXCEPTION;
					}

					//check seq num
					if(stCtx.ddwSeqNum != (uint64_t)video_packet.getSeqId())
					{
						snprintf(m_err,sizeof(m_err),"seq is not equal,pack_seq[%lu]---local_seq[%lu]",video_packet.getSeqId(),stCtx.ddwSeqNum);
						//clear conn ctx
						ClearConnCtx(&stCtx);
						return -SEQ_NOT_EQUAL;
					}

					uint32_t dwRet = video_packet.getResult();


					if(dwRet == 0)//remote svr do ok
					{
						taf::JceInputStream<taf::BufferReader> isbody; 
						isbody.setBuffer(video_packet.getBody().c_str(),video_packet.getBody().length());

						string strTmp = video_packet.getBody();

						try
						{
							stRsq.readFrom(isbody);
						}
						catch(exception &e)
						{
							snprintf(m_err,sizeof(m_err),"jce decode catch exception,msg[%s]",e.what());
							return -JCE_DECODE_EXCEPTION;
						}

						return 0;
					}
					else
					{
						snprintf(m_err,sizeof(m_err),"ret code[%u] from remote svr",dwRet);
						return dwRet;
					}
				}
				else
				{
					snprintf(m_err,sizeof(m_err),"Invoke error,code[%d],msg[%s],remoteip[%s],remoteport[%u],send_len[%d],recv_len[%d]",stRet.code,stRet.what.c_str(),stRet.ip.c_str(),stRet.port,stRet.txlen,stRet.rxlen);
					return -NET_WORK_LEVEL_ERR;
				}
			}

			int DoJceRpc(uint16_t wCmdId,std::string &stReq,std::string &stRsq,
                    videocomm::VideoCommHeader *stVideoHeader = NULL,uint64_t ddwSeqNum = 0)
			{
				CVideoPacket video_packet;
				InvokeCtx stCtx;
				int ret = 0;

				video_packet.setCommand(wCmdId);//set command

				if(ddwSeqNum == 0)//caller do not send seqnum to us
				{
					stCtx.ddwSeqNum = seqObj.GetSeq();
				}
				else
				{
					stCtx.ddwSeqNum = ddwSeqNum;
				}

				video_packet.setSeqId(stCtx.ddwSeqNum);//set seq num

				//we handle pack header data here
				if(stVideoHeader)
				{
					//dirty code to set header fields
					video_packet.setReqUin(stVideoHeader->BasicInfo.ReqUin);
					video_packet.setServiceType(stVideoHeader->BasicInfo.ServiceType);
					video_packet.setVersion(stVideoHeader->BasicInfo.version);
					video_packet.setResult(stVideoHeader->BasicInfo.Result);
					video_packet.setCallerID(stVideoHeader->BasicInfo.CallerID);
					//video_packet.setSubCmd(stVideoHeader->BasicInfo.SubCmd);
					//video_packet.setBodyFlag(stVideoHeader->BasicInfo.BodyFlag);


					video_packet.setProxyIP(stVideoHeader->AccessInfo.ProxyIP);
					video_packet.setServerIP(stVideoHeader->AccessInfo.ServerIP);
					video_packet.setClientIP(stVideoHeader->AccessInfo.ClientIP);
					video_packet.setClientPort(stVideoHeader->AccessInfo.ClientPort);
					video_packet.setServiceTime(stVideoHeader->AccessInfo.ServiceTime);
					video_packet.setServiceName(stVideoHeader->AccessInfo.ServiceName);
					video_packet.setRtxName(stVideoHeader->AccessInfo.RtxName);
					video_packet.setFileName(stVideoHeader->AccessInfo.FileName);
					video_packet.setFuncName(stVideoHeader->AccessInfo.FuncName);
					video_packet.setLine(stVideoHeader->AccessInfo.Line);
					video_packet.setCgiProcId(stVideoHeader->AccessInfo.CgiProcId);
					video_packet.setFromInfo(stVideoHeader->AccessInfo.FromInfo);
					video_packet.setAccIP(stVideoHeader->AccessInfo.AccIP);
					video_packet.setAccPort(stVideoHeader->AccessInfo.AccPort);
					video_packet.setAccId(stVideoHeader->AccessInfo.AccId);
					video_packet.setClientID(stVideoHeader->AccessInfo.ClientID);


					video_packet.setLoginToken(stVideoHeader->LoginTokens);
					//video_packet.setAccCmdBody(stVideoHeader->AccCmdBody);

				}

				video_packet.setBody((const char *)stReq.c_str(), stReq.length());

				try
				{
					ret = video_packet.encode();
					if(ret != 0)
					{
						snprintf(m_err,sizeof(m_err),"CVideoPacket encode error,ret[%d]",ret);
						return -VIDEO_PACK_ENCODE_ERR;
					}
				}
				catch(exception &e)
				{
					snprintf(m_err,sizeof(m_err),"CVideoPacket encode catch exception,msg[%s]",e.what());
					return -VIDEO_PACK_ENCODE_EXCEPTION;
				}

				VIResult stRet = Invoke((const char *)video_packet.getPacket(),(int)video_packet.getPacketLen(),recv_buf,(int)sizeof(recv_buf),CheckVideoPack,(void *)&stCtx); 

				if(stRet.code  == 0)//we recv network pack suc
				{
					video_packet.set_packet((uint8_t *)recv_buf,(uint32_t)stRet.rxlen);

					try
					{
						ret = video_packet.decode();
						if(ret != 0)
						{
							snprintf(m_err,sizeof(m_err),"CVideoPacket decode error,ret[%d]",ret);
							return -VIDEO_PACK_DECODE_ERR;
						}
					}
					catch(exception &e)
					{
						snprintf(m_err,sizeof(m_err),"CVideoPacket decode catch exception,msg[%s]",e.what());
						return -VIDEO_PACK_DECODE_EXCEPTION;
					}

					//check seq num
					if(stCtx.ddwSeqNum != (uint64_t)video_packet.getSeqId())
					{
						snprintf(m_err,sizeof(m_err),"seq is not equal,pack_seq[%lu]---local_seq[%lu]",video_packet.getSeqId(),stCtx.ddwSeqNum);
						//clear conn ctx
						ClearConnCtx(&stCtx);
						return -SEQ_NOT_EQUAL;
					}

					uint32_t dwRet = video_packet.getResult();


					if(dwRet == 0)//remote svr do ok
					{
						taf::JceInputStream<taf::BufferReader> isbody; 
						isbody.setBuffer(video_packet.getBody().c_str(),video_packet.getBody().length());

						stRsq = video_packet.getBody();

						return 0;
					}
					else
					{
						snprintf(m_err,sizeof(m_err),"ret code[%u] from remote svr",dwRet);
						return dwRet;
					}
				}
				else
				{
					snprintf(m_err,sizeof(m_err),"Invoke error,code[%d],msg[%s],remoteip[%s],remoteport[%u],send_len[%d],recv_len[%d]",stRet.code,stRet.what.c_str(),stRet.ip.c_str(),stRet.port,stRet.txlen,stRet.rxlen);
					return -NET_WORK_LEVEL_ERR;
				}
			}


		const char *GetErrMsg()
		{
			return m_err;
		}

	private:
		char m_err[256];
		SeqGenerator seqObj;

	private:
		char recv_buf[MAX_RECV_BUF_LEN];
	};

}

#endif
