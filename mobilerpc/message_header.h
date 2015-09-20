#ifndef __PLUTO_MESSAGE_HEADER_H__
#define __PLUTO_MESSAGE_HEADER_H__

#include <stdint.h>

namespace pluto
{
	typedef struct message_header{
		int32_t opcode;
		int32_t length;
	}MessageHeader;
}

#endif  //  __PLUTO_MESSAGE_HEADER_H__