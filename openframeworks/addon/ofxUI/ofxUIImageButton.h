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

#ifndef OFXUI_IMAGE_BUTTON
#define OFXUI_IMAGE_BUTTON

#include "ofxUIButton.h"

class ofxUIImageButton : public ofxUIButton
{
public:
    ofxUIImageButton() {}
    virtual ~ofxUIImageButton();
    
    ofxUIImageButton(float x, float y, float w, float h, bool _value,
                     string _pathURL, string _name);

    ofxUIImageButton(float w, float h, bool _value,
                     string _pathURL, string _name);
    
    void init(float w, float h, bool _value, string _pathURL, string _name);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawBack();
    virtual void drawFill();
    virtual void drawFillHighlight();
    virtual void drawOutlineHighlight();
    virtual void stateChange();
	virtual void setParent(ofxUIWidget *_parent);
    virtual void setValue(bool _value);
    virtual void setVisible(bool _visible);
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    ofImage *img; 
}; 

#endif
