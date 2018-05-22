cmake_minimum_required(VERSION 2.8.7)
project(iio_examples C)

# TODO: On Darwin link -framework to iio-monitor
# add_executable(iio-monitor iio-monitor.c)
# target_link_libraries(iio-monitor iio pthread ncurses cdk)

add_executable(ad9361-iiostream ad9361-iiostream.c)
target_link_libraries(ad9361-iiostream  iio)

add_executable(ad9371-iiostream ad9371-iiostream.c)
target_link_libraries(ad9371-iiostream iio)

add_executable(dummy-iiostream dummy-iiostream.c)
target_link_libraries(dummy-iiostream iio)

