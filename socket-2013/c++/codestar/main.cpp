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

static const char * HOSTSTR = "codestar.alloyteam.com";
const int BUFSIZE = 1024;
const int SIZE = BUFSIZE * BUFSIZE;
const int PORT = 80;

#include "../sample/hostToIp.hpp"
#include "../jinshan/main.hpp"

int main(int argc, char **argv) {
	char ipStr[INET_ADDRSTRLEN];

	int state = getIP(HOSTSTR, ipStr);
	if (state != 0) {
		printf("get ip failed!\n");
		exit(1);
	}

	int sockfd = connect(ipStr, PORT);
	if (sockfd <= 0) {
		printf("connect failed!\n");
		exit(1);
	}

	printf("connect to server  sucess\n");

	time_t timep;
	time(&timep);

	char postUrl[] = "/signup";
	printf("%s\n",postUrl);
	char postData[] = "{\"name\":\"tiankonguse\",\"email\":\"i@tiankonguse.com\",\"timestamp\":\"\"}";
	httpPost(sockfd, HOSTSTR, postUrl, postData);

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
		printf("select\n");
		state = select(sockfd + 1, &t_set1, NULL, NULL, &tv);
		printf("%d\n",state);
		if (state <0) {
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
		}else{
			break;
		}
	}
	close(sockfd);
	printf("read end！\n");

	printf("%s\n", data);

	return 0;
}

