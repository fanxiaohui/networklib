/*
 * threadBase.h
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#ifndef THREADBASE_H_
#define THREADBASE_H_

#include <pthread.h>

/*
 * 线程的回调函数
 * 子类需要实现run函数，回调函数主要实现调用run函数
 * 业务的run函数应该是个死循环
 */
typedef void (*ThreadBaseFuncType)(void *);

class ThreadBase {
public:
	ThreadBase();
	virtual ~ThreadBase();
	virtual void run() = 0;
	void start();
	void join();
protected:
private:
	pthread_t m_id;
	int m_init_flag;
};

#endif /* THREADBASE_H_ */
