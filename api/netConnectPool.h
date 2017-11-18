/*
 * netConnectPool.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef NETCONNECTPOOL_H_
#define NETCONNECTPOOL_H_

#include "netConnect.h"

class NetConnectPool {
public:
	NetConnectPool() {
		pthread_mutex_init(&m_mutex, NULL);
	}
	~NetConnectPool() {
		pthread_mutex_lock(&m_mutex);
		map<string, VConnection*>::iterator it = m_vconnmap.begin();
		for (; it != m_vconnmap.end(); it++) {
			if (it->second != NULL) {
				delete it->second;
			}
		}
		pthread_mutex_unlock(&m_mutex);
		pthread_mutex_destroy(&m_mutex);
	}

	NetConnect* GetConnection(const string &ip, int port, NetProto proto,
			int timeout) {
		string key = GetKey(ip, port, proto);
		pthread_mutex_lock(&m_mutex);
		map<string, VConnection*>::iterator it = m_vconnmap.find(key);
		pthread_mutex_unlock(&m_mutex);
		if (it != m_vconnmap.end()) {
			return it->second;
		}

		VConnection *vconn = new VConnection(ip, port, proto, timeout);
		if (vconn == NULL) {
			return NULL;
		}

		pthread_mutex_lock(&m_mutex);
		m_vconnmap.insert(make_pair<string, VConnection*>(key, vconn));
		pthread_mutex_unlock(&m_mutex);

		return vconn;
	}
	void RemoveConnection(const string &ip, int port, NetProto proto) {
		pthread_mutex_lock(&m_mutex);
		map<string, VConnection*>::iterator it = m_vconnmap.find(
				GetKey(ip, port, proto));
		if (it != m_vconnmap.end()) {
			if (it->second != NULL) {
				delete it->second;
			}
			m_vconnmap.erase(it);
		}
		pthread_mutex_unlock(&m_mutex);

		return;
	}

private:
	string GetKey(const string &ip, int port, NetProto proto) {
		char key[128];
		snprintf(key, sizeof(key), "%lu_%s_%u_%d", pthread_self(), ip.c_str(),
				port, proto);
		return key;
	}

	map<string, NetConnect*> m_vconnmap;
	pthread_mutex_t m_mutex;
};

#endif /* NETCONNECTPOOL_H_ */
