/*************************************************************************
  > File Name: client_tcp_socket.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: Thu 16 Nov 2017 04:06:14 PM UTC
***********************************************************************/

#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
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
    


    ent = gethostbyname(domain);
    if(ent == NULL){
        printf("gethostbyname error. \n");
        return 0;
    }


    fd = socket(PF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        printf("socket error. fd = %d\n", fd);
        return 0;
    }

    inetaddr->sin_family = AF_INET;
    inetaddr->sin_port = htons(80);
    inetaddr->sin_addr.s_addr = ((struct in_addr *) ent->h_addr)->s_addr;

    ret = connect(fd, (struct sockaddr *) inetaddr, sizeof(struct sockaddr_in));
    if(ret < 0){
        printf("connect error\n");
        return 0;
    }

    printf("next\n");
    return 0;
}
