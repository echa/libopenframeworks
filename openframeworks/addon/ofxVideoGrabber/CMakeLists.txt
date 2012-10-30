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

REQUIRES (HAVE_DC1394 "ofxVideoGrabber disabled")
REQUIRES (HAVE_POCO "ofxVideoGrabber disabled")
REQUIRES (HAVE_OFX_XMLSETTINGS "ofxVideoGrabber disabled")
message("-- Adding: ofxVideoGrabber")


set (OFX_VIDEOGRABBER_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber
    )

set (OFX_VIDEOGRABBER_LDFLAGS)
set (OFX_VIDEOGRABBER_CFLAGS)
set (OFX_VIDEOGRABBER_LIBDIRS)
set (OFX_VIDEOGRABBER_LIBS)


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
EXPORT_CONFIG_VAR (HAVE_OFX_VIDEOGRABBER)
set (OFX_VIDEOGRABBER_INCLUDES ${OFX_VIDEOGRABBER_INCLUDES} PARENT_SCOPE)
set (OFX_VIDEOGRABBER_LDFLAGS  ${OFX_VIDEOGRABBER_LDFLAGS}  PARENT_SCOPE)
set (OFX_VIDEOGRABBER_CFLAGS   ${OFX_VIDEOGRABBER_CFLAGS}   PARENT_SCOPE)
set (OFX_VIDEOGRABBER_LIBDIRS  ${OFX_VIDEOGRABBER_LIBDIRS}  PARENT_SCOPE)
set (OFX_VIDEOGRABBER_LIBS     ${OFX_VIDEOGRABBER_LIBS}     PARENT_SCOPE)

# and append to 'all' OFX vars
set (OFX_INCLUDES ${OFX_INCLUDES} ${OFX_VIDEOGRABBER_INCLUDES} PARENT_SCOPE)
set (OFX_LDFLAGS  ${OFX_LDFLAGS}  ${OFX_VIDEOGRABBER_LDFLAGS}  PARENT_SCOPE)
set (OFX_CFLAGS   ${OFX_CFLAGS}   ${OFX_VIDEOGRABBER_CFLAGS}   PARENT_SCOPE)
set (OFX_LIBDIRS  ${OFX_LIBDIRS}  ${OFX_VIDEOGRABBER_LIBDIRS}  PARENT_SCOPE)
set (OFX_LIBS     ${OFX_LIBS}     ${OFX_VIDEOGRABBER_LIBS}     PARENT_SCOPE)

set (OFX_SOURCES
    ${OFX_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxIIDCSettings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxVideoGrabber.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxVideoGrabberFeature.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxVideoGrabberSettings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/ofxControlPanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394Grabber.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberFeatureHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberFramerateHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberVideoFormatHelper.cpp
    PARENT_SCOPE
)

set (OFX_HEADERS
    ${OFX_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiBaseObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiCallbacks.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiColor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiCustomImpl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiIncludes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTextBase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiType2DSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeButtonSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeCustom.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeDrawable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeMultiToggle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypePanel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeSlider.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeText.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeTextDropDown.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiTypeToggle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiValue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/guiXmlValue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/ofxControlPanel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/simpleColor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394Grabber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberFeatureHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberFramerateHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberUtils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Libdc1394Grabber/Libdc1394GrabberVideoFormatHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxIIDCSettings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxVideoGrabber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxVideoGrabberFeature.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxVideoGrabberSDK.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ofxVideoGrabberSettings.h
    PARENT_SCOPE
)
