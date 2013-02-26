#############################################################################
# KidTsunami - Professional. Live. Video.
#
# File:     CMakeLists.txt
# Author:   Alexander Eichhorn <echa@kidtsunami.com>
# Contents: OpenFrameWorks Example
#
#
# Copyright 2013 KidTsunami. All Rights Reserved.
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


# project name, creates new/private variables
project(PCL_STATISTICAL_REMOVAL_EXAMPLE)

set (target_name "ofxPclStatisticalRemovalExample")
set (msg "OFX: ${target_name} disabled")

REQUIRES (HAVE_OPENFRAMEWORKS ${msg})
REQUIRES (HAVE_PCL ${msg})
MESSAGE("-- Adding OFX: ${target_name}")

# source files for this application
add_executable(${target_name}
    main.cpp
    testApp.cpp
)

# libraries to link the target against (a list of CMake variables)
target_link_libraries(${target_name} openframeworks)

# additional linker flags
if (OF_LDFLAGS)
    set_target_properties(${target_name} PROPERTIES LINK_FLAGS ${OF_LDFLAGS})
endif ()
