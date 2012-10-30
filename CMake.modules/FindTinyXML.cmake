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

# - Try to find TinyXML
# Once done, this will define
#
#  TINYXML_FOUND - system has libAvahi-client-dev
#  TINYXML_INCLUDE_DIRS - the include directory
#  TINYXML_LIBRARIES - libraries to link
#  TINYXML_LIBRARY_DIRS - libraries directories
#  TINYXML_CFLAGS - compile flags
#  TINYXML_LDFLAGS - linker flags

include(FindPkgConfig)

if (NOT TinyXML_FIND_QUIETLY)
    if (TinyXML_FIND_VERSION)
        message (STATUS "Checking for TinyXML (>= ${TinyXML_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for TinyXML...")
    endif ()
endif ()


if (TinyXML_FIND_VERSION)
    pkg_check_modules(TinyXML_PC QUIET tinyxml>=${TinyXML_FIND_VERSION})
else ()
    pkg_check_modules(TinyXML_PC QUIET tinyxml)
endif()


if (TinyXML_PC_FOUND)
    set (TINYXML_LIBRARY_DIRS ${TinyXML_PC_LIBRARY_DIRS})
    set (TINYXML_INCLUDE_DIRS ${TinyXML_PC_INCLUDE_DIRS})

    if (BUILD_SHARED_LIBS)
        set (TINYXML_LIBRARIES ${TinyXML_PC_LIBRARIES})
    else ()
        set (TINYXML_LIBRARIES ${TinyXML_PC_STATIC_LIBRARIES})
    endif ()

    set (TINYXML_LDFLAGS ${TinyXML_PC_LDFLAGS_OTHER})
    set (TINYXML_CFLAGS ${TinyXML_PC_CFLAGS_OTHER})
    set (TINYXML_VERSION ${TinyXML_PC_VERSION})

    if (NOT TinyXML_FIND_QUIETLY)
        message(STATUS "  TinyXML found version: ${TINYXML_VERSION}")
        message(STATUS "    includes:  ${TINYXML_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${TINYXML_CFLAGS}")
        message(STATUS "    libraries: ${TINYXML_LIBRARIES}")
        message(STATUS "    libdirs:   ${TINYXML_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${TINYXML_LDFLAGS}")
    endif ()
    set (TINYXML_FOUND true)
else ()
    set (TINYXML_FOUND false)
    if (TinyXML_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find libtinyxml.")
    endif()
endif ()

