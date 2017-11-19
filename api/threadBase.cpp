/*
 * threadBase.cpp
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#include "threadBase.h"

ThreadBase::ThreadBase() {
	m_init_flag = 0;
	m_id = 0;
}

ThreadBase::~ThreadBase() {
}


void* ThreadBaseFuncApd(void * param) {
	ThreadBase * threadPtr = (ThreadBase *) param;
	threadPtr->run();
	pthread_exit(NULL);
}

void ThreadBase::start() {
	if (m_init_flag == 1) {
		return;
	}
	m_init_flag = 1;
	pthread_create(&m_id, 0, ThreadBaseFuncApd, this);
}

void ThreadBase::join() {
	if (m_init_flag == 0) {
		return;
	}
	pthread_join(m_id, NULL);
}
