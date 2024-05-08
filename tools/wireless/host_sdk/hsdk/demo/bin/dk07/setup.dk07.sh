#!/bin/ash

for f in *.so; do
    mv -- "$f" "${f%.so}.so.1"
done

chmod +x *.so.1 Thread_Shell

cp *.so.1 /usr/lib
ln -s /lib/libc.so.1 /lib/libc.so.0
ln -s /lib/libpthread.so.1 /lib/libthread_db.so.1

echo  "42" > /sys/class/gpio/export
echo  "45" > /sys/class/gpio/export
echo "falling" > /sys/class/gpio/gpio42/edge
echo "out" > /sys/class/gpio/gpio45/direction

insmod tun.ko
# Delete previous tunnel
ip link del dev threadtap0
# Create a new TAP interface for Thread interaction.
ip -6 tuntap add mode tap threadtap0
# The interface is ready.
ip link set threadtap0 up

brctl addif br-lan threadtap0
brctl show
/etc/init.d/odhcpd restart

# Uncomment the following lines to reset the border router
# echo "49" > /sys/class/gpio/export
# echo "out" > /sys/class/gpio/gpio49/direction
# echo "0" > /sys/class/gpio/gpio49/value
# echo "1" > /sys/class/gpio/gpio49/value
