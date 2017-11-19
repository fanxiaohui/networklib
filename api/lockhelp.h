/*
 * lockhelp.h
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#ifndef LOCKHELP_H_
#define LOCKHELP_H_

#include <pthread.h>

/*
 * 后续可以对 pthread_mutex_t 进行封装，然后可以简单的防止double lock
 */
struct LockHelp {
	LockHelp(pthread_mutex_t* plock);

	/*
	 * 添加主动操作的接口， 有时候需要提前释放锁
	 */
	int lock(pthread_mutex_t* plock);
	int unlock();
	~LockHelp();
private:
	pthread_mutex_t* plock;
};

#endif /* LOCKHELP_H_ */
