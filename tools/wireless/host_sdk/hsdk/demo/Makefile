CC=gcc
CFLAGS=-O3 -Wall -Wno-unused-function

PROJROOT=$(shell pwd)
HSDK_ROOT=$(PROJROOT)/..
BUILDDIR=$(PROJROOT)/build
BINDIR=$(PROJROOT)/bin

SYS_INC=-I$(HSDK_ROOT)/include/sys
PHY_INC=-I$(HSDK_ROOT)/include/physical
UART_INC=-I$(HSDK_ROOT)/include/physical/UART
PCAP_INC=-I$(HSDK_ROOT)/include/physical/PCAP
SPI_INC=-I$(HSDK_ROOT)/include/physical/SPI
PROTO_INC=-I$(HSDK_ROOT)/include/protocol
FSCI_INC=-I$(HSDK_ROOT)/include/protocol/FSCI

BUILDFLAGS=-c $(SYS_INC) $(PHY_INC) $(UART_INC) $(PCAP_INC) $(SPI_INC) $(PROTO_INC) $(FSCI_INC)
HSDK_LIBS=-lframer -lfsci -lphysical -luart -lsys

UNAME := $(shell uname)
SPI?=yes

ifeq ($(UNAME), Linux)
	LDFLAGS=-lpthread -lrt

	ifeq ($(SPI), yes)
		HSDK_LIBS += -lspi
		CFLAGS += -D__linux__spi__
	endif

endif

ifeq ($(UNAME), Darwin)
	LDFLAGS=-lpthread
endif

ifeq ($(OPENWRT), yes)
	CC=mips-openwrt-linux-uclibc-gcc
	CFLAGS+=-DOPENWRT -Os -s
endif

ifeq ($(ARMHF), yes)
	CC=arm-linux-gnueabihf-gcc
endif


build: clean pre-build FsciBootloader GetKinetisDevices 

spi: SPITest

pre-build:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BINDIR)

FsciBootloader: FsciBootloader.o
	$(CC) $(BUILDDIR)/$^ -o $(BINDIR)/$@ $(HSDK_LIBS) $(LDFLAGS)
FsciBootloader.o: FsciBootloader.c
	$(CC) $(CFLAGS) $(BUILDFLAGS) $^ -o $(BUILDDIR)/$@

GetKinetisDevices: GetKinetisDevices.o
	$(CC) $(BUILDDIR)/$^ -o $(BINDIR)/$@ $(HSDK_LIBS) $(LDFLAGS)
GetKinetisDevices.o: GetKinetisDevices.c
	$(CC) $(CFLAGS) $(BUILDFLAGS) $^ -o $(BUILDDIR)/$@

clean:
	rm -f $(BUILDDIR)/*
	find $(BINDIR)/ -maxdepth 1 -type f -exec rm {} \;
