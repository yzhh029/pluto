#ifndef __PLUTO_RPC_CHANNEL_H__
#define __PLUTO_RPC_CHANNEL_H__

#include <iostream>
#include <string.h>
#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

namespace pluto
{
	class RpcChannel : public google::protobuf::RpcChannel
	{
	public:
		RpcChannel(const std::string &host, uint16_t port);
		
		virtual ~RpcChannel();

		virtual void CallMethod(const google::protobuf::MethodDescriptor* method,
			google::protobuf::RpcController* controller,
			const google::protobuf::Message* request,
			google::protobuf::Message* response,
			google::protobuf::Closure* done);

		int Connect();

		void Close();

	private:
		int sockfd_;

		char ip_[16];
		int16_t port_;
	};

};

#endif  //  __PLUTO_RPC_CHANNEL_H__