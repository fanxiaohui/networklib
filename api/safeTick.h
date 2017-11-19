/*
 * safeTick.h
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#ifndef SAFETICK_H_
#define SAFETICK_H_

#include <queue>
#include "lockhelp.h"

/*
 * 线程安全的计数器
 */
struct SafeTick {
	SafeTick();
	~SafeTick();
	int done();
	int update();
private:
	int tick;
	pthread_mutex_t m_lock;
};

#endif /* SAFETICK_H_ */
