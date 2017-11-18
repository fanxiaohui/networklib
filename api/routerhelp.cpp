/*
 * routerhelp.cpp
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#include "routerhelp.h"

RouterHelp::RouterHelp() {
	m_err[0] = 0;
	timeout = 30;
	routeindex = 0;
}

void RouterHelp::setTimeout(int timeout) {
	this->timeout = 0;
}

void RouterHelp::Init(const std::string& domain) {
	this->domain = domain;
}

void RouterHelp::Init(const std::vector<RouterInfo>& routeList) {
	this->routeList = routeList;
}

void RouterHelp::add(const RouterInfo& routerInfo) {
	this->routeList.push_back(routerInfo);
}

int RouterHelp::GetRoute(std::string &ip, int &port) {
	if (domain.length() > 0) {
		return GetRouteFromDomain(ip, port);
	} else {
		return GetRouteFromIP(ip, port);
	}
}

int RouterHelp::GetRouteFromDomain(string &ip, int &port) {
	struct hostent *ent = NULL;
	static char str[32];
	ent = gethostbyname(host);
	if (NULL == ent) {
		return -__LINE__;
	}
	ip = inet_ntop(ent->h_addrtype, ent->h_addr, str, sizeof(str) );
	port = 80;
	return 0;
}

int RouterHelp::GetRouteFromIP(std::string &ip, int &port) {
	if (routeList.size() == 0) {
		snprintf(m_err, sizeof(m_err), "empty routeList!");
		return __LINE__;
	}
	if (routeindex >= routeList.size()) {
		routeindex = 0;
	}

	RouterInfo& routerInfo = routeList[routeindex];
	ip = routerInfo.ip;
	port = routerInfo.port;
	m_err[0] = 0;
	return 0;
}
