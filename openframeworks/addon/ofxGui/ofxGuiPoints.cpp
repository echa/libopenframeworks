/*
 *  ofxGuiPoints.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//      ----------------------------------------------------------------------------------------------------

#include <ofxGuiPoints.h>

//      ----------------------------------------------------------------------------------------------------

ofxGuiPoints::ofxGuiPoints()
{
    mParamType = kofxGui_Object_Points;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiPoints::init(int id, string name, int x, int y, int width, int height, ofVec2f min, ofVec2f max, ofVec2f value, int display, int steps)
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

    mList.points.push_back(ofVec2f(mMinVal.x, mMinVal.y + mValDlt.y * 0.5));
    mList.points.push_back(ofVec2f(mMaxVal.x, mMinVal.y + mValDlt.y * 0.5));

    float       size    = mGlobals->mPointSize / 2.0;
    float       x1              = size / mCtrWidth;
    float       y1              = size / mCtrHeight;
    float       x2              = x1 * mValDlt.x;
    float       y2              = y1 * mValDlt.y;

    mDistance           = sqrt(x2 * x2 + y2 * y2);
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiPoints::setValue(ofVec2f value)
{
    mValue = value;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiPoints::setRange(ofVec2f min, ofVec2f max)
{
    mMinVal     = min;
    mMaxVal     = max;
    mValDlt     = mMaxVal / mMinVal;
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::update(int id, int task, void* data, int length)
{
    bool                handled = false;
    ofVec2f  value   = mValue;

    if(id == mParamId)
    {
        if(task == kofxGui_Set_Float)
            setValue(ofVec2f(mMinVal.x + CLAMP(*(float*)data, 0.0, 1.0) * mValDlt.x, mValue.y));
        else if(task == kofxGui_Set_Point)
            setValue(*(ofVec2f*)data);

        handled = true;
    }

    if(value!= mValue)
    {
        mOutVal = mList.positionToValue(mValue);
        mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mOutVal, sizeof(ofVec2f));
    }

    return handled;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiPoints::draw()
{
    glPushMatrix();

    glTranslatef(mObjX, mObjY, 0.0f);

    if(mParamName != "")
        drawParamString(0.0, 0.0, mParamName + ": " + pointToString(mList.activePoint != INVALID_POINT ?
                                                                    mOutVal : mValue, mDisplay), false);

    ofVec2f  p       = fractionToLocal(valueToFraction(mValue));

    //          float           x       = mCtrWidth * p.x;
    //          float           y       = mCtrHeight * p.y;

    float               d       = mGlobals->mPointSize;
    float               r       = d / 2.0;

    ofFill();

    //  background
    glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
    ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

    ofNoFill();

    //  lines
    glColor4f(mGlobals->mCurveColor.r, mGlobals->mCurveColor.g, mGlobals->mCurveColor.b, mGlobals->mCurveColor.a);

    ofBeginShape();
    for(size_t i = 0; i < mList.points.size(); i++)
    {
        ofVec2f p = fractionToLocal(valueToFraction(mList.points.at(i)));
        ofVertex(p.x, p.y);
    }
    ofEndShape(false);

    //  x-bar
    glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals->mAxisColor.a);
    ofLine(p.x + 0.5, mCtrY, p.x + 0.5, mCtrBottom);

    if(mList.activePoint != INVALID_POINT)
    {
        //      y-bar
        glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b,mGlobals->mAxisColor.a);
        ofLine(mCtrX, p.y + 0.5, mCtrRight, p.y + 0.5);
    }

    //  handles
    for(size_t i = 0; i < mList.points.size(); i++)
    {
        glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);

        ofVec2f p    = fractionToLocal(valueToFraction(mList.points.at(i)));
        ofRect(p.x - r, p.y - r, d, d);
    }

    //  frame
    glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
    ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

    glPopMatrix();
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::mouseDragged(int x, int y, int button)
{
    if(mMouseIsDown)
    {
        ofVec2f      value   = mValue;
        ofVec2f      point   = fractionToValue(mouseToFraction(mouseToLocal(x, y)));

        if(mList.activePoint != INVALID_POINT)
        {
            if(mList.activePoint == 0)
            {
                point.x = mMinVal.x;
                mList.points[mList.activePoint] = point;
            }
            else if(mList.activePoint == mList.points.size() - 1)
            {
                point.x = mMaxVal.x;
                mList.points[mList.activePoint] = point;
            }
            else
            {
                if(point.x < mList.points[mList.activePoint - 1].x)
                    point.x = mList.points[mList.activePoint - 1].x;
                else if(point.x > mList.points[mList.activePoint + 1].x)
                    point.x = mList.points[mList.activePoint + 1].x;

                mList.points[mList.activePoint] = point;
            }
        }

        setValue(point);

        if(value != mValue)
        {
            mOutVal = mList.positionToValue(point);
            mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mOutVal, sizeof(ofVec2f));
        }
    }

    return mMouseIsDown;
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::mousePressed(int x, int y, int button)
{
    ofVec2f point = mouseToLocal(x, y);

    if(isPointInsideMe(point))
    {
        ofVec2f      inside  = fractionToValue(mouseToFraction(point));
        bool            onPoint = isPointWithinDistance(inside);

        if(button == 2)
        {
            if(onPoint)
                mList.deleteActivePoint();
            else
                mList.addPointAtPosition(inside);
        }

        mMouseIsDown = true;
        mouseDragged(x, y, button);
    }
    else
    {
        mMouseIsDown = false;
    }

    return mMouseIsDown;
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::mouseReleased(int x, int y, int button)
{
    bool handled = mMouseIsDown;

    if(mMouseIsDown)
    {
        mMouseIsDown            = false;
        mList.activePoint       = INVALID_POINT;
    }

    return handled;
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiPoints::buildFromXml()
{
    int numberOfTags = mGlobals->mXml.getNumTags("POINT");

    if(numberOfTags > 0)
    {
        mList.points.clear();

        for(int i = 0; i < numberOfTags; i++)
        {
            mGlobals->mXml.pushTag("POINT", i);

            float       x = mGlobals->mXml.getValue("X", 0.0);
            float       y = mGlobals->mXml.getValue("Y", 0.0);

            mList.points.push_back(ofVec2f(x, y));

            mGlobals->mXml.popTag();
        }
    }

    mOutVal = mList.positionToValue(mValue);
    mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mOutVal, sizeof(ofVec2f));
}

//      ----------------------------------------------------------------------------------------------------

void ofxGuiPoints::saveToXml()
{
    int id = saveObjectData();

    mGlobals->mXml.setValue("OBJECT:MIN_X", mMinVal.x, id);
    mGlobals->mXml.setValue("OBJECT:MIN_Y", mMinVal.y, id);
    mGlobals->mXml.setValue("OBJECT:MAX_X", mMaxVal.x, id);
    mGlobals->mXml.setValue("OBJECT:MAX_Y", mMaxVal.y, id);
    mGlobals->mXml.setValue("OBJECT:VALUE_X", mValue.x, id);
    mGlobals->mXml.setValue("OBJECT:VALUE_Y", mValue.y, id);

    mGlobals->mXml.pushTag("OBJECT", id);

    for(size_t i = 0; i < mList.points.size(); i++)
    {
        ofVec2f p    = mList.points.at(i);

        id = mGlobals->mXml.addTag("POINT");

        mGlobals->mXml.setValue("POINT:X", p.x, id);
        mGlobals->mXml.setValue("POINT:Y", p.y, id);
    }

    mGlobals->mXml.popTag();
}

//      ----------------------------------------------------------------------------------------------------

ofVec2f ofxGuiPoints::valueToFraction(ofVec2f value)
{
    return ofVec2f((value.x - mMinVal.x) / mValDlt.x, (value.y - mMinVal.y) / mValDlt.y);
}

//      ----------------------------------------------------------------------------------------------------

ofVec2f ofxGuiPoints::fractionToValue(ofVec2f fraction)
{
    return ofVec2f((mValDlt.x * fraction.x) + mMinVal.x, (mValDlt.y * fraction.y) + mMinVal.y);
}

//      ----------------------------------------------------------------------------------------------------

bool ofxGuiPoints::isPointWithinDistance(ofVec2f position)
{
    mList.activePoint = INVALID_POINT;

    for(size_t i = 0; i < mList.points.size(); i++)
    {
        ofVec2f      point   = mList.points.at(i);
        float           delta   = point.distance(position);

        if(delta < mDistance)
        {
            mList.activePoint = i;
            break;
        }
    }

    return mList.activePoint != INVALID_POINT;
}
