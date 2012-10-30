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

# - Try to find ALSA2
# Once done, this will define
#
#  ALSA_FOUND - system has ALSA
#  ALSA_INCLUDE_DIRS - the ALSA include directories
#  ALSA_LIBRARIES - link these to use ALSA
#  ALSA_LIBRARY_DIRS
#  ALSA_LDFLAGS
#  ALSA_CFLAGS

include(FindPkgConfig)

if (NOT ALSA_FIND_QUIETLY)
    message (STATUS "Checking for ALSA...")
endif ()

pkg_check_modules(ALSA_PC QUIET alsa)

if (ALSA_PC_FOUND)
    set (ALSA_LIBRARY_DIRS ${ALSA_PC_LIBRARY_DIRS})
    set (ALSA_INCLUDE_DIRS ${ALSA_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (ALSA_LIBRARIES ${ALSA_PC_LIBRARIES})
    else ()
        set (ALSA_LIBRARIES ${ALSA_PC_STATIC_LIBRARIES})
    endif ()

    set (ALSA_LDFLAGS ${ALSA_PC_LDFLAGS_OTHER})
    set (ALSA_CFLAGS ${ALSA_PC_CFLAGS_OTHER})
    set (ALSA_VERSION ${ALSA_PC_VERSION})

    if (NOT ALSA_FIND_QUIETLY)
        message(STATUS "  ALSA found version: ${ALSA_VERSION}")
        message(STATUS "    includes:  ${ALSA_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${ALSA_CFLAGS}")
        message(STATUS "    libraries: ${ALSA_LIBRARIES}")
        message(STATUS "    libdirs:   ${ALSA_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${ALSA_LDFLAGS}")
    endif ()
    set (ALSA_FOUND true)
else ()
    set (ALSA_FOUND FALSE)
    if (ALSA_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find ALSA.")
    endif()
endif ()

