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

# - Try to find MPG123
# Once done, this will define
#
#  MPG123_FOUND - system has MPG123 dev libs
#  MPG123_INCLUDE_DIRS - the include directory
#  MPG123_LIBRARIES - libraries to link
#  MPG123_LIBRARY_DIRS - libraries directories
#  MPG123_CFLAGS - compile flags
#  MPG123_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT MPG123_FIND_QUIETLY)
    if (MPG123_FIND_VERSION)
        message (STATUS "Checking for MPG123 (>= ${MPG123_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for MPG123...")
    endif()
endif ()


if (MPG123_FIND_VERSION)
    pkg_check_modules(MPG123_PC QUIET libmpg123>=${MPG123_FIND_VERSION})
else ()
    pkg_check_modules(MPG123_PC QUIET libmpg123)
endif()


if (MPG123_PC_FOUND)
    set (MPG123_LIBRARY_DIRS ${MPG123_PC_LIBRARY_DIRS})
    set (MPG123_INCLUDE_DIRS ${MPG123_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (MPG123_LIBRARIES ${MPG123_PC_LIBRARIES})
    else ()
        set (MPG123_LIBRARIES ${MPG123_PC_STATIC_LIBRARIES})
    endif ()

    set (MPG123_LDFLAGS ${MPG123_PC_LDFLAGS_OTHER})
    set (MPG123_CFLAGS ${MPG123_PC_CFLAGS_OTHER})
    set (MPG123_VERSION ${MPG123_PC_VERSION})

    if (NOT MPG123_FIND_QUIETLY)
        message(STATUS "  found MPG123, version ${MPG123_VERSION}")
        message(STATUS "    includes:  ${MPG123_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${MPG123_CFLAGS}")
        message(STATUS "    libraries: ${MPG123_LIBRARIES}")
        message(STATUS "    libdirs:   ${MPG123_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${MPG123_LDFLAGS}")
    endif ()
    set (MPG123_FOUND true)
else ()
    set (MPG123_FOUND FALSE)
    if (MPG123_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find mpg123.")
    endif()
endif ()
