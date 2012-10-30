#include "ofAppNoWindow.h"
#include "ofBaseApp.h"
#include "ofMain.h"

#ifdef OF_USING_POCO
static ofEventArgs voidEventArgs;
#endif

//----------------------------------------------------------
ofAppNoWindow::ofAppNoWindow(){
    timeNow                             = 0;
    timeThen                    = 0;
    fps                                 = 60; //give a realistic starting value - win32 issues
    nFramesForFPS               = 0;
    nFrameCount                 = 0;
    bFrameRateSet               = false;
    millisForFrame              = 0;
    prevMillis                  = 0;
    diffMillis                  = 0;
    frameRate                   = 0;
}

//------------------------------------------------------------
void ofAppNoWindow::runAppViaInfiniteLoop(ofBaseApp * appPtr){

    ofAppPtr = appPtr;

    if(ofAppPtr){
        ofAppPtr->setup();
        ofAppPtr->update();
        nFramesForFPS++;
        nFrameCount++;          // increase the overall frame count
    }

#ifdef OF_USING_POCO
    ofNotifyEvent( ofEvents.setup, voidEventArgs );
    ofNotifyEvent( ofEvents.update, voidEventArgs );
#endif

    //    printf("before main loop\n");
    while (true)
    {
        if (nFrameCount != 0 && bFrameRateSet == true){
            diffMillis = ofGetElapsedTimeMillis() - prevMillis;
            if (diffMillis > millisForFrame){
                ; // we do nothing, we are already slower than target frame
            } else {
                int waitMillis = millisForFrame - diffMillis;
#ifdef TARGET_WIN32
                Sleep(waitMillis);         //windows sleep in milliseconds
#else
                usleep(waitMillis * 1000);   //mac sleep in microseconds - cooler :)
#endif
            }
        }
        prevMillis = ofGetElapsedTimeMillis(); // you have to measure here


        /// listen for escape
#ifdef TARGET_WIN32
        if (GetAsyncKeyState(VK_ESCAPE))
            OF_EXIT_APP(0);
#endif

        /// update
        if (ofAppPtr)
            ofAppPtr->update();

#ifdef OF_USING_POCO
        ofNotifyEvent( ofEvents.update, voidEventArgs);
#endif


        // -------------- fps calculation:
        timeNow = ofGetElapsedTimef();
        timeDiff = timeNow-timeThen;
        if( (timeDiff) > 0.05f || nFramesForFPS == 0 ) {
            fps = (double)nFramesForFPS / (timeDiff);
            timeThen = timeNow;
            nFramesForFPS = 0;

            //hack for windows - was getting NAN - maybe unitialized vars???
            if( nFrameCount < 5) frameRate = fps;
            else frameRate = 0.9f * frameRate + 0.1f * fps;
        }
        nFramesForFPS++;
        // --------------

        nFrameCount++;          // increase the overall frame count

    }
}

//------------------------------------------------------------
float ofAppNoWindow::getFrameRate(){
    return frameRate;
}

//------------------------------------------------------------
int ofAppNoWindow::getFrameNum(){
    return nFrameCount;
}

double ofAppNoWindow::getLastFrameTime(){
    return timeDiff;
}

//------------------------------------------------------------
void ofAppNoWindow::setFrameRate(float targetRate){
    // given this FPS, what is the amount of millis per frame
    // that should elapse?

    // --- > f / s

    if (targetRate == 0){
        bFrameRateSet = false;
        return;
    }

    bFrameRateSet                       = true;
    float durationOfFrame       = 1.0f / (float)targetRate;
    millisForFrame                      = (int)(1000.0f * durationOfFrame);

    frameRate                           = targetRate;

}
