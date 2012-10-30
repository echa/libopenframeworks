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

# - Try to find RTAUDIO
# Once done, this will define
#
#  RTAUDIO_FOUND - system has RTAUDIO dev libs
#  RTAUDIO_INCLUDE_DIRS - the include directory
#  RTAUDIO_LIBRARIES - libraries to link
#  RTAUDIO_LIBRARY_DIRS - libraries directories
#  RTAUDIO_CFLAGS - compile flags
#  RTAUDIO_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT RTAUDIO_FIND_QUIETLY)
    if (RTAUDIO_FIND_VERSION)
        message (STATUS "Checking for RtAudio (>= ${RTAUDIO_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for RtAudio...")
    endif()
endif ()


if (RTAUDIO_FIND_VERSION)
    pkg_check_modules(RTAUDIO_PC QUIET rtaudio>=${RTAUDIO_FIND_VERSION})
else ()
    pkg_check_modules(RTAUDIO_PC QUIET rtaudio)
endif()


if (RTAUDIO_PC_FOUND)
    set (RTAUDIO_LIBRARY_DIRS ${RTAUDIO_PC_LIBRARY_DIRS})
    set (RTAUDIO_INCLUDE_DIRS ${RTAUDIO_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (RTAUDIO_LIBRARIES ${RTAUDIO_PC_LIBRARIES})
    else ()
        set (RTAUDIO_LIBRARIES ${RTAUDIO_PC_STATIC_LIBRARIES})
    endif ()

	# flags come as list already, but we need to split them for proper handling
    #expand_list("${RTAUDIO_PC_LDFLAGS}" RTAUDIO_LDFLAGS) # "${RTAUDIO_PC_LDFLAGS_OTHER}")
    #expand_list("${RTAUDIO_PC_CFLAGS}" RTAUDIO_CFLAGS)

    set (RTAUDIO_LDFLAGS ${RTAUDIO_PC_LDFLAGS_OTHER})
    set (RTAUDIO_CFLAGS ${RTAUDIO_PC_CFLAGS_OTHER})

    if (NOT RTAUDIO_FIND_QUIETLY)
        message(STATUS "  RtAudio found version: ${RTAUDIO_PC_VERSION}")
        message(STATUS "    includes:  ${RTAUDIO_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${RTAUDIO_CFLAGS}")
        message(STATUS "    libraries: ${RTAUDIO_LIBRARIES}")
        message(STATUS "    libdirs:   ${RTAUDIO_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${RTAUDIO_LDFLAGS}")
    endif ()
    set (RTAUDIO_FOUND true)
else ()
    set (RTAUDIO_FOUND FALSE)
    if (RtAudio_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find rtaudio.")
    endif()
endif ()

