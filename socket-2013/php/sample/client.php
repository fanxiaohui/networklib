<?php

/* client.php make by tiankonguse */
$server_ip = "127.0.0.1";
$port = 8888;
/*
 * resource socket_create ( int $domain , int $type , int $protocol ) 创建并返回一个套接字，也称作一个通讯节点。一个典型的网络连接由 2 个套接字构成，一个运行在客户端，另一个运行在服务器端。 domain 参数指定哪个协议用在当前套接字上。 Domain	描述 AF_INET	 IPv4 网络协议。TCP 和 UDP 都可使用此协议。 AF_INET6	 IPv6 网络协议。TCP 和 UDP 都可使用此协议。 AF_UNIX	 本地通讯协议。具有高性能和低成本的 IPC（进程间通讯）。 type 参数用于选择套接字使用的类型。 类型	 描述 SOCK_STREAM 提供一个顺序化的、可靠的、全双工的、基于连接的字节流。支持数据传送流量控制机制。TCP 协议即基于这种流式套接字。 SOCK_DGRAM	 提供数据报文的支持。(无连接，不可靠、固定最大长度).UDP协议即基于这种数据报文套接字。 SOCK_SEQPACKET	 提供一个顺序化的、可靠的、全双工的、面向连接的、固定最大长度的数据通信；数据端通过接收每一个数据段来读取整个数据包。 SOCK_RAW	 提供读取原始的网络协议。这种特殊的套接字可用于手工构建任意类型的协议。一般使用这个套接字来实现 ICMP 请求（例如 ping）。 SOCK_RDM	 提供一个可靠的数据层，但不保证到达顺序。一般的操作系统都未实现此功能。 protocol 参数，是设置指定 domain 套接字下的具体协议。 这个值可以使用 getprotobyname() 函数进行读取。 如果所需的协议是 TCP 或 UDP，可以直接使用常量 SOL_TCP 和 SOL_UDP 。 名称	 描述 icmp	 Internet Control Message Protocol 主要用于网关和主机报告错误的数据通信。例如“ping”命令（在目前大部分的操作系统中）就是使用 ICMP 协议实现的。 udp	 User Datagram Protocol 是一个无连接的、不可靠的、具有固定最大长度的报文协议。由于这些特性，UDP 协议拥有最小的协议开销。 tcp	 Transmission Control Protocol 是一个可靠的、基于连接的、面向数据流的全双工协议。TCP 能够保障所有的数据包是按照其发送顺序而接收的。如果任意数据包在通讯时丢失，TCP 将自动重发数据包直到目标主机应答已接收。因为可靠性和性能的原因，TCP 在数据传输层使用 8bit 字节边界。因此，TCP 应用程序必须允许传送部分报文的可能。
 */

if (isset ( $_POST ['buf'] )) {
    $sock = @socket_create ( AF_INET, SOCK_DGRAM, 0 );
    
    if (! $sock) {
        echo "socket create failure";
    }
    
    $buf = $_POST ['buf'];
    
    if(strcmp($buf, "") == 0){
        $buf = "buf is empty!";
    }
    
    if (! @socket_sendto ( $sock, $buf, strlen ( $buf ), 0, $server_ip, $port )) {
        echo "send error\n";
        socket_close ( $sock );
        exit ();
    }
    
    $buf = "";
    $msg = "";
    
    if (! @socket_recvfrom ( $sock, $msg, 256, 0, &$server_ip, &$port )) {
        
        echo "recvieve error!";
        
        socket_close ( $sock );
        
        exit ();
    }
    
    echo trim ( $msg ) . "\n";
    
    socket_close ( $sock );
}

?>
<form action="client.php" method="post">
	<input type="text" name="buf"> <input type="submit" value="submit">
</form>