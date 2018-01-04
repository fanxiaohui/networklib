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

string consumer_secret = "5vqFk6Hi83dAWjyv";
string oauth_token_secret = "b27b05dcda9749e4900340b4e12e0b4f";

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

	Url url;
	url.setMethod(METHOD);
	url.setScheme(SCHEME);
	url.setDomain(HOSTSTR);
	char path[] = "/1/fileops/create_folder";
	url.setPath(path);
	url.addParame(Parame("oauth_version","1.0"));
	url.addParame(Parame("oauth_token","fa361a4a1dfc4a739869020e586582f9"));
	url.addParame(Parame("oauth_signature_method","HMAC-SHA1"));
	url.addParame(Parame("oauth_nonce","58456623"));
	url.addParame(Parame("oauth_timestamp","1328881571"));
	url.addParame(Parame("oauth_consumer_key","79a7578ce6cf4a6fa27dbf30c6324df4"));
	url.addParame(Parame("path","/test@kingsoft.com"));
	url.addParame(Parame("root","kuaipan"));

	string base =base_string(url);

	cout<<base<<endl;

	string keys = consumer_secret + "&" + oauth_token_secret;

	return 0;
}

