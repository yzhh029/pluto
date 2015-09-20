#ifndef __PLUTO_RPC_SERVER_H__
#define __PLUTO_RPC_SERVER_H__

#include <iostream>
#include <map>
#include <google/protobuf/service.h>
#include "rpc_method.h"

namespace pluto
{
	class Dispatcher;

	class RpcServer
	{
		typedef std::map<uint64_t, RpcMethod*> RpcMethodMap;
	public:
		RpcServer(uint16_t port);
		
		virtual ~RpcServer();

		void RegisterService(google::protobuf::Service *service);

		void set_dispatcher(Dispatcher *dispatcher);

		void Start();

		void OnRead(int fd);

		void OnWrite();

		void OnAccept(int fd);

		int ListenFd();
	
	private:
		int listen_fd_;

		Dispatcher *dispatcher_;
		RpcMethodMap rpc_method_map_;
	};
};

#endif  //  __PLUTO_RPC_SERVER_H__