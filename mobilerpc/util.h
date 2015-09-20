#ifndef __PLUTO_UTIL_H__
#define __PLUTO_UTIL_H__

//#include <sys/types.h>

#define MAX_EPOLL_NUM 1000

#define BUF_SIZE 1024
#define ECHO_PORT 6000

//typedef int SOCKET  //socket

#define EVENT_NONE 0x00
#define EVENT_READ 0x01
#define EVENT_WRITE 0x02

unsigned int hash_string(const char *str);

#endif  //  __PLUTO_UTIL_H__