#############################################################################
# KidTsunami - Professional. Live. Video.
#
# File:     CMakeLists.txt
# Author:   Alexander Eichhorn <echa@kidtsunami.com>
# Contents: CMake rules for oF Addon
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

REQUIRES (HAVE_OPENCV "ofxCv disabled")
message("-- Adding: ofxCv")

set (OFX_CV_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set (OFX_CV_LDFLAGS)
set (OFX_CV_CFLAGS)
set (OFX_CV_LIBDIRS)
set (OFX_CV_LIBS)

#--------------------------------------------------------------------------
#   exports the following variables:
#       OFX_<ADDON_NAME>_INCLUDES  - addon specific include dirs
#       OFX_<ADDON_NAME>_LDFLAGS   - addon specific linker flags
#       OFX_<ADDON_NAME>_CFLAGS    - addon specific compiler flags
#       OFX_<ADDON_NAME>_LIBDIRS   - addon specific library dirs
#       OFX_<ADDON_NAME>_LIBS      - addon specific libraries
#       HAVE_OFX_<ADDON_NAME>      - set if addon is available (dependencies OK)
#       OFX_INCLUDES               - all addons include dirs
#       OFX_LDFLAGS                - all addons linker flags
#       OFX_CFLAGS                 - all addons compiler flags
#       OFX_LIBDIRS                - all addons library dirs
#       OFX_LIBS                   - all addons libraries
#       OFX_SOURCES                - all source files for addons
#--------------------------------------------------------------------------
EXPORT_CONFIG_VAR (HAVE_OFX_CV)
set (OFX_CV_INCLUDES ${OFX_CV_INCLUDES} PARENT_SCOPE)
set (OFX_CV_LDFLAGS  ${OFX_CV_LDFLAGS}  PARENT_SCOPE)
set (OFX_CV_CFLAGS   ${OFX_CV_CFLAGS}   PARENT_SCOPE)
set (OFX_CV_LIBDIRS  ${OFX_CV_LIBDIRS}  PARENT_SCOPE)
set (OFX_CV_LIBS     ${OFX_CV_LIBS}     PARENT_SCOPE)

# and append to 'all' OFX vars
set (OFX_INCLUDES ${OFX_INCLUDES} ${OFX_CV_INCLUDES} PARENT_SCOPE)
set (OFX_LDFLAGS  ${OFX_LDFLAGS}  ${OFX_CV_LDFLAGS}  PARENT_SCOPE)
set (OFX_CFLAGS   ${OFX_CFLAGS}   ${OFX_CV_CFLAGS}   PARENT_SCOPE)
set (OFX_LIBDIRS  ${OFX_LIBDIRS}  ${OFX_CV_LIBDIRS}  PARENT_SCOPE)
set (OFX_LIBS     ${OFX_LIBS}     ${OFX_CV_LIBS}     PARENT_SCOPE)

set (OFX_SOURCES
    ${OFX_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Calibration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/ContourFinder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Distance.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Flow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Helpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/RunningBackground.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Tracker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Utilities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Wrappers.cpp
    PARENT_SCOPE
)

set (OFX_HEADERS
    ${OFX_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv.h
    PARENT_SCOPE
)

set (OFX_CV_HEADERS
    ${OFX_CV_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Calibration.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/ContourFinder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Distance.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Helpers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/RunningBackground.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Tracker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Utilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Wrappers.h
    PARENT_SCOPE
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Calibration.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/ContourFinder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Distance.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Helpers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/RunningBackground.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Tracker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Utilities.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxCv/Wrappers.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/ofxCv)
