#############################################################################
# KidTsunami - Professional. Live. Video.
#
# File:     CMakeLists.txt
# Author:   Alexander Eichhorn <echa@kidtsunami.com>
# Contents: Main CMake File for libopenframeworks and its addons
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

#--------------------------------------------------------------------------
# Build Configuration - options can be set using "cmake -DOPTION="
#--------------------------------------------------------------------------
if (DEFINED CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "build type")
else ()
    set (CMAKE_BUILD_TYPE debug CACHE STRING "build type")
endif ()

if (DEFINED CMAKE_VERBOSE_MAKEFILE)
    set (CMAKE_VERBOSE_MAKEFILE ${CMAKE_VERBOSE_MAKEFILE} CACHE BOOL "verbose")
else ()
    set (CMAKE_VERBOSE_MAKEFILE false CACHE BOOL "verbose")
endif ()

# supported configurations
set (CMAKE_CONFIGURATION_TYPES "debug;release" CACHE STRING "Configurations")

#  prefix path for searching private libs
set (CMAKE_PREFIX_PATH $ENV{HOME} CACHE PATH "library search path")
set (CMAKE_INSTALL_PREFIX ${CMAKE_PREFIX_PATH} CACHE PATH "install path")

set (BUILD_SHARED_LIBS false CACHE BOOL "build shared libs") # on, (off)
set (LINK_SEARCH_END_STATIC true)  #  (on), off


# always prefer files in CMAKE_MODULE_PATH
if(POLICY CMP0017)
   cmake_policy(SET CMP0017 OLD)
endif()
cmake_minimum_required(VERSION 2.8)


# Project definition
project (openframeworks)

set (OF_VERSION_MAJOR 0)
set (OF_VERSION_MINOR 0)
set (OF_VERSION_PATCH 71)
set (OF_VERSION ${OF_VERSION_MAJOR}.${OF_VERSION_MINOR}.${OF_VERSION_PATCH})

#--------------------------------------------------------------------------
# System Type
#--------------------------------------------------------------------------

# check for 32/64-bit system
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set (IS_LINUX true)
    if (CMAKE_SIZEOF_VOID_P MATCHES "8")
        SET (IS_AMD64 true)
        set (IS_LINUX64 true)
    else ()
        SET (IS_AMD64 false)
        set (IS_LINUX32 true)
    endif ()
    set (CMAKE_find_library_SUFFIXES ".a" ".so")
endif ()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set (IS_DARWIN true)
    if (CMAKE_SIZEOF_VOID_P MATCHES "8")
        set (IS_DARWIN64 true)
    else ()
        set (IS_DARWIN32 true)
    endif ()
    set (CMAKE_find_library_SUFFIXES ".a" ".dylib")
endif ()


#--------------------------------------------------------------------------
# Definitions for Build Types
#--------------------------------------------------------------------------
## DEBUG build
if (IS_DARWIN64)
    set (CMAKE_CXX_FLAGS_DEBUG "-O2 -g3 -DDEBUG -Wall")
else()
    set (CMAKE_CXX_FLAGS_DEBUG "-O2 -g3 -ggdb3 -DDEBUG -Wall")
endif ()

set (CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
set (BUILD_WITH_DEBUG_INFO ON CACHE BOOL "Include debug info into debug libs")

## Release build
set (CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall")
set (CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

## PROFILING build option
option (ENABLE_PROFILING "Enable code profiling (default: NO)" false)
if (ENABLE_PROFILING)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
    set (CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})

    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pg")
    set (CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
endif ()

set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_DEBUG_POSTFIX "d")

## Examples
option (BUILD_EXAMPLES "Build OpenFrameworks Example Programs" false)

#--------------------------------------------------------------------------
# CMake PATH Configuration
#--------------------------------------------------------------------------

# extra path for CMake Find modules
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake.modules ${CMAKE_MODULE_PATH})

# '.' in include paths
set (CMAKE_INCLUDE_CURRENT_DIR true)
set (CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE true)

## define INSTALL directories
set( LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/ CACHE PATH
     "Install path for libraries." )
set( INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/openframeworks CACHE
     PATH "Install path for header files." )
set( BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin/ CACHE PATH
     "Install path for executables." )
set( SHARE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/openframeworks CACHE PATH
     "Install path for shared data.")
set( CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/of )

## create separate BUILD directories for libs and binaries (valid for in-source
#  and out-of-source builds)

# set output path for the shared libraries (cmake built-in)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH
    "Output directory for shared libraries")

# set output path for the static libraries (cmake built-in)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH
    "Output directory for static libraries")

# set output path for executables (cmake built-in)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH
     "Output directory for applications")

# set output path for extra data (see macro below)
set (EXTRA_DATA_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/share/openframeworks
     CACHE PATH "Output directory for data (e.g. share/openframeworks)")


#--------------------------------------------------------------------------
# Macro: REQUIRES (the dependency must be defined to build)
#--------------------------------------------------------------------------
macro (REQUIRES DEPENDENCY MSG)
    if (NOT DEFINED ${DEPENDENCY} OR NOT ${DEPENDENCY})
        message("EE ${MSG}: ${DEPENDENCY} not defined")
        RETURN()
    endif ()
endmacro ()

#--------------------------------------------------------------------------
# Macro: SET_EMPTY_DEPENDENCY (def all variables empty to avoid missing vars)
#--------------------------------------------------------------------------
macro (SET_EMPTY_DEPENDENCY DEP)
    if (DEFINED HAVE_${DEP})
        # OK, all variables set
    else ()
        # define empty variables
        set (${DEP}_INCLUDES "")
        set (${DEP}_LIBDIRS "")
        set (${DEP}_CFLAGS "")
        set (${DEP}_LDFLAGS "")
        set (${DEP}_LIBS "")
        set (HAVE_${DEP} false)
    endif ()
endmacro ()

#--------------------------------------------------------------------------
# Macro: USES (calls SET_EMPTY for list of dependencies)
#--------------------------------------------------------------------------
macro (USES DEPENDENCIES)
    foreach (DEPENDENCY ${ARGV})
        SET_EMPTY_DEPENDENCY(${DEPENDENCY})
    endforeach (DEPENDENCY ${ARGV})
endmacro (USES)

#--------------------------------------------------------------------------
# Macro: SET_CONFIG_VAR (set HAVE_XXX in current scope)
#--------------------------------------------------------------------------
macro (SET_CONFIG_VAR V)
    # set for local usage in current scope
    set (${V} true)
endmacro ()

#--------------------------------------------------------------------------
# Macro: EXPORT_CONFIG_VAR (stores HAVE_XXX variable for parent scope)
#--------------------------------------------------------------------------
macro (EXPORT_CONFIG_VAR V)
    # set for local usage in current scope
    set (${V} true)

    # export into parent scope
    set (${V} true PARENT_SCOPE)

    # append to list for push (in case the same command is later called
    # again in the current scope)
    set (_EXPORT_CONFIG_VAR_LIST ${_EXPORT_CONFIG_VAR_LIST} ${V})

    # export into parent scope
    set (_EXPORT_CONFIG_VAR_LIST ${_EXPORT_CONFIG_VAR_LIST} PARENT_SCOPE)

endmacro ()

#--------------------------------------------------------------------------
# Macro: PUSH_EXPORT_VARS (pushes all exported variables one scope up)
#--------------------------------------------------------------------------
macro (PUSH_EXPORT_VARS)
    foreach (EXPORT_VAR ${_EXPORT_CONFIG_VAR_LIST})
        set (${EXPORT_VAR} ${${EXPORT_VAR}} PARENT_SCOPE)
    endforeach ()
endmacro ()

