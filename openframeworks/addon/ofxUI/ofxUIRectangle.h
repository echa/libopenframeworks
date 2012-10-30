/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI_RECTANGLE
#define OFXUI_RECTANGLE

#include "ofMain.h"

class ofxUIRectangle : public ofRectangle
{

public:
    ofxUIRectangle();
    ofxUIRectangle(float _x, float _y, float _w, float _h)    ;
    ofxUIRectangle(ofRectangle const & r);
    virtual ~ofxUIRectangle() {}

    void setParent(ofxUIRectangle *_parent);
	void setHeight(float _height);
	void setWidth(float _width);
    bool inside(ofPoint p);
    bool inside(float px, float py);
    bool insideChild(float px, float py);
    bool insideParent(float px, float py);
	ofVec2f percentInside(float px, float py);//Assumes your already inside rect 
	ofVec2f percentInsideChild(float px, float py);
    ofVec2f percentInsideParent(float px, float py);

    void draw();

	float getX();
	float getY();
	float getWidth();
	float getHeight();
	
protected: 
    ofxUIRectangle *parent; 
};

#endif
