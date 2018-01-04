
int httpGet(int sockfd, const char* host, const char* url) {
	//发送数据

	char postData[SIZE];
	socklen_t postDataLen;
	char postDataLenStr[SIZE];

	memset(postData, 0, SIZE);
	strcat(postData, "");
	postDataLen = strlen(postData);
	sprintf(postDataLenStr, "%d", postDataLen);

	char requestHeader[SIZE];
	memset(requestHeader, 0, SIZE);

	strcat(requestHeader, "GET ");
	strcat(requestHeader, url);
	strcat(requestHeader, " HTTP/1.1\n");

	strcat(requestHeader, "Host: ");
	strcat(requestHeader, host);
	strcat(requestHeader, "\n");

	strcat(requestHeader, "Connection: keep-alive\n");
	strcat(requestHeader,
			"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n");
	strcat(requestHeader,
			"User-Agent: Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/28.0.1500.71 Chrome/28.0.1500.71 Safari/537.36\n");
	strcat(requestHeader, "Accept-Encoding: gzip,deflate,sdch\n");
	strcat(requestHeader, "Accept-Language: zh-CN,zh;q=0.8,en;q=0.6,gl;q=0.4,it;q=0.2,ro;q=0.2,zh-TW;q=0.2\n");
	strcat(requestHeader, "\r\n\r\n");

	int ret = write(sockfd, requestHeader, strlen(requestHeader));
	if (ret < 0) {
		return -1;
	}
	return ret;
}

int httpPost(int sockfd, const char* host, const char* url, const char* data) {
	//发送数据

	char postData[SIZE];
	socklen_t postDataLen;
	char postDataLenStr[SIZE];

	memset(postData, 0, SIZE);
	strcat(postData, "");
	postDataLen = strlen(postData);
	sprintf(postDataLenStr, "%d", postDataLen);

	char requestHeader[SIZE];
	memset(requestHeader, 0, SIZE);

	strcat(requestHeader, "POST ");
	strcat(requestHeader, url);
	strcat(requestHeader, " HTTP/1.1\n");

	strcat(requestHeader, "Host: ");
	strcat(requestHeader, host);
	strcat(requestHeader, "\n");

	strcat(requestHeader, "Connection: keep-alive\n");
	strcat(requestHeader,
			"Content-Type: application/x-www-form-urlencoded; charset=UTF-8\n");
	strcat(requestHeader, "http://codestar.alloyteam.com\n");
	strcat(requestHeader, "X-Requested-With: XMLHttpRequest\n");
	strcat(requestHeader, "Referer: http://codestar.alloyteam.com/1/1\n");
	strcat(requestHeader, "Cookie: connect.sid=s%3AOo4r576YPzT3NxRbh5PV2n4v.4AbO3RiqOUMLxjgfmeNoKGgovqpILV%2BmwccoxI2rGeY0oCDfzHFS57R64ZLDGrWyAFO9WsNjve20kwllba%2FDWg; pgv_pvi=4690461696; pgv_si=s1994801152");

	strcat(requestHeader, "Content-Length: ");
	strcat(requestHeader, postDataLenStr);
	strcat(requestHeader, "\n\n");

	strcat(requestHeader, postData);
	strcat(requestHeader, "\r\n\r\n");

	int ret = write(sockfd, requestHeader, strlen(requestHeader));
	if (ret < 0) {
		return -1;
	}
	return ret;
}