#--------------------------------------------------------------------------
# Macro: EXPAND_LIST (converts any number of Cmake lists to a single whitespace
#        delimited string)
#--------------------------------------------------------------------------
macro (EXPAND_LIST S)
  set (${S} "")
  foreach(ARGLIST ${ARGN})  # ARGN is the variable containing all remaining args
    foreach(ARG ${ARGLIST})
      set(${S} "${${S}} ${ARG}")
    endforeach()
  endforeach()
endmacro()


#--------------------------------------------------------------------------
# Macro: APPEND_LIBRARIES (copies all entries that look like libraries)
#--------------------------------------------------------------------------
macro (APPEND_LIBRARIES T S)
    set (_SKIP_LIB_ENTRY false)
    # message ("=== Append lib: S='${${S}}' >> T='${${T}}' ")
    foreach (LIB_ENTRY ${${S}})
        if (${LIB_ENTRY} STREQUAL "-framework")
            set (_SKIP_LIB_ENTRY true)
        else ()
            if (NOT ${_SKIP_LIB_ENTRY})
                set (${T} ${${T}} ${LIB_ENTRY})
                set (_SKIP_LIB_ENTRY false)
            endif ()
        endif ()
    endforeach ()
    # message ("=== Result lib: ${${T}}")
endmacro ()

#--------------------------------------------------------------------------
# Macro: APPEND_FRAMEWORKS (copies all entries that look like OSX Frameworks)
#--------------------------------------------------------------------------
macro (APPEND_FRAMEWORKS T S)
    set (_NEXT_IS_FRAMEWORK false)
    # message ("=== Append fw: S='${${S}}' >> T='${${T}}' ")
    if (IS_DARWIN)
        foreach (LIB_ENTRY ${${S}})
            if (${LIB_ENTRY} STREQUAL "-framework")
                set (_NEXT_IS_FRAMEWORK true)
            else ()
                if (${_NEXT_IS_FRAMEWORK})
                    set (${T} ${${T}} "-framework ${LIB_ENTRY}")
                    set (_NEXT_IS_FRAMEWORK false)
             endif ()
            endif ()
        endforeach ()
    endif ()
    # message ("=== Result fw: ${${T}}")
endmacro ()


message("==================================================================")
message(" OpenFrameworks Library ")
message("==================================================================")

#--------------------------------------------------------------------------
# Build Dependencies Check
#--------------------------------------------------------------------------
set (OF_BROKEN_DEPENDENCY FALSE)
set (GSTREAMER_MIN_VERSION 0.10)
set (OPENCV_MIN_VERSION 2.1)
set (PORTAUDIO_MIN_VERSION 19)
set (OPENAL_MIN_VERSION 1.12)
set (MPG123_MIN_VERSION 1.12.1)
set (CAIRO_MIN_VERSION 1.10.0)
set (OPENASSETIMPORT_MIN_VERSION 2.0)
set (PCL_MIN_VERSION 1.7)
set (OPENNI_MIN_VERSION 1.5)

#--------------------------------------------------------------------------
# Fmodex (Note: find requires correct CMAKE_PREFIX_PATH)
#--------------------------------------------------------------------------
message (STATUS "Checking for Fmod...")
find_library(FMOD_LIBRARIES NAMES fmodex fmodex64 DOC "Fmod Audio Library")
find_library(FMODL_LIBRARIES NAMES fmodexL fmodexL64 DOC "Fmod Audio Library")
if (NOT FMOD_LIBRARIES OR NOT FMODL_LIBRARIES)
    message("EE FMod libraries NOT FOUND. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    set (OF_BROKEN_DEPENDENCY true)
    SET_EMPTY_DEPENDENCY(FMOD)
else ()
    get_filename_component(FMOD_LIBRARY_DIRS ${FMOD_LIBRARIES} PATH)
    get_filename_component(FMOD_LIBRARY ${FMOD_LIBRARIES} NAME)
    get_filename_component(FMODL_LIBRARY ${FMODL_LIBRARIES} NAME)
    find_path(FMOD_INCLUDE_DIRS fmod.h PATH_SUFFIXES fmodex)

    # version
    FILE(STRINGS ${FMOD_INCLUDE_DIRS}/fmod.h FM_VSTR REGEX ".*define FMOD_VERSION.*")
    STRING(REGEX REPLACE ".*[^0-9]([0-9]*).*" "\\1" FM_V "${FM_VSTR}")
    MATH ( EXPR FM_MAJ "${FM_V} / 10000")
    MATH ( EXPR FM_MIN "(${FM_V} - ${FM_MAJ} * 10000) / 100")
    MATH ( EXPR FM_PAT "${FM_V} % 100")
    SET (FMOD_VERSION "${FM_MAJ}.${FM_MIN}.${FM_PAT}")

    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${FMOD_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${FMOD_LIBRARY} ${FMODL_LIBRARY})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} -DOF_SOUND_PLAYER_FMOD)
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${FMOD_LIBRARY_DIRS})

    message(STATUS "  Fmod found version: ${FMOD_VERSION}")
    message(STATUS "    includes:  ${FMOD_INCLUDE_DIRS}")
    message(STATUS "    libraries: ${FMOD_LIBRARY}, ${FMODL_LIBRARY}")
    message(STATUS "    libdirs:   ${FMOD_LIBRARY_DIRS}")

    SET_CONFIG_VAR (HAVE_FMODEX)
endif ()

#--------------------------------------------------------------------------
# OpenCV (required for addon)
#--------------------------------------------------------------------------
find_package(OpenCV ${OPENCV_MIN_VERSION})
if (NOT OPENCV_FOUND)
    message("WW OpenCV >= ${OPENCV_MIN_VERSION} NOT FOUND. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly OR install system-wide package.")
    SET_EMPTY_DEPENDENCY(OPENCV)
else ()
    SET_CONFIG_VAR (HAVE_OPENCV)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "opencv")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${OPENCV_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${OPENCV_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${OPENCV_CFLAGS})
#    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${OPENCV_LDFLAGS})
    APPEND_FRAMEWORKS(OF_FRAMEWORKS OPENCV_LDFLAGS)
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${OPENCV_LIBRARY_DIRS})
endif ()

#--------------------------------------------------------------------------
# PCL (required for addon)
#--------------------------------------------------------------------------
message (STATUS "Checking for Point Cloud Library (PCL) >= ${PCL_MIN_VERSION}...")
find_package(PCL ${PCL_MIN_VERSION})
if (NOT PCL_FOUND)
    message("WW PCL ${PCL_MIN_VERSION} NOT FOUND. Please install from contrib/ or package.")
    SET_EMPTY_DEPENDENCY(PCL)
else ()
    SET_CONFIG_VAR (HAVE_PCL)
    list (APPEND OF_PKGCONF_DEPENDS
        pcl_features
        pcl_surface
        pcl_filters
        pcl_segmentation
        pcl_io
        pcl_sample_consensus
        pcl_common
        pcl_kdtree
        pcl_octree
    )
    list (APPEND OF_CORE_INCLUDES ${PCL_INCLUDE_DIRS})

    # remove the nasty -DDISABLE_LIBUSB-1.0 from CMAKE definitions
    # since it creates compile warnings
    remove_definitions("-DDISABLE_LIBUSB-1.0")

    if(NOT APPLE)
        add_definitions("-fopenmp")
