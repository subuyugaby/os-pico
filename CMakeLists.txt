cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(main
    main.c
    tests/tests.c
    devices/timer.c
    threads/thread.c

    tests/alarm-negative.c
    tests/alarm-zero.c
    tests/one-thread.c
    tests/multi-thread.c

    list.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)