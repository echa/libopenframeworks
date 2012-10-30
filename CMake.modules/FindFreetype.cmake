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

# - Try to find Freetype2
# Once done, this will define
#
#  FREETYPE_FOUND - system has Freetype
#  FREETYPE_INCLUDE_DIRS - the Freetype include directories
#  FREETYPE_LIBRARIES - link these to use Freetype
#  FREETYPE_LINK_DIRECTORIES

include(FindPkgConfig)

if (NOT Freetype_FIND_QUIETLY)
    message (STATUS "Checking for Freetype...")
endif ()

pkg_check_modules(FT_PC QUIET freetype2)

if (FT_PC_FOUND)
    set (FREETYPE_LIBRARY_DIRS ${FT_PC_LIBRARY_DIRS})
    set (FREETYPE_INCLUDE_DIRS ${FT_PC_INCLUDE_DIRS})
    if (BUILD_SHARED_LIBS)
        set (FREETYPE_LIBRARIES ${FT_PC_LIBRARIES})
    else ()
        set (FREETYPE_LIBRARIES ${FT_PC_STATIC_LIBRARIES})
    endif ()
    set (FREETYPE_LDFLAGS ${FT_PC_LDFLAGS_OTHER})
    set (FREETYPE_CFLAGS ${FT_PC_CFLAGS_OTHER})
    set (FREETYPE_VERSION ${FT_PC_VERSION})

    if (NOT Freetype_FIND_QUIETLY)
        message(STATUS "  Freetype found version: ${FREETYPE_VERSION}")
        message(STATUS "    includes:  ${FREETYPE_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${FREETYPE_CFLAGS}")
        message(STATUS "    libraries: ${FREETYPE_LIBRARIES}")
        message(STATUS "    libdirs:   ${FREETYPE_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${FREETYPE_LDFLAGS}")
    endif ()
    set (FREETYPE_FOUND true)
else ()
    set (FREETYPE_FOUND FALSE)
    if (Freetype_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find freetype.")
    endif()
endif ()


