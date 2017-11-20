#pragma once

#include <sys/time.h> /* for gettimeofday */

class TimeHelp {
public:
	void start() {
		gettimeofday(&m_start, NULL);
	}
	void end() {
		gettimeofday(&m_end, NULL);
	}
	long long cost() {
		return (m_end.tv_sec - m_start.tv_sec) * 1000000 + m_end.tv_usec
			- m_start.tv_usec;
	}
private:
	struct timeval m_start;
	struct timeval m_end;
};
