#include <ofUtils.h>
#include <dirent.h>
#include <algorithm>

#include <pngReader.h>
#include <fileCache.h>
#include <ofxDiskGrabber.h>

ofxDiskGrabber::ofxDiskGrabber()
{
    // common
    bIsFrameNew                         = false;
    bVerbose                            = false;
    bGrabberInited                      = false;
    deviceID                            = 0;
    width                                       = 320;  // default setting
    height                                      = 240;  // default setting
    pixels                                      = NULL;
    attemptFramerate            = -1;

    dir = "./";

    ImageReader *png = new PngReader();
    //  imgReader = new Freeview(png);
    imgReader = new FileCache(png, 100, 3);
}

ofxDiskGrabber::~ofxDiskGrabber(){
    close();
}

//--------------------------------------------------------------------
void ofxDiskGrabber::setVerbose(bool bTalkToMe){
    bVerbose = bTalkToMe;
}

//--------------------------------------------------------------------
void ofxDiskGrabber::setDeviceID(int _deviceID){
    deviceID            = _deviceID;
}

//--------------------------------------------------------------------
void ofxDiskGrabber::setDesiredFrameRate(int framerate){
    attemptFramerate = framerate;
}

//---------------------------------------------------------------------------
unsigned char * ofxDiskGrabber::getPixels(){
    return pixels;
}

bool  ofxDiskGrabber::isFrameNew(){
    return bIsFrameNew;
}

// TODO: fix the algorithm to work also if the last file in a dir is not an image
void ofxDiskGrabber::grabFrame()
{
    std::string file = "";
    file.append(dir);
    file.append(files[next]);

    memset(pixels, '\0', width * height * 3);

    if(imgReader->readFrame(file, width, height, pixels))
    {
        bIsFrameNew = true;
    }
    next = (next + 1) % files.size();
}

void ofxDiskGrabber::close(){
    if (pixels != 0)
    {
        delete[] pixels;
        pixels = 0;
    }

    delete imgReader;
}

void ofxDiskGrabber::videoSettings(void)
{
}

bool ofxDiskGrabber::openDir(void)
{
    DIR *dp;
    struct dirent *dirp;

    if((dp  = opendir(dir.c_str())) == 0)
    {
        ofLog(OF_LOG_FATAL_ERROR, "ofxDiskGrabber - can't open directory %s", dir.c_str());
        return false;
    }

    while((dirp = readdir(dp)) != 0) {
        if(imgReader->checkExtension(dirp->d_name)) {
            files.push_back(std::string(dirp->d_name));
        }
    }

    if(! files.size()) {
        ofLog(OF_LOG_FATAL_ERROR, "ofxDiskGrabber - directory %s contains no image files", dir.c_str());
        return false;
    }

    ofLog(OF_LOG_NOTICE, "ofxDiskGrabber - directory %s contains %d image files",
          dir.c_str(), files.size());

    closedir(dp);
    std::sort(files.begin(), files.end());
    next = 0;
    return true;
}

bool ofxDiskGrabber::initGrabber(int _width, int _height, std::string _dir)
{
    width = _width;
    height = _height;
    dir = _dir;

    // TODO: dangerous if someone is holding the reference to pixels
    if(pixels)
    {
        free(pixels);
    }
    pixels = new unsigned char[width * height * 3];

    return openDir();
}

float ofxDiskGrabber::getHeight(){
    return (float)height;
}

float ofxDiskGrabber::getWidth(){
    return (float)width;
}
