/*
 * basehelp.h
 *
 *  Created on: 2017年11月18日
 *      Author: skyyuan
 */

#ifndef BASEHELP_H_
#define BASEHELP_H_

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "atomic.h"
#include <time.h>
#include <signal.h>

namespace BASE_TOOLS {

    // if ifstr == NULL; use eth1(inner network)
    // if ifstr == "all"; use 0.0.0.0
    // else query the interface IP using ifstr
    unsigned getip(const char* ifstr = NULL) {
        char ifname[16] = { 0 };
        if (!ifstr)
        {
            strncpy(ifname, "eth1", sizeof(ifname) - 1);
        }
        else if (0 == strncmp(ifname, "all", sizeof(ifname)))
        {
            return 0U; // all interface = IP 0.0.0.0
        }
        else
        {
            strncpy(ifname, ifstr, sizeof(ifname) - 1);
        }

        register int fd, intrface;
        struct ifreq buf[10];
        struct ifconf ifc;
        unsigned ip = 0;

        if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
        {
            ifc.ifc_len = sizeof(buf);
            ifc.ifc_buf = (caddr_t)buf;

            if (!ioctl(fd, SIOCGIFCONF, (char*)&ifc))
            {
                intrface = ifc.ifc_len / sizeof(struct ifreq);

                while (intrface-- > 0)
                {
                    if (strcmp(buf[intrface].ifr_name, ifname) == 0)
                    {
                        if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))
                            ip = (unsigned)((struct sockaddr_in *)(&buf[intrface].ifr_addr))->sin_addr.s_addr;

                        break;
                    }
                }
            }

            close(fd);
        }

        return ip;
    }

}


int check_process_exist(pid_t pid)
{
    int ret = kill(pid, 0);

    if (ret == 0 || errno != ESRCH)
    {
        // 存在
        return 1;
    }

    // 不存在
    return 0;
}

#endif /* BASEHELP_H_ */
