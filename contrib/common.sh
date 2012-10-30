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
# Content: common BASH scripting functions
# Usage:  use 'source common.sh' to use this file in your scripts

CMDLINE=$@
ME=`basename $0`
FAILEDFLAG=".failed-${ME}-$$"

if [ -z "${TOPDIR}" ]; then
    TOPDIR=`pwd`
fi

if [ -z "${LOGFILE}" ]; then
    LOGFILE=${ME}-$$.log
fi

function strip_extension() {
    tmp="$1"
    tmp="${tmp%*.tar.gz}"
    tmp="${tmp%*.tar.bz2}"
    tmp="${tmp%*.tgz}"
    echo $tmp
    unset tmp
}

function LOG()
{
    if [ -n "${1}" ]; then
        logstr=$1
        echo -e "$(DATE)  ${logstr//$'\n'/\n$(DATE)  }" >&3
    fi
}

logstream() {
    while read l; do
        LOG "$l"
    done
}

setuplogstream() {
    npipe=/tmp/$$.tmp
    TEMPFILES+=( "$npipe" )
    mkfifo $npipe
    $(logstream <$npipe) &
    exec 4>$npipe
}


function DATE()
{
    date "+%b %d %H:%m:%S"
}

function DIE()
{
    reason="$@"
    ERRHANDLER ${reason:-"unknown error"}
    if $dieatonce ; then
        LOG "Aborting $ME: ${reason:-"unknown error"}"
        exit 1
    fi
}

function ERRHANDLER()
{
    echo "$@"
}

function SIGHANDLER()
{
#    if [ ! -z $sub_pid ]; then
#        kill $sub_pid &> /dev/null
#    fi
    echo "$(DATE)  Catched Signal"
    LOG "Aborting $ME after signal"
    exit 2
#    kill $(jobs -p)
#    echo "$(DATE)  Children terminatedj"
}

function RUN()
{
    rm -f $FAILEDFLAG
    echo "$(DATE)  \$ ${@}" >&3
    ( $@ || touch $FAILEDFLAG ) 2>&1 | tee -a $LOGFILE
    if [ -e $FAILEDFLAG ]; then
	    rm -f $FAILEDFLAG
    	DIE
    fi
}

function checkfile()
{
    if [ -z ${2} ]; then
	CMD="-e"
    else
	CMD=${2}
    fi
    if [ ! ${CMD} ${1} ]; then
	echo "Error: file ${1} does not exist (${CMD})."
	exit 1
    fi
}

function PRE_EXIT()
{
    rm -f $FAILEDFLAG
    if [ $(declare -F cleanup) ]; then
    	cleanup
    fi
    cd ${TOPDIR}
}


# ---------------------------------------------------------------------------
# ERROR HANDLING
# ---------------------------------------------------------------------------
failed=false
failedonce=false

if [ ! -n "$dieatonce" ]; then
    dieatonce=true
fi

setfailed() {
    failed=true       # true
    failedonce=true   # true
}

resetfailed() {
    failed=false       # false
}

# exit on error
set -e

trap ERRHANDLER ERR
trap SIGHANDLER SIGINT SIGKILL
trap PRE_EXIT EXIT


cleanup() {
    # delete all temp files
    for filename in ${TEMPFILES[@]}; do
        rm -rf "$filename"
    done
}

# ---------------------------------------------------------------------------
# REDIRECTIONS
# ---------------------------------------------------------------------------

# redirect all logging to FD3 into logfile
exec 3>>$LOGFILE

# create logging pipe using FD4
setuplogstream

# if stdout is not a terminal, redirect FD1 to null
if test ! -t 1; then
    echo "See logfile $LOGFILE for output."
    exec 1> /dev/null
fi
