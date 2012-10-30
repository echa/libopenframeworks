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

# returns immediately on failure and leaves variables below undefined
REQUIRES (HAVE_OFX_XMLSETTINGS "ofxGui disabled")
message("-- Adding: ofxGui")

set (OFX_GUI_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set (OFX_GUI_LDFLAGS)
set (OFX_GUI_CFLAGS)
set (OFX_GUI_LIBDIRS)
set (OFX_GUI_LIBS)

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
EXPORT_CONFIG_VAR (HAVE_OFX_GUI)
set (OFX_GUI_INCLUDES ${OFX_GUI_INCLUDES} PARENT_SCOPE)
set (OFX_GUI_LDFLAGS  ${OFX_GUI_LDFLAGS}  PARENT_SCOPE)
set (OFX_GUI_CFLAGS   ${OFX_GUI_CFLAGS}   PARENT_SCOPE)
set (OFX_GUI_LIBDIRS  ${OFX_GUI_LIBDIRS}  PARENT_SCOPE)
set (OFX_GUI_LIBS     ${OFX_GUI_LIBS}     PARENT_SCOPE)

# and append to 'all' OFX vars
set (OFX_INCLUDES ${OFX_INCLUDES} ${OFX_GUI_INCLUDES} PARENT_SCOPE)
set (OFX_LDFLAGS  ${OFX_LDFLAGS}  ${OFX_GUI_LDFLAGS}  PARENT_SCOPE)
set (OFX_CFLAGS   ${OFX_CFLAGS}   ${OFX_GUI_CFLAGS}   PARENT_SCOPE)
set (OFX_LIBDIRS  ${OFX_LIBDIRS}  ${OFX_GUI_LIBDIRS}  PARENT_SCOPE)
set (OFX_LIBS     ${OFX_LIBS}     ${OFX_GUI_LIBS}     PARENT_SCOPE)

set (OFX_SOURCES
    ${OFX_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiColor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiFiles.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiGlobals.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiKnob.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiMatrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiPanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiPoints.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiRadar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiScope.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiSlider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiSwitch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiXyPad.cpp
    PARENT_SCOPE
)

set (OFX_HEADERS
    ${OFX_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiColor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiFiles.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiGlobals.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiKnob.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiMatrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiPanel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiPoints.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiRadar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiScope.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiSwitch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiTypes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxGuiXyPad.h
    PARENT_SCOPE
)
