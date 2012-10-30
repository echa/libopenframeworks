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
REQUIRES (HAVE_OFX_XMLSETTINGS "ofxUI disabled")
message("-- Adding: ofxUI")


set (OFX_UI_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
set (OFX_UI_LDFLAGS)
set (OFX_UI_CFLAGS)
set (OFX_UI_LIBDIRS)
set (OFX_UI_LIBS)

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
EXPORT_CONFIG_VAR (HAVE_OFX_UI)
set (OFX_UI_INCLUDES ${OFX_UI_INCLUDES} PARENT_SCOPE)
set (OFX_UI_LDFLAGS  ${OFX_UI_LDFLAGS}  PARENT_SCOPE)
set (OFX_UI_CFLAGS   ${OFX_UI_CFLAGS}   PARENT_SCOPE)
set (OFX_UI_LIBDIRS  ${OFX_UI_LIBDIRS}  PARENT_SCOPE)
set (OFX_UI_LIBS     ${OFX_UI_LIBS}     PARENT_SCOPE)

# and append to 'all' OFX vars
set (OFX_INCLUDES ${OFX_INCLUDES} ${OFX_UI_INCLUDES} PARENT_SCOPE)
set (OFX_LDFLAGS  ${OFX_LDFLAGS}  ${OFX_UI_LDFLAGS}  PARENT_SCOPE)
set (OFX_CFLAGS   ${OFX_CFLAGS}   ${OFX_UI_CFLAGS}   PARENT_SCOPE)
set (OFX_LIBDIRS  ${OFX_LIBDIRS}  ${OFX_UI_LIBDIRS}  PARENT_SCOPE)
set (OFX_LIBS     ${OFX_LIBS}     ${OFX_UI_LIBS}     PARENT_SCOPE)

# append source files
set (OFX_SOURCES
  ${OFX_SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUI2DPad.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIBiLabelSlider.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIButton.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUICanvas.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIDropDownList.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIFPS.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIFPSSlider.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIImage.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIImageButton.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIImageToggle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUILabel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUILabelButton.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUILabelToggle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIMinimalSlider.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIMovingGraph.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUINumberDialer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRadio.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRangeSlider.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRectangle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRotarySlider.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUISlider.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUISpacer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUISpectrum.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUITextInput.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIToggle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIToggleMatrix.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIWaveform.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIWidget.cpp
  PARENT_SCOPE
)

set (OFX_HEADERS
    ${OFX_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUI.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUI2DPad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIBiLabelSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUICanvas.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIdefs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIDropDownList.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIEventArgs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIFPS.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIFPSSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIImage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIImageButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIImageToggle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUILabel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUILabelButton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUILabelToggle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIMinimalSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIMovingGraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUINumberDialer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRadio.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRangeSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRectangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIRotarySlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUISlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUISpacer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUISpectrum.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUITextInput.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIToggle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIToggleMatrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIWaveform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxUIWidget.h
    PARENT_SCOPE
)
