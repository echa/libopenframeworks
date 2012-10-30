#ifndef _OFX_DISK_GRABBER
#define _OFX_DISK_GRABBER

#include "ofConstants.h"
#include "ofTexture.h"
#include "ofTypes.h"

#include "imageReader.h"

#include <vector>

/*
  Usage: ./setcomm -w 480 -h 320 -q 4 -c DISK:/disk/3D/MSR3DVideo-Breakdancers/cam0/
*/

class ofxDiskGrabber : public ofBaseVideo{

 public :

    ofxDiskGrabber();
    virtual ~ofxDiskGrabber();

    bool            isFrameNew();
    void            grabFrame();
    void            close();
    bool            initGrabber(int width, int height, std::string dir);
    void            videoSettings();
    unsigned char   *getPixels();
    void            setVerbose(bool bTalkToMe);
    void            setDeviceID(int _deviceID);
    void            setDesiredFrameRate(int framerate);

    float                   getHeight();
    float                   getWidth();

    ofTexture& getTextureReference() { return tex; };
    void setUseTexture(bool) { };
    void update() { grabFrame(); };
    void draw(float, float) {};
    void draw(float, float, float, float) {};

 protected:

    int                     deviceID;
    bool                    bUseTexture;
    bool                    bVerbose;
    bool                    bGrabberInited;
    unsigned char *         pixels;
    int                     attemptFramerate;
    bool                    bIsFrameNew;
    ofTexture tex;

 private:
    bool                    openDir(void);

    vector<std::string>     files;
    std::string             dir;
    ImageReader*            imgReader;
    int                     height;
    int                     width;
    int                     next;
};

#endif

