/*
 * lockhelp.cpp
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#include "lockhelp.h"

LockHelp::LockHelp(pthread_mutex_t* plock) {
	this->plock = NULL;
	lock(plock);
}
LockHelp::~LockHelp() {
	unlock();
}

int LockHelp::lock(pthread_mutex_t* plock) {
	if (this->plock == NULL) {
		this->plock = plock;
		pthread_mutex_lock(this->plock);
		return 0;
	} else {
		return 1;
	}
}

int LockHelp::unlock() {
	if(this->plock == NULL){
		return 1;
	}else{
		pthread_mutex_unlock(this->plock);
		this->plock = NULL;
		return 0;
	}
}
