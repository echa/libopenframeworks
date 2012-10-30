#ifndef OFX_CV_CONSTANTS_H
#define OFX_CV_CONSTANTS_H

#ifdef True
#undef True
#undef False
#endif

// OpenCV on OSX assert macro collossion
// https://code.ros.org/trac/opencv/ticket/1377
// will be fixed in OpenCV > 2.3.1
#ifdef check
#undef check
#endif

#include "cv.h"
#include <vector>
#include "ofMain.h"

enum ofxCvRoiMode {
    OFX_CV_ROI_MODE_INTERSECT,
    OFX_CV_ROI_MODE_NONINTERSECT
};

#endif
