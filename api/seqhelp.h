/*
 * seqhelp.h
 *
 *  Created on: 2017年11月19日
 *      Author: skyyuan
 */

#ifndef SEQHELP_H_
#define SEQHELP_H_

class SeqGenerator {
public:
	SeqGenerator() {
		fd_rand = -1;
	}

	~SeqGenerator() {
		if (fd_rand != -1) {
			close(fd_rand);
			fd_rand = -1;
		}
	}

	uint64_t GetSeq() {
		struct timeval tv;
		uint64_t ticks = 0;
		uint64_t r = 0;

		gettimeofday(&tv, NULL);
		ticks = tv.tv_sec * 1000000 + tv.tv_usec;
		//只打开一次
		if (fd_rand == -1) {
			fd_rand = open("/dev/urandom", O_RDONLY);
		}

		if (fd_rand > 0) {
			read(fd_rand, &r, sizeof(r));
		}

		return ((ticks + r) & 0xFFFFFFFF);
	}

private:
	int fd_rand;
};

#endif /* SEQHELP_H_ */
