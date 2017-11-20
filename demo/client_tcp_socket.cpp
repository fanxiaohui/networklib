/*************************************************************************
 > File Name: client_tcp_socket.cpp
 > Author: tiankonguse(skyyuan)
 > Mail: i@tiankonguse.com
 > Created Time: Thu 16 Nov 2017 04:06:14 PM UTC
 ***********************************************************************/

#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>  /*for socket           */
#include <sys/types.h>  /* BSD socket required  */
#include <netdb.h>      /* for gethostbyname    */
#include <arpa/inet.h>  /* for inet_ntop        */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include "httpClient.h"
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

void syncHttpTest(int times) {

	//get host
	//http://github.tiankonguse.com/data/test_2.json
	//http://github.tiankonguse.com/data/test_1.json

	STHttpReq req;
	STHttpRsp rsp;
	int iRet = 0;

	HttpClientApi httpClientApi;
	std::string domain = "github.tiankonguse.com";
	httpClientApi.setRoute(domain);
	req.eType = "GET";
	req.strHost = domain;


	while (times-- >= 0) {
		req.strUrl = "/data/test_1.json";

		iRet = httpClientApi.httpRpc(req, rsp);
		if (iRet == 0) {
			if (times < 0) {
				printf("%s\n", req.strUrl.c_str());
				printf("%s\n", rsp.strContent.c_str());
			}
		}
		else {
			printf("iRet=%d\n", iRet);
			req.output();
			rsp.output();
		}

		req.strUrl = "/data/test_2.json";
		iRet = httpClientApi.httpRpc(req, rsp);
		if (iRet == 0) {
			if (times < 0) {
				printf("%s\n", req.strUrl.c_str());
				printf("%s\n", rsp.strContent.c_str());
			}
		}
		else {
			printf("iRet=%d\n", iRet);
			req.output();
			rsp.output();
		}
	}

}


int main() {

	TimeHelp timehelp;
	int times = 20;
	timehelp.start();
	syncHttpTest(times);
	timehelp.end();
	printf("times=%d cost %lldus\n", times, timehelp.cost());
	return 0;
}
