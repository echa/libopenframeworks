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

#ifndef OFXUI_2D_PAD
#define OFXUI_2D_PAD

#include "ofxUIWidget.h"
#include "ofxUILabel.h"

class ofxUI2DPad : public ofxUIWidget
{
public:
    ofxUI2DPad(float x, float y, float w, float h,
               ofPoint _value, string _name);

    ofxUI2DPad(float x, float y, float w, float h,
               ofPoint _rangeX, ofPoint _rangeY, ofPoint _value, string _name);
    
    ofxUI2DPad(float w, float h, ofPoint _value, string _name);
	
    ofxUI2DPad(float w, float h,
               ofPoint _rangeX, ofPoint _rangeY, ofPoint _value, string _name);
    
    virtual ~ofxUI2DPad() {}
    
    void init(float w, float h,
              ofPoint _rangeX, ofPoint _rangeY, ofPoint _value, string _name);
    
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    virtual void drawFillHighlight();

    float getIncrement();
    void setIncrement(float _increment);

    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void windowResized(int w, int h);
    
	void input(float x, float y);
	void updateLabel();	
    virtual void stateChange();
    virtual void setVisible(bool _visible);
	void setValue(ofPoint _value);
	ofPoint getValue();
	ofPoint getPercentValue();
	ofPoint getScaledValue();
	ofxUILabel *getLabel();
	virtual void setParent(ofxUIWidget *_parent);
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	ofPoint value; 
    float increment;
	ofxUILabel *label; 
    ofPoint rangeX, rangeY; 
}; 

#endif
