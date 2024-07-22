CC=gcc
CFLAGS=-O3 -Wall -Wno-unused-function

# PREFIX must be part of the LD_LIBRARY_PATH
PREFIX?=/usr/local/lib
# PREFIX_CONF and PREFIX_UDEV_RULES MUST not be modified.
# These variables are only exposed for automated Yocto builds.
PREFIX_CONF?=/usr/local/etc
PREFIX_UDEV_RULES?=/lib/udev/rules.d

PROJROOT=$(shell pwd)
BUILDDIR="$(PROJROOT)/build/"

SYS_INC=-Iinclude/sys
PHY_INC=-Iinclude/physical
UART_INC=-Iinclude/physical/UART
PROTO_INC=-Iinclude/protocol
FSCI_INC=-Iinclude/protocol/FSCI

UNAME := $(shell uname)

UDEV?=yes
SPI?=yes
RNDIS?=yes

ifeq ($(UNAME), Linux)

	LDFLAGS=-lpthread -lrt $(LUDEV)
	FRAMEWORKS=

	ifeq ($(UDEV), yes)
		CFLAGS += -D__linux__udev__
		LUDEV=-ludev
	endif

	ifeq ($(SPI), yes)
		CFLAGS += -D__linux__spi__
		SPI_INC=-Iinclude/physical/SPI
		LIBSPI=$(addsuffix $(EXTENSION), libspi)
		LSPI=-lspi
	endif

	ifeq ($(RNDIS), yes)
		CFLAGS += -D__linux__pcap__
		PCAP_INC=-Iinclude/physical/PCAP
		LIBRNDIS=$(addsuffix $(EXTENSION), librndis)
		LRNDIS=-lrndis
	endif
endif

ifeq ($(UNAME), Darwin)
	LDFLAGS=-lpthread
	LUDEV=
	FRAMEWORKS=-framework IOKit -framework CoreFoundation
endif

ifeq ($(OPENWRT), yes)
	CC=mips-openwrt-linux-uclibc-gcc
	CFLAGS+=-Os -s
endif

ifeq ($(ARMHF), yes)
	CC=arm-linux-gnueabihf-gcc
endif

BUILDFLAGS=-c $(SYS_INC) $(PHY_INC) $(PROTO_INC) $(UART_INC) $(SPI_INC) $(PCAP_INC) $(FSCI_INC)
LIB_OPTION=dynamic

ifeq ($(LIB_OPTION), static)
	LIB_INCLUDE=
	LIBCFLAGS=
	LIBLFLAGS=-rcs
	EXTENSION=.a
	LL=ar
else
	LIB_INCLUDE=-L$(BUILDDIR)
	LIBCFLAGS=-fPIC
	ifeq ($(UNAME), Darwin)
		LIBLFLAGS=-dynamiclib -o
		EXTENSION=.dylib
	else
		LIBLFLAGS=-shared -Wl,-soname,
		EXTENSION=.so
		VERSION=.1
		FULL_VERSION=.1.12.0.0
	endif
	LL=$(CC)
endif

all: clean pre-build build cleanObj

documentation:
	rm -rf Documentation/html Documentation/latex
	doxygen Documentation/Doxyfile

build: pre-build $(addsuffix $(EXTENSION), libsys) $(addsuffix $(EXTENSION), libuart) $(LIBSPI) $(LIBRNDIS) $(addsuffix $(EXTENSION), libfsci) $(addsuffix $(EXTENSION), libphysical) $(addsuffix $(EXTENSION), libframer)

pre-build:
	mkdir -p $(BUILDDIR)


$(addsuffix $(EXTENSION), libsys): utils.o RawFrame.o MessageQueue.o hsdkThread.o hsdkEvent.o hsdkFile.o hsdkLock.o hsdkSemaphore.o EventManager.o hsdkLogger.o
ifeq ($(LIB_OPTION), dynamic)
	$(LL) $(LIBLFLAGS)$@$(VERSION) -o $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^) -lpthread
else
	$(LL) $(LIBLFLAGS) $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^)
endif

utils.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/utils.c -o $(BUILDDIR)$@
hsdkLogger.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/hsdkLogger.c -o $(BUILDDIR)$@
RawFrame.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/RawFrame.c -o $(BUILDDIR)$@
MessageQueue.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/MessageQueue.c -o $(BUILDDIR)$@
hsdkThread.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/hsdkThread.c -o $(BUILDDIR)$@
hsdkEvent.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/hsdkEvent.c -o $(BUILDDIR)$@
hsdkFile.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/hsdkFile.c -o $(BUILDDIR)$@
hsdkLock.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/hsdkLock.c -o $(BUILDDIR)$@
hsdkSemaphore.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/hsdkSemaphore.c -o $(BUILDDIR)$@
EventManager.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) sys/EventManager.c -o $(BUILDDIR)$@


$(addsuffix $(EXTENSION), libframer): Framer.o FSCIFramer.o
ifeq ($(LIB_OPTION), dynamic)
	$(LL) $(LIB_INCLUDE) $(LIBLFLAGS)$@$(VERSION) -o $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $<) -lsys -lfsci -lphysical
