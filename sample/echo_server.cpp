#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "util.h"
#include "rpc_server.h"
#include "dispatcher.h"
#include "echo.pb.h"

using namespace echo;
using namespace pluto;

class EchoServiceImpl : public echo::EchoService 
{
public:
	EchoServiceImpl() {
	};

	virtual void Echo(::google::protobuf::RpcController* controller,
		const echo::EchoRequest* request,
		echo::EchoResponse* response,
		::google::protobuf::Closure* done) {
			printf("Received1:%s\n", request->message().c_str());

			response->set_response(request->message());
			if (done) {
				done->Run();
			}
	}
};

int main(int argc, char *argv[])
{
	printf("echo_server start\n");
	signal(SIGPIPE, SIG_IGN);

	pluto::Dispatcher dispatcher;
	pluto::RpcServer rpc_server(ECHO_PORT);
	rpc_server.set_dispatcher(&dispatcher);
	//dispatcher.StartServer();
	::google::protobuf::Service *service = new EchoServiceImpl();
	rpc_server.RegisterService(service);
	rpc_server.Start();
	return 0;
}
