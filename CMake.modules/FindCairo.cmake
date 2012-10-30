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

# - Try to find Cairo
# Once done, this will define
#
#  CAIRO_FOUND - system has Cairo dev libs
#  CAIRO_INCLUDE_DIRS - the include directory
#  CAIRO_LIBRARIES - libraries to link
#  CAIRO_LIBRARY_DIRS - libraries directories
#  CAIRO_CFLAGS - compile flags
#  CAIRO_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT Cairo_FIND_QUIETLY)
    if (Cairo_FIND_VERSION)
        message (STATUS "Checking for Cairo (>= ${Cairo_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for Cairo...")
    endif()
endif ()


if (Cairo_FIND_VERSION)
    pkg_check_modules(Cairo_PC QUIET cairo>=${Cairo_FIND_VERSION})
else ()
    pkg_check_modules(Cairo_PC QUIET cairo)
endif()


if (Cairo_PC_FOUND)
    set (CAIRO_LIBRARY_DIRS ${Cairo_PC_LIBRARY_DIRS})
    set (CAIRO_INCLUDE_DIRS ${Cairo_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (CAIRO_LIBRARIES ${Cairo_PC_LIBRARIES})
    else ()
        set (CAIRO_LIBRARIES ${Cairo_PC_STATIC_LIBRARIES})
    endif ()

    set (CAIRO_LDFLAGS ${Cairo_PC_LDFLAGS_OTHER})
    set (CAIRO_CFLAGS ${Cairo_PC_CFLAGS_OTHER})
    set (CAIRO_VERSION ${Cairo_PC_VERSION})

    if (NOT Cairo_FIND_QUIETLY)
        message(STATUS "  Cairo found version: ${CAIRO_VERSION}")
        message(STATUS "    includes:  ${CAIRO_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${CAIRO_CFLAGS}")
        message(STATUS "    libraries: ${CAIRO_LIBRARIES}")
        message(STATUS "    libdirs:   ${CAIRO_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${CAIRO_LDFLAGS}")
    endif ()
    set (CAIRO_FOUND true)
else ()
    set (CAIRO_FOUND FALSE)
    if (Cairo_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find Cairo.")
    endif()
endif ()

