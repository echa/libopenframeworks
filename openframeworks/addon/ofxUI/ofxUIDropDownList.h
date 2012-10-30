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

#ifndef OFXUI_DROP_DOWN_LIST
#define OFXUI_DROP_DOWN_LIST

#include "ofxUIToggle.h"
#include "ofxUILabelToggle.h"

class ofxUIDropDownList : public ofxUIToggle
{
public:    
    ofxUIDropDownList(float x, float y, float w,
                      string _name, vector<string> items, int _size);
    ofxUIDropDownList(float w, string _name, vector<string> items, int _size);
    ofxUIDropDownList(float x, float y,
                      string _name, vector<string> items, int _size);
    ofxUIDropDownList(string _name, vector<string> items, int _size);
    virtual ~ofxUIDropDownList() {}

    void init(string _name, vector<string> items, int _size);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    void initToggles(vector<string> &items, int _size);
    virtual void setParent(ofxUIWidget *_parent);
    virtual void mouseReleased(int x, int y, int button);
    void setAutoClose(bool _autoClose);
    void open();
    void close();
    virtual void setVisible(bool _visible);
    void setToggleVisibility(bool _value);
    vector<ofxUILabelToggle *>& getToggles();
    void triggerEvent(ofxUIWidget *child);
	void activateToggle(string _name);
    void setAllowMultiple(bool _allowMultiple);
    bool isOpen();
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool autoSize;
    bool autoClose;
    vector<ofxUILabelToggle *> toggles;
    bool allowMultiple;
}; 

#endif
