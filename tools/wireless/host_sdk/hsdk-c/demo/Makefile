CC=gcc
CFLAGS=-std=c99 -fshort-enums -Wall -Wfatal-errors -pthread
LDFLAGS=-lframer -lfsci -lphysical -luart -lsys -pthread

HSDK_PATH=../../hsdk
SYS_INC  =-I$(HSDK_PATH)/include/sys
PHY_INC  =-I$(HSDK_PATH)/include/physical
UART_INC =-I$(HSDK_PATH)/include/physical/UART
PROTO_INC=-I$(HSDK_PATH)/include/protocol
FSCI_INC =-I$(HSDK_PATH)/include/protocol/FSCI

INC=-I../inc/ $(SYS_INC) $(PHY_INC) $(PROTO_INC) $(UART_INC) $(FSCI_INC)
CFLAGS+=$(INC)

all: clean HeartRateSensor

HeartRateSensor.o: HeartRateSensor.c
	$(CC) -c -o $@ $< $(CFLAGS)

cmd_ble.o: ../src/cmd_ble.c
	$(CC) -c -o $@ $< $(CFLAGS)

evt_ble.o: ../src/evt_ble.c
	$(CC) -c -o $@ $< $(CFLAGS)

unload_ble.o: ../src/unload_ble.c
	$(CC) -c -o $@ $< $(CFLAGS)

evt_printer_ble.o: ../src/evt_printer_ble.c
	$(CC) -c -o $@ $< $(CFLAGS)

HeartRateSensor: HeartRateSensor.o cmd_ble.o evt_ble.o unload_ble.o evt_printer_ble.o
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)


clean:
	rm -f *.o HeartRateSensor
