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

#ifndef OFXUI_RADIO
#define OFXUI_RADIO

#include "ofxUIWidget.h"
#include "ofxUIToggle.h"
#include "ofxUILabel.h"


class ofxUIRadio : public ofxUIWidget
{
public:
    ofxUIRadio(float x, float y, float w, float h, string _name,
               vector<string> names, int _orientation);
    ofxUIRadio(float w, float h, string _name, vector<string> names,
               int _orientation);
    virtual ~ofxUIRadio() {}
    
    void init(float w, float h, string _name, vector<string> names,
              int _orientation);
        
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
	ofxUILabel *getLabel();
    virtual void setVisible(bool _visible);
	void activateToggle(string _name);
	virtual void setParent(ofxUIWidget *_parent);
	
	vector<ofxUIToggle *> getToggles();
	virtual void triggerEvent(ofxUIWidget *child);

protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	int orientation; 
	ofxUILabel *label; 
	vector<ofxUIToggle *> toggles; 		   
    bool allowMultiple;
}; 

#endif
