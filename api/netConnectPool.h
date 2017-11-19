/*
 * netConnectPool.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef NETCONNECTPOOL_H_
#define NETCONNECTPOOL_H_

#include <map>
#include "netConnect.h"

class NetConnectPool {
public:
	NetConnectPool();
	~NetConnectPool();

	NetConnect* getConnection(const std::string &ip, int port,
			NetProtoType proto, int timeout);
	void removeConnection(const std::string &ip, int port, NetProtoType proto);

private:
	std::string getKey(const std::string &ip, int port, NetProtoType proto);
	std::map<std::string, NetConnect*> m_vconnmap;
	pthread_mutex_t m_mutex;
};

#endif /* NETCONNECTPOOL_H_ */
