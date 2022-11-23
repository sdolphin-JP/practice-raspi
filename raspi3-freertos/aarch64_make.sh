#!/bin/bash

export          PATH=${PATH}:/opt/gcc-arm-aarch64-aarch64-none-elf/bin
export          ARCH=aarch64
export CROSS_COMPILE=aarch64-none-elf-
export            CC=${CROSS_COMPILE}gcc
export           CXX=${CROSS_COMPILE}g++
export            AR=${CROSS_COMPILE}ar
export            AS=${CROSS_COMPILE}as
export            LD=${CROSS_COMPILE}ld
export            OC=${CROSS_COMPILE}objcopy
export            OD=${CROSS_COMPILE}objdump
export         STRIP=${CROSS_COMPILE}strip

make $*
