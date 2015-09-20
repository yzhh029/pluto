#ifndef __PLUTO_RPC_METHOD_H__
#define __PLUTO_RPC_METHOD_H__

#include <google/protobuf/service.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/common.h>

namespace pluto
{
	struct RpcMethod{
	public:
		RpcMethod(google::protobuf::Service *service,
			const google::protobuf::Message *request,
			const google::protobuf::Message *respones,
			const google::protobuf::MethodDescriptor *method)
			: service_(service),
			request_(request),
			response_(respones),
			method_(method)
		{

		}
	
	google::protobuf::Service *service_;
	const google::protobuf::Message *request_;
	const google::protobuf::Message *response_;
	const google::protobuf::MethodDescriptor *method_;
	};
}

#endif // !__PLUTO_RPC_METHOD_H__
