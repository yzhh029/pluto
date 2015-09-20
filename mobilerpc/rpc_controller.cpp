#include "rpc_controller.h"

namespace pluto{

RpcController::RpcController()
{

}

RpcController::~RpcController()
{

}

void RpcController::Reset() {}

bool RpcController::Failed() const {
	return !fail_reason_.empty();
}

std::string RpcController::ErrorText() const {
	return fail_reason_;
}

void RpcController::StartCancel() {}


void RpcController::SetFailed(const std::string& reason) {
	fail_reason_ = reason;
}

bool RpcController::IsCanceled() const {
	return false;
}

void RpcController::NotifyOnCancel(google::protobuf::Closure* callback) {}

};