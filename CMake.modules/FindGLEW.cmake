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

# - Try to find libGLEW
# Once done, this will define
#
#  GLEW_FOUND - system has libGLEW-client-dev
#  GLEW_INCLUDE_DIRS - the include directory
#  GLEW_LIBRARIES - libraries to link
#  GLEW_LIBRARY_DIRS - libraries directories
#  GLEW_CFLAGS - compile flags
#  GLEW_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT GLEW_FIND_QUIETLY)
    if (GLEW_FIND_VERSION)
        message (STATUS "Checking for GLEW (>= ${GLEW_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for GLEW...")
    endif()
endif ()


if (GLEW_FIND_VERSION)
    pkg_check_modules(GLEW_PC QUIET glew>=${GLEW_FIND_VERSION})
else ()
    pkg_check_modules(GLEW_PC QUIET glew)
endif()


if (GLEW_PC_FOUND)
    set (GLEW_LIBRARY_DIRS ${GLEW_PC_LIBRARY_DIRS})
    set (GLEW_INCLUDE_DIRS ${GLEW_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (GLEW_LIBRARIES ${GLEW_PC_LIBRARIES})
    else ()
        set (GLEW_LIBRARIES ${GLEW_PC_STATIC_LIBRARIES})
    endif ()

    set (GLEW_LDFLAGS ${GLEW_PC_LDFLAGS_OTHER})
    set (GLEW_CFLAGS ${GLEW_PC_CFLAGS_OTHER})
    set (GLEW_VERSION ${GLEW_PC_VERSION})

    if (NOT GLEW_FIND_QUIETLY)
        message(STATUS "  GLEW found version: ${GLEW_VERSION}")
        message(STATUS "    includes:  ${GLEW_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${GLEW_CFLAGS}")
        message(STATUS "    libraries: ${GLEW_LIBRARIES}")
        message(STATUS "    libdirs:   ${GLEW_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${GLEW_LDFLAGS}")
    endif ()
    set (GLEW_FOUND true)
else ()
    set (GLEW_FOUND FALSE)
    if (GLEW_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find GLEW.")
    endif()
endif ()
