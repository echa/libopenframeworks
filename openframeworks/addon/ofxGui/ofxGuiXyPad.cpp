/*
 *  ofxGuiXYPad.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//      ----------------------------------------------------------------------------------------------------

#include <ofxGuiXyPad.h>

//      ----------------------------------------------------------------------------------------------------

ofxGuiXYPad::ofxGuiXYPad()
{
    mParamType = kofxGui_Object_XYPad;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiXYPad::init(int id, string name, int x, int y, int width, int height, ofVec2f min, ofVec2f max, ofVec2f value, int display, int steps)
{
    int textHeight      = (name == "") ? 0 : mGlobals->mParamFontHeight;

    mParamId            = id;
    mParamName          = name;

    mObjX                       = x;
    mObjY                       = y;

    mObjWidth           = width;
    mObjHeight          = textHeight + height;

    mDisplay            = display;
    mSteps                      = steps;

    setRange(min, max);
    setValue(value);
    setControlRegion(0, textHeight, width, height);
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiXYPad::setValue(ofVec2f value)
{
    mValue = value;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiXYPad::setRange(ofVec2f min, ofVec2f max)
{
    mMinVal     = min;
    mMaxVal     = max;
    mValDlt     = mMaxVal / mMinVal;
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiXYPad::update(int id, int task, void* data, int length)
{
    bool handled = false;

    if(id == mParamId && length == sizeof(ofVec2f))
    {
        setValue(*(ofVec2f*)data);
        handled = true;
    }

    return handled;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiXYPad::draw()
{
    glPushMatrix();

    glTranslatef(mObjX, mObjY, 0.0f);

    if(mParamName != "")
        drawParamString(0.0, 0.0, mParamName + ": " + pointToString(mValue, mDisplay), false);

    ofVec2f  p       = fractionToLocal(valueToFraction(mValue));

    float               d       = mGlobals->mPointSize;
    float               r       = d / 2.0;

    ofFill();

    //  background
    glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
    ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

    //  x-bar
    glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals-> mAxisColor.a);
    ofLine(p.x + 0.5, mCtrY, p.x + 0.5, mCtrBottom);

    //  y-bar
    glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals->mAxisColor.a);
    ofLine(mCtrX, p.y + 0.5, mCtrRight, p.y + 0.5);

    ofNoFill();

    //  handle
    glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
    ofRect(p.x - r, p.y - r, d, d);

    //  frame
    glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
    ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

    glPopMatrix();
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiXYPad::mouseDragged(int x, int y, int button)
{
    if(mMouseIsDown)
    {
        ofVec2f value = fractionToValue(mouseToFraction(mouseToLocal(x, y)));

        if(value != mValue)
        {
            setValue(value);
            mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mValue, sizeof(ofVec2f));
        }
    }

    return mMouseIsDown;
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiXYPad::mousePressed(int x, int y, int button)
{
    mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));

    if(mMouseIsDown)
        mouseDragged(x, y, button);

    return mMouseIsDown;
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiXYPad::mouseReleased(int x, int y, int button)
{
    bool handled = mMouseIsDown;

    if(mMouseIsDown)
        mMouseIsDown = false;

    return handled;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiXYPad::buildFromXml()
{
    mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mValue, sizeof(ofVec2f));
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiXYPad::saveToXml()
{
    int id = saveObjectData();

    mGlobals->mXml.setValue("OBJECT:MIN_X", mMinVal.x, id);
    mGlobals->mXml.setValue("OBJECT:MIN_Y", mMinVal.y, id);
    mGlobals->mXml.setValue("OBJECT:MAX_X", mMaxVal.x, id);
    mGlobals->mXml.setValue("OBJECT:MAX_Y", mMaxVal.y, id);
    mGlobals->mXml.setValue("OBJECT:VALUE_X", mValue.x, id);
    mGlobals->mXml.setValue("OBJECT:VALUE_Y", mValue.y, id);
}

//      ----------------------------------------------------------------------------------------------------

ofVec2f ofxGuiXYPad::valueToFraction(ofVec2f value)
{
    return ofVec2f((value.x - mMinVal.x) / mValDlt.x, (value.y - mMinVal.y) / mValDlt.y);
}

//      ----------------------------------------------------------------------------------------------------

ofVec2f ofxGuiXYPad::fractionToValue(ofVec2f fraction)
{
    return ofVec2f((mValDlt.x * fraction.x) + mMinVal.x, (mValDlt.y * fraction.y) + mMinVal.y);
}

//      ----------------------------------------------------------------------------------------------------
