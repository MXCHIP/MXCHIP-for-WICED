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
# Download HIDAPI Tar ball
#
###################################################################################################


# Fetch hidapi - clone it then zip the cloned directory for later use
if [ ! -e ./$DOWNLOAD_DIR/hidapi-$HIDAPI_REPO_HASH.tar.gz ]; then
    echo "Downloading hidapi"
    cd ./$DOWNLOAD_DIR
    rm -rf ./hidapi/
    git clone $HIDAPI_REPO_URL
    cd hidapi
    git checkout  $HIDAPI_REPO_HASH
    cd ..
    tar -zcvf hidapi-$HIDAPI_REPO_HASH.tar.gz hidapi/
    rm -rf hidapi/
    cd ..
fi


###################################################################################################
#
# Build HIDAPI
#
###################################################################################################

# Extract hidapi
echo "Extracting HIDAPI"
rm -rf ./hidapi/
tar -zxvf ./$DOWNLOAD_DIR/$HIDAPI_FILENAME

# Build HIDAPI
echo "Building HIDAPI"
rm -rf hidapi-build hidapi-install
mkdir -p hidapi-build
mkdir -p hidapi-install

cd hidapi
git am ../patches/hidapi.patch
./bootstrap
cd ../hidapi-build
../hidapi/configure --prefix=`pwd`/../hidapi-install/ --enable-shared=no CFLAGS="-g"
make install
cd ..
