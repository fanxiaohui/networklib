/*
 *  write by tiankonguse
 *	email:i@tiankonguse.com
 *	reason:
 *		socket 编程往往需要使用ip,但是我们往往只有域名，那我们就需要做一个具有由域名得到ip的功能的程序。
 *		由于一个域名可能有多个ip,我们返回的时候，就需要返回一个二维数组了，来保存这个ip列表
 *		但是，我这里就只返回一个ip，如果ip不存在，则返回 NULL
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hostToIp.hpp"

int main(int argc, char **argv) {
	char hostName[100] = "tiankonguse.com";
	if(argc == 2){
		strcpy(hostName, argv[1]);
	}

	char ip[INET_ADDRSTRLEN];

	printf("hostname : %s\n", hostName);

	int state = getIpByHome(hostName, ip);

	if(state == 0){
		printf("ip : %s\n",ip);
	}else{
		printf("error code : %d\n",state);
	}

	return 0;
}
