#include <string.h>
#include <errno.h>
#include "util.h"
#include "net_util.h"
#include "message_header.h"
#include "dispatcher.h"
#include "rpc_server.h"

namespace pluto{

RpcServer::RpcServer(uint16_t port)
{
	printf("rpc server init\n");
	int fd = netlib_socket();
	if (fd < 0)
	{
		printf("netlib_socket error:%d\n",errno);
		exit(EXIT_FAILURE);
	}
	if(netlib_bind(fd, port) < 0)
	{
		printf("netlib_bind error:%d\n",errno);
		exit(EXIT_FAILURE);
	}
	if (netlib_listen(fd,5))
	{
		printf("netlib_listen error:%d\n",errno);
		exit(EXIT_FAILURE);
	}
	listen_fd_ = fd;
}

RpcServer::~RpcServer()
{
	close(listen_fd_);
}

void RpcServer::RegisterService(google::protobuf::Service *service)
{
	const google::protobuf::ServiceDescriptor *descriptor = service->GetDescriptor();
	printf("RegisterService%d\n", descriptor->method_count());
	for (int i = 0; i < descriptor->method_count(); i++)
	{
		printf("register service =>%d",i);
		const google::protobuf::MethodDescriptor *method = descriptor->method(i);
		const google::protobuf::Message *request = &service->GetRequestPrototype(method);
		const google::protobuf::Message *response = &service->GetResponsePrototype(method);
		RpcMethod *rpc_method = new RpcMethod(service, request, response, method);
		std::string methodname=std::string(method->full_name());
		int32_t hash = hash_string(methodname.c_str());
		RpcMethodMap::const_iterator iter = rpc_method_map_.find(hash);
		if (iter == rpc_method_map_.end())
			rpc_method_map_[hash] = rpc_method;
		else
		{
			std::string pre_name = std::string(iter->second->method_->full_name());
			printf("register service error the same hash:%s with %s\n",methodname.c_str(),pre_name.c_str());
		}
	}
}

void RpcServer::set_dispatcher(Dispatcher *dispatcher)
{
	dispatcher_ = dispatcher;
	dispatcher_->SetServer(this);
}

void RpcServer::Start()
{
	printf("rpc server start\n");
	dispatcher_->AddEvent(listen_fd_, EVENT_READ | EVENT_WRITE);
	dispatcher_->StartServer();
}

void RpcServer::OnRead(int fd)
{
	printf("on read\n");
	char buf[BUF_SIZE] = {0};
	int bytes = recv(fd, buf, sizeof(buf), 0);
	if (bytes <= 0)
	{
		printf("rpcserver onread error:%d\n",errno);
		return;
	}

	MessageHeader header;
	memcpy((char*)(&header),buf,sizeof(header));
	printf("opcode=%d,length=%d\n", header.opcode,header.length);
	RpcMethodMap::const_iterator iter = rpc_method_map_.find(header.opcode);
	if (iter == rpc_method_map_.end())
	{
		return;
	}
	RpcMethod* rpc_method = iter->second;
	const google::protobuf::MethodDescriptor *method = rpc_method->method_;
	google::protobuf::Message *request = rpc_method->request_->New();
	google::protobuf::Message *response = rpc_method->response_->New();
	request->ParseFromString(buf + sizeof(header));

	rpc_method->service_->CallMethod(method,NULL,request,response,NULL);
	
	size_t msg_len = response->ByteSize();

	char* buf2 = NULL;
	buf2 = (char*)malloc(msg_len);
	response->SerializeToArray(buf2, msg_len);
	send(fd, buf2,msg_len,0);
	free(buf2);
}

void RpcServer::OnAccept(int fd)
{
	printf("on accept\n");
	dispatcher_->AddEvent(fd, EVENT_READ | EVENT_WRITE);

}

int RpcServer::ListenFd()
{
	return listen_fd_;
}
};