/*
 *  ofxGuiPoints.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//      ----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_POINTS
#define OFX_GUI_POINTS

//      ----------------------------------------------------------------------------------------------------

#include <ofxGuiTypes.h>
#include <ofxGuiObject.h>

//      ----------------------------------------------------------------------------------------------------

class ofxGuiPoints : public ofxGuiObject
{

 public:

    ofxGuiPoints();

    void                init(int id, string name, int x, int y, int width, int height, ofVec2f min, ofVec2f max, ofVec2f value, int display, int steps);

    void                setValue(ofVec2f value);
    void                setRange(ofVec2f min, ofVec2f max);

    bool                update(int id, int task, void* data, int length);
    void                draw();

    bool                mouseDragged(int x, int y, int button);
    bool                mousePressed(int x, int y, int button);
    bool                mouseReleased(int x, int y, int button);

    void                buildFromXml();
    void                saveToXml();

    ofVec2f  valueToFraction(ofVec2f value);
    ofVec2f  fractionToValue(ofVec2f fraction);

    bool                isPointWithinDistance(ofVec2f position);

    float               mDistance;

    ofVec2f  mValue, mOutVal;

    ofVec2f  mMinVal;
    ofVec2f  mMaxVal;
    ofVec2f  mValDlt;

    ofPointList mList;
};

//      ----------------------------------------------------------------------------------------------------

#endif

//      ----------------------------------------------------------------------------------------------------
