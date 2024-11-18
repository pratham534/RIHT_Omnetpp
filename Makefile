# Makefile
#INET_DIR = $(OMNETPP_ROOT)/inet
#include $(INET_DIR)/Makefile.inc

all: checkmakefiles
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile

makefiles:
	cd src && opp_makemake -f --deep
	

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi

	
SOURCES = src/RIHTPacket.msg src/RIHTRouter.cc src/Sender.cc src/Receiver.cc src/MyRoutingProtocol.cc
	