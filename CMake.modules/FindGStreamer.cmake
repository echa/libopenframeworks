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

# Find Gstreamer Library
#
# Defines:
#  GST_FOUND        - system has GStreamer
#  GST_INCLUDE_DIRS - the GStreamer include directory
#  GST_LIBRARY_DIRS - lib dirs
#  GST_LIBRARIES    - the libraries needed to use GStreamer
#  GST_CFLAGS       - compile switches
#  GST_LDFLAGS      - linker flags
#
#

include (FindPkgConfig)

if (NOT GStreamer_FIND_QUIETLY)
    message (STATUS "Checking for Gstreamer (version >= ${GSTREAMER_MIN_VERSION})...")
endif ()

pkg_check_modules(GST_PC QUIET gstreamer-${GSTREAMER_MIN_VERSION}>=${GSTREAMER_MIN_VERSION})

pkg_check_modules(GST_BASE_PC QUIET gstreamer-base-${GSTREAMER_MIN_VERSION}>=${GSTREAMER_MIN_VERSION})

pkg_check_modules(GST_APP_PC QUIET gstreamer-app-${GSTREAMER_MIN_VERSION}>=${GSTREAMER_MIN_VERSION})

pkg_check_modules(GST_IF_PC QUIET gstreamer-interfaces-${GSTREAMER_MIN_VERSION}>=${GSTREAMER_MIN_VERSION})

pkg_check_modules(GST_VIDEO_PC QUIET gstreamer-video-${GSTREAMER_MIN_VERSION}>=${GSTREAMER_MIN_VERSION})


if (GST_PC_FOUND AND GST_IF_PC_FOUND AND GST_APP_PC_FOUND AND GST_BASE_PC_FOUND)

    set (GST_LIBRARY_DIRS
        ${GST_PC_LIBRARY_DIRS}
        ${GST_BASE_PC_LIBRARY_DIRS}
        ${GST_APP_PC_LIBRARY_DIRS}
        ${GST_IF_PC_LIBRARY_DIRS}
        ${GST_VIDEO_PC_LIBRARY_DIRS}
        )

    set (GST_INCLUDE_DIRS
        ${GST_PC_INCLUDE_DIRS}
        ${GST_BASE_PC_INCLUDE_DIRS}
        ${GST_APP_PC_INCLUDE_DIRS}
        ${GST_IF_PC_INCLUDE_DIRS}
        ${GST_VIDEO_PC_INCLUDE_DIRS}
        )
    if (BUILD_SHARED_LIBS)
        SET (GST_LIBRARIES
            ${GST_PC_LIBRARIES}
            ${GST_BASE_PC_LIBRARIES}
            ${GST_APP_PC_LIBRARIES}
            ${GST_IF_PC_LIBRARIES}
            ${GST_VIDEO_PC_LIBRARIES}
            )
    else ()
        SET (GST_LIBRARIES
            ${GST_PC_STATIC_LIBRARIES}
            ${GST_BASE_PC_STATIC_LIBRARIES}
            ${GST_APP_PC_STATIC_LIBRARIES}
            ${GST_IF_PC_STATIC_LIBRARIES}
            ${GST_VIDEO_PC_STATIC_LIBRARIES}
            )
    endif ()

    set (GST_LDFLAGS
            ${GST_PC_LDFLAGS_OTHER}
            ${GST_BASE_PC_LDFLAGS_OTHER}
            ${GST_APP_PC_LDFLAGS_OTHER}
            ${GST_IF_PC_LDFLAGS_OTHER}
            ${GST_VIDEO_PC_LDFLAGS_OTHER}
            )

    set (GST_CFLAGS
            ${GST_PC_CFLAGS_OTHER}
            ${GST_BASE_PC_CFLAGS_OTHER}
            ${GST_APP_PC_CFLAGS_OTHER}
            ${GST_IF_PC_CFLAGS_OTHER}
            ${GST_VIDEO_PC_CFLAGS_OTHER}
            )

    set (GST_VERSION ${GST_PC_VERSION})

    # remove duplicates
    list (REMOVE_DUPLICATES GST_INCLUDE_DIRS)
    list (REMOVE_DUPLICATES GST_LIBRARIES)

    if (NOT Gstreamer_FIND_QUIETLY)
        message(STATUS "  GStreamer found version: ${GST_VERSION}")
        message(STATUS "    includes: ${GST_INCLUDE_DIRS}")
        message(STATUS "    cflags:    ${GST_CFLAGS}")
        message(STATUS "    libraries: ${GST_LIBRARIES}")
        message(STATUS "    libdirs:   ${GST_LIBRARY_DIRS}")
        message(STATUS "    ldflags:   ${GST_LDFLAGS}")
    endif ()

    set (GST_FOUND TRUE)
else ()
    set (GST_FOUND FALSE)
    if (Gtreamer_FIND_REQUIRED)
        message(FATAL_ERROR "EE Could not find Gstreamer.")
    endif()
endif ()
