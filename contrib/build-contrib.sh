#!/usr/bin/env bash
#
# Copyright 2012 KidTsunami. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ---
#
# Author: Alexander Eichhorn <echa@kidtsunami.com>
#
# Content: build script for 3rd-party software packages

# ---------------------------------------------------------------------------
# Configuration variables
# ---------------------------------------------------------------------------
TOPDIR=`pwd`
INSTDIR=${HOME}                 # Install directory (./configure --prefix)
BUILDDIR=${TOPDIR}/build        # all software is built here
PATCHDIR=${TOPDIR}/patches      # all pre-build patches are stored here
PKGCONFDIR=${TOPDIR}/pkgconf    # pkgconf templates to install post-build
LOGFILE=${BUILDDIR}/build.log   # build logfile
ARCHIVEDIR=${TOPDIR}/archives   # downloaded archives temporary storage
DESC_SUFFIX="bdesc"             # detect build description files by suffix
MAKEOPTS="-j4"

# ---------------------------------------------------------------------------
# Architecture Handling
# ---------------------------------------------------------------------------
BUILD_SYSTEM=$(uname -s)
TARGET_SYSTEM=$(uname -s)
TARGET_ARCH=$(uname -m)

case ${TARGET_SYSTEM} in
  'Darwin')
        # detecting 32/64 bit on Darwin is tricky, we assume
        # default on 10.5 is i386 and on >10.6 x86_64
        # Darwin kernel versions
        #  10.5: 9.8.0
        #  10.6: 10.8.0
        if [ $(uname -r | cut -f1 -d.) -gt 9 ]; then
            TARGET_ARCH=x86_64
        else
            TARGET_ARCH=i386
        fi

        if [ ${TARGET_ARCH} = 'i386' ]; then
             TARGET_CPU=generic
        elif [ ${TARGET_ARCH} = 'x86_64' ]; then
             TARGET_CPU=core2
        fi
        ;;
  'Linux')
        if [ ${TARGET_ARCH} = 'x86_64' ]; then
             TARGET_CPU=core2
        else
             TARGET_CPU=generic
        fi
        ;;
   *)
        DIE 'Unsupported System ${TARGET_SYSTEM}'
        ;;
#   'Android')
#        TARGET_ARCH=arm
#        TARGET_CPU=arm # TODO
#        ;;
esac

# ---------------------------------------------------------------------------
# Default build using 'configure'
# ---------------------------------------------------------------------------
default_build() {

    # Packages downloaded with git reside in a folder named after the package
    if [ -z "$archive" ]; then
        cd "$pkgname"
    else
        cd `strip_extension $archive`
    fi

    ./configure --prefix=$INSTDIR $config_args
    make $MAKEOPTS
    make install
}

# ---------------------------------------------------------------------------
# Default Download using wget/svn/git
# ---------------------------------------------------------------------------
default_download() {

    # No need to download if the archive already exists, or it uses git
    if [ -e "$archive" -o -d "$pkgname" ]; then
        return
    fi

    if [ -z "$url" ]; then
        cp ${ARCHIVEDIR}/$archive .
        return
    fi

    case "${url%:*}" in
	http|https)
	    # Download to ${archive}.tmp and move to $archive if successful
	    wget --no-check-certificate "$url" -O "${archive}.tmp"
	    mv "${archive}.tmp" "$archive"
	    ;;
	git)
	    # clone to a temp-dir, move after it succeeds
	    git clone "$url" "${pkgname}.tmp"
	    mv "${pkgname}.tmp" "$pkgname"
	    ;;
	svn)
	    # checkout a read-only version of a subversion repo, move at success
	    svn co "$url" "${pkgname}.tmp"
	    mv "${pkgname}.tmp" "$pkgname"
	    ;;
	*)
	    # die if we can't download
	    DIE "unknown url: ${url}"
	    ;;
    esac

}

