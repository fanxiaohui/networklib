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
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

int main() {
	//get host
	struct hostent *ent;
	const char* domain = "github.tiankonguse.com";
	int fd = 0;
	int ret = 0;
	struct sockaddr_in inetaddr;
	char str[32];

	ent = gethostbyname(domain);
	if (ent == NULL) {
		printf("gethostbyname error. \n");
		return 0;
	}
	printf(" first address: %s\n", inet_ntop(ent->h_addrtype, ent->h_addr, str, sizeof(str)));

	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		printf("socket error. fd = %d\n", fd);
		return 0;
	}
//	ret = connect(fd, (struct sockaddr *) inetaddr, sizeof(struct sockaddr_in));
//	if (ret < 0) {
//		printf("connect error\n");
//		return 0;
//	}

	printf("next\n");
	return 0;
}
