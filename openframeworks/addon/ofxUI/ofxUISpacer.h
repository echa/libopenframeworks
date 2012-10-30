#ifndef OFXUI_LINE_SPACER
#define OFXUI_LINE_SPACER

#include "ofxUIWidget.h"

class ofxUISpacer : public ofxUIWidget
{
public:
    ofxUISpacer(float x, float y, float w, float h);
    ofxUISpacer(float x, float y, float w, float h, string _name);
    ofxUISpacer(float w, float h);
    ofxUISpacer(float w, float h, string _name);

    virtual ~ofxUISpacer() {}
    
    void init(float w, float h);
	virtual void setParent(ofxUIWidget *_parent);
    void toggleColor();
    void setToggleColor(bool _value);
}; 

#endif
