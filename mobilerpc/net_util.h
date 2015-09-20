
#ifndef __PLUTO_NET_UTIL_H__
#define __PLUTO_NET_UTIL_H__

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace pluto
{
	extern int netlib_setnonblocking(int sockfd);
	extern int netlib_socket();
	extern int netlib_bind(int sockfd, uint16_t port);
	extern int netlib_listen(int sockfd, int backlog);
	extern int netlib_connect(const char* server_ip, uint16_t port);
	
};


#endif  //  __PLUTO_NET_UTIL_H__
