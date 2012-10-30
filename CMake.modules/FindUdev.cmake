#############################################################################
# KidTsunami - Professional. Live. Video.
#
# File:     CMakeLists.txt
# Author:   Alexander Eichhorn <echa@kidtsunami.com>
# Contents: CMake Find Module
#
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
#############################################################################

# - Try to find libudev
# Once done, this will define
#
#  UDEV_FOUND - system has libudev
#  UDEV_INCLUDE_DIRS - the include directory
#  UDEV_LIBRARIES - libraries to link
#  UDEV_LIBRARY_DIRS - libraries directories
#  UDEV_CFLAGS - compile flags
#  UDEV_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT Udev_FIND_QUIETLY)
    if (Udev_FIND_VERSION)
        message (STATUS "Checking for libudev (>= ${Udev_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for libudev...")
    endif()
endif ()

if (UDEV_FIND_VERSION)
    pkg_check_modules(UDEV_PC QUIET libudev>=${Udev_FIND_VERSION})
else ()
    pkg_check_modules(UDEV_PC QUIET libudev)
endif()

if (UDEV_PC_FOUND)
    set (UDEV_LIBRARY_DIRS ${UDEV_PC_LIBRARY_DIRS})
    set (UDEV_INCLUDE_DIRS ${UDEV_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (UDEV_LIBRARIES ${UDEV_PC_LIBRARIES})
    else ()
        set (UDEV_LIBRARIES ${UDEV_PC_STATIC_LIBRARIES})
    endif ()

    set (UDEV_LDFLAGS ${UDEV_PC_LDFLAGS_OTHER})
    set (UDEV_CFLAGS ${UDEV_PC_CFLAGS_OTHER})
    set (UDEV_VERSION ${UDEV_PC_VERSION})

    if (NOT Udev_FIND_QUIETLY)
        message(STATUS "  Udev found version: ${UDEV_VERSION}")
        message(STATUS "    includes:  ${UDEV_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${UDEV_CFLAGS}")
        message(STATUS "    libraries: ${UDEV_LIBRARIES}")
        message(STATUS "    libdirs:   ${UDEV_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${UDEV_LDFLAGS}")
    endif ()
    set (UDEV_FOUND true)
else ()
    set (UDEV_FOUND FALSE)
    if (Udev_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find udev.")
    endif()
endif ()

