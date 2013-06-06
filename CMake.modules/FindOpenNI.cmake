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

# - Try to find OPENNI
#
#  OPENNI_FOUND - system has Unicap
#  OPENNI_INCLUDE_DIRS - the Unicap include directories
#  OPENNI_LIBRARIES - link these to use Unicap
#  OPENNI_LIBRARY_DIRS - libraries directories
#  OPENNI_CFLAGS - Unicap compile flags
#  OPENNI_LDFLAGS - Unicap linker flags

include(FindPkgConfig)

if (NOT OPENNI_FIND_QUIETLY)
    message (STATUS "Checking for OpenNI...")
endif ()

pkg_check_modules(OPENNI_PC QUIET openni)

if (OPENNI_PC_FOUND)
    set (OPENNI_LIBRARY_DIRS ${OPENNI_PC_LIBRARY_DIRS})
    set (OPENNI_INCLUDE_DIRS ${OPENNI_PC_INCLUDE_DIRS})
    if (BUILD_SHARED_LIBS)
        set (OPENNI_LIBRARIES ${OPENNI_PC_LIBRARIES})
    else ()
        set (OPENNI_LIBRARIES ${OPENNI_PC_STATIC_LIBRARIES})
    endif ()
    set (OPENNI_LDFLAGS ${OPENNI_PC_LDFLAGS_OTHER})
    set (OPENNI_CFLAGS ${OPENNI_PC_CFLAGS_OTHER})
    set (OPENNI_VERSION ${OPENNI_PC_VERSION})

    if (NOT OPENNI_FIND_QUIETLY)
        message(STATUS "  OpenNI found version: ${OPENNI_VERSION}")
        message(STATUS "    includes:  ${OPENNI_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${OPENNI_CFLAGS}")
        message(STATUS "    libraries: ${OPENNI_LIBRARIES}")
        message(STATUS "    libdirs:   ${OPENNI_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${OPENNI_LDFLAGS}")
    endif ()

    set (OPENNI_FOUND true)
else ()
    set (OPENNI_FOUND false)
    if (OPENNI_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find OpenNI.")
    endif()
endif ()

