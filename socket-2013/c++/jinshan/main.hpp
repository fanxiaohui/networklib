int getIP(const char* hostStr, char* ipStr) {
	int state = getIpByHome(hostStr, ipStr);
	if (state != 0) {
		return 1;
	}
	return 0;
}

int connect(char*ipStr, int PORT) {
	struct sockaddr_in servaddr;

	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	};

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, ipStr, &servaddr.sin_addr) <= 0) {
		//convert addresses to binary failed!
		return -2;
	};

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		//connect to server failed!
		return -3;
	}
	return sockfd;
}


