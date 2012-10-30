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

# - Try to find Kiss
# Once done, this will define
#
#  Kiss_FOUND - system has Kiss dev libs
#  Kiss_INCLUDE_DIRS - the include directory
#  Kiss_LIBRARIES - libraries to link
#  Kiss_LIBRARY_DIRS - libraries directories
#  Kiss_CFLAGS - compile flags
#  Kiss_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT Kiss_FIND_QUIETLY)
    if (Kiss_FIND_VERSION)
        message (STATUS "Checking for Kiss (>= ${Kiss_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for Kiss...")
    endif()
endif ()


if (Kiss_FIND_VERSION)
    pkg_check_modules(Kiss_PC QUIET kiss>=${Kiss_FIND_VERSION})
else ()
    pkg_check_modules(Kiss_PC QUIET kiss)
endif()


if (Kiss_PC_FOUND)
    set (KISS_LIBRARY_DIRS ${Kiss_PC_LIBRARY_DIRS})
    set (KISS_INCLUDE_DIRS ${Kiss_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (KISS_LIBRARIES ${Kiss_PC_LIBRARIES})
    else ()
        set (KISS_LIBRARIES ${Kiss_PC_STATIC_LIBRARIES})
    endif ()

    set (KISS_LDFLAGS ${Kiss_PC_LDFLAGS_OTHER})
    set (KISS_CFLAGS ${Kiss_PC_CFLAGS_OTHER})
    set (KISS_VERSION ${Kiss_PC_VERSION})

    if (NOT Kiss_FIND_QUIETLY)
        message(STATUS "  Kiss found version: ${KISS_VERSION}")
        message(STATUS "    includes:  ${KISS_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${KISS_CFLAGS}")
        message(STATUS "    libraries: ${KISS_LIBRARIES}")
        message(STATUS "    libdirs:   ${KISS_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${KISS_LDFLAGS}")
    endif ()
    set (KISS_FOUND true)
else ()
    set (KISS_FOUND FALSE)
    if (Kiss_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find libkiss.")
    endif()
endif ()

