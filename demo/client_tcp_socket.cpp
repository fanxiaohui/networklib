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

int main() {
	//get host
	
	STHttpReq req;
	STHttpRsp rsp;

	HttpClientApi httpClientApi;
	httpClientApi.setRoute("github.tiankonguse.com");
	

	return 0;
}
