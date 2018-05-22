#!/bin/sh
# Helper script to get dummy iio kernel modules loaded and configured
# for dummy-iiostream example.

# Check if `configfs` is already mounted
mount | grep 'config' || mount -t configfs none /sys/kernel/config

modprobe industrialio
modprobe industrialio-configfs
modprobe industrialio-sw-device
modprobe industrialio-sw-trigger
modprobe iio-trig-hrtimer
modprobe iio_dummy

# Create trigger and dummy device under `/sys/kernel/config`
mkdir /sys/kernel/config/iio/triggers/hrtimer/instance1
mkdir /sys/kernel/config/iio/devices/dummy/my_dummy_device

# iio_info