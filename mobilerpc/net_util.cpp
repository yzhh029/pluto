#include <string.h>
#include "net_util.h"

namespace pluto
{
	int netlib_setnonblocking(int sockfd)
	{
		return fcntl( sockfd, F_SETFL, fcntl( sockfd, F_GETFD, 0 )|O_NONBLOCK );
	}

	int netlib_socket()
	{
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			return -1;
		}

		if (netlib_setnonblocking(sockfd) < 0)
		{
			return -1;
		}
		return sockfd;
	}

	int netlib_bind(int sockfd, uint16_t port)
	{
		struct sockaddr_in addr;
		//memset(&addr, 0, sizeof(addr));
		bzero(&addr,sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = htonl( INADDR_ANY ); 

		int r = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
		if (r < 0)
			return -1;
		return 0;
	}

	int netlib_listen(int sockfd, int backlog)
	{
		return listen(sockfd, backlog);
	}


	int netlib_connect(const char* server_ip, uint16_t port)
	{
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			return -1;
		}

		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(server_ip);

		int r = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
		if (r < 0)
		{
			return -2;
		}
		return sockfd;
	}
}