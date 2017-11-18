/*
 * fdhelp.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef FDHELP_H_
#define FDHELP_H_

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
	friend FdHelp;

	FdHelp() {
		newfd();
	}
	FdHelp(const FdHelp& fdHelp) {
		pInnerFd = fdHelp.ref();
	}
	FdHelp& operator=(const FdHelp& fdHelp) {
		//同一个类
		if (&fdHelp == this) {
			return *this;
		}

		//同一个fd引用
		if (fdHelp->ref() == pInnerFd) {
			return *this;
		}

		if (pInnerFd != NULL) {
			freefd();
		}
		pInnerFd = fdHelp->ref();
		return *this;
	}
	void updateFd(int fd) {
		pInnerFd->fd = fd;
	}
	int& fd() {
		return pInnerFd->fd;
	}

	void reset() {
		if (pInnerFd->count > 1) {
			freefd();
			newfd();
		} else {
			closefd();
		}
	}
	void closefd() {
		if (pInnerFd->fd > 0) {
			close(pInnerFd->fd);
			pInnerFd->fd = 0;
		}
	}

	~FdHelp() {
		freefd();
	}
private:
	void newfd() {
		pInnerFd = new InnerFd;
		pInnerFd->count = 1;
		pInnerFd->fd = 0;
	}
	void freefd() {
		pInnerFd->count--;
		if (0 == pInnerFd->count) {
			closefd();
			delete pInnerFd;
		}
		pInnerFd = NULL;
	}
	InnerFd* ref() {
		return this->pInnerFd;
	}
	InnerFd* pInnerFd;
};

#endif /* FDHELP_H_ */
