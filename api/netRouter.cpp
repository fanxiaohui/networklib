/*
 * netRouter.cpp
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#include "netRouter.h"

NetRouter::NetRouter() {
	m_err[0] = 0;
	timeout = 30;
	routeindex = 0;
}

void NetRouter::setTimeout(int timeout) {
	this->timeout = 0;
}

void NetRouter::init(const std::string& domain) {
	this->domain = domain;
}

void NetRouter::init(const std::vector<RouterInfo>& routeList) {
	this->routeList = routeList;
}

void NetRouter::add(const RouterInfo& routerInfo) {
	this->routeList.push_back(routerInfo);
}

int NetRouter::get(std::string &ip, unsigned short &port) {
	if (domain.length() > 0) {
		return getFromDomain(ip, port);
	} else {
		return getFromIP(ip, port);
	}
}

/*
 *  由于域名很慢， 后续可以对域名拉到的ip进行缓存
 */
int NetRouter::getFromDomain(std::string &ip, unsigned short &port) {

	struct hostent *ent = NULL;
	static char str[32];
	ent = gethostbyname(domain.c_str());
	if (NULL == ent) {
		return -__LINE__;
	}
	ip = inet_ntop(ent->h_addrtype, ent->h_addr, str, sizeof(str) );
	port = 80;
	return 0;
}

int NetRouter::getFromIP(std::string &ip, unsigned short &port) {
	if (routeList.size() == 0) {
		snprintf(m_err, sizeof(m_err), "empty routeList!");
		return __LINE__;
	}
	if (routeindex >= (int) routeList.size()) {
		routeindex = 0;
	}

	RouterInfo& routerInfo = routeList[routeindex];
	ip = routerInfo.ip;
	port = routerInfo.port;
	m_err[0] = 0;
	return 0;
}

/*
 * 分布式路由，同一个key进来路由到同一个ip
 */
int getByKey(std::string &ip, unsigned short &port, int key) {
	return 0;
}

/*
 * 分布式路由，同一个key进来路由到同一个ip
 */
int getByKey(std::string &ip, unsigned short &port, std::string key) {
	return 0;
}

/*
 * 上报主要用于负载均衡和容灾
 * 某个ip不可用，应该快速剔除对应的ip
 */
void NetRouter::report(const std::string &ip, unsigned short port, int result,
		int cost) {

}
