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
# Download LibFTDI Tar ball
#
###################################################################################################


# Download libFTDI
if [ ! -e ./$DOWNLOAD_DIR/$LIBFTDI_FILENAME ]; then
    echo "Downloading libFTDI"
    cd $DOWNLOAD_DIR
    $WGET $LIBFTDI_URL
    cd ..
fi


###################################################################################################
#
# Build LibFTDI
#
###################################################################################################

# Extract libFTDI
echo "Extracting libFTDI"
rm -rf ./libftdi-$LIBFTDI_VER/
tar -zxvf ./$DOWNLOAD_DIR/$LIBFTDI_FILENAME
echo "Patching libFTDI"
patch --ignore-whitespace -p1 -N -d libftdi-$LIBFTDI_VER < patches/libftdi-${LIBFTDI_VER}.patch

# Build libFTDI
echo "Building libFTDI"
rm -rf libftdi-build libftdi-install
mkdir -p libftdi-build
mkdir -p libftdi-install

if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "msys2" ]]; then
    export PATH=`pwd`/libftdi-build/:$PATH
    cp libusb-config-msys libftdi-build/libusb-config
fi
if [[ "$OSTYPE" == *darwin* ]]; then
    export PATH=../libusb-compat-install/bin/:$PATH
    export EXTRA_CFLAGS="$EXTRA_CFLAGS -I`pwd`/libusb-compat-install/include/ -I`pwd`/libusb-install/include/libusb-1.0" # -L`pwd`/libusb-compat-install/lib/" # -L`pwd`/libusb-install/lib/" # -lusb-1.0"
fi

cd libftdi-build
../libftdi-$LIBFTDI_VER/configure --prefix=`pwd`/../libftdi-install/ --enable-shared=no
make CFLAGS="-g -L`pwd`/../libusb-win32-src-$LIBUSB_WIN32_VER/ -L`pwd`/../libusb-compat-install/lib/ -lusb -I`pwd`/../libusb-win32-src-$LIBUSB_WIN32_VER/src -I`pwd`/../libusb-compat-install/include/ -I/opt/local/include $EXTRA_CFLAGS" install
cd ..