# TODO: fix LD_FLAGS bug in OF examples first
#        list(APPEND OF_CORE_LDFLAGS "-fopenmp")
    endif()

    list (APPEND PCL_ALL_LIBRARIES
        ${PCL_FEATURES_LIBRARIES}
        ${PCL_SURFACE_LIBRARIES}
        ${PCL_FILTERS_LIBRARIES}
        ${PCL_SEGMENTATION_LIBRARIES}
        ${PCL_KDTREE_LIBRARIES}
        ${PCL_OCTREE_LIBRARIES}
        ${PCL_IO_LIBRARIES}
        ${PCL_COMMON_LIBRARIES}
        ${PCL_SAMPLE_CONSENSUS_LIBRARIES}
    )

    # parse PCL lib list to extract optimized versions only, sort them so
    # all pcl libraries are listed first
    set (PCL_SKIP_NEXT_LIB 0)
    foreach(PCL_L ${PCL_ALL_LIBRARIES})
        if (${PCL_SKIP_NEXT_LIB} GREATER 0)
            math(EXPR PCL_SKIP_NEXT_LIB "${PCL_SKIP_NEXT_LIB} - 1")
        else ()
            if ("${PCL_L}" MATCHES "optimized")
                set (PCL_SKIP_NEXT_LIB 0)
            elseif ("${PCL_L}" MATCHES "debug")
                set (PCL_SKIP_NEXT_LIB 1)
            else ()
                if ("${PCL_L}" MATCHES "^.*pcl.*$")
                    if (("${PCL_L}" MATCHES "^.*pcl_sample_consensus.*$") OR
                        ("${PCL_L}" MATCHES "^.*pcl_search.*$") OR
                        ("${PCL_L}" MATCHES "^.*pcl_kdtree.*$") OR
                        ("${PCL_L}" MATCHES "^.*pcl_common.*$"))
                        list(APPEND PCL_CLEANED_REORDERED_LIBRARIES ${PCL_L})
                    else ()
                        list(APPEND PCL_CLEANED_LIBRARIES ${PCL_L})
                    endif()
                else ()
                    list(APPEND PCL_OTHER_LIBRARIES ${PCL_L})
                endif()
            endif()
        endif()
    endforeach()
    list (REMOVE_DUPLICATES PCL_OTHER_LIBRARIES)
    list (REMOVE_DUPLICATES PCL_CLEANED_LIBRARIES)
    list (REMOVE_DUPLICATES PCL_CLEANED_REORDERED_LIBRARIES)

    if (NOT APPLE)
        list(APPEND PCL_OTHER_LIBRARIES "gomp")
    endif()

    list (APPEND OF_CORE_LIBS ${PCL_CLEANED_LIBRARIES} ${PCL_CLEANED_REORDERED_LIBRARIES} ${PCL_OTHER_LIBRARIES})
    list (APPEND OF_CORE_LIBDIRS ${PCL_LIBRARY_DIRS})

endif ()

#--------------------------------------------------------------------------
# OpenNI (required for addon)
#--------------------------------------------------------------------------
find_package(OpenNI ${OPENNI_MIN_VERSION})
if (NOT OPENNI_FOUND)
    message("WW OpenNI >= ${OPENNI_MIN_VERSION} NOT FOUND. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly OR install system-wide package.")
    SET_EMPTY_DEPENDENCY(OPENNI)
else ()
    SET_CONFIG_VAR (HAVE_OPENNI)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "openni")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${OPENNI_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${OPENNI_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${OPENNI_CFLAGS})
#    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${OPENNI_LDFLAGS})
    APPEND_FRAMEWORKS(OF_FRAMEWORKS OPENNI_LDFLAGS)
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${OPENNI_LIBRARY_DIRS})
endif ()

#--------------------------------------------------------------------------
# Gstreamer (also requires udev)
#--------------------------------------------------------------------------
find_package(GStreamer ${GSTREAMER_MIN_VERSION})
find_package(Udev)
if (NOT GST_FOUND OR NOT UDEV_FOUND)
    if (NOT GST_FOUND)
        message("WW GStreamer >= ${GSTREAMER_MIN_VERSION} NOT FOUND: some video components disabled. Please install package gstreamer to enable.")
        SET_EMPTY_DEPENDENCY(GSTREAMER)
    endif ()
    if (NOT UDEV_FOUND)
        message("WW libudev NOT FOUND, Gstreamer video disabled. Please install package libudev-dev to enable.")
        SET_EMPTY_DEPENDENCY(UDEV)
    endif ()
