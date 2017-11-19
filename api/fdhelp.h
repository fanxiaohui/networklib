/*
 * fdhelp.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef FDHELP_H_
#define FDHELP_H_

#include <stdio.h>
#include <unistd.h>

/*
 * FD辅助类
 * 非线程安全
 */
class FdHelp {
	struct InnerFd {
		int count;
		int fd;
	};
public:
	FdHelp();
	FdHelp(FdHelp& fdHelp);
	FdHelp& operator=(FdHelp& fdHelp);
	void updateFd(int fd);
	int& fd();

	void reset();
	void closefd();

	~FdHelp();
private:
	void newfd();
	void freefd();
	FdHelp::InnerFd* ref();
	FdHelp::InnerFd* pInnerFd;
};

#endif /* FDHELP_H_ */
