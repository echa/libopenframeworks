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

# - Try to find GLee
#
#  GLEE_FOUND - system has Unicap
#  GLEE_INCLUDE_DIRS - the Unicap include directories
#  GLEE_LIBRARIES - link these to use Unicap
#  GLEE_LIBRARY_DIRS - libraries directories
#  GLEE_CFLAGS - Unicap compile flags
#  GLEE_LDFLAGS - Unicap linker flags

include(FindPkgConfig)

if (NOT GLee_FIND_QUIETLY)
    message (STATUS "Checking for GLee...")
endif ()

pkg_check_modules(GLEE_PC QUIET glee)

if (GLEE_PC_FOUND)
    set (GLEE_LIBRARY_DIRS ${GLEE_PC_LIBRARY_DIRS})
    set (GLEE_INCLUDE_DIRS ${GLEE_PC_INCLUDE_DIRS})
    if (BUILD_SHARED_LIBS)
        set (GLEE_LIBRARIES ${GLEE_PC_LIBRARIES})
    else ()
        set (GLEE_LIBRARIES ${GLEE_PC_STATIC_LIBRARIES})
    endif ()
    set (GLEE_LDFLAGS ${GLEE_PC_LDFLAGS_OTHER})
    set (GLEE_CFLAGS ${GLEE_PC_CFLAGS_OTHER})
    set (GLEE_VERSION ${GLEE_PC_VERSION})

    if (NOT GLee_FIND_QUIETLY)
        message(STATUS "  GLee found version: ${GLEE_VERSION}")
        message(STATUS "    includes:  ${GLEE_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${GLEE_CFLAGS}")
        message(STATUS "    libraries: ${GLEE_LIBRARIES}")
        message(STATUS "    libdirs:   ${GLEE_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${GLEE_LDFLAGS}")
    endif ()

    set (GLEE_FOUND true)
else ()
    set (GLEE_FOUND false)
    if (GLee_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find GLee.")
    endif()
endif ()

