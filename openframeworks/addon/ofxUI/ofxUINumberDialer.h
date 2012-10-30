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

#ifndef OFXUI_NUMBER_DIALER
#define OFXUI_NUMBER_DIALER

#include "ofxUIWidget.h"
#include "ofxUILabel.h"

class ofxUINumberDialer : public ofxUIWidget
{
public:
    ofxUINumberDialer(float x, float y, float _min, float _max, float _value,
                      int _precision, string _name, int _size);
    
    ofxUINumberDialer(float _min, float _max, float _value, int _precision,
                      string _name, int _size);
    virtual ~ofxUINumberDialer() {}

    void init(float _min, float _max, float _value, int _precision,
              string _name, int _size);

    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    float getValue();
    void setValue(float _value);
    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual void windowResized(int w, int h);
    virtual void stateChange();
		
    virtual void setVisible(bool _visible);
	ofxUILabel* getLabel();
	string getTextString();
	void setTextString(string s);
	virtual void setParent(ofxUIWidget *_parent);
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	ofxUILabel *label; 
	string textstring;  
    string displaystring; 

    int precision; 
	float value, zoneMultiplier; 
	float max, min; 
    ofPoint hitPoint; 
    int numOfPrecisionZones; 
    int currentPrecisionZone;
}; 

#endif
