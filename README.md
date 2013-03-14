libopenframeworks
=================

**A clean port of OpenFrameworks 0071 that merges all oF modules into a single static library and uses CMake for building.**

This port follows the typical Linux packaging style and allows you to install oF as library plus headers. It is meant for developers who find the fat distribution concept of OpenFrameworks less useful.

libopenframeworks allows a greater flexibility in using and extending OpenFrameworks. You can either use system-wide versions of 3rd party libraries or you can bootstrap private library versions using the contained build scripts. Most libraries are statically linked into executables resulting in less run-time dependencies and easier portability of projects between machines. When optional libraries are missing libopenframeworks would still build with some of the modules or addons disabled. As a side-effect oF projects become smaller which is beneficial for repositories and use less disk space during development.

**Main Features**

* complete CMake build environment
* build scripts for all 3rd-party libraries
* debug and release builds available
* conditional build when 3rd-party libs are missing
* available modules are defined in ofconfig.h
* builds a static library version of OpenFrameworks
* can install headers and library for easy reuse in multiple projects
* comes with a pkgconfig file
* comes with CMake find script
* contains working oF examples
* contains main oF addons (see below)
* contains extra bug-fixes

**Differences from vanilla OpenFrameworks**

* works on Linux (32/64bit) and Mac OSX (10.6 - 10.8) only
* there is no Android or iOS support (yet)
* 3rd-party libraries are not pro-built
* single location for shared data such as images, fonts, shaders, models, etc.
* root data-path is share/openframeworks/

**Included OpenFrameworks addons**

* ofx3dModeler
* ofxAccelerometer
* ofxAssimpModelLoader
* ofxDiscGrabber
* ofxGui
* ofxMultiTouch
* ofxNetwork
* ofxOpenCv
* ofxOsx
* ofxSynth
* ofxThreadedImageLoader
* ofxUI
* ofxVectorGraphics
* ofxVideoGrabber
* ofxXmlSettings


Prerequisites on Linux
--------------------------

Please make sure the following packages are installed on your system. Consult your distribution's package manager for details:

    alsa-utils avahi boost bzip2 cmake freeglut freeimage freetype2
    gcc git gzip libusb make openal opencl-headers patch pkg-config
    portaudio python tar wget yasm zip


Prerequisites on OSX
--------------------------

Developing on Mac OSX requires you to install the Apple Developer SDK (which includes compilers, header files and the XCode IDE). You can download the latest version from http://developers.apple.com. Note, you need to register a free user account before downloading.

In addition you need to install the following packages via MacPorts or Fink or compile them manually:

    git-core zlib python27 pkgconfig bzip2 glib2 cmake
    wget unzip yasm freetype freeimage glew portaudio
    boost cairo avahi jpeg tiff jasper libpng openexr
    mpg123 libsndfile xz

When you prefer homebrew as package manager on OSX, remember to add extend the PKG_CONFIG_PATH variable with

    export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:/usr/X11/lib/pkgconfig


3rd Party Libraries
----------------------

OpenFrameworks relies on different 3rd party libraries which are shipped as pre-built binaries with the original 'fat' OpenFrameworks distribution. To save space and enable static linkage we let you build those 3rd party libs from scratch:

    cd contrib
    ./build-contrib.sh -i <CONTRIB_INSTALL_PATH>
    cd ..

You can check contrib/build/build.log for detailed output and errors.


Building libopenframeworks
----------------------------

Configuration and build follows the normal CMake workflow. We suggest you opt for an *out-of-source* build to keep your source directories clean. All examples below assume you are in the repository's root path (refered to as source directory). Here's a step-by step guide:

    # set PKG_CONFIG_PATH so CMake finds your private 3rd-party libraries
    export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:<CONTRIB_INSTALL_PATH>/lib/pkgconfig/

    # create a build directory and enter it
    mkdir build
    cd build

    # configure, build and install libopenframeworks
    #
    # CONTRIB_INSTALL_PATH is the directory where you've installed the
    # 3rd-party libraries
    #
    # CMAKE_INSTALL_PREFIX is the directory where you want to install
    # libOpenFrameworks into
    #
    # The third parameter is the source directory of libopenframeworks, i.e.
    # the repository root (you can use a relative path, i.e. '..' as shown)
    #
    cmake -DCMAKE_PREFIX_PATH=<CONTRIB_INSTALL_PATH> -DCMAKE_INSTALL_PREFIX= <OF_INSTALL_DIR> ..
    make
    make install


For configuring the build process you can set any of the variables

    Variable                 Default Value       Description
    ----------------------------------------------------------------------
    CMAKE_BUILD_TYPE         debug               build type (debug or release)
    CMAKE_PREFIX_PATH        HOME                3rd-party library search path
    CMAKE_INSTALL_PREFIX     CMAKE_PREFIX_PATH   install destination
    CMAKE_VERBOSE_MAKEFILE   false               be verbose during build
    ENABLE_PROFILING         false               build profiling version
    BUILD_WITH_DEBUG_INFO    true                include debug info in library
    BUILD_EXAMPLES           false               build OpenFramework examples


Running Examples from the BUILD directory
------------------------------------------------

Examples will not be installed by default. You can find them inside the build directory under bin/. To run them follow the steps below:

    # First download and unpack the shared data into the source directory
    curl -O http://code.kidtsunami.com/of-share-0.7.1.tar.gz

    # assuming you are inside the source directory call
    tar -xzf of-share-0.7.1.tar.gz

    # set the library path (required for dynamic libraries such as FMod)
    #
    # Note the difference: use DYLD_LIBRARY_PATH on Mac OSX
    #                      and LD_LIBRARY_PATH on Linux
    #
    export DYLD_LIBRARY_PATH=<CONTRIB_INSTALL_PATH>/lib

    # run examples (either from the source directory or from within build/bin)
    ./build/bin/3dml

Project Template using libopenframeworks
------------------------------------------------

It's easy to develop your app with libopenframeworks. Just download the project template

    curl -O http://code.kidtsunami.com/of-template.tar.gz

unpack and start writing your own code. To compile your project run

    cd build
    cmake -DCMAKE_PREFIX_PATH=<CONTRIB_INSTALL_PATH>/lib/cmake/of ..
    make

and that's it. All the necessary libopenframeworks build configuration is kept in a single place where you've installed the library to. CMake fetches this configuration when building your project. See the main CMakeLists.txt file inside the template archive for details.
