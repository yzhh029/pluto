#mobilerpc

CC = g++
CCFLAGS = -g
LDFLAGS = 

PROTO_LDFLAGS = -L/user/local/lib -lprotobuf
USER_LDFLAGS = $(PROTO_LDFLAGS)

PROTOC = protoc
#MKDIR = mkdir -p

LIBS=-lprotobuf
#CFLAGS = -g -Wall

MOBILE_INCL = -I../mobilerpc
MOBILE_LIB = -L../mobilerpc -lmobilerpc

CCFLAGS += $(MOBILE_INCL)
LDFLAGS += $(MOBILE_LIB)

#TMPLIB = .libs

#all: mkdir echo_client echo_server
#mkdir:
#	$(MKDIR) $(TMPLIB)

LIBOBJS = echo.pb.o

TARGET = echo.pb.o echo_client echo_server

all: $(TARGET)

echo_client:  echo_client.o $(LIBOBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(USER_LDFLAGS) $^ -o $@ 
echo_server:  echo_server.o $(LIBOBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(USER_LDFLAGS) $^ -o $@

echo.pb.o: echo.pb.cc
	$(CC) $(CCFLAGS) -c $^ -o $@

echo.pb.cc echo.pb.h: echo.proto
	$(PROTOC) -I=. --cpp_out=. echo.proto

clean:
	rm -f echo_client echo_server *.o

# make rule	
%.o : %.c
	$(CC) $(CCFLAGS) -c $^ -o $@

%.o : %.cc
	$(CC) $(CCFLAGS) -c $^ -o $@

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@
