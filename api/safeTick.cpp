/*
 * safeTick.cpp
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#include "safeTick.h"

SafeTick::SafeTick() {
	tick = 0;
	pthread_mutex_init(&m_lock, NULL);
}
SafeTick::~SafeTick() {
	pthread_mutex_destroy(&m_lock);
}
int SafeTick::done() {
	LockHelp l(&m_lock);
	return this->tick;
}
int SafeTick::update() {
	LockHelp l(&m_lock);
	this->tick++;
	return this->tick;
}
