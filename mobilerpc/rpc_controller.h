#ifndef __PLUTO_RPC_CONTROLLER_H__
#define __PLUTO_RPC_CONTROLLER_H__

#include <iostream>
#include <google/protobuf/service.h>

namespace pluto
{
	class RpcController : public google::protobuf::RpcController
	{
	public:
		RpcController();
		virtual ~RpcController();

		virtual void Reset();
		virtual bool Failed() const;
		virtual std::string ErrorText() const;
		virtual void StartCancel();

		virtual void SetFailed(const std::string& reason);
		virtual bool IsCanceled() const;
		virtual void NotifyOnCancel(google::protobuf::Closure* callback);

	private:
		std::string fail_reason_;
	};
};

#endif // !__PLUTO_RPC_CONTROLLER_H__
