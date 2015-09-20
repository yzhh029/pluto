#mobilerpc

ifeq ($(origin version), undefined)
	version = 0.1.0
endif

all:
	@( cd mobilerpc; make )
	@( cd sample; make )
mobilerpc:
	@( cd mobilerpc; make )
sample:
	@( cd sample; make )

clean:
	@(cd mobilerpc; make clean)
	@(cd sample; make clean)