# ---------------------------------------------------------------------------
# Default Archive Unpack
# ---------------------------------------------------------------------------
default_unpack() {

    if [ -z "$archive" ]; then
        return
    fi

    case "$archive" in
	*.zip)
	    unzip -o ${archive}
	    return
	    ;;
	*.tgz)
	    unpack_args="-zxf"
	    ;;
	*.tar.gz)
	    unpack_args="-zxf"
	    ;;
	*.tar.xz)
	    unpack_args="-zxf"
	    ;;
	*.tar.bz2)
	    unpack_args="-jxf"
	    ;;
	*.dmg)
	    # works only on osx
        mountpoint=${BUILDDIR}/${archive/.dmg/}-mount
        unpackdir=${BUILDDIR}/${archive/.dmg/}
	    mkdir -p ${unpackdir}
	    hdiutil attach -mountpoint ${mountpoint} "$archive"
	    cp -Rf ${mountpoint}/* ${unpackdir}
	    hdiutil detach ${mountpoint}
	    return
	    ;;
	*)
	    DIE "Unknown archive type: $archive"
	    ;;
    esac

    tar "$unpack_args" "$archive"
}

# ---------------------------------------------------------------------------
# Display work indicator (a rotating line/slash)
# ---------------------------------------------------------------------------
work_indicator() {
    sub_pid=$!
    echo -en "$1\t "
    while ps | grep -v grep | grep $sub_pid &>/dev/null; do
	echo -en "\b-"
	sleep 0.1
	echo -en "\b\\"
	sleep 0.1
	echo -en "\b|"
	sleep 0.1
	echo -en "\b/"
	sleep 0.1
    done

    # need to set +e because wait can return with a non-zero exit code
    set +e
    wait $sub_pid
    if [ $? -eq 0 ]; then
        echo -e "\b\033[32mDone\033[0m"
    else
        echo -e "\b\033[31mFailed\033[0m"
        setfailed
        DIE "$2 error."
    fi
    unset sub_pid
    # re-enable exit on error
    set -e
}

# ---------------------------------------------------------------------------
# Reset variables for next build
# ---------------------------------------------------------------------------
reset_vars() {
    unset pkgname
    unset url
    unset config_args
    unset pkgver
    unset archive

    # unset the package-specific functions in case they were defined
    unset precond
    unset build
    unset unpack
    unset download
    unset pkgconf
}

# ---------------------------------------------------------------------------
# Builds one 3rd-party package
#
# FIXME: When catching an interrupt, make sure to kill childs too!
#
# ---------------------------------------------------------------------------

build_package() {

    resetfailed

    # source the build description
    source "$1"
    echo -e "Processing \033[1m$pkgname\033[0m"
    LOG "Processing $pkgname"

    cd $BUILDDIR

    # precondition check
    if [ $(declare -F precond) ]; then
        error_msg=""
        precond >&4 2>&4
        if [ -n "$error_msg" ]; then
          echo -e "\033[1mExcluded from build: ${error_msg}\033[0m"
          LOG "excluded from build: ${error_msg}"
          cd $TOPDIR
          reset_vars
          return
        fi
    fi

    # download or checkout the source
    if [ $(declare -F download) ]; then
        download >&4 2>&4 &
    else
        default_download >&4 2>&4 &
    fi
    work_indicator '  Downloading:' 'download'

    if $failed ; then
        cd $TOPDIR
        reset_vars
        return
    fi

    # unpack the downlaoded archive
    if [ $(declare -F unpack) ]; then
        unpack >&4 2>&4 &
    else
        default_unpack >&4 2>&4 &
    fi
    work_indicator '  Unpacking:' 'unpack'

    if $failed ; then
        cd $TOPDIR
        reset_vars
        return
    fi

    # build the package
    if [ $(declare -F build) ]; then
        build >&4 2>&4 &
    else
        default_build >&4 2>&4 &
    fi
    work_indicator '  Building:' 'build'

    if $failed ; then
        cd $TOPDIR
        reset_vars
        return
    fi

    # create pkgconfig description
    if [ $(declare -F pkgconf) ]; then
        pkgconf >&4 2>&4 &
        work_indicator '  pkgconf:' 'pkgconf'
    fi

    if $failed ; then
        cd $TOPDIR
        reset_vars
        return
    fi

    # final output statement
    echo "$pkgname has been installed"
    LOG "$pkgname installed successfully"

    cd $TOPDIR
    reset_vars
}

usage() {
    echo -e "Usage: $0 [OPTION]... [FILE]..."
    echo -e ""
    echo -e "Builds and installs 3rd-party software packages"
    echo -e "  -i install directory (default is \$HOME)"
    echo -e "  -t target system (use for cross-compiling)"
    echo -e "  -a target CPU architecture (use for cross-comiling)"
    echo -e "  -c continue building after error"
    echo -e "  -h display this help and exit"
}

# ---------------------------------------------------------------------------
# MAIN
# ---------------------------------------------------------------------------
set -e
packages=( )

# process the command-line argument list
while getopts ":dhci:t:a:" optname; do
    case "$optname" in
        i)
            INSTDIR=${OPTARG%/}
            ;;
        h)
            usage
            exit 0
            ;;
        c)
            dieatonce=false
            ;;
        t)
            TARGET_SYSTEM=${OPTARG}
            ;;
        a)
    	    TARGET_ARCH=${OPTARG}
    	    ;;
        ?)
            echo "Unknown option '-$OPTARG'"
            exit 1
            ;;
        :)
            echo "No argument value for option $OPTARG"
            ;;
        *)
            echo "No argument value for option $OPTARG"
            ;;
    esac
done

# if no arguments are given, glob all description files
if [ -z "$1" ]; then
    packages=*.${DESC_SUFFIX}
    echo "Building all packages"
else
    # else, if only options were given, and glob all files as well
    if [ $(($#+1)) -eq $OPTIND ]; then
        echo "Building all packages"
        packages=*.${DESC_SUFFIX}
    else
        # else, packages have been specified
        for p in "${@:$OPTIND}"; do
            packages+=("$p")
        done
    fi
fi

# move existing logfile out of the way
if [ -e $LOGFILE ]; then
    mv $LOGFILE ${LOGFILE/.log/.old}
fi

# create build directory if it does not exist
if [ -e $BUILDDIR -a ! -d ${BUILDDIR} ]; then
    echo 'Cannot create build directory. A file of the same name already exists.'
    exit 1
else
    mkdir -p ${BUILDDIR} 2> /dev/null
fi

# load common functions and create log file (important: after creating builddir)
source ${TOPDIR}/common.sh
LOG "${ME} ${CMDLINE}"

# create target (install) pkgconf directory if it does not exist
if [ ! -d ${INSTDIR}/lib/pkgconfig ]; then
    LOG "$(mkdir -p ${INSTDIR}/lib/pkgconfig)"
fi

echo "Building on   ${BUILD_SYSTEM}"
echo "Target is     ${TARGET_SYSTEM}_${TARGET_ARCH}"
echo "Installing to ${INSTDIR}"

LOG "Building on ${BUILD_SYSTEM}"
LOG "Target is ${TARGET_SYSTEM}_${TARGET_ARCH}"
LOG "Installing to ${INSTDIR}"

export PATH=${INSTDIR}/bin:$PATH
export LD_LIBRARY_PATH=${INSTDIR}/lib:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=${INSTDIR}/lib/pkgconfig:$PKG_CONFIG_PATH

# run the script on these arguments
for package in ${packages[@]}; do
    build_package "$package"
done

if $failedonce ; then
    echo -e "\b\033[31mSome packages failed!\033[0m"
    LOG "${ME} some packages failed"
    exit 1
else
    echo "All packages built successfully."
    LOG "${ME} finished successfully"
    exit 0
fi
