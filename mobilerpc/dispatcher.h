#ifndef __PLUTO_DISPATCHER_H__
#define __PLUTO_DISPATCHER_H__

#include <sys/epoll.h>
#include "util.h"

namespace pluto
{
	class RpcServer;

	class Dispatcher
	{
	public:
		Dispatcher();

		~Dispatcher();

		void StartServer();

		void Run();

		void SetServer(RpcServer *rpc_server);

		int AddEvent(int fd, short flags);

		void RemoveEvent(int fd);

	private:
		int epoll_fd_;

		bool running_;

		RpcServer *rpc_server_;

		struct epoll_event events_[MAX_EPOLL_NUM];
	};
};



#endif  // __PLUTO_DISPATCHER_H__