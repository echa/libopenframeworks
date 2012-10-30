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

#
# Try to find the FreeImage library and include path.
# Once done this will define
#
# FREEIMAGE_FOUND
# FREEIMAGE_INCLUDE_PATH
# FREEIMAGE_LIBRARY
#

FIND_PATH( FREEIMAGE_INCLUDE_PATH FreeImage.h
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    DOC "The directory where FreeImage.h resides")
FIND_LIBRARY( FREEIMAGE_LIBRARY
    NAMES FreeImage freeimage
    PATHS
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    DOC "The FreeImage library")

#The library directories
GET_FILENAME_COMPONENT(FREEIMAGE_LIBRARY_DIRS "${FREEIMAGE_LIBRARY}" PATH)

IF (FREEIMAGE_INCLUDE_PATH AND FREEIMAGE_LIBRARY)
    SET( FREEIMAGE_FOUND TRUE)
ELSE ()
    SET( FREEIMAGE_FOUND FALSE)
ENDIF ()

MARK_AS_ADVANCED(
    FREEIMAGE_FOUND
    FREEIMAGE_LIBRARY
    FREEIMAGE_LIBRARY_DIRS
    FREEIMAGE_INCLUDE_PATH)


