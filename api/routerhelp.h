/*
 * routerhelp.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef ROUTERHELP_H_
#define ROUTERHELP_H_

#include <netdb.h>      /* for gethostbyname    */
#include <string>
#include <vector>

struct RouterInfo {
	std::string ip;
	int port;
};

class RouterHelp {
public:
	RouterHelp();
	void setTimeout(int timeout);
	void Init(const std::string& domain);
	void Init(const std::vector<RouterInfo>& routeList);
	void add(const RouterInfo& routerInfo);
	int GetRoute(std::string &ip, int &port);

	int GetRouteFromDomain(string &ip, int &port);
	int GetRouteFromIP(std::string &ip, int &port);
private:
	int timeout; //单位毫秒
	std::vector<RouterInfo> routeList;
	int routeindex;
	std::string domain;
	char m_err[1024];
};

#endif /* ROUTERHELP_H_ */
