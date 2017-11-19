/*
 * routerhelp.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef ROUTERHELP_H_
#define ROUTERHELP_H_

#include <netdb.h>      /* for gethostbyname    */
#include <arpa/inet.h>  /* for inet_ntop  */
#include <string>
#include <vector>

/*
 * 路由方式， 目前支持两种
 * 保留
 */
enum RouterType {
	ROUTER_TYPE_IP = 0, //
	ROUTER_TYPE_DOMAIN = 1,
};

/*
 * 面向业务的一个节点
 * weight保留，因为不同的ip:port可能性能不同，为后续扩展使用
 */
struct RouterInfo {
	std::string ip;
	int port;
	int weight;
};

/*
 * 路由算法
 * 后续可以升级为负载均衡算法
 */
class NetRouter {
public:
	NetRouter();
	void setTimeout(int timeout);
	void init(const std::string& domain);
	void init(const std::vector<RouterInfo>& routeList);

	/*
	 * 给业务一个接口，可以手动的添加ip
	 */
	void add(const RouterInfo& routerInfo);

	/*
	 * 默认算法随机得到一个ip
	 */
	int get(std::string &ip, int &port);

	/*
	 * 分布式路由，同一个key进来路由到同一个ip
	 */
	int getByKey(std::string &ip, int &port, int key);

	/*
	 * 分布式路由，同一个key进来路由到同一个ip
	 */
	int getByKey(std::string &ip, int &port, std::string key);

	/*
	 * 根据域名得到ip
	 */
	int getFromDomain(std::string &ip, int &port);
	int getFromIP(std::string &ip, int &port);

	/*
	 * 给业务一个主动上报的方式
	 * 因为业务是最了解对方是否可用的。
	 */
	void report(const std::string &ip, unsigned short port, int result, int cost);
private:
	int timeout; //单位毫秒
	std::vector<RouterInfo> routeList;
	int routeindex;
	std::string domain;
	char m_err[1024];
};

#endif /* ROUTERHELP_H_ */
