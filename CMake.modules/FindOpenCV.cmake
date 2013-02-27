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

# - Try to find OpenCV
# Once done, this will define
#
#  OPENCV_FOUND - system has OPENCV
#  OPENCV_INCLUDE_DIRS - the OPENCV include directories
#  OPENCV_LIBRARIES - link these to use OPENCV
#  OPENCV_LIBRARY_DIRS - libraries directories
#  OPENCV_CFLAGS - OPENCV compile flags
#  OPENCV_LDFLAGS - OPENCV linker flags

include(FindPkgConfig)

if (NOT OpenCV_FIND_QUIETLY)
    if (OpenCV_FIND_VERSION)
        message (STATUS "Checking for OpenCV (>= ${OpenCV_FIND_VERSION})...")
    else ()
        message (STATUS "Checking for OpenCV...")
    endif()
endif ()

if (OpenCV_FIND_VERSION)
    pkg_check_modules(OPENCV_PC QUIET opencv>=${OpenCV_FIND_VERSION})
else ()
    pkg_check_modules(OPENCV_PC QUIET opencv)
endif()

if (OPENCV_PC_FOUND)
    set (OPENCV_LIBRARY_DIRS ${OPENCV_PC_LIBRARY_DIRS})
    set (OPENCV_INCLUDE_DIRS ${OPENCV_PC_INCLUDE_DIRS})
    if (BUILD_SHARED_LIBS)
        set (OPENCV_LIBRARIES ${OPENCV_PC_LIBRARIES})
    else ()
        set (OPENCV_LIBRARIES ${OPENCV_PC_STATIC_LIBRARIES})
    endif ()
    set (OPENCV_LDFLAGS "")

    # on OSX put -framework entries into LD_FLAGS
    if (IS_DARWIN)
        set(ALL_LIBS ${OPENCV_LIBRARIES} ${OPENCV_PC_LDFLAGS_OTHER})
        foreach(L ${ALL_LIBS})
            if ("${L}" MATCHES "-framework")
                set (WAS_FRAMEWORK true)
            else ()
                if (WAS_FRAMEWORK)
                    list(APPEND OPENCV_DARWIN_FRAMEWORKS "-framework;${L}")
                    set(WAS_FRAMEWORK false)
                else ()
                    list(APPEND OPENCV_DARWIN_LIBRARIES ${L})
                endif()
            endif()
        endforeach()
        set (OPENCV_LIBRARIES ${OPENCV_DARWIN_LIBRARIES})
        set (OPENCV_LDFLAGS ${OPENCV_DARWIN_FRAMEWORKS})
    else ()
        set (OPENCV_LIBRARIES ${OPENCV_LIBRARIES} ${OPENCV_PC_LDFLAGS_OTHER})
    endif()

    # sort lib list and place all opencv libs first
    foreach(OCV_L ${OPENCV_LIBRARIES})
        if ("${OCV_L}" MATCHES "^.*opencv.*$")
            list(APPEND OCV_CORE_LIBRARIES ${OCV_L})
        else ()
            list(APPEND OCV_OTHER_LIBRARIES ${OCV_L})
        endif()
    endforeach()

    set (OPENCV_LIBRARIES ${OCV_CORE_LIBRARIES} ${OCV_OTHER_LIBRARIES})

    set (OPENCV_CFLAGS ${OPENCV_PC_CFLAGS_OTHER})
    set (OPENCV_VERSION ${OPENCV_PC_VERSION})

    if (NOT OpenCV_FIND_QUIETLY)
        message(STATUS "  OpenCV found version: ${OPENCV_VERSION}")
        message(STATUS "    includes:  ${OPENCV_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${OPENCV_CFLAGS}")
        message(STATUS "    libraries: ${OPENCV_LIBRARIES}")
        message(STATUS "    libdirs:   ${OPENCV_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${OPENCV_LDFLAGS}")
    endif ()
    set (OPENCV_FOUND TRUE)
else ()
    set (OPENCV_FOUND FALSE)
    if (OpenCV_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find OpenCV.")
    endif()
endif ()


