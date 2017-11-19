/*
 * netConnectPool.cpp
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#include "netConnectPool.h"

NetConnectPool::NetConnectPool() {
	pthread_mutex_init(&m_mutex, NULL);
}
NetConnectPool::~NetConnectPool() {
	LockHelp l(&m_mutex);
	std::map<std::string, NetConnect*>::iterator it = m_vconnmap.begin();
	for (; it != m_vconnmap.end(); it++) {
		if (it->second != NULL) {
			delete it->second;
		}
	}
	l.unlock();
	pthread_mutex_destroy(&m_mutex);
}

NetConnect* NetConnectPool::getConnection(const std::string &ip, int port,
		NetProtoType proto, int timeout) {
	std::string key = getKey(ip, port, proto);
	LockHelp l(&m_mutex);
	std::map<std::string, NetConnect*>::iterator it = m_vconnmap.find(key);
	l.unlock();
	if (it != m_vconnmap.end()) {
		return it->second;
	}

	NetConnect *vconn = new NetConnect(ip, port, proto, timeout);
	if (vconn == NULL) {
		return NULL;
	}

	l.lock(&m_mutex);
	m_vconnmap.insert(std::make_pair<std::string, NetConnect*>(key, vconn));
	l.unlock();

	return vconn;
}
void NetConnectPool::removeConnection(const std::string &ip, int port,
		NetProtoType proto) {
	LockHelp l(&m_mutex);
	std::map<std::string, NetConnect*>::iterator it = m_vconnmap.find(
			getKey(ip, port, proto));
	if (it != m_vconnmap.end()) {
		if (it->second != NULL) {
			delete it->second;
		}
		m_vconnmap.erase(it);
	}
	l.unlock();

	return;
}

std::string NetConnectPool::getKey(const std::string &ip, int port,
		NetProtoType proto) {
	char key[128];
	snprintf(key, sizeof(key), "%lu_%s_%u_%d", pthread_self(), ip.c_str(), port,
			proto);
	return key;
}

