#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/regex.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace boost;

#include "hostToIp.hpp"

const char * HOSTSTR = "tiankonguse.com";
const int BUFSIZE = 1024;
const int SIZE = BUFSIZE * BUFSIZE;
const int PORT = 80;

int main(int argc, char **argv) {
	char ipStr[INET_ADDRSTRLEN];
	int state = getIpByHome(HOSTSTR, ipStr);
	if (state != 0) {
		printf("get ip from host failed!\n");
		exit(0);
	}

	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket failed!\n");
		exit(0);
	};

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, ipStr, &servaddr.sin_addr) <= 0) {
		printf("convert addresses to binary failed!\n");
		exit(0);
	};

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		printf("connect to server failed!\n");
		exit(0);
	}

	printf("connect to server  sucess\n");

	//发送数据

	char postData[SIZE];
	socklen_t postDataLen;
	char postDataLenStr[SIZE];

	memset(postData, 0, SIZE);
	strcat(postData, "num=5&id=9");
	postDataLen = strlen(postData);
	sprintf(postDataLenStr, "%d", postDataLen);

	char requestHeader[SIZE];
	memset(requestHeader, 0, SIZE);
	strcat(requestHeader, "POST /timeline/inc/control.php?state=1 HTTP/1.1\n");
	strcat(requestHeader, "Host: tiankonguse.com\n");
	strcat(requestHeader, "Connection: keep-alive\n");
	strcat(requestHeader,
			"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\n");
	strcat(requestHeader, "Content-Length: ");
	strcat(requestHeader, postDataLenStr);
	strcat(requestHeader, "\n\n");

	strcat(requestHeader, postData);
	strcat(requestHeader, "\r\n\r\n");
	//printf("%s\n", requestHeader);

	int ret = write(sockfd, requestHeader, strlen(requestHeader));
	if (ret < 0) {
		printf("send failed! error code:%d，error info'%s'\n", errno,
				strerror(errno));
		exit(0);
	} else {
		printf("send success，send %d byte！\n\n", ret);
	}

	char buf[BUFSIZE];
	char data[SIZE];
	int bufSize;
	memset(data, 0, SIZE);
	struct timeval tv;

	fd_set t_set1;
	FD_ZERO(&t_set1);
	FD_SET(sockfd, &t_set1);

	printf("read begin！\n");
	while (1) {
		sleep(2);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		state = 0;
		state = select(sockfd + 1, &t_set1, NULL, NULL, &tv);
		if (state < 0) {
			close(sockfd);
			printf("read error!\n");
			return -1;
		};

		if (state > 0) {
			memset(buf, 0, BUFSIZE);
			bufSize = read(sockfd, buf, BUFSIZE - 1);
			if (bufSize == 0) {
				break;
			} else {
				strcat(data, buf);
			}
		}
	}
	close(sockfd);
	printf("read end！\n");

	printf("%s\n", data);

	return 0;
}

