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

static const char * HOSTSTR = "openapi.kuaipan.cn";
const char * METHOD = "GET";
const char * SCHEME = "http";

const int BUFSIZE = 1024;
const int SIZE = BUFSIZE * BUFSIZE;
const int PORT = 80;

#include "../sample/hostToIp.hpp"
#include "../http.hpp"
#include "main.hpp"
#include "../urlencode.hpp"
#include "../parame.hpp"
#include "../base_string.hpp"
/*
consumer_key xcjpi1bDpitGfwEE
consumer_secret 5vqFk6Hi83dAWjyv
*/

/*
1.requestToken
在这个网址自动生成 http://www.kuaipan.cn/developers/createsign.htm?doit=1
{
"oauth_token_secret":"b27b05dcda9749e4900340b4e12e0b4f",
"oauth_token":"796a9c6ee9bd4cd684981854d56f55ae",
"expires_in":1800,
"oauth_callback_confirmed":false}
*/

/*
2.authorize
授权码：597988772
*/

/*
3.accessToken
{
"oauth_token_secret":"b98de1094a134a9c991e88650d860c3d",
"oauth_token":"029744400e4a512fad0a69b0",
"charged_dir":"186692951227760645",
"user_id":43467840,
"expires_in":31536000
}
*/

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

	Url url;
	url.setMethod(METHOD);
	url.setScheme(SCHEME);
	url.setDomain(HOSTSTR);
	char path[] = "/1/account_info/";
	url.setPath(path);
	url.addParame(Parame("oauth_version","1.0"));
	url.addParame(Parame("oauth_token","fa361a4a1dfc4a739869020e586582f9"));
	url.addParame(Parame("oauth_signature_method","HMAC-SHA1"));
	url.addParame(Parame("oauth_nonce","58456623"));
	url.addParame(Parame("oauth_timestamp","1328881571"));
	url.addParame(Parame("oauth_consumer_key","79a7578ce6cf4a6fa27dbf30c6324df4"));
	url.addParame(Parame("path","/test@kingsoft.com"));
	url.addParame(Parame("root","kuaipan"));

	cout<<base_string(url)<<endl;

	return 0;

	char postUrl[] = "oauth_signature=SPdOpmUW8fzuBmKc4XGd2ikNHOE%3D&oauth_consumer_key=xcjpi1bDpitGfwEE&oauth_nonce=21GTaQzZ&oauth_signature_method=HMAC-SHA1&oauth_timestamp=1382426656&oauth_token=029744400e4a512fad0a69b0&oauth_version=1.0";
	printf("%s\n",postUrl);



	httpGet(sockfd, HOSTSTR, postUrl);

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

