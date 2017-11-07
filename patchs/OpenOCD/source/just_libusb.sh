#!/bin/bash

#
# Copyright 2016, Cypress Semiconductor Corporation or a subsidiary of 
 # Cypress Semiconductor Corporation. All Rights Reserved.
 # This software, including source code, documentation and related
 # materials ("Software"), is owned by Cypress Semiconductor Corporation
 # or one of its subsidiaries ("Cypress") and is protected by and subject to
 # worldwide patent protection (United States and foreign),
 # United States copyright laws and international treaty provisions.
 # Therefore, you may use this Software only as provided in the license
 # agreement accompanying the software package from which you
 # obtained this Software ("EULA").
 # If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 # non-transferable license to copy, modify, and compile the Software
 # source code solely for use in connection with Cypress's
 # integrated circuit products. Any reproduction, modification, translation,
 # compilation, or representation of this Software except as specified
 # above is prohibited without the express written permission of Cypress.
 #
 # Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 # EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 # WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 # reserves the right to make changes to the Software without notice. Cypress
 # does not assume any liability arising out of the application or use of the
 # Software or any product or circuit described in the Software. Cypress does
 # not authorize its products for use in any products where a malfunction or
 # failure of the Cypress product may reasonably be expected to result in
 # significant property damage, injury or death ("High Risk Product"). By
 # including Cypress's product in a High Risk Product, the manufacturer
 # of such system or application assumes all risk of such use and in doing
 # so agrees to indemnify Cypress against all liability.
#

if [ "$PREREQUISITES_DONE" != "yes" ]; then
source ./prerequisites.sh
fi

###################################################################################################
#
# Download LibUSBTar balls
#
###################################################################################################


# Download libusb 1.x
if [ ! -e ./$DOWNLOAD_DIR/$LIBUSB_FILENAME ]; then
    echo "Downloading libUSB"
    cd $DOWNLOAD_DIR
    $WGET $LIBUSB_URL
    cd ..
fi




# Windows Specific
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "msys2" ]]; then

    # Download libusb 0.x on Windows
    if [ ! -e ./$DOWNLOAD_DIR/$LIBUSB_WIN32_FILENAME ]
    then
        echo "Downloading libUSB-win32"
    cd $DOWNLOAD_DIR
        $WGET $LIBUSB_WIN32_URL
    cd ..
    fi

fi


# Fetch libusb and libusb-compat on OS-X
if [[ "$OSTYPE" == *darwin* ]]; then

    if [ ! -e ./$DOWNLOAD_DIR/$LIBUSB_COMPAT_FILENAME ]; then
        echo "Downloading libUSB-compat"
                cd $DOWNLOAD_DIR
        $WGET $LIBUSB_COMPAT_URL
                cd ..
    fi
fi



###################################################################################################
#
# Build LibUSB
#
###################################################################################################


# Build libusb on Windows
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "msys2" ]]; then

    # NOTE: libusb-win32 is needed because many WICED users have the libusb-win32 windows driver installed
    #       and the libusb-compat layer  does not work with the old libusb-win32 driver.

    echo "Unzipping libUSB 0.x  (libUSB-win32)"

    rm -rf ./libusb-win32-src-$LIBUSB_WIN32_VER/

    # Unzip fails with segmentation violation first time when used in long directory path for some reason
    unzip -o ./$DOWNLOAD_DIR/$LIBUSB_WIN32_FILENAME || unzip -o ./$DOWNLOAD_DIR/$LIBUSB_WIN32_FILENAME

    echo "Patching libUSB 0.x  (libUSB-win32)"
    patch --ignore-whitespace -p1 -N -d libusb-win32-src-$LIBUSB_WIN32_VER < patches/libusb-win32-src-$LIBUSB_WIN32_VER.patch

    echo "Building libUSB 0.x  (libUSB-win32)"
    CFLAGS="-g $EXTRA_CFLAGS" make -C ./libusb-win32-src-$LIBUSB_WIN32_VER/ static_lib

    # Create a package config file for LibUSB-Win32
    mkdir -p ./libusb-win32-src-$LIBUSB_WIN32_VER/pkgconfig/
    echo "Name: libusb" > ./libusb-win32-src-$LIBUSB_WIN32_VER/pkgconfig/libusb.pc
    echo "Description: Legacy C API for USB device access from Windows userspace" >> ./libusb-win32-src-$LIBUSB_WIN32_VER/pkgconfig/libusb.pc
    echo "Version: win32-1.0.18" >> ./libusb-win32-src-$LIBUSB_WIN32_VER/pkgconfig/libusb.pc
    echo "Libs: -lusb" >> ./libusb-win32-src-$LIBUSB_WIN32_VER/pkgconfig/libusb.pc
    echo "Libs.private: " >> ./libusb-win32-src-$LIBUSB_WIN32_VER/pkgconfig/libusb.pc
    echo "Cflags:" >> ./libusb-win32-src-$LIBUSB_WIN32_VER/pkgconfig/libusb.pc

    cp ./libusb-win32-src-$LIBUSB_WIN32_VER/src/lusb0_usb.h ./libusb-win32-src-$LIBUSB_WIN32_VER/src/usb.h


    CONFIG_PARAMS="--enable-static=yes --enable-shared=no"
else
    CONFIG_PARAMS="--enable-static=no"
fi

# Build libusb 1.x

echo "Unzipping libUSB 1.x"
rm -rf ./libusb-$LIBUSB_VER/
tar -jxvf ./$DOWNLOAD_DIR/$LIBUSB_FILENAME

echo "Patching libUSB 1.x"
# Note - this patch should not be needed when https://github.com/libusb/libusb/pull/140 is merged into a libusb release
patch --ignore-whitespace -p1 -N -d libusb-$LIBUSB_VER < patches/libusb-${LIBUSB_VER}.patch


echo "Building libUSB 1.x"
mkdir -p libusb-build
mkdir -p libusb-install
cd libusb-build
../libusb-$LIBUSB_VER/configure --prefix=`pwd`/../libusb-install/ $CONFIG_PARAMS
make install
cd ..

# Build libusb & libusb-compat on OS-X
if [[ "$OSTYPE" == *darwin* ]]; then


    export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:`pwd`/libusb-install/lib/pkgconfig/

    echo "Unzipping libUSB-compat"
    rm -rf ./libusb-$LIBUSB_COMPAT_VER/
    tar -jxvf ./$DOWNLOAD_DIR/$LIBUSB_COMPAT_FILENAME

    echo "Building libUSB-compat"
    mkdir -p libusb-compat-build
    mkdir -p libusb-compat-install
    cd libusb-compat-$LIBUSB_COMPAT_VER
    # Copy config.guess/config.sub files that allow compilation on MSYS2
    cp ../patches/msys2-config.guess ./config.guess
    cp ../patches/msys2-config.sub   ./config.sub

    touch configure.ac aclocal.m4 configure Makefile.am Makefile.in
    cd ../libusb-compat-build
    ../libusb-compat-$LIBUSB_COMPAT_VER/configure --prefix=`pwd`/../libusb-compat-install/ --enable-static=no CFLAGS="-g -I`pwd`/libusb-install/include/libusb-1.0 -L`pwd`/libusb-install/lib/"
    make install
    cd ..
    if [ "$OSTYPE" == *darwin* ]; then
        cp libusb-install/lib/libusb-1.0.0.dylib $INSTALL_DIR/$HOST_TYPE/
        cp libusb-compat-install/lib/libusb-0.1.4.dylib $INSTALL_DIR/$HOST_TYPE/
    fi
fi