else ()
    SET_CONFIG_VAR (HAVE_GSTREAMER)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "gstreamer")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${GST_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${GST_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${GST_CFLAGS} -DOF_VIDEO_PLAYER_GSTREAMER -DOF_VIDEO_CAPTURE_GSTREAMER)
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${GST_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${GST_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_UDEV)
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${UDEV_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${UDEV_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${UDEV_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${UDEV_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${UDEV_LIBRARY_DIRS})
endif ()

#--------------------------------------------------------------------------
# Freetype
#--------------------------------------------------------------------------
find_package(Freetype)
if (NOT FREETYPE_FOUND)
    message("EE Freetype Library NOT FOUND, please install libfreetype6-dev")
    set (OF_BROKEN_DEPENDENCY true)
    SET_EMPTY_DEPENDENCY(FREETYPE)
else ()
    SET_CONFIG_VAR (HAVE_FREETYPE)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "freetype2")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${FREETYPE_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${FREETYPE_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${FREETYPE_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${FREETYPE_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${FREETYPE_LIBRARY_DIRS})
endif ()

#--------------------------------------------------------------------------
# FreeImage
#--------------------------------------------------------------------------
message (STATUS "Checking for FreeImage...")
find_library(FREEIMAGE_LIBRARIES NAMES FreeImage freeimage)
if (NOT FREEIMAGE_LIBRARIES)
    message("EE FreeImage libraries NOT FOUND, please install libfreeimage-dev")
    set (OF_BROKEN_DEPENDENCY true)
    SET_EMPTY_DEPENDENCY(FREEIMAGE)
else ()
    get_filename_component(FREEIMAGE_LIBRARY_DIRS ${FREEIMAGE_LIBRARIES} PATH)
    get_filename_component(FREEIMAGE_LIBRARY ${FREEIMAGE_LIBRARIES} NAME)
    find_path(FREEIMAGE_INCLUDE_DIRS FreeImage.h)

    # version
    FILE(STRINGS ${FREEIMAGE_INCLUDE_DIRS}/FreeImage.h FI_VSTR REGEX ".*define FREEIMAGE_MAJOR_VERSION.*")
    STRING(REGEX REPLACE ".*[^0-9]([0-9]*).*" "\\1" FI_MAJ "${FI_VSTR}")
    FILE(STRINGS ${FREEIMAGE_INCLUDE_DIRS}/FreeImage.h FI_VSTR REGEX ".*define FREEIMAGE_MINOR_VERSION.*")
    STRING(REGEX REPLACE ".*[^0-9]([0-9]*).*" "\\1" FI_MIN "${FI_VSTR}")
    FILE(STRINGS ${FREEIMAGE_INCLUDE_DIRS}/FreeImage.h FI_VSTR REGEX ".*define FREEIMAGE_RELEASE_SERIAL.*")
    STRING(REGEX REPLACE ".*[^0-9]([0-9]*).*" "\\1" FI_PAT "${FI_VSTR}")
    SET (FREEIMAGE_VERSION "${FI_MAJ}.${FI_MIN}.${FI_PAT}")

    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${FREEIMAGE_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${FREEIMAGE_LIBRARY})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${FREEIMAGE_LIBRARY_DIRS})

    message(STATUS "  FreeImage found version: ${FREEIMAGE_VERSION}")
    message(STATUS "   includes:  ${FREEIMAGE_INCLUDE_DIRS}")
    message(STATUS "   libraries: ${FREEIMAGE_LIBRARIES}")

    SET_CONFIG_VAR (HAVE_FREEIMAGE)
ENDIF ()

#--------------------------------------------------------------------------
# OpenGL
#--------------------------------------------------------------------------
message(STATUS "Checking for OpenGL...")
find_package(OpenGL QUIET)
if (NOT OPENGL_FOUND)
    message("EE OpenGL Libraries NOT FOUND. Please install packages (e.g. freeglut3-dev libglu1-mesa-dev libgl-mesa-dev libglu-dev)")
    set (OF_BROKEN_DEPENDENCY true)
    SET_EMPTY_DEPENDENCY(OPENGL)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${OPENGL_INCLUDE_DIR})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${OPENGL_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${OPENGL_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${OPENGL_LIBRARY_DIRS})

    # special library handling on OSX
    if (IS_DARWIN)
        set (OPENGL_LIBRARIES "")
        set (OPENGL_LDFLAGS "-framework;OpenGL;-framework;AGL")
        APPEND_FRAMEWORKS(OF_FRAMEWORKS OPENGL_LDFLAGS)
    else ()
        set (OF_CORE_LIBS ${OF_CORE_LIBS} ${OPENGL_LIBRARIES})
    endif ()

    message(STATUS "  OpenGL found.")
    message(STATUS "    includes: ${OPENGL_INCLUDE_DIR}")
    message(STATUS "    library:  ${OPENGL_LIBRARIES}")
    message(STATUS "    libdir:   ${OPENGL_LIBRARY_DIRS}")
    message(STATUS "    cflags:   ${OPENGL_CFLAGS}")
    message(STATUS "    ldflags:  ${OPENGL_LDFLAGS}")
    SET_CONFIG_VAR (HAVE_OPENGL)

endif ()

#--------------------------------------------------------------------------
# GLUT
#--------------------------------------------------------------------------
message(STATUS "Checking for GLUT...")
find_package(GLUT QUIET)
if (NOT GLUT_FOUND)
    message("EE GL Utility Library glut NOT FOUND. Please install packages (e.g. freeglut3-dev)")
    set (OF_BROKEN_DEPENDENCY true)
    SET_EMPTY_DEPENDENCY(GLUT)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${GLUT_INCLUDE_DIR})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${GLUT_LDFLAGS})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${GLUT_CFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${GLUT_LIBRARY_DIRS})

    # special library handling on OSX
    if (IS_DARWIN)
        # create a list: -framework;Name1;-framework;Name2
        string(REPLACE " " ";" GLUT_LDFLAGS "${GLUT_LIBRARIES}")
        set(GLUT_LIBRARIES "")
        APPEND_FRAMEWORKS(OF_FRAMEWORKS GLUT_LDFLAGS)
    else ()
        set (OF_CORE_LIBS ${OF_CORE_LIBS} ${GLUT_LIBRARIES})
    endif ()

    message(STATUS "  GLUT found.")
    message(STATUS "    includes: ${GLUT_INCLUDE_DIR}")
    message(STATUS "    library:  ${GLUT_LIBRARIES}")
    message(STATUS "    libdir:   ${GLUT_LIBRARY_DIRS}")
    message(STATUS "    cflags:   ${GLUT_CFLAGS}")
    message(STATUS "    ldflags:  ${GLUT_LDFLAGS}")
    SET_CONFIG_VAR (HAVE_GLUT)

endif ()

#--------------------------------------------------------------------------
# GLEW
#--------------------------------------------------------------------------
find_package(GLEW)
if (NOT GLEW_FOUND)
    message("EE GLEW Library NOT FOUND. Please install packages (e.g. glew)")
    set (OF_BROKEN_DEPENDENCY true)
    SET_EMPTY_DEPENDENCY(GLEW)
else ()
    SET_CONFIG_VAR (HAVE_GLEW)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "glew")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${GLEW_INCLUDE_DIR})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${GLEW_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${GLEW_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${GLEW_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${GLEW_LIBRARY_DIRS})
endif ()

#--------------------------------------------------------------------------
# POCO
#--------------------------------------------------------------------------
find_package(Poco)
if (NOT POCO_FOUND)
    message("WW Poco Foundation libraries NOT FOUND: oF Events, oF Arduino and ofxVideoGrabber disabled. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    SET_EMPTY_DEPENDENCY(POCO)
else ()
    SET_CONFIG_VAR (HAVE_POCO)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "poco")
    if (IS_DARWIN)
        foreach (I ${POCO_INCLUDE_DIRS})
            # add idirafter to let gcc include Poco headers _after_ all system
            # headers; this avoids lookup conflicts with basic string on OSX
            set (OF_CORE_CFLAGS_INTERNAL ${OF_CORE_CFLAGS_INTERNAL} -idirafter ${I})
        endforeach ()
    else ()
        set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${POCO_INCLUDE_DIRS})
    endif ()
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${POCO_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${POCO_CFLAGS} -DOF_USING_POCO)
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${POCO_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${POCO_LIBRARY_DIRS})
endif ()


#--------------------------------------------------------------------------
# RtAudio
#--------------------------------------------------------------------------
FIND_package(RtAudio)
if (NOT RTAUDIO_FOUND)
    message("WW RtAudio library NOT FOUND. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    SET_EMPTY_DEPENDENCY(RTAUDIO)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${RTAUDIO_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${RTAUDIO_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${RTAUDIO_CFLAGS} -DOF_SOUNDSTREAM_RTAUDIO)
#    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${RTAUDIO_LDFLAGS})
    APPEND_FRAMEWORKS(OF_FRAMEWORKS RTAUDIO_LDFLAGS)
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${RTAUDIO_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_RTAUDIO)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "rtaudio")
endif ()

#--------------------------------------------------------------------------
# PortAudio (new in oF 0.07)
#--------------------------------------------------------------------------
find_package(PortAudio ${PORTAUDIO_MIN_VERSION})
if (NOT PORTAUDIO_FOUND)
    message("WW PortAudio NOT FOUND. Please install packages (e.g. portaudio and portaudio_cpp)")
    SET_EMPTY_DEPENDENCY(PORTAUDIO)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${PORTAUDIO_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${PORTAUDIO_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${PORTAUDIO_CFLAGS} -DOF_SOUNDSTREAM_PORTAUDIO)
#    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${PORTAUDIO_LDFLAGS})
    APPEND_FRAMEWORKS(OF_FRAMEWORKS PORTAUDIO_LDFLAGS)
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${PORTAUDIO_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_PORTAUDIO)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "portaudio-2.0")
endif ()

#--------------------------------------------------------------------------
# OpenAL (new in oF 0.07, requires KISS)
#--------------------------------------------------------------------------
find_package(SndFile)
find_package(Kiss)
find_package(OpenAL ${OPENAL_MIN_VERSION})
if (NOT OPENAL_FOUND OR NOT KISS_FOUND OR NOT SNDFILE_FOUND)
    if (NOT OPENAL_FOUND)
        message("WW OpenAL NOT FOUND. Please install packages (e.g. openal)")
        SET_EMPTY_DEPENDENCY(OPENAL)
    endif ()
    if (NOT KISS_FOUND)
        message("WW Kiss library NOT FOUND. This library is required for OpenAL support in oF. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
        SET_EMPTY_DEPENDENCY(KISS)
    endif ()
    if (NOT SNDFILE_FOUND)
        message("WW sndfile library NOT FOUND. This library is required for OpenAL support in oF. Please install package (e.g. libsndfile)")
        SET_EMPTY_DEPENDENCY(SNDFILE)
    endif ()
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${OPENAL_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${OPENAL_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${OPENAL_CFLAGS} -DOF_SOUND_PLAYER_OPENAL)
#    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${OPENAL_LDFLAGS})
    APPEND_FRAMEWORKS(OF_FRAMEWORKS OPENAL_LDFLAGS)
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${OPENAL_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_OPENAL)
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${KISS_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${KISS_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${KISS_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${KISS_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${KISS_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_KISS)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "kiss")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${SNDFILE_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${SNDFILE_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${SNDFILE_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${SNDFILE_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${SNDFILE_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_SNDFILE)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "sndfile")
endif ()

#--------------------------------------------------------------------------
# MPG123 (new in oF 0.07)
#--------------------------------------------------------------------------
find_package(MPG123 ${MPG123_MIN_VERSION})
if (NOT MPG123_FOUND)
    message("WW MPG123 NOT FOUND. Please install packages (e.g. mpg123)")
    SET_EMPTY_DEPENDENCY(MPG123)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${MPG123_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${MPG123_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${MPG123_CFLAGS} -DOF_USING_MPG123)
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${MPG123_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${MPG123_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_MPG123)
endif ()


#--------------------------------------------------------------------------
# OpenAssetImport (new in oF 0.07)
#--------------------------------------------------------------------------
find_package(OpenAssetImport ${OPENASSETIMPORT_MIN_VERSION})
if (NOT OAI_FOUND)
    message("WW OpenAssetImport library NOT FOUND. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    SET_EMPTY_DEPENDENCY(OAI)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${OAI_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${OAI_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${OAI_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${OAI_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${OAI_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_OPENASSETIMPORT)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "assimp")
endif ()


#--------------------------------------------------------------------------
# Cairo (new in oF 0.07) - optional
#--------------------------------------------------------------------------
find_package(Cairo ${CAIRO_MIN_VERSION})
if (NOT CAIRO_FOUND)
    message("WW Cairo NOT FOUND. Please install packages (e.g. cairo)")
    SET_EMPTY_DEPENDENCY(CAIRO)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${CAIRO_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${CAIRO_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${CAIRO_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${CAIRO_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${CAIRO_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_CAIRO)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "cairo")
endif ()

#--------------------------------------------------------------------------
# Tess2 (new in oF 0.07)
#--------------------------------------------------------------------------
find_package(Tess2)
if (NOT TESS2_FOUND)
    message("EE Tess2 NOT FOUND. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    set (OF_BROKEN_DEPENDENCY true)
    SET_EMPTY_DEPENDENCY(TESS2)
else ()
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${TESS2_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${TESS2_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${TESS2_CFLAGS})
#    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${TESS2_LDFLAGS})
    APPEND_FRAMEWORKS(OF_FRAMEWORKS TESS2_LDFLAGS)
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${TESS2_LIBRARY_DIRS})
    SET_CONFIG_VAR (HAVE_TESS2)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "tess2")
endif ()

#--------------------------------------------------------------------------
# TinyXML (required for addon)
#--------------------------------------------------------------------------
find_package(TinyXML ${TinyXML_MIN_VERSION})
if (NOT TINYXML_FOUND)
    message("WW TinyXML >= ${TinyXML_MIN_VERSION} NOT FOUND: XML read/write support disabled. Please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    SET_EMPTY_DEPENDENCY(TINYXML)
else ()
    SET_CONFIG_VAR (HAVE_TINYXML)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "tinyxml")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${TINYXML_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${TINYXML_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${TINYXML_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${TINYXML_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${TINYXML_LIBRARY_DIRS})
endif ()

#--------------------------------------------------------------------------
# DC1394 (required for addon)
#--------------------------------------------------------------------------
find_package(DC1394)
if (NOT DC1394_FOUND)
    message("WW libdc1394 NOT FOUND: IEEE1394 support disabled. Please install packages.")
    SET_EMPTY_DEPENDENCY(DC1394)
else ()
    SET_CONFIG_VAR (HAVE_DC1394)
    set (OF_PKGCONF_DEPENDS ${OF_PKGCONF_DEPENDS} "libdc1394-2")
    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${DC1394_INCLUDE_DIRS})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${DC1394_LIBRARIES})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} ${DC1394_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS} ${DC1394_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${DC1394_LIBRARY_DIRS})
endif ()

#--------------------------------------------------------------------------
# OSC (required for addon)
#--------------------------------------------------------------------------
message (STATUS "Checking for OSCpack...")
find_library(OSC oscpack DOC "Open Sound Control Library")
if (NOT OSC)
    message("WW OSCpack library NOT FOUND, please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    SET_EMPTY_DEPENDENCY(OSC)
else ()
    get_filename_component(OSC_LIBRARY_PATH ${OSC} PATH)
    get_filename_component(OSC_LIBRARY_NAME ${OSC} NAME)
    find_path(OSC_INCLUDE_PATH OscTypes.h PATH_SUFFIXES osc)
    find_path(OSCIP_INCLUDE_PATH IpEndpointName.h PATH_SUFFIXES ip)

    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES}
         ${OSC_INCLUDE_PATH} ${OSCIP_INCLUDE_PATH})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${OSC_LIBRARY_NAME})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${OSC_LIBRARY_PATH})

    message(STATUS "  OSCpack found.")
    message(STATUS "    includes: ${OSC_INCLUDE_PATH}, ${OSCIP_INCLUDE_PATH}")
    message(STATUS "    library:  ${OSC_LIBRARY_NAME}")
    message(STATUS "    libdir:   ${OSC_LIBRARY_PATH}")
    SET_CONFIG_VAR (HAVE_OSC)
endif ()


#--------------------------------------------------------------------------
# CreEPS (required for addon)
#--------------------------------------------------------------------------
message (STATUS "Checking for CreEPS...")
find_library(CREEPS CreEPS DOC "Create EPS Library")
if (NOT CREEPS)
    message("WW CreEPS library NOT FOUND, please install from contrib/ AND set CMAKE_PREFIX_PATH properly")
    SET_EMPTY_DEPENDENCY(CREEPS)
else ()
    get_filename_component(CREEPS_LIBRARY_PATH ${CREEPS} PATH)
    get_filename_component(CREEPS_LIBRARY_NAME ${CREEPS} NAME)
    find_path(CREEPS_INCLUDE_PATH CreEPS.hpp PATH_SUFFIXES CreEPS)

    # version
    FILE(STRINGS ${CREEPS_INCLUDE_PATH}/CreEPS.hpp CR_VSTR REGEX ".*EPS  Version.*")
    STRING(REGEX REPLACE ".*[^0-9]([0-9]+.[0-9]+).*" "\\1" CR_VERSION
        "${CR_VSTR}")

    set (OF_CORE_INCLUDES ${OF_CORE_INCLUDES} ${CREEPS_INCLUDE_PATH})
    set (OF_CORE_LIBS ${OF_CORE_LIBS} ${CREEPS_LIBRARY_NAME})
    set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS})
    set (OF_CORE_LDFLAGS ${OF_CORE_LDFLAGS})
    set (OF_CORE_LIBDIRS ${OF_CORE_LIBDIRS} ${CREEPS_LIBRARY_PATH})

    message(STATUS "  CreEPS found version: ${CR_VERSION}")
    message(STATUS "    includes:  ${CREEPS_INCLUDE_PATH}")
    message(STATUS "    library:   ${CREEPS_LIBRARY_NAME}")
    message(STATUS "    libdir:    ${CREEPS_LIBRARY_PATH}")

    SET_CONFIG_VAR (HAVE_CREEPS)
endif ()

#--------------------------------------------------------------------------
#   FAIL on serious error (when required library dependency is not present)
#--------------------------------------------------------------------------
if (OF_BROKEN_DEPENDENCY)
    message("EE Cannot build OpenFrameworks Library. See details above.")
    SET_EMPTY_DEPENDENCY(OF_CORE)
    return ()
endif ()

set (HAVE_OPENFRAMEWORKS true)

#--------------------------------------------------------------------------
#   Define core variables before recursing into addons
#--------------------------------------------------------------------------

if (IS_DARWIN32)
  list(APPEND OF_FRAMEWORKS
       "-framework QuickTime"
       "-framework QTKit"
       "-framework CoreVideo"
       "-framework Carbon")
endif ()

if (IS_DARWIN64)
  list(APPEND OF_FRAMEWORKS
       "-framework QTKit"
       "-framework CoreVideo"
       "-framework Carbon")
endif ()


# add the oF directories to the include list
set (OF_INCLUDES
    ${OF_CORE_INCLUDES}
    ${CMAKE_SOURCE_DIR}/openframeworks
    ${CMAKE_SOURCE_DIR}/openframeworks/3d
    ${CMAKE_SOURCE_DIR}/openframeworks/app
    ${CMAKE_SOURCE_DIR}/openframeworks/communication
    ${CMAKE_SOURCE_DIR}/openframeworks/events
    ${CMAKE_SOURCE_DIR}/openframeworks/gl
    ${CMAKE_SOURCE_DIR}/openframeworks/graphics
    ${CMAKE_SOURCE_DIR}/openframeworks/math
    ${CMAKE_SOURCE_DIR}/openframeworks/sound
    ${CMAKE_SOURCE_DIR}/openframeworks/types
    ${CMAKE_SOURCE_DIR}/openframeworks/utils
    ${CMAKE_SOURCE_DIR}/openframeworks/video
    )


#--------------------------------------------------------------------------
#   Recurse into addon directories (order is important for build dependendies)
#   These will define:
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
message("==================================================================")
message(" OpenFrameworks Addons ")
message("==================================================================")
add_subdirectory (openframeworks/addon/ofxXmlSettings/)
add_subdirectory (openframeworks/addon/ofx3DModelLoader/)
add_subdirectory (openframeworks/addon/ofxAccelerometer/)
add_subdirectory (openframeworks/addon/ofxAssimpModelLoader/)
add_subdirectory (openframeworks/addon/ofxCv/)
add_subdirectory (openframeworks/addon/ofxDiskGrabber/)
add_subdirectory (openframeworks/addon/ofxGui/)
add_subdirectory (openframeworks/addon/ofxLibdc/)
#add_subdirectory (openframeworks/addon/ofxMultiTouch/)
add_subdirectory (openframeworks/addon/ofxNetwork/)
add_subdirectory (openframeworks/addon/ofxOpenCv/)
add_subdirectory (openframeworks/addon/ofxOsc/)
add_subdirectory (openframeworks/addon/ofxSynth/)
add_subdirectory (openframeworks/addon/ofxThreadedImageLoader/)
add_subdirectory (openframeworks/addon/ofxUI/)
add_subdirectory (openframeworks/addon/ofxVectorGraphics/)
add_subdirectory (openframeworks/addon/ofxVideoGrabber/)
add_subdirectory (openframeworks/addon/ofxPCL/)

#--------------------------------------------------------------------------
# BUILD Library
#--------------------------------------------------------------------------

# collect sound-related source files
set(SOUND_SOURCES
    openframeworks/sound/ofSoundPlayer.cpp
    openframeworks/sound/ofBaseSoundPlayer.cpp
    openframeworks/sound/ofSoundStream.cpp
    openframeworks/sound/ofBaseSoundStream.cpp
)

set(SOUND_HEADERS
    openframeworks/sound/ofBaseSoundPlayer.h
    openframeworks/sound/ofBaseSoundStream.h
    openframeworks/sound/ofSoundPlayer.h
    openframeworks/sound/ofSoundStream.h
)

if (HAVE_PORTAUDIO)
    set(SOUND_SOURCES ${SOUND_SOURCES}
        openframeworks/sound/ofPASoundStream.cpp)
    set(SOUND_HEADERS ${SOUND_HEADERS}
        openframeworks/sound/ofPASoundStream.h)
endif()

if (HAVE_OPENAL)
    set(SOUND_SOURCES ${SOUND_SOURCES}
        openframeworks/sound/ofOpenALSoundPlayer.cpp)
    set(SOUND_HEADERS ${SOUND_HEADERS}
        openframeworks/sound/ofOpenALSoundPlayer.h)
endif()

if (HAVE_FMODEX)
    set(SOUND_SOURCES ${SOUND_SOURCES}
        openframeworks/sound/ofFmodSoundPlayer.cpp)
    set(SOUND_HEADERS ${SOUND_HEADERS}
        openframeworks/sound/ofFmodSoundPlayer.h)
endif()

if (HAVE_RTAUDIO)
    set(SOUND_SOURCES ${SOUND_SOURCES}
        openframeworks/sound/ofRtAudioSoundStream.cpp)
    set(SOUND_HEADERS ${SOUND_HEADERS}
        openframeworks/sound/ofRtAudioSoundStream.h)
endif ()

if (HAVE_CAIRO)
    set(CAIRO_SOURCES openframeworks/graphics/ofCairoRenderer.cpp)
    set(CAIRO_HEADERS openframeworks/graphics/ofCairoRenderer.h)
endif ()


# collect video related source files
set(VIDEO_SOURCES
    openframeworks/video/ofVideoPlayer.cpp
    openframeworks/video/ofVideoGrabber.cpp
)

set (VIDEO_HEADERS
    openframeworks/video/ofVideoGrabber.h
    openframeworks/video/ofVideoPlayer.h
)

if (HAVE_GSTREAMER)
    set(VIDEO_SOURCES ${VIDEO_SOURCES}
        openframeworks/video/ofGstVideoPlayer.cpp
        openframeworks/video/ofGstUtils.cpp
        openframeworks/video/ofGstVideoGrabber.cpp
    )
    set(VIDEO_HEADERS ${VIDEO_HEADERS}
        openframeworks/video/ofGstVideoPlayer.h
        openframeworks/video/ofGstUtils.h
        openframeworks/video/ofGstVideoGrabber.h
    )
endif()

if (IS_DARWIN32)
    set(VIDEO_SOURCES ${VIDEO_SOURCES}
        openframeworks/video/ofxQTKitVideoGrabber.mm
        openframeworks/video/ofxQTKitVideoPlayer.mm
        openframeworks/video/QTKitMovieRenderer.m
#        openframeworks/video/ofQuickTimePlayer.cpp
#        openframeworks/video/ofQtUtils.cpp
#        openframeworks/video/ofQuickTimeGrabber.cpp
    )
    set(VIDEO_HEADERS ${VIDEO_HEADERS}
        openframeworks/video/ofxQTKitVideoGrabber.h
        openframeworks/video/ofxQTKitVideoPlayer.h
        openframeworks/video/QTKitMovieRenderer.h
#        openframeworks/video/ofQtUtils.h
#        openframeworks/video/ofQuickTimeGrabber.h
#        openframeworks/video/ofQuickTimePlayer.h
    )
endif()

if (IS_DARWIN64)
    set(VIDEO_SOURCES ${VIDEO_SOURCES}
        openframeworks/video/ofxQTKitVideoGrabber.mm
    )
    set(VIDEO_HEADERS ${VIDEO_HEADERS}
        openframeworks/video/ofxQTKitVideoGrabber.h
    )
endif()

if (IS_DARWIN64 OR IS_DARWIN32)
    set(DARWIN_SOURCES ${DARWIN_SOURCES}
        openframeworks/utils/ofCocoa.mm
    )
    set(DARWIN_HEADERS ${DARWIN_HEADERS}
        openframeworks/utils/ofCocoa.h
    )
endif()

set (COMMON_HEADERS
    openframeworks/3d/of3dUtils.h
    openframeworks/3d/ofCamera.h
    openframeworks/3d/ofEasyCam.h
    openframeworks/3d/ofMesh.h
    openframeworks/3d/ofNode.h
    openframeworks/app/ofAppBaseWindow.h
    openframeworks/app/ofAppGlutWindow.h
    openframeworks/app/ofAppNoWindow.h
    openframeworks/app/ofAppRunner.h
    openframeworks/app/ofBaseApp.h
    openframeworks/communication/ofArduino.h
    openframeworks/communication/ofSerial.h
    openframeworks/events/ofEvents.h
    openframeworks/events/ofEventUtils.h
    openframeworks/gl/ofFbo.h
    openframeworks/gl/ofGLRenderer.h
    openframeworks/gl/ofGLUtils.h
    openframeworks/gl/ofLight.h
    openframeworks/gl/ofMaterial.h
    openframeworks/gl/ofShader.h
    openframeworks/gl/ofTexture.h
    openframeworks/gl/ofVbo.h
    openframeworks/gl/ofVboMesh.h
    openframeworks/graphics/ofBitmapFont.h
    openframeworks/graphics/ofGraphics.h
    openframeworks/graphics/ofImage.h
    openframeworks/graphics/ofPath.h
    openframeworks/graphics/ofPixels.h
    openframeworks/graphics/ofPolyline.h
    openframeworks/graphics/ofRendererCollection.h
    openframeworks/graphics/ofTessellator.h
    openframeworks/graphics/ofTrueTypeFont.h
    openframeworks/math/ofMath.h
    openframeworks/math/ofMatrix3x3.h
    openframeworks/math/ofMatrix4x4.h
    openframeworks/math/ofQuaternion.h
    openframeworks/math/ofVec2f.h
    openframeworks/math/ofVec3f.h
    openframeworks/math/ofVec4f.h
    openframeworks/math/ofVectorMath.h
    openframeworks/ofMain.h
    openframeworks/types/ofBaseTypes.h
    openframeworks/types/ofColor.h
    openframeworks/types/ofPoint.h
    openframeworks/types/ofRectangle.h
    openframeworks/types/ofTypes.h
    openframeworks/utils/ofConstants.h
    openframeworks/utils/ofFileUtils.h
    openframeworks/utils/ofLog.h
    openframeworks/utils/ofNoise.h
    openframeworks/utils/ofSystemUtils.h
    openframeworks/utils/ofThread.h
    openframeworks/utils/ofURLFileLoader.h
    openframeworks/utils/ofUtils.h
)

set (COMMON_SOURCES
    openframeworks/3d/ofEasyCam.cpp
    openframeworks/3d/ofNode.cpp
    openframeworks/3d/of3dUtils.cpp
    openframeworks/3d/ofCamera.cpp
    openframeworks/3d/ofMesh.cpp
    openframeworks/graphics/ofTrueTypeFont.cpp
    openframeworks/graphics/ofBitmapFont.cpp
    openframeworks/graphics/ofGraphics.cpp
    openframeworks/graphics/ofPixels.cpp
    openframeworks/graphics/ofImage.cpp
    openframeworks/graphics/ofPath.cpp
    openframeworks/graphics/ofTessellator.cpp
    openframeworks/graphics/ofPolyline.cpp
    openframeworks/communication/ofSerial.cpp
    openframeworks/communication/ofArduino.cpp
    openframeworks/gl/ofTexture.cpp
    openframeworks/gl/ofLight.cpp
    openframeworks/gl/ofFbo.cpp
    openframeworks/gl/ofVbo.cpp
    openframeworks/gl/ofShader.cpp
    openframeworks/gl/ofMaterial.cpp
    openframeworks/gl/ofVboMesh.cpp
    openframeworks/gl/ofGLRenderer.cpp
    openframeworks/events/ofEvents.cpp
    openframeworks/utils/ofUtils.cpp
    openframeworks/utils/ofFileUtils.cpp
    openframeworks/utils/ofURLFileLoader.cpp
    openframeworks/utils/ofSystemUtils.cpp
    openframeworks/utils/ofLog.cpp
    openframeworks/utils/ofThread.cpp
    openframeworks/types/ofColor.cpp
    openframeworks/types/ofRectangle.cpp
    openframeworks/types/ofBaseTypes.cpp
    openframeworks/types/ofPoint.cpp
    openframeworks/app/ofAppNoWindow.cpp
    openframeworks/app/ofAppRunner.cpp
    openframeworks/app/ofAppGlutWindow.cpp
    openframeworks/math/ofVec2f.cpp
    openframeworks/math/ofMath.cpp
    openframeworks/math/ofMatrix3x3.cpp
    openframeworks/math/ofVec4f.cpp
    openframeworks/math/ofQuaternion.cpp
    openframeworks/math/ofMatrix4x4.cpp
)

add_library (${CMAKE_PROJECT_NAME} STATIC
    ${COMMON_SOURCES}
    ${SOUND_SOURCES}
    ${VIDEO_SOURCES}
    ${OFX_SOURCES}
    ${DARWIN_SOURCES}
    ${CAIRO_SOURCES}
)

set (OF_ALL_HEADERS
    ${COMMON_HEADERS}
    ${SOUND_HEADERS}
    ${VIDEO_HEADERS}
    ${OFX_HEADERS}
    ${DARWIN_HEADERS}
    ${CAIRO_HEADERS}
)

#--------------------------------------------------------------------------
# Prepare for using config.h
#--------------------------------------------------------------------------
set (OF_CORE_CFLAGS ${OF_CORE_CFLAGS} "-DHAVE_OF_CONFIG_H")
include_directories (${CMAKE_BINARY_DIR})

#--------------------------------------------------------------------------
# Set final variables for library building and output to pkgconf
#--------------------------------------------------------------------------

# Inludes -----------------------------------------------------------------
#
set (OF_INCLUDES ${OF_INCLUDES} ${OFX_INCLUDES})
if (OF_INCLUDES)

    list (REMOVE_DUPLICATES OF_INCLUDES)
    include_directories (${OF_INCLUDES})

    # Note that during install we merge all headers into a single directory
    # thus we don't need the long list of includes in pkgconf

endif()

# CFlags -----------------------------------------------------------------
#
set (OF_CFLAGS ${OF_CORE_CFLAGS} ${OFX_CFLAGS})
if (OF_CFLAGS)
    list (REMOVE_DUPLICATES OF_CFLAGS)
    add_definitions (${OF_CFLAGS})

    EXPAND_LIST(OF_EXPANDED_CFLAGS ${OF_CFLAGS})

endif ()

# Internal CFlags (used during build only) -------------------------------
#
if (CMAKE_BUILD_TYPE STREQUAL "debug")
    set (OF_CFLAGS_INTERNAL
         ${OF_CORE_CFLAGS_INTERNAL} ${CMAKE_CXX_FLAGS_DEBUG})
elseif (CMAKE_BUILD_TYPE STREQUAL "release")
    set (OF_CFLAGS_INTERNAL
         ${OF_CORE_CFLAGS_INTERNAL} ${CMAKE_CXX_FLAGS_RELEASE})
endif ()


if (OF_CFLAGS_INTERNAL)
    list (REMOVE_DUPLICATES OF_CFLAGS_INTERNAL)
    add_definitions (${OF_CFLAGS_INTERNAL})

    # internal flags are not exported to pkgconf, but printed below
    EXPAND_LIST(OF_EXPANDED_CFLAGS_INTERNAL ${OF_CFLAGS_INTERNAL})

endif ()

# Library search dirs ----------------------------------------------------
#
set (OF_LIBDIRS ${OF_CORE_LIBDIRS} ${OFX_LIBDIRS})
if (OF_LIBDIRS)
    list (REMOVE_DUPLICATES OF_LIBDIRS)
    link_directories (${OF_LIBDIRS})

    foreach(_OF_LIB_DIR ${OF_LIBDIRS})
        set (_OF_EXPANDED_LIBDIRS ${_OF_EXPANDED_LIBDIRS} "-L${_OF_LIB_DIR}")
    endforeach ()

    EXPAND_LIST(OF_EXPANDED_LIBDIRS ${_OF_EXPANDED_LIBDIRS})

endif ()

# Libraries --------------------------------------------------------------
#
set (OF_LIBS ${OF_CORE_LIBS} ${OFX_LIBS})
if (OF_LIBS)
    list (REMOVE_DUPLICATES OF_LIBS)
    if (OF_FRAMEWORKS)
        list (REMOVE_DUPLICATES OF_FRAMEWORKS)
    endif ()

    target_link_libraries(${CMAKE_PROJECT_NAME}
                          ${OF_LIBS} ${OF_FRAMEWORKS})

    # for expansion prepend '-l' if library name is not a full name already
    # i.e. contains a '.' in its filename
    #
    foreach(_LIB_NAME ${OF_LIBS})
        if (${_LIB_NAME} MATCHES ".*\\..*")
            set(_OF_PREFIXED_LIBS ${_OF_PREFIXED_LIBS} ${_LIB_NAME})
        else ()
            set(_OF_PREFIXED_LIBS ${_OF_PREFIXED_LIBS} "-l${_LIB_NAME}")
        endif ()
    endforeach ()

    # create a whitespace delimited list from Cmake's list format
    EXPAND_LIST(OF_EXPANDED_LIBS ${_OF_PREFIXED_LIBS} ${OF_FRAMEWORKS})

endif ()

# LDFlags ----------------------------------------------------------------
#
set (OF_LDFLAGS ${OF_CORE_LDFLAGS} ${OFX_LDFLAGS})
if (OF_LDFLAGS)
    list (REMOVE_DUPLICATES OF_LDFLAGS)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS ${OF_LDFLAGS})

    EXPAND_LIST(OF_EXPANDED_LDFLAGS ${OF_LDFLAGS})

endif()

# Pkgconf dependencies ---------------------------------------------------
#
if (OF_PKGCONF_DEPENDS)
    list (REMOVE_DUPLICATES OF_PKGCONF_DEPENDS)
    set (_LIST_COPY ${OF_PKGCONF_DEPENDS})
    EXPAND_LIST(OF_PKGCONF_DEPENDS ${_LIST_COPY})
endif()


#--------------------------------------------------------------------------
#  Build Examples (examples and their shared data will not be installed)
#--------------------------------------------------------------------------
if (BUILD_EXAMPLES)
  message("==================================================================")
  message(" OpenFrameworks Examples ")
  message("==================================================================")

  add_subdirectory(examples)

  # soft-link shared data into build directory

  # make sure EXTRA_DATA_OUTPUT_DIRECTORY (without the last name part) exists
  get_filename_component(_SHARE_PATH_BASE ${EXTRA_DATA_OUTPUT_DIRECTORY} PATH)

  # create base directory
  file(MAKE_DIRECTORY ${_SHARE_PATH_BASE})

  # link shared/ from source tree to build tree
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                  ${CMAKE_SOURCE_DIR}/share ${EXTRA_DATA_OUTPUT_DIRECTORY})

  # create bin directory (so linking below succeeds)
  file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

  # mirror the shared directory into bin/ so examples find it
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                  ${CMAKE_BINARY_DIR}/share
                  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/share)

endif ()


#--------------------------------------------------------------------------
#  Write config.h (after all dependency checks have passed)
#--------------------------------------------------------------------------
configure_file (
    ${CMAKE_SOURCE_DIR}/ofconfig.h.in
    ${CMAKE_BINARY_DIR}/ofconfig.h @ONLY
)


#--------------------------------------------------------------------------
#  Generate a pkg-config .pc file
#--------------------------------------------------------------------------

get_target_property(OF_LIB_TYPE ${CMAKE_PROJECT_NAME} TYPE)

if (CMAKE_BUILD_TYPE STREQUAL "debug")

    set(OF_LIB_POSTFIX ${CMAKE_DEBUG_POSTFIX})
    get_target_property(OF_LIB_NAME ${CMAKE_PROJECT_NAME} LOCATION_DEBUG)
    get_filename_component(OF_LIB_NAME ${OF_LIB_NAME} NAME)

elseif (CMAKE_BUILD_TYPE STREQUAL "release")

    set(OF_LIB_POSTFIX ${CMAKE_RELEASE_POSTFIX})
    get_target_property(OF_LIB_NAME ${CMAKE_PROJECT_NAME} LOCATION_RELEASE)
    get_filename_component(OF_LIB_NAME ${OF_LIB_NAME} NAME)

endif ()

configure_file(
    ${CMAKE_SOURCE_DIR}/openframeworks.pc.in
    ${CMAKE_BINARY_DIR}/openframeworks${OF_LIB_POSTFIX}.pc @ONLY
)

#--------------------------------------------------------------------------
#  Generate .cmake config file
#--------------------------------------------------------------------------

configure_file (
    ${CMAKE_SOURCE_DIR}/of-config.cmake.in
    ${CMAKE_BINARY_DIR}/of-config.cmake @ONLY
)

configure_file (
    ${CMAKE_SOURCE_DIR}/of-config-version.cmake.in
    ${CMAKE_BINARY_DIR}/of-config-version.cmake @ONLY
)


#--------------------------------------------------------------------------
#  Install Targets
#--------------------------------------------------------------------------

# headers
install(FILES ${OF_ALL_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR})

# library
install(TARGETS ${CMAKE_PROJECT_NAME}
        EXPORT OF_EXPORT
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR})

# shared
install(FILES ${OF_ALL_SHARED} DESTINATION ${SHARE_INSTALL_DIR})

# ofconfig.h
install(FILES ${CMAKE_BINARY_DIR}/ofconfig.h DESTINATION ${INCLUDE_INSTALL_DIR})


# FindOF.cmake module
#install(FILES ${CMAKE_SOURCE_DIR}/share/FindOF.cmake
#        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake-2.8/Modules)

# cmake config: create and install import/export declarations
install(EXPORT OF_EXPORT DESTINATION ${CMAKECONFIG_INSTALL_DIR}
        FILE of-targets.cmake)

install(FILES ${CMAKE_BINARY_DIR}/of-config.cmake
        DESTINATION ${CMAKECONFIG_INSTALL_DIR})

install(FILES ${CMAKE_BINARY_DIR}/of-config-version.cmake
        DESTINATION ${CMAKECONFIG_INSTALL_DIR})

# pkgconfig
install(FILES "${CMAKE_BINARY_DIR}/openframeworks${OF_LIB_POSTFIX}.pc"
        DESTINATION ${LIB_INSTALL_DIR}/pkgconfig/ )


#--------------------------------------------------------------------------
# Output Summary
#--------------------------------------------------------------------------

message("==================================================================")
message(" OpenFrameworks Build Summary ")
message("==================================================================")
message("Build Type:    ${CMAKE_BUILD_TYPE}")
message("OF version:    ${OF_VERSION}")
message("Library:       ${OF_LIB_NAME}  (${OF_LIB_TYPE})")
message("Install path:  ${CMAKE_INSTALL_PREFIX}")
message("")
message("OF includes:   ${OF_INCLUDES}")
message("")
message("OF cflags:     ${OF_EXPANDED_CFLAGS} ${OF_EXPANDED_CFLAGS_INTERNAL}")
message("")
message("OF ldflags:    ${OF_EXPANDED_LDFLAGS}")
message("")
message("OF libs:       ${OF_EXPANDED_LIBS}")
message("")
message("OF libdirs:    ${OF_EXPANDED_LIBDIRS}")
