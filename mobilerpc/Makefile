#mobilerpc

CC = g++
AR = ar cru
CCFLAGS = -Wall -g -fPIC
SOFLAGS = -shared
#LDFLAGS = -lstdc++ -pthread
LDFLAGS = 

PROTO_LDFLAGS = -L/user/local/lib -lprotobuf
USER_LDFLAGS = $(PROTO_LDFLAGS)

LIBOBJS = util.o net_util.o rpc_channel.o rpc_server.o dispatcher.o rpc_controller.o

TARGET = libmobilerpc.so libmobilerpc.a

all:  $(TARGET)

libmobilerpc.so: $(LIBOBJS)
	$(CC) $(SOFLAGS) $(USER_LDFLAGS) $^ -o $@
libmobilerpc.a: $(LIBOBJS)
	$(AR) $@ $^

clean:
	rm -f *.o *.so *.a
	
# make rule
%.o : %.c
	$(CC) $(CCFLAGS) -c $^ -o $@	

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@
