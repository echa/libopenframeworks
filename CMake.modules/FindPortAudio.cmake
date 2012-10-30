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

# - Try to find PortAudio
# Once done, this will define
#
#  PORTAUDIO_FOUND - system has PortAudio dev libs
#  PORTAUDIO_INCLUDE_DIRS - the include directory
#  PORTAUDIO_LIBRARIES - libraries to link
#  PORTAUDIO_LIBRARY_DIRS - libraries directories
#  PORTAUDIO_CFLAGS - compile flags
#  PORTAUDIO_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT PortAudio_FIND_QUIETLY)
    if (PortAudio_FIND_VERSION)
        message (STATUS "Checking for PortAudio2 (>= ${PortAudio_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for PortAudio2...")
    endif()
endif ()


if (PortAudio_FIND_VERSION)
    pkg_check_modules(PortAudio_PC QUIET portaudio-2.0>=${PortAudio_FIND_VERSION})
else ()
    pkg_check_modules(PortAudio_PC QUIET portaudio-2.0)
endif()


if (PortAudio_PC_FOUND)
    set (PORTAUDIO_LIBRARY_DIRS ${PortAudio_PC_LIBRARY_DIRS})
    set (PORTAUDIO_INCLUDE_DIRS ${PortAudio_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (PORTAUDIO_LIBRARIES ${PortAudio_PC_LIBRARIES})
    else ()
        set (PORTAUDIO_LIBRARIES ${PortAudio_PC_STATIC_LIBRARIES})
    endif ()

    set (PORTAUDIO_LDFLAGS ${PortAudio_PC_LDFLAGS_OTHER})
    set (PORTAUDIO_CFLAGS ${PortAudio_PC_CFLAGS_OTHER})
    set (PORTAUDIO_VERSION ${PortAudio_PC_VERSION})

    if (NOT PortAudio_FIND_QUIETLY)
        message(STATUS "  PortAudio2 found version: ${PORTAUDIO_VERSION}")
        message(STATUS "    includes:  ${PORTAUDIO_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${PORTAUDIO_CFLAGS}")
        message(STATUS "    libraries: ${PORTAUDIO_LIBRARIES}")
        message(STATUS "    libdirs:   ${PORTAUDIO_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${PORTAUDIO_LDFLAGS}")
    endif ()
    set (PORTAUDIO_FOUND true)
else ()
    set (PORTAUDIO_FOUND FALSE)
    if (PortAudio_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find portaudio.")
    endif()
endif ()

