#!/bin/bash
#
# oFdiff outputs a diff between the original openFrameworks GIT rep
# and the KidTsunami CMake version of oF

if [ $# -lt 2 ]; then
  echo "Usage: $0 <original-repo> <kidtsunami-repo>"
  exit 1
fi

OF_GIT_DIR=${1}/libs/openFrameworks
OF_NL_DIR=${2}/openframeworks

OF_SUBDIRS="3d app communication events gl graphics math sound types utils video ofMain.h"

for SUBDIR in ${OF_SUBDIRS}; do
  diff -Naur  ${OF_NL_DIR}/${SUBDIR} ${OF_GIT_DIR}/${SUBDIR}
  read -n 1 -s -p "Press key to continue..."
done;