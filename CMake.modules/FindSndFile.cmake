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

# - Try to find SndFile
# Once done, this will define
#
#  SNDFILE_FOUND - system has SndFile dev libs
#  SNDFILE_INCLUDE_DIRS - the include directory
#  SNDFILE_LIBRARIES - libraries to link
#  SNDFILE_LIBRARY_DIRS - libraries directories
#  SNDFILE_CFLAGS - compile flags
#  SNDFILE_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT SndFile_FIND_QUIETLY)
    if (SndFile_FIND_VERSION)
        message (STATUS "Checking for libsndfile (>= ${SndFile_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for libsndfile...")
    endif()
endif ()


if (SndFile_FIND_VERSION)
    pkg_check_modules(SndFile_PC QUIET sndfile>=${SndFile_FIND_VERSION})
else ()
    pkg_check_modules(SndFile_PC QUIET sndfile)
endif()


if (SndFile_PC_FOUND)
    set (SNDFILE_LIBRARY_DIRS ${SndFile_PC_LIBRARY_DIRS})
    set (SNDFILE_INCLUDE_DIRS ${SndFile_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (SNDFILE_LIBRARIES ${SndFile_PC_LIBRARIES})
    else ()
        set (SNDFILE_LIBRARIES ${SndFile_PC_STATIC_LIBRARIES})
    endif ()

    set (SNDFILE_LDFLAGS ${SndFile_PC_LDFLAGS_OTHER})
    set (SNDFILE_CFLAGS ${SndFile_PC_CFLAGS_OTHER})
    set (SNDFILE_VERSION ${SndFile_PC_VERSION})

    if (NOT SndFile_FIND_QUIETLY)
        message(STATUS "  libsndfile found version: ${SNDFILE_VERSION}")
        message(STATUS "    includes:  ${SNDFILE_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${SNDFILE_CFLAGS}")
        message(STATUS "    libraries: ${SNDFILE_LIBRARIES}")
        message(STATUS "    libdirs:   ${SNDFILE_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${SNDFILE_LDFLAGS}")
    endif ()
    set (SNDFILE_FOUND true)
else ()
    set (SNDFILE_FOUND FALSE)
    if (SndFile_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find libsoundfile.")
    endif()
endif ()

