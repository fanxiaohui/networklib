/*server.c*/
/*
 * gcc -o server server.c 生成server程序
 * 在服务器端运行./server
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
 *  function inet_addr
 *  The inet_addr() function converts the Internet  host  address  cp  from IPv4  numbers-and-dots notation into binary data in network byte order.
 *  If the input is invalid, INADDR_NONE (usually -1) is returned.
 *  Use  of this   function   is   problematic   because  -1  is  a  valid  address (255.255.255.255).
 *  Avoid   its   use   in   favor   of   inet_aton(), inet_pton(3), or getaddrinfo(3) which provide a cleaner way to indicate error return.
 *
 *
 *	 inet_pton - convert IPv4 and IPv6 addresses from text to binary form
 *
 *  function htons
 *  The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
 *
 *	function socket
 *	socket - create an endpoint for communication
 *	socket()  creates  an endpoint for communication and returns a descrip‐tor.
 *
 *	#include <sys/types.h>          //See NOTES
 *	#include <sys/socket.h>
 *	int socket(int domain, int type, int protocol);
 *
 *  Name                Purpose                          Man page
 *  AF_UNIX, AF_LOCAL   Local communication              unix(7)
 *  AF_INET             IPv4 Internet protocols          ip(7)
 *  AF_INET6            IPv6 Internet protocols          ipv6(7)
 *  AF_IPX              IPX - Novell protocols
 *  AF_NETLINK          Kernel user interface device     netlink(7)
 *  AF_X25              ITU-T X.25 / ISO-8208 protocol   x25(7)
 *  AF_AX25             Amateur radio AX.25 protocol
 *  AF_ATMPVC           Access to raw ATM PVCs
 *  AF_APPLETALK        Appletalk                        ddp(7)
 *  AF_PACKET           Low level packet interface       packet(7)
 *
 *  The  socket  has  the indicated type, which specifies the communication semantics.
 *  Currently defined types are:
 *
 *	SOCK_STREAM
 *		Provides sequenced, reliable, two-way, connection-based byte  streams.
 *		An out-of-band data transmission mecha‐nism may be supported.
 *
 *	SOCK_DGRAM
 *		Supports datagrams (connectionless, unreliable messages of a fixed maximum length).
 *
 *	SOCK_SEQPACKET
 *		Provides  a  sequenced,  reliable,  two-way connection-based data transmission path  for  datagrams  of  fixed maximum  length;
 *		a  consumer  is  required  to read an entire packet with each input system call.
 *
 *	SOCK_RAW
 *		Provides raw network protocol access.
 *
 *	SOCK_RDM
 *		Provides a reliable datagram layer that does not  guar‐antee ordering.
 *
 *	SOCK_PACKET
 *		Obsolete  and  should  not be used in new programs; see packet(7).
 *
 *	Since Linux 2.6.27, the type argument serves a second purpose:
 *		in addi‐tion to specifying a socket type, it may include the bitwise OR of any of the following values, to modify the behavior of socket():
 *		SOCK_NONBLOCK
 *			Set  the  O_NONBLOCK  file  status flag on the new open file description.
 *			Using this flag saves extra calls to fcntl(2) to achieve the same result.
 *
 *		SOCK_CLOEXEC
 *			Set the close-on-exec (FD_CLOEXEC) flag on the new file descriptor.
 *			See the description of the O_CLOEXEC  flag in open(2) for reasons why this may be useful.
 *
 *	The  protocol  specifies  a  particular  protocol  to  be used with the socket.
 *	Normally only a single protocol exists to support a particular socket  type within a given protocol family, in which case protocol can be specified as 0.
 *	However, it is possible  that  many  protocols  may exist,  in  which  case a particular protocol must be specified in this manner.
 *	The protocol number to use is specific to  the  “communication domain” in which communication is to take place;
 *	see protocols(5).
 *	See getprotoent(3) on how to map protocol name strings to protocol numbers.
 *
 *
 *	function bind
 *	bind - bind a name to a socket
 *	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 *	When  a  socket  is  created  with socket(2), it exists in a name space (address family) but has no address assigned to it.
 *	bind() assigns the address  specified  to  by  addr  to the socket referred to by the file descriptor sockfd.
 *	addrlen  specifies  the  size,  in  bytes,  of  the address structure pointed to by addr.
 *	Traditionally, this operation is called “assigning a name to a socket”.
 *
 *
 *	function recvfrom
 *	ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
 *	The  recvfrom() and recvmsg() calls are used to receive messages from a socket,
 *	and may be used to receive data on a socket whether or  not  it is connection-oriented.
 *
 *	If  src_addr  is  not  NULL,  and  the underlying protocol provides the source address, this source address is filled  in.
 *	When  src_addr  is NULL,  nothing  is  filled  in;
 *	in this case, addrlen is not used, and should also be NULL.
 *	The argument addrlen is a value-result  argument, which  the  caller should initialize before the call to the size of the
       buffer associated with src_addr, and modified on return to indicate the
       actual  size  of the source address.  The returned address is truncated
       if the buffer provided is too small; in this case, addrlen will  return
       a value greater than was supplied to the call.
 *
 *
 *	The domain argument specifies a communication domain;
 *	this selects  the protocol  family  which will be used for communication.
 *	These families are  defined  in  <sys/socket.h>.
 *	 The  currently  understood  formats include:
 *
 *	Perl Programmers Reference Guide
 *  use Socket;
 *
 *	$proto = getprotobyname('udp');
 *	socket(Socket_Handle, PF_INET, SOCK_DGRAM, $proto);
 *	$iaddr = gethostbyname('hishost.com');
 *	$port = getservbyname('time', 'udp');
 *	$sin = sockaddr_in($port, $iaddr);
 *	send(Socket_Handle, 0, 0, $sin);
 *
 *	$proto = getprotobyname('tcp');
 *	socket(Socket_Handle, PF_INET, SOCK_STREAM, $proto);
 *	$port = getservbyname('smtp', 'tcp');
 *	$sin = sockaddr_in($port,inet_aton("127.1"));
 *	$sin = sockaddr_in(7,inet_aton("localhost"));
 *	$sin = sockaddr_in(7,INADDR_LOOPBACK);
 *	connect(Socket_Handle,$sin);
 *
 *	($port, $iaddr) = sockaddr_in(getpeername(Socket_Handle));
 *	$peer_host = gethostbyaddr($iaddr, AF_INET);
 *	$peer_addr = inet_ntoa($iaddr);
 *
 *
 *  $proto = getprotobyname('tcp');
 *  socket(Socket_Handle, PF_UNIX, SOCK_STREAM, $proto);
 *  unlink('/var/run/usock');
 *  $sun = sockaddr_un('/var/run/usock');
 *  connect(Socket_Handle,$sun);
 *
 */

