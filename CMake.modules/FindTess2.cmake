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

# - Try to find TESS2
# Once done, this will define
#
#  TESS2_FOUND - system has TESS2 dev libs
#  TESS2_INCLUDE_DIRS - the include directory
#  TESS2_LIBRARIES - libraries to link
#  TESS2_LIBRARY_DIRS - libraries directories
#  TESS2_CFLAGS - compile flags
#  TESS2_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT Tess2_FIND_QUIETLY)
    if (Tess2_FIND_VERSION)
        message (STATUS "Checking for Tess2 (>= ${Tess2_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for Tess2...")
    endif()
endif ()


if (Tess2_FIND_VERSION)
    pkg_check_modules(TESS2_PC QUIET tess2>=${Tess2_FIND_VERSION})
else ()
    pkg_check_modules(TESS2_PC QUIET tess2)
endif()


if (TESS2_PC_FOUND)
    set (TESS2_LIBRARY_DIRS ${TESS2_PC_LIBRARY_DIRS})
    set (TESS2_INCLUDE_DIRS ${TESS2_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (TESS2_LIBRARIES ${TESS2_PC_LIBRARIES})
    else ()
        set (TESS2_LIBRARIES ${TESS2_PC_STATIC_LIBRARIES})
    endif ()

    set (TESS2_LDFLAGS ${TESS2_PC_LDFLAGS_OTHER})
    set (TESS2_CFLAGS ${TESS2_PC_CFLAGS_OTHER})
    set (TESS2_VERSION ${TESS2_PC_VERSION})

    if (NOT Tess2_FIND_QUIETLY)
        message(STATUS "  Tess2 found version: ${TESS2_VERSION}")
        message(STATUS "    includes:  ${TESS2_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${TESS2_CFLAGS}")
        message(STATUS "    libraries: ${TESS2_LIBRARIES}")
        message(STATUS "    libdirs:   ${TESS2_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${TESS2_LDFLAGS}")
    endif ()
    set (TESS2_FOUND true)
else ()
    set (TESS2_FOUND FALSE)
    if (Tess2_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find libtess2.")
    endif()
endif ()