else
	$(LL) $(LIBLFLAGS) $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^)
endif

Framer.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) protocol/Framer.c -o $(BUILDDIR)$@


$(addsuffix $(EXTENSION), libphysical): PhysicalDevice.o
ifeq ($(LIB_OPTION), dynamic)
	$(LL) $(LIB_INCLUDE) $(LIBLFLAGS)$@$(VERSION) -o $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^) -lsys -luart $(LRNDIS) $(LUDEV) $(LSPI)
else
	$(LL) $(LIBLFLAGS) $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^)
endif

PhysicalDevice.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) physical/PhysicalDevice.c -o $(BUILDDIR)$@


$(addsuffix $(EXTENSION), libfsci): FSCIFrame.o FSCIFramer.o
ifeq ($(LIB_OPTION), dynamic)
	$(LL) $(LIB_INCLUDE) $(LIBLFLAGS)$@$(VERSION) -o $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^) -lsys
else
	$(LL) $(LIBLFLAGS) $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^)
endif

FSCIFrame.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) protocol/FSCI/FSCIFrame.c -o $(BUILDDIR)$@

FSCIFramer.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) protocol/FSCI/FSCIFramer.c -o $(BUILDDIR)$@


$(addsuffix $(EXTENSION), libuart): UARTDiscovery.o UARTDevice.o UARTConfiguration.o
ifeq ($(LIB_OPTION), dynamic)
	$(LL) $(FRAMEWORKS) $(LIB_INCLUDE) $(LIBLFLAGS)$@$(VERSION) -o $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^) -lsys $(LUDEV)
else
	$(LL) $(LIBLFLAGS) $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^)
endif

UARTDiscovery.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) physical/UART/UARTDiscovery.c -o $(BUILDDIR)$@
UARTDevice.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) physical/UART/UARTDevice.c -o $(BUILDDIR)$@
UARTConfiguration.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) physical/UART/UARTConfiguration.c -o $(BUILDDIR)$@


$(addsuffix $(EXTENSION), libspi): SPIDevice.o SPIConfiguration.o
ifeq ($(LIB_OPTION), dynamic)
	$(LL) $(LIB_INCLUDE) $(LIBLFLAGS)$@$(VERSION) -o $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^) -lsys
else
	$(LL) $(LIBLFLAGS) $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^)
endif

SPIDevice.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) physical/SPI/SPIDevice.c -o $(BUILDDIR)$@
SPIConfiguration.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) physical/SPI/SPIConfiguration.c -o $(BUILDDIR)$@


$(addsuffix $(EXTENSION), librndis): PCAPDevice.o
ifeq ($(LIB_OPTION), dynamic)
	$(LL) $(LIB_INCLUDE) $(LIBLFLAGS)$@$(VERSION) -o $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^) -lsys -lpthread -lpcap
else
	$(LL) $(LIBLFLAGS) $(BUILDDIR)$@ $(addprefix $(BUILDDIR), $^)
endif

PCAPDevice.o:
	$(CC) $(LIBCFLAGS) $(CFLAGS) $(BUILDFLAGS) physical/PCAP/PCAPDevice.c -o $(BUILDDIR)$@


clean:
	rm -f $(BUILDDIR)*
	rm -rf $(BUILDDIR)

cleanObj:
	rm -f $(BUILDDIR)*.o

install: uninstall
ifeq ($(OPENWRT), yes)
	cp $(BUILDDIR)*$(EXTENSION) $(STAGING_DIR)/lib/
else
	# Copy shared libraries to $(PREFIX) with fully-qualified major.minor names. Run ldconfig to generate symlinks to *.so.x.
	# Manually set symlinks .so -> .so.x
	for f in $(shell find $(BUILDDIR) -name '*$(EXTENSION)' -exec basename {} \;); do \
		cp $(BUILDDIR)$$f $(PREFIX)/$$f$(FULL_VERSION) ; \
		ldconfig $(PREFIX) ; \
		ln -s $(PREFIX)/$$f$(VERSION) $(PREFIX)/$$f ; \
	done
	cp res/77-mm-usb-device-blacklist.rules $(PREFIX_UDEV_RULES)/77-mm-usb-device-blacklist.rules
	udevadm control --reload-rules
	mkdir -p $(PREFIX_CONF)/hsdk
	cp res/hsdk.conf $(PREFIX_CONF)/hsdk
endif

uninstall:
	# Placing shared libraries in /usr/lib is now deprecated, yet any leftovers are removed here.
	rm -f /usr/lib/libframer.* /usr/lib/libphysical.* /usr/lib/librndis.* /usr/lib/libsys.* /usr/lib/libuart.* /usr/lib/libspi.* /usr/lib/libfsci.* /usr/lib/libztc.*
	rm -f $(PREFIX)/libframer.* $(PREFIX)/libphysical.* $(PREFIX)/librndis.* $(PREFIX)/libsys.* $(PREFIX)/libuart.* $(PREFIX)/libspi.* $(PREFIX)/libfsci.* $(PREFIX)/libztc.*
	rm -rf $(PREFIX_CONF)/hsdk
	ldconfig $(PREFIX)
