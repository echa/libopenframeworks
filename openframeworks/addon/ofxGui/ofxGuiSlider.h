/*
 *  ofxGuiSlider.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//      ----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_SLIDER
#define OFX_GUI_SLIDER

//      ----------------------------------------------------------------------------------------------------

#include <ofxGuiTypes.h>
#include <ofxGuiObject.h>

//      ----------------------------------------------------------------------------------------------------

class ofxGuiSlider : public ofxGuiObject
{

 public:

    ofxGuiSlider();

    void        init(int id, string name, int x, int y, int width, int height, float min, float max, float value, int display, int steps);

    void        setValue(float value);
    void        setRange(float min, float max);

    bool        update(int id, int task, void* data, int length);
    void        draw();

    bool        mouseDragged(int x, int y, int button);
    bool        mousePressed(int x, int y, int button);
    bool        mouseReleased(int x, int y, int button);

    void        buildFromXml();
    void        saveToXml();

    float       valueToFraction(float value);
    float       fractionToValue(float fraction);

    float       mValue, mMinVal, mMaxVal, mValDlt;
};

//      ----------------------------------------------------------------------------------------------------

#endif

//      ----------------------------------------------------------------------------------------------------
