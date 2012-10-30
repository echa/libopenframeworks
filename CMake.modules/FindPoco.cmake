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

# Find Poco Library
#
# Defines:
#  POCO_FOUND        - system has Poco
#  POCO_INCLUDE_DIRS - the Poco include directories
#  POCO_LIBRARY_DIRS - library dirs
#  POCO_LIBRARIES    - link these to use Poco
#  POCO_CFLAGS       - compiler flags
#  POCO_LDFLAGS      - linker flags
#
#

include(FindPkgConfig)

if (NOT Poco_FIND_QUIETLY)
    message (STATUS "Checking for PocoFoundation...")
endif ()

pkg_check_modules(POCO_PC QUIET poco)

if (POCO_PC_FOUND)
    set (POCO_LIBRARY_DIRS ${POCO_PC_LIBRARY_DIRS})
    set (POCO_INCLUDE_DIRS ${POCO_PC_INCLUDE_DIRS})

    # version
    if (POCO_PC_VERSION)
        SET(POCO_VERSION ${POCO_PC_VERSION})
    else ()
        FIND_FILE(P_VERSION_FILE Version.h ${POCO_INCLUDE_DIRS} NO_DEFAULT_PATH)
        FILE(STRINGS ${P_VERSION_FILE} P_VSTR REGEX ".*define POCO_VERSION.*")
        STRING(REGEX REPLACE ".*[^0-9]([0-9]*).*" "\\1" P_V "${P_VSTR}")
        MATH ( EXPR P_MAJ "${P_V} / 1000000")
        MATH ( EXPR P_MIN "(${P_V} - ${P_MAJ} * 1000000) / 10000")
        MATH ( EXPR P_REV "(${P_V} - ${P_MAJ} * 1000000 - ${P_MIN} * 10000) / 100")
        MATH ( EXPR P_PAT "${P_V} % 100")
        SET (POCO_VERSION "${P_MAJ}.${P_MIN}.${P_REV}p${P_PAT}")
    endif ()

    if (BUILD_SHARED_LIBS)
        SET (POCO_LIBRARIES ${POCO_PC_LIBRARIES})
    else ()
        set (POCO_LIBRARIES ${POCO_PC_STATIC_LIBRARIES})
    endif ()

    set (POCO_LDFLAGS ${POCO_PC_LDFLAGS_OTHER})
    set (POCO_CFLAGS ${POCO_PC_CFLAGS_OTHER})

    if (NOT Poco_FIND_QUIETLY)
        message(STATUS "  Poco found version: ${POCO_VERSION}")
        message(STATUS "    includes:  ${POCO_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${POCO_CFLAGS}")
        message(STATUS "    libraries: ${POCO_LIBRARIES}")
        message(STATUS "    libdirs:   ${POCO_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${POCO_LDFLAGS}")
    endif ()
    set (POCO_FOUND true)
else ()
    set (POCO_FOUND FALSE)
    if (Poco_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find Poco.")
    endif()
endif ()

