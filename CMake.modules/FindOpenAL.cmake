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

# - Try to find OpenAL
# Once done, this will define
#
#  OpenAL_FOUND - system has OpenAL dev libs
#  OpenAL_INCLUDE_DIRS - the include directory
#  OpenAL_LIBRARIES - libraries to link
#  OpenAL_LIBRARY_DIRS - libraries directories
#  OpenAL_CFLAGS - compile flags
#  OpenAL_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT OpenAL_FIND_QUIETLY)
    if (OpenAL_FIND_VERSION)
        message (STATUS "Checking for OpenAL (>= ${OpenAL_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for OpenAL...")
    endif()
endif ()

if (APPLE)
    # code taken from CMake 2.8 FindOpenAL.cmake
    FIND_PATH(_OPENAL_INCLUDE_DIR OpenAL/al.h
      HINTS
      PATH_SUFFIXES include
      PATHS
      ~/Library/Frameworks
      /Library/Frameworks
      /System/Library/Frameworks
      /usr/local
      /usr
      /sw # Fink
      /opt/local # DarwinPorts
      /opt/csw # Blastwave
    )

    set (_OPENAL_LIBRARY "")
    set (_OPENAL_LIBRARY_DIR "")
    set (_OPENAL_LDFLAGS "-framework;OpenAL")
    set (_OPENAL_CFLAGS "")
    set (_OPENAL_VERSION "")
    set (_OPENAL_FOUND true)

else ()

    # on Linux take the pkgconfig file
    if (OpenAL_FIND_VERSION)
        pkg_check_modules(_OPENAL_PC QUIET openal>=${OpenAL_FIND_VERSION})
    else ()
        pkg_check_modules(_OPENAL_PC QUIET openal)
    endif()

    if (_OPENAL_PC_FOUND)
        set (_OPENAL_LIBRARY_DIR ${_OPENAL_PC_LIBRARY_DIRS})
        set (_OPENAL_INCLUDE_DIR ${_OPENAL_PC_INCLUDE_DIRS})

        if (BUILD_SHARED_LIBS)
            set (_OPENAL_LIBRARY ${_OPENAL_PC_LIBRARIES})
        else ()
            set (_OPENAL_LIBRARY ${_OPENAL_PC_STATIC_LIBRARIES})
        endif ()

        set (_OPENAL_LDFLAGS ${_OPENAL_PC_LDFLAGS_OTHER})
        set (_OPENAL_CFLAGS ${_OPENAL_PC_CFLAGS_OTHER})
        set (_OPENAL_VERSION ${_OPENAL_PC_VERSION})
        set (_OPENAL_FOUND true)
    endif ()

endif()

if (_OPENAL_FOUND)

    set (OPENAL_LIBRARY_DIRS ${_OPENAL_LIBRARY_DIR})
    set (OPENAL_INCLUDE_DIRS ${_OPENAL_INCLUDE_DIR})
    set (OPENAL_LIBRARIES ${_OPENAL_LIBRARY})
    set (OPENAL_LDFLAGS ${_OPENAL_LDFLAGS})
    set (OPENAL_CFLAGS ${_OPENAL_CFLAGS})
    set (OPENAL_VERSION ${_OPENAL_VERSION})

    if (NOT OpenAL_FIND_QUIETLY)
        message(STATUS "  OpenAL found version: ${OPENAL_VERSION}")
        message(STATUS "    includes:  ${OPENAL_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${OPENAL_CFLAGS}")
        message(STATUS "    libraries: ${OPENAL_LIBRARIES}")
        message(STATUS "    libdirs:   ${OPENAL_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${OPENAL_LDFLAGS}")
    endif ()
    set (OPENAL_FOUND true)
else ()
    set (OPENAL_FOUND FALSE)
    if (OpenAL_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find OpenAL.")
    endif()
endif ()
