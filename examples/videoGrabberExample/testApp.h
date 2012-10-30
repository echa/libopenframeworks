#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxVideoGrabber.h"

class testApp : public ofBaseApp {
 public:

    void setup();
    void update();
    void draw();
    void calculateCaptureFramerate();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

    ofxVideoGrabber vidGrabber;

    int camWidth;
    int camHeight;
    int appWidth;
    int appHeight;
    /*framerate display*/
    char  buf[255];
    char  buf2[255];
    float mytimeNow, mytimeThen, myframeRate;

    float myfps;
    float myframes;
};

#endif
