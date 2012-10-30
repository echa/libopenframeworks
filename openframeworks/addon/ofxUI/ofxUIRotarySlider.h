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

#ifndef OFXUI_ROTARY_SLIDER
#define OFXUI_ROTARY_SLIDER

#include "ofxUIWidget.h"
#include "ofxUILabel.h"

class ofxUIRotarySlider : public ofxUIWidget
{
public:    
    ofxUIRotarySlider(float x, float y, float w, float _min, float _max,
                      float _value, string _name);
    ofxUIRotarySlider(float w, float _min, float _max, float _value,
                      string _name);
    virtual ~ofxUIRotarySlider() {}
    
    void init(float w, float _min, float _max, float _value, string _name);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawBack();
    virtual void drawFill();
    virtual void drawFillHighlight();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void keyPressed(int key);
    void drawArcStrip(float percent);
    void setIncrement(float _increment);
	void input(float x, float y);
	void updateLabel();
    virtual void stateChange();
    virtual void setVisible(bool _visible);
	void setValue(float _value);
	float getValue();
	float getScaledValue();
	ofxUILabel* getLabel();
	virtual void setParent(ofxUIWidget *_parent);

protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	float value, increment; 
	float max, min; 
	ofxUILabel *label; 
    ofPoint center; 
    ofPoint hitPoint; 
    ofPoint homePoint; 
    float outerRadius, innerRadius;
}; 

#endif
