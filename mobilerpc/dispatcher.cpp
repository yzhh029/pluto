#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#include "net_util.h"
#include "rpc_channel.h"
#include "rpc_server.h"
#include "dispatcher.h"

namespace pluto{

Dispatcher::Dispatcher()
	:epoll_fd_(-1),
	running_(false)
{
	epoll_fd_ = epoll_create(MAX_EPOLL_NUM);
	if (epoll_fd_ < 0)
	{
		printf("epoll_create errno:%d\n",errno);
		exit(EXIT_FAILURE);
	}
	printf("dispatcher init\n");
}

Dispatcher::~Dispatcher()
{
	close(epoll_fd_);
}

void Dispatcher::StartServer()
{

	
	//int r = netlib_setnonblocking(epoll_fd_);
	//if (r < 0)
	//{
	//	return;
	//}

	Run();

}

void Dispatcher::Run()
{
	printf("dispatcher start\n");
	int nfds = 0;
	if (running_)
	{
		return;
	}
	running_ = true;

	while (1)
	{
		printf("before epoll wait\n");
		nfds = epoll_wait(epoll_fd_, events_, MAX_EPOLL_NUM, -1);  //wait_timeout
		printf("epoll wait nfds=%d\n",nfds);
		for (int i = 0; i < nfds; i++)
		{
			int what = events_[i].events;

			int fd = events_[i].data.fd;
			
			if (fd == rpc_server_->ListenFd())
			{
				printf("listen==>\n");
				struct sockaddr_in client_addr;
				socklen_t   len = sizeof( struct sockaddr_in );
				int conn_fd = accept(fd, (struct sockaddr*)&client_addr, &len);
				if (conn_fd < 0)
				{
					printf("accept error");
				}
				rpc_server_->OnAccept(conn_fd);
			}
			else
			{
				printf("read\n");
				rpc_server_->OnRead(fd);
				RemoveEvent(fd);
			}
		}
	}
}

void Dispatcher::SetServer(RpcServer *rpc_server)
{
	rpc_server_ = rpc_server;
}

int Dispatcher::AddEvent(int fd, short flags)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	/*
	short events = EVENT_NONE;
	if (flags & EVENT_READ)
		events |= EPOLLIN;
	if (flags & EVENT_WRITE)
		events |= EPOLLOUT;
	*/
	ev.events = EPOLLIN;
	if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev) < 0)
	{
		printf("add event error:%d\n", errno);
		return -1;
		//exit(EXIT_FAILURE);
	}
	printf("add event\n");
	return 0;

}

void Dispatcher::RemoveEvent(int fd)
{
	struct epoll_event ev;  //todo:majianfei
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	close(fd);
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &ev);
}

};