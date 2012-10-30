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

# - Try to find Open Asset Import Library
# Once done, this will define
#
#  OAI_FOUND - system has OpenAssetImport
#  OAI_INCLUDE_DIRS - the include directory
#  OAI_LIBRARIES - libraries to link
#  OAI_LIBRARY_DIRS - libraries directories
#  OAI_CFLAGS - compile flags
#  OAI_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT OpenAssetImport_FIND_QUIETLY)
    if (OpenAssetImport_FIND_VERSION)
        message (STATUS "Checking for OpenAssetImport (>= ${OpenAssetImport_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for OpenAssetImport...")
    endif()
endif ()


if (OpenAssetImport_FIND_VERSION)
    pkg_check_modules(OAI_PC QUIET assimp>=${OpenAssetImport_FIND_VERSION})
else ()
    pkg_check_modules(OAI_PC QUIET assimp)
endif()


if (OAI_PC_FOUND)
    set (OAI_LIBRARY_DIRS ${OAI_PC_LIBRARY_DIRS})
    set (OAI_INCLUDE_DIRS ${OAI_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (OAI_LIBRARIES ${OAI_PC_LIBRARIES})
    else ()
        set (OAI_LIBRARIES ${OAI_PC_STATIC_LIBRARIES})
    endif ()

    set (OAI_LDFLAGS ${OAI_PC_LDFLAGS_OTHER})
    set (OAI_CFLAGS ${OAI_PC_CFLAGS_OTHER})
    set (OAI_VERSION ${OAI_PC_VERSION})


    if (NOT OpenAssetImport_FIND_QUIETLY)
        message(STATUS "  OpenAssetImport version ${OAI_VERSION}")
        message(STATUS "    includes:  ${OAI_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${OAI_CFLAGS}")
        message(STATUS "    libraries: ${OAI_LIBRARIES}")
        message(STATUS "    libdirs:   ${OAI_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${OAI_LDFLAGS}")

    endif ()
    set (OAI_FOUND true)
else ()
    set (OAI_FOUND FALSE)
    if (OpenAssetImport_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find OpenAssetImport.")
    endif()
endif ()

