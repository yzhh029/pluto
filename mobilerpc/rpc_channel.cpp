#include <errno.h>
#include "util.h"
#include "message_header.h"
#include "net_util.h"
#include "rpc_channel.h"

namespace pluto{

RpcChannel::RpcChannel(const std::string &host, uint16_t port)
{

	strcpy(ip_,host.c_str());
	port_ = port;

}

RpcChannel::~RpcChannel()
{
	Close();
}

int RpcChannel::Connect()
{
	int fd = netlib_connect(ip_, port_);
	if (fd < 0)
	{
		printf("rpc channel init error:%d\n",errno);
		return -1;
	}
	sockfd_ = fd;
	return 0;
}

void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
						google::protobuf::RpcController* controller,
						const google::protobuf::Message* request,
						google::protobuf::Message* response,
						google::protobuf::Closure* done)
{
	printf("CallMethod start\n");
	std::string methodname = std::string(method->full_name());
	int32_t opcode = hash_string(methodname.c_str());  //todo: hash
	int32_t length = request->ByteSize();
	
	MessageHeader header;
	header.opcode = opcode;
	header.length = length;

	int32_t total_len = length + sizeof(header);
	char* buf = NULL;
	buf = (char*)malloc(total_len+1);
	memcpy(buf, &header, sizeof(header));
	request->SerializeToArray(buf+sizeof(header), request->ByteSize());
	send(sockfd_, buf, total_len, 0);
	free(buf);
	
	char buf2[BUF_SIZE] = {};
	recv(sockfd_, buf2, BUF_SIZE, 0);
	response->ParseFromString(buf2);
	
}

void RpcChannel::Close()
{
	if (sockfd_ > 0)
	{
		close(sockfd_);
	}
}
};