/*
 * safeQueue.h
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#ifndef SAFEQUEUE_H_
#define SAFEQUEUE_H_

#include <queue>
#include "lockhelp.h"



/*
 * 线程安全的队列
 */
template<typename Task>
struct SafeQueue {
	SafeQueue() {
		pthread_mutex_init(&m_lock, NULL);
	}
	~SafeQueue() {
		pthread_mutex_destroy(&m_lock);
	}
	bool get(Task& task) {
		LockHelp l(&m_lock);
		bool _empty = false;
		_empty = que.empty();
		if (!_empty) {
			task = que.front();
			que.pop();
		}
		return _empty;
	}
	void push(Task& task) {
		LockHelp l(&m_lock);
		que.push(task);
	}
	int size() {
		LockHelp l(&m_lock);
		int len = 0;
		len = que.size();
		return len;
	}

private:
	std::queue<Task> que;
	pthread_mutex_t m_lock;
};

#endif /* SAFEQUEUE_H_ */
