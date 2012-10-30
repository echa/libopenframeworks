#ifndef _OF_APPNOWINDOW_H
#define _OF_APPNOWINDOW_H

#include "ofConstants.h"
#include "ofAppBaseWindow.h"

class ofBaseApp;

class ofAppNoWindow : public ofAppBaseWindow {

 public:
    ofAppNoWindow();
    virtual ~ofAppNoWindow(){}

    void runAppViaInfiniteLoop(ofBaseApp * appPtr);
    virtual int getFrameNum();
    virtual float getFrameRate();
    virtual void setFrameRate(float targetRate);
    virtual double getLastFrameTime();

 private:
    float   timeNow, timeThen, fps, timeDiff;
    int     nFramesForFPS;
    int     nFrameCount;
    bool    bFrameRateSet;
    int     millisForFrame;
    int     prevMillis;
    int     diffMillis;
    float   frameRate;

    ofBaseApp* ofAppPtr;
};

#endif
