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

set -e

# Enable this to print commands as they are executed
#set -x


###################################################################################################
#
# Global Defines
#
###################################################################################################

export HIDAPI_REPO_HASH=d17db57b9d4354752e0af42f5f33007a42ef2906
export HIDAPI_FILENAME=hidapi-$HIDAPI_REPO_HASH.tar.gz
export HIDAPI_REPO_URL=https://github.com/signal11/hidapi.git
export LIBUSB_WIN32_VER=1.2.6.0
export LIBUSB_WIN32_FILENAME=libusb-win32-src-$LIBUSB_WIN32_VER.zip
export LIBUSB_WIN32_URL=http://downloads.sourceforge.net/project/libusb-win32/libusb-win32-releases/$LIBUSB_WIN32_VER/$LIBUSB_WIN32_FILENAME
export LIBUSB_VER=1.0.20
export LIBUSB_FILENAME=libusb-$LIBUSB_VER.tar.bz2
export LIBUSB_URL=http://downloads.sourceforge.net/project/libusb/libusb-1.0/libusb-$LIBUSB_VER/$LIBUSB_FILENAME
export LIBUSB_COMPAT_VER=0.1.5
export LIBUSB_COMPAT_FILENAME=libusb-compat-$LIBUSB_COMPAT_VER.tar.bz2
export LIBUSB_COMPAT_URL=http://downloads.sourceforge.net/project/libusb/libusb-compat-0.1/libusb-compat-$LIBUSB_COMPAT_VER/$LIBUSB_COMPAT_FILENAME
export LIBFTDI_VER=0.19
export LIBFTDI_FILENAME=libftdi-$LIBFTDI_VER.tar.gz
export LIBFTDI_URL=http://www.intra2net.com/en/developer/libftdi/download/$LIBFTDI_FILENAME
export PKG_CONFIG_WIN32_VER=0.28-1
export PKG_CONFIG_WIN32_FILENAME=pkg-config-lite-${PKG_CONFIG_WIN32_VER}_bin-win32.zip
export PKG_CONFIG_WIN32_URL=http://downloads.sourceforge.net/project/pkgconfiglite/${PKG_CONFIG_WIN32_VER}/$PKG_CONFIG_WIN32_FILENAME
#export OPENOCD_REPO_URL=http://repo.or.cz/r/openocd.git
#export OPENOCD_REPO_HASH=v0.9.0
#export OPENOCD_REPO_DIR
export OPENOCD_REPO_URL=https://github.com/Broadcom/WICED-OpenOCD.git
export OPENOCD_REPO_HASH=wiced
export OPENOCD_REPO_DIR=WICED-OpenOCD


export INSTALL_DIR=..
export DOWNLOAD_DIR=download

#export DEBUG_OPENOCD=yes

export OLDPATH=$PATH

if [ "$OSTYPE" == "msys" ]; then
    if ( pacman -V ); then
        export OSTYPE=msys2
    else
        # Must not have spaces in path when set inside MinGW for some reason
        export MSYS_WD=`(echo "/$WD" | sed -e 's/\\\\/\\//g' -e 's/://')`
        export PATH=$MSYS_WD../mingw/bin:$MSYS_WD:$MSYS_WD../../../bin/:$PATH:/c/"Program Files (x86)"/Git/cmd:/c/PROGRA~1/Git/bin/:`pwd`/libftdi-build/
        # MinGW paths are broken - prevents autoconf & aclocal from working without these
        umount /MinGW || true
        mount c:/MinGW /MinGW
        cp -r "$MSYS_WD../share/aclocal" /MinGW/share/
    fi
    export WGET=wget
    if [ "$HOSTTYPE" == "x86_64" ]; then
        export HOST_TYPE=Win64
    else
        export HOST_TYPE=Win32
    fi
elif [ "$OSTYPE" == "linux-gnu" -o "$OSTYPE" == "linux" ]; then
    export WGET=wget
    if [ "$HOSTTYPE" == "x86_64" -o "$HOSTTYPE" == "x86_64-linux" ]; then
        export HOST_TYPE=Linux64
    else
        export HOST_TYPE=Linux32
    fi
elif [[ "$OSTYPE" == *darwin* ]]; then
    export WGET="curl -L -O"
    export HOST_TYPE=OSX
else
    echo "Unknown OS $OSTYPE"
    exit -1
fi


###################################################################################################
#
# Check Prerequisites
#
###################################################################################################

print_linux_packages ()
{
    echo "";
    echo "Install all packages on Ubuntu/Mint Linux with this command:";
    echo "";
    echo "sudo apt-get install texinfo libusb-dev libtool automake binutils-dev libusb-1.0.0-dev libiberty-dev git libudev-dev g++";
    echo "";
    exit 1;
}

# Check git is installed
if ( ! ( git --version ) ); then echo "git not found! Ensure you have installed git and it is in the system path"; print_linux_packages ; fi

# Check make is installed
if ( ! ( make --version ) ); then echo "gnu make not found! Ensure you have installed make and it is in the system path"; print_linux_packages ; fi

# Check autoconf is installed
if ( ! ( autoconf --version ) ); then echo "autoconf not found! Ensure you have installed autoconf and it is in the system path"; print_linux_packages ; fi

