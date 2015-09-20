#include <stdio.h>
#include <errno.h>
#include <google/protobuf/stubs/common.h>
#include "util.h"
#include "rpc_channel.h"
#include "rpc_controller.h"
#include "echo.pb.h"

using namespace pluto;
using namespace echo;

int main(int argc, char *argv[])
{
	printf("echo_client start\n");
	EchoRequest request;
	RpcController rpc_controller;
	RpcChannel rpc_channel("127.0.0.1",ECHO_PORT);

	int r = rpc_channel.Connect();
	if (r < 0)
	{
		printf("rpc connect error:%d\n",errno);
	}

	echo::EchoService::Stub stub(&rpc_channel);
	echo::EchoResponse response;
	request.set_message("hello world");

	stub.Echo(&rpc_controller, &request, &response, NULL);
	printf("response:%s\n", response.response().c_str());
	return 0;
}