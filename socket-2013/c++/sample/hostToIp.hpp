/*
 * function name : getIpByHome
 * return val:
 *     0 : sucess
 *     -1:hostName error
 *     1 : unknown error
 */

#include<netdb.h>
#include<arpa/inet.h>

int getIpByHome(char const * hostName, char*ip){
	struct hostent *host;
	char **p;

	if ((host = gethostbyname(hostName)) == NULL) {
		return -1;
	}
	p = host->h_addr_list;  //Get the first IP from the List
	if(*p != NULL){
		inet_ntop(AF_INET, *p, ip, INET_ADDRSTRLEN);
		return 0;
	}else{
		return 1;
	}

}
