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

#ifndef OFXUI_SLIDER
#define OFXUI_SLIDER

#include "ofxUIWidget.h"
#include "ofxUILabel.h"

class ofxUISlider : public ofxUIWidget
{
public:
    ofxUISlider() {}
    ofxUISlider(float x, float y, float w, float h, float _min, float _max,
                float _value, string _name);
    
    ofxUISlider(float w, float h, float _min, float _max, float _value,
                string _name);

    virtual ~ofxUISlider() {}
    
    
    void init(float w, float h, float _min, float _max, float _value,
              string _name);

    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void drawFill();
    virtual void drawFillHighlight();

    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void windowResized(int w, int h);
    float getIncrement();
    void setIncrement(float _increment);
	virtual void input(float x, float y);
	virtual void updateLabel();
    virtual void stateChange();

	void setValue(float _value);
	float getValue();
	float getPercentValue();
	float getScaledValue();

	ofxUILabel* getLabel();
    void setLabelVisible(bool _labelVisible);
    virtual void setVisible(bool _visible);
	virtual void setParent(ofxUIWidget *_parent);

    void setLabelPrecision(int _precision);
    void setMax(float _max);
    float getMax();
    void setMin(float _min);
    float getMin();
    ofVec2f getMaxAndMind();
    void setMaxAndMin(float _max, float _min);
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	float value, increment; 
	float max, min; 
	ofxUILabel *label; 
    int labelPrecision;
}; 

#endif
