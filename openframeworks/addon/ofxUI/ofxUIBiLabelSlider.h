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

#ifndef OFXUI_BILABEL_SLIDER
#define OFXUI_BILABEL_SLIDER

#include "ofxUISlider.h"
#include "ofxUILabel.h"

class ofxUIBiLabelSlider : public ofxUISlider
{
public:
    ofxUIBiLabelSlider(float x, float y, float w, float h,
                       float _min, float _max, float _value,
                       string _name, string _leftLabel, string _rightLabel);

    ofxUIBiLabelSlider(float w, float h, float _min, float _max,
                       float _value, string _name, string _leftLabel,
                       string _rightLabel);
    
    ofxUIBiLabelSlider(float x, float y, float w, float _min, float _max,
                       float _value, string _name, string _leftLabel,
                       string _rightLabel, int _size);
    
    ofxUIBiLabelSlider(float w, float _min, float _max, float _value,
                       string _name, string _leftLabel, string _rightLabel,
                       int _size);

    virtual ~ofxUIBiLabelSlider() {}
    
    void init(float w, float h, float _min, float _max, float _value,
              string _name, string _leftLabel, string _rightLabel, int _size);

    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    virtual void drawFillHighlight();
    void input(float x, float y);
	void updateLabel();
	virtual void setParent(ofxUIWidget *_parent);
    ofxUILabel* getRightLabel();
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool autoSize;     
    string leftLabel, rightLabel; 
    ofxUILabel *rlabel; 
}; 

#endif
