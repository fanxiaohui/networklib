/*
 * parame.hpp
 *
 *  Created on: 2013-10-25
 *      Author: tiankonguse
 */

#include <string>
using namespace std;

#ifndef PARAME_HPP_
#define PARAME_HPP_

class Parame{
	string name;
	string val;
public:

	Parame(){}
	Parame(const string name, const string val):name(name),val(val){

	}
	bool operator<(const Parame o)const{
		return this->name < o.getName();
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	const string& getVal() const {
		return val;
	}

	void setVal(const string& val) {
		this->val = val;
	}
};

class Url{
public:
	const string& getDomain() const {
		return domain;
	}

	void setDomain(const string&domain) {
		this->domain = domain;
	}

	const string& getMethod() const {
		return method;
	}

	void setMethod(const string method) {
		this->method = method;
	}

	const vector<Parame>& getParames() const {
		return parames;
	}

	void setParames(const vector<Parame>& parames) {
		this->parames = parames;
	}

	void addParame(Parame parame){
		this->parames.push_back(parame);
	}

	void sortParames(){
		sort(this->parames.begin(), this->parames.end());
	}

	const string& getPath() const {
		return path;
	}

	void setPath(const string path) {
		this->path = path;
	}

	const string& getPort() const {
		return port;
	}

	void setPort(const string port) {
		this->port = port;
	}

	const string& getScheme() const {
		return scheme;
	}

	void setScheme(const string scheme) {
		this->scheme = scheme;
	}

	string getBaseUri(){
		return this->getScheme() + "://" + this->getDomain() + this->getPath();
	}
	vector<Parame>parames;

private:
	string method;// GET or POST
	string scheme;
	string domain;
	string port;//不需要端口
	string path;

};



#endif /* PARAME_HPP_ */
