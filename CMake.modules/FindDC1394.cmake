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

# Once done this will define
#
#  DC1394_FOUND - system has DC1394
#  DC1394_INCLUDE_DIRS - the DC1394 include directory
#  DC1394_LIBRARIES - the libraries needed to use DC1394
#  DC1394_LIBRARY_DIRS - libraries directories
#  DC1394_CFLAGS - compile flags
#  DC1394_LDFLAGS - linker flags

include(FindPkgConfig)


if (NOT DC1394_FIND_QUIETLY)
    message (STATUS "Checking for 1394 libraries...")
endif ()

pkg_check_modules(DC1394_PC QUIET libdc1394-2)
pkg_check_modules(RAW1394_PC QUIET libraw1394)


if (DC1394_PC_FOUND AND RAW1394_PC_FOUND)
    set (DC1394_LIBRARY_DIRS ${DC1394_PC_LIBRARY_DIRS} ${DC1394_PC_LIBDIR}
        ${RAW1394_PC_LIBRARY_DIRS} ${RAW1394_PC_LIBDIR})
    set (DC1394_INCLUDE_DIRS ${DC1394_PC_INCLUDE_DIRS} ${DC1394_PC_INCLUDEDIR}
        ${RAW1394_PC_INCLUDE_DIRS} ${RAW1394_PC_INCLUDEDIR})

    if (BUILD_SHARED_LIBS)
        set (DC1394_LIBRARIES ${DC1394_PC_LIBRARIES} ${RAW1394_PC_LIBRARIES})
    else ()
        set (DC1394_LIBRARIES ${DC1394_PC_STATIC_LIBRARIES}
            ${RAW1394_PC_STATIC_LIBRARIES})
    endif ()

    set (DC1394_LDFLAGS ${RAW1394_PC_LDFLAGS_OTHER})
    set (DC1394_CFLAGS ${RAW1394_PC_CFLAGS_OTHER})

    if (NOT DC1394_FIND_QUIETLY)
        message(STATUS "  1394 found versions: dc1394 ${DC1394_PC_VERSION},  raw1394 ${RAW1394_PC_VERSION}")
        message(STATUS "    includes:  ${DC1394_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${DC1394_CFLAGS}")
        message(STATUS "    libraries: ${DC1394_LIBRARIES}")
        message(STATUS "    libdirs:   ${DC1394_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${DC1394_LDFLAGS}")

    endif ()
    set (DC1394_FOUND true)
else ()
    set (DC1394_FOUND FALSE)
    if (DC1394_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find 1394 libs.")
    endif()
endif ()