# Check automake is installed
if ( ! ( automake --version ) ); then echo "automake not found! Ensure you have installed automake and it is in the system path"; print_linux_packages ; fi

# Check makeinfo is installed
if ( ! ( makeinfo --version ) ); then echo "makeinfo not found! Ensure you have installed the texinfo package"; print_linux_packages ; fi

# Check g++ is installed
if ( ! ( g++ --version ) ); then echo "g++ not found! Ensure you have installed the g++ package"; print_linux_packages ; fi

# Check patch is installed
if ( ! ( patch --version ) ); then echo "patch not found! Ensure you have installed the package"; print_linux_packages ; fi

# Check prerequisite packages on linux
if [ "$OSTYPE" == "linux-gnu" -o "$OSTYPE" == "linux-gnu" ]; then
    # Check libusb-dev is installed on linux
    echo "libusb-config version"
    if ( ! ( libusb-config --version ) ); then echo "libusb-config not found! Ensure you have installed the libusb-dev package"; print_linux_packages ; fi

    # Check texinf  is installed on linux
    echo "texindex version"
    if ( ! ( texindex --version ) ); then echo "texindex not found! Ensure you have installed the texinfo package"; print_linux_packages ; fi

    # Check libtool is installed on linux
    echo "libtool version"
    if ( ! ( libtool --version ) ); then echo "libtool not found! Ensure you have installed the libtool package"; print_linux_packages ; fi

    # Check automake is installed on linux
    echo "automake version"
    if ( ! ( automake --version ) ); then echo "automake not found! Ensure you have installed the automake package"; print_linux_packages ; fi

    # Check binutils-dev is installed on linux
    echo "libiberty.a existence"
    if [[ (! -e /usr/lib/libiberty.a) && (! -e /usr/lib/i386-linux-gnu/libiberty.a) && (! -e /usr/lib/x86_64-linux-gnu/libiberty.a) ]]; then echo "libiberty.a not found! Ensure you have installed the binutils-dev package"; print_linux_packages ; fi

    # Check libusb-1.0.0-dev is installed on linux
    echo "libusb 1.0 version"
    if [ ! -e /usr/include/libusb-1.0/libusb.h ]; then echo "/usr/include/libusb-1.0/libusb.h not found! Ensure you have installed the libusb-1.0.0-dev package"; print_linux_packages ; fi

    # Check libudev is installed on linux
    echo "libudev existence"
    if ( ! ( pkg-config --exists --print-errors libudev ) ); then echo "libudev not found! Ensure you have installed the libudev-dev package"; print_linux_packages ; fi


fi

# Check pkg-config is installed on OSX
if [[ "$OSTYPE" == *darwin* ]]; then
    echo "pkg-config"
    if ( ! ( pkg-config --version ) ); then echo "pkg-config not found! Ensure you have installed the pkgconfig package via macports.org:  sudo port install pkgconfig"; exit 1 ; fi

#    echo "libusb"
#    if [ ! -e /opt/local/lib/libusb-1.0.a ]; then echo "/opt/local/lib/libusb-1.0.a not found! Ensure you have installed the libusb package via macports.org:  sudo port install libusb"; exit 1 ; fi

    # Check libtool is installed on Mac
    echo "libtool version"
    if ( ! ( which libtool ) ); then echo "libtool not found! Ensure you have installed the libtool package via macports.org:  sudo port install libtool"; exit 1 ; fi
fi

# Create download directory
if [ ! -d ./$DOWNLOAD_DIR ]; then
    echo "Creating download directory"
    mkdir -p $DOWNLOAD_DIR
fi

# Check for unzip and wget on Windows
if [ "$OSTYPE" == "msys" ]; then
    echo "Installing unzip if not already installed"
    mingw-get install msys-unzip

    echo "Installing wget if not already installed"
    mingw-get install msys-wget

    # Ensure pkg-config exists on Windows
    if ( ! ( pkg-config --version ) ); then
        echo "Downloading pkg-config"
        cd $DOWNLOAD_DIR
        $WGET $PKG_CONFIG_WIN32_URL
        unzip -j -o ./$PKG_CONFIG_WIN32_FILENAME pkg-config-lite-${PKG_CONFIG_WIN32_VER}/bin/pkg-config.exe -d /bin/
        unzip -j -o ./$PKG_CONFIG_WIN32_FILENAME pkg-config-lite-${PKG_CONFIG_WIN32_VER}/share/aclocal/pkg.m4 -d /share/aclocal/
        cd ..
    fi
fi

# Check for unzip and wget on MSYS2
if [ "$OSTYPE" == "msys2" ]; then
    echo "Installing unzip if not already installed"
    pacman -Q unzip || pacman -S unzip

    echo "Installing wget if not already installed"
    pacman -Q wget || pacman -S wget

    echo "Installing pkg-config if not already installed"
    pacman -Q pkg-config || pacman -S pkg-config
fi


# Create install directory
if [ ! -d ./$INSTALL_DIR/$HOST_TYPE ]; then
    echo "Creating install directory"
    mkdir -p $INSTALL_DIR/$HOST_TYPE
fi

export PREREQUISITES_DONE=yes
