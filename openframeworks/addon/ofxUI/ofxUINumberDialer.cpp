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

#include "ofxUINumberDialer.h"
#include <cmath>

ofxUINumberDialer::ofxUINumberDialer(float x, float y, float _min, float _max,
                                     float _value, int _precision, string _name,
                                     int _size)
{
    rect = new ofxUIRectangle(x,y,0,0); 
    init(_min, _max, _value, _precision, _name, _size); 
}

ofxUINumberDialer::ofxUINumberDialer(float _min, float _max, float _value,
                                     int _precision, string _name, int _size)
{
    rect = new ofxUIRectangle(0,0,0,0); 
    init(_min, _max, _value, _precision, _name, _size); 
}    

void ofxUINumberDialer::init(float _min, float _max, float _value,
                             int _precision, string _name, int _size)
{
    name = _name; 		
    kind = OFX_UI_WIDGET_NUMBERDIALER;  		
    value = _value; 
    max = _max; 
    min = _min; 
    if(value > max)
    {
        value = max;             
    }
    else if(value < min)
    {
        value = min; 
    }
    precision = _precision; 
    
    string minString = ofToString(min, precision); 
    string maxString = ofToString(max, precision);         
    if(minString.length() > maxString.length())
    {
        textstring = minString; 
        numOfPrecisionZones = minString.length()-1;             //1 for the "-" sign
    }
    else
    {
        textstring = maxString; 
        numOfPrecisionZones = maxString.length(); 
    }
    
    if(precision > 0)
    {
        numOfPrecisionZones -= 1; 
    }
    
    displaystring = textstring; 
    
    paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
    paddedRect->setParent(rect); 
    
    label = new ofxUILabel(padding*2.0,0,(name+" LABEL"), textstring, _size); 
    label->setParent(label); 
    label->setRectParent(rect);     
}

void ofxUINumberDialer::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect; 
    label->setDrawPadding(false);
}

void ofxUINumberDialer::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline; 
    label->setDrawPaddingOutline(false);
}  

float ofxUINumberDialer::getValue()
{
    return value; 
}

void ofxUINumberDialer::setValue(float _value)
{
    if(_value > max)
    {
        _value = max;             
    }
    else if(_value < min)
    {
        _value = min; 
    }            
    value = _value; 
    setTextString(ofToString(value, precision));         
}

void ofxUINumberDialer::mouseMoved(int x, int y ) 
{
    if(rect->inside(x, y))
    {
        state = OFX_UI_STATE_OVER;         			
    }    
    else
    {
        state = OFX_UI_STATE_NORMAL;        
    }
    stateChange();         
}

void ofxUINumberDialer::mouseDragged(int x, int y, int button) 
{
    if(hit)
    {            
        value += zoneMultiplier*(hitPoint.y-y); 
        if(value > max)
        {
            value = max;             
        }
        else if(value < min)
        {
            value = min; 
        }            
        hitPoint = ofPoint(x,y); 
        setTextString(ofToString(value, precision));     
        triggerEvent(this);             
        state = OFX_UI_STATE_DOWN;         
    }    
    else
    {
        state = OFX_UI_STATE_NORMAL;               
    }
    stateChange();     
}

void ofxUINumberDialer::mousePressed(int x, int y, int button) 
{
    if(rect->inside(x, y))
    {
        hit = true; 
        hitPoint = ofPoint(x,y); 
        currentPrecisionZone = ceil(ofMap(x,rect->getX(),rect->getX()+rect->getWidth(),0,numOfPrecisionZones));             
        zoneMultiplier = pow(10.0,numOfPrecisionZones-currentPrecisionZone-precision);     
        state = OFX_UI_STATE_DOWN;     
        triggerEvent(this);            
    }    
    else
    {
        state = OFX_UI_STATE_NORMAL;        
    }
    stateChange();         
}

void ofxUINumberDialer::mouseReleased(int x, int y, int button) 
{
    if(hit)
    {
#ifdef TARGET_OPENGLES
        state = OFX_UI_STATE_NORMAL;        
#else            
        state = OFX_UI_STATE_OVER; 
#endif 
        triggerEvent(this); 
    }    
    else
    {
        state = OFX_UI_STATE_NORMAL;         
    }
    stateChange();   
    hit = false; 
}

void ofxUINumberDialer::keyPressed(int key) 
{}

void ofxUINumberDialer::keyReleased(int key) 
{}

void ofxUINumberDialer::windowResized(int w, int h) 
{}

void ofxUINumberDialer::stateChange()
{        
    switch (state) {
        case OFX_UI_STATE_NORMAL:
        {            
            draw_fill_highlight = false;             
            draw_outline_highlight = false;  
            label->unfocus(); 								
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;            
            draw_outline_highlight = true;  
            label->focus(); 								
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_fill_highlight = false;            
            draw_outline_highlight = true;             
            label->focus(); 					
        }
            break;
        case OFX_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;            
            draw_outline_highlight = false;                         
            label->unfocus(); 								
        }
            break;            
            
        default:
            break;
    }        
}
    
void ofxUINumberDialer::setVisible(bool _visible)
{
    visible = _visible; 
    label->setVisible(visible); 
}

ofxUILabel* ofxUINumberDialer::getLabel()
{
    return label; 
}

string ofxUINumberDialer::getTextString()
{
    return textstring; 
}

void ofxUINumberDialer::setTextString(string s)	
{
    textstring = s; 
    displaystring = s; 
    while(label->getStringWidth(displaystring) > rect->width-padding*4.0)
    {
        string::iterator it;
        it=displaystring.begin();
        displaystring.erase (it);                    
    }
    label->setLabel(displaystring);         
}

void ofxUINumberDialer::setParent(ofxUIWidget *_parent)
{
    parent = _parent; 
    rect->height = label->getPaddingRect()->height+padding*2.0; 
    rect->width = label->getPaddingRect()->width+padding*2.0; 
    ofxUIRectangle *labelrect = label->getRect(); 
    float h = labelrect->getHeight(); 
    float ph = rect->getHeight(); 	
    
    labelrect->y = ph/2.0 - h/2.0; 
    
    paddedRect->height = rect->height+padding*2.0; 
    paddedRect->width = rect->width+padding*2.0;         
    setTextString(ofToString(value, precision));                     
}	
