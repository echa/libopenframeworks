#############################################################################
# KidTsunami - Professional. Live. Video.
#
# File:     CMakeLists.txt
# Author:   Alexander Eichhorn <echa@kidtsunami.com>
# Contents: CMake Find Module for libOpenFrameworks
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

# This module defines
#
#  OF_FOUND         - defined if libOpenFramworks was found
#  OF_VERSION       - OpenFrameworks version
#  OF_INCLUDE_DIRS  - include directories
#  OF_LIBRARIES     - link against these libs to use OF
#  OF_LIBRARY_DIRS  - include these directories into the libraries search path
#  OF_CFLAGS        - extra OF compile flags
#  OF_LDFLAGS       - extra OF linker flags
#  OF_FRAMEWORKS    - list of frameworks to link (on OSX only)

include(FindPkgConfig)

if (NOT OF_FIND_QUIETLY)
  if (OF_FIND_VERSION)
    message (STATUS "Checking for libOpenFramrworks (>= ${OF_FIND_VERSION})...")
  else ()
    message (STATUS "Checking for libOpenFramrworks...")
  endif()
endif ()


# determine build type
if (CMAKE_BUILD_TYPE STREQUAL "debug")
    set(OF_POSTFIX ${CMAKE_RELEASE_POSTFIX})
elseif (CMAKE_BUILD_TYPE STREQUAL "release")
    set(OF_POSTFIX ${CMAKE_DEBUG_POSTFIX})
else ()
    set(OF_POSTFIX)
endif ()

if (OF_FIND_VERSION)
    pkg_check_modules(OF_PC QUIET
                      openframeworks${OF_POSTFIX}>=${OpenCV_FIND_VERSION})
else ()
    pkg_check_modules(OF_PC QUIET openframeworks${OF_POSTFIX})
endif()

if (OF_PC_FOUND)
    set (OF_LIBRARY_DIRS ${OF_PC_LIBRARY_DIRS})
    set (OF_INCLUDES ${OF_PC_INCLUDE_DIRS})
    if (BUILD_SHARED_LIBS)
        set (OF_LIBRARIES ${OF_PC_LIBRARIES})
    else ()
        set (OF_LIBRARIES ${OF_PC_STATIC_LIBRARIES})
    endif ()

    #message(STATUS "  OF_PC_LIBRARY_DIRS: ${OF_PC_LIBRARY_DIRS}")
    #message(STATUS "  OF_PC_INCLUDE_DIRS: ${OF_PC_INCLUDE_DIRS}")
    #message(STATUS "  OF_PC_LIBRARIES: ${OF_PC_LIBRARIES}")
    #message(STATUS "  OF_PC_STATIC_LIBRARIES: ${OF_PC_STATIC_LIBRARIES}")
    #message(STATUS "  OF_PC_LDFLAGS_OTHER: ${OF_PC_LDFLAGS_OTHER}")
    #message(STATUS "  OF_PC_LDFLAGS: ${OF_PC_LDFLAGS}")
    #message(STATUS "  OF_PC_CFLAGS: ${OF_PC_CFLAGS}")
    #message(STATUS "  OF_PC_CFLAGS_OTHER: ${OF_PC_CFLAGS_OTHER}")
    #message(STATUS "  OF_PC_VERSION: ${OF_PC_VERSION}")

    # on OSX put '-framework' entries into OF_LDFLAGS and OF_FRAMEWORKS
    #
    if (APPLE)
        set(_ALL_LIBS ${OF_LIBRARIES} ${OF_PC_LDFLAGS_OTHER} ${OF_PC_LDFLAGS})
        foreach(L ${_ALL_LIBS})
            if ("${L}" MATCHES "^-framework.*")
                list(APPEND OF_DARWIN_FRAMEWORKS ${L})
            else ()
                list(APPEND OF_DARWIN_LIBRARIES ${L})
            endif()
        endforeach()
        set (OF_LIBRARIES ${OF_DARWIN_LIBRARIES})
        set (OF_LDFLAGS ${OF_DARWIN_LDFLAGS})
        set (OF_FRAMEWORKS ${OF_DARWIN_FRAMEWORKS})
    else ()
        set (OF_LIBRARIES ${OF_LIBRARIES} ${OF_PC_LDFLAGS_OTHER})
        set (OF_LDFLAGS "")
    endif()
    set (OF_CFLAGS ${OF_PC_CFLAGS_OTHER})
    set (OF_VERSION ${OF_PC_VERSION})

    if (NOT OF_FIND_QUIETLY)
        message(STATUS "  libOpenFrameworks found version: ${OF_VERSION}")
        message(STATUS "    includes:   ${OF_INCLUDES}")
        message(STATUS "    cflags:     ${OF_CFLAGS}")
        message(STATUS "    libraries:  ${OF_LIBRARIES}")
        message(STATUS "    libdirs:    ${OF_LIBRARY_DIRS}")
        message(STATUS "    ldflags:    ${OF_LDFLAGS}")
        if (APPLE)
        message(STATUS "    frameworks: ${OF_FRAMEWORKS}")
        endif ()
    endif ()
    set (OF_FOUND TRUE)
else ()
    set (OF_FOUND FALSE)
    set (OF_VERSION)
    set (OF_INCLUDES)
    set (OF_LIBRARIES)
    set (OF_LIBRARY_DIRS)
    set (OF_CFLAGS)
    set (OF_LDFLAGS)
    set (OF_FRAMEWORKS)

    if (OF_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find libOpenFrameworks.")
    endif()
endif ()

mark_as_advanced (
    OF_FOUND
    OF_VERSION
    OF_INCLUDES
    OF_LIBRARIES
    OF_LIBRARY_DIRS
    OF_CFLAGS
    OF_LDFLAGS
    OF_FRAMEWORKS
)

