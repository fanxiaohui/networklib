/*
 * fdhelp.cpp
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#include "fdhelp.h"

FdHelp::FdHelp() {
	newfd();
}
FdHelp::FdHelp(FdHelp& fdHelp) {
	pInnerFd = fdHelp.ref();
}
FdHelp::InnerFd* FdHelp::ref() {
	return this->pInnerFd;
}
FdHelp::~FdHelp() {
	freefd();
}

FdHelp& FdHelp::operator=(FdHelp& fdHelp) {
	//同一个类
	if (&fdHelp == this) {
		return *this;
	}

	//同一个fd引用
	if (fdHelp.ref() == pInnerFd) {
		return *this;
	}

	if (pInnerFd != NULL) {
		freefd();
	}
	pInnerFd = fdHelp.ref();
	return *this;
}
void FdHelp::updateFd(int fd) {
	pInnerFd->fd = fd;
}
int& FdHelp::fd() {
	return pInnerFd->fd;
}

void FdHelp::reset() {
	if (pInnerFd->count > 1) {
		freefd();
		newfd();
	} else {
		closefd();
	}
}
void FdHelp::closefd() {
	if (pInnerFd->fd > 0) {
		::close(pInnerFd->fd);
		pInnerFd->fd = 0;
	}
}
void FdHelp::newfd() {
	pInnerFd = new InnerFd;
	pInnerFd->count = 1;
	pInnerFd->fd = 0;
}
void FdHelp::freefd() {
	pInnerFd->count--;
	if (0 == pInnerFd->count) {
		closefd();
		delete pInnerFd;
	}
	pInnerFd = NULL;
}
