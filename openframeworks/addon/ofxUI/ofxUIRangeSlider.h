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

#ifndef OFXUI_RANGE_SLIDER
#define OFXUI_RANGE_SLIDER

#include "ofxUIWidget.h"
#include "ofxUILabel.h"

class ofxUIRangeSlider : public ofxUIWidget
{
public:
    ofxUIRangeSlider(float x, float y, float w, float h, float _min, float _max,
                     float _valuelow, float _valuehigh, string _name);
    ofxUIRangeSlider(float w, float h, float _min, float _max, float _valuelow,
                     float _valuehigh, string _name);

    virtual ~ofxUIRangeSlider() {}

    void init(float w, float h, float _min, float _max, float _valuelow,
              float _valuehigh, string _name);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    virtual void drawFillHighlight();
    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void windowResized(int w, int h);

    void setIncrement(float _increment);
	void input(float x, float y);
	void updateLabel();
    virtual void stateChange();

    virtual void setVisible(bool _visible);
	void setValueLow(float _value);
	void setValueHigh(float _value);

	float getPercentValueLow();
	float getPercentValueHigh();
	float getScaledValueLow();
	float getScaledValueHigh();
	ofxUILabel* getLabel();
    void setLabelVisible(bool _labelVisible);
	virtual void setParent(ofxUIWidget *_parent);
    void setMax(float _max);
    void setMin(float _min);
    void setMaxAndMin(float _max, float _min);
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	float valuelow, valuehigh, increment; 
    float hitValueLow, hitValueHigh; 
	bool hitHigh, hitLow, hitCenter; 
	float hitPoint; 
	float max, min; 
	ofxUILabel *label; 
}; 

#endif