int main() {
	int sock;
	struct sockaddr_in server, client;
	int recvd, snd;
	int structlength;
	char * server_ip = "127.0.0.1";/*server ip address*/
	int port = 8888;
	char recvbuf[2000], sendbuf[2000];

	char str1[] = "I have received:\n";

	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_port = htons(port);

	memset((char *) &client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	client.sin_port = htons(port);

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("socket create error!\n");
		exit(1);
	}

	structlength = sizeof(server);
	if (bind(sock, (struct sockaddr *) &server, structlength) < 0) {
		printf("socket bind error!\n");
		perror("bind");
		exit(1);
	}

	while (1) {
		structlength = sizeof(client);

		printf("waiting.......\n");
		recvd = recvfrom(sock, recvbuf, sizeof(recvbuf), 0,
				(struct sockaddr *) &client, &structlength);
		if (recvd < 0) {
			perror("recvfrom");
			exit(EXIT_FAILURE);
		} else {
			printf("received:%s\n", recvbuf);

			memset(sendbuf, 0, strlen(sendbuf));
			memcpy(sendbuf, str1, strlen(str1));

			snd = sendto(sock, sendbuf, strlen(str1), 0,
					(struct sockaddr *) &client, structlength);

			if (snd < 0) {
				perror("sendto");
				exit(1);
			}
			printf("sendok!\n");

		}

	}

	close(sock);
	return 0;
}
