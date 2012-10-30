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

#include "ofxUILabel.h"

ofxUILabel::ofxUILabel(float x, float y, string _name, string _label, int _size)
{
    rect = new ofxUIRectangle(x,y,0,0); 
    init(_name, _label, _size); 		
    autoSize = true;
}

ofxUILabel::ofxUILabel(float x, float y, string _name, int _size)
{
    rect = new ofxUIRectangle(x,y,0,0); 
    init(_name, _name, _size); 		
    autoSize = true;
}

ofxUILabel::ofxUILabel(string _name, string _label, int _size)
{
    rect = new ofxUIRectangle(0,0,0,0); 
    init(_name, _label, _size); 		
    autoSize = true;        
}	

ofxUILabel::ofxUILabel(string _name, int _size)
{
    rect = new ofxUIRectangle(0,0,0,0); 
    init(_name, _name, _size); 		
    autoSize = true;
}   

ofxUILabel::ofxUILabel(float x, float y, float w, string _name, string _label,
                       int _size)
{
    rect = new ofxUIRectangle(x,y,w,0); 
    init(_name, _label, _size); 		
    autoSize = false;
}

ofxUILabel::ofxUILabel(float x, float y, float w, string _name, int _size)
{
    rect = new ofxUIRectangle(x,y,w,0); 
    init(_name, _name, _size); 		
    autoSize = false;
}

ofxUILabel::ofxUILabel(float w, string _name, string _label, int _size)
{
    rect = new ofxUIRectangle(0,0,w,0); 
    init(_name, _label, _size); 		
    autoSize = false;        
}	

ofxUILabel::ofxUILabel(float w, string _name, int _size)
{
    rect = new ofxUIRectangle(0,0,w,0); 
    init(_name, _name, _size); 		
    autoSize = false;
}   


void ofxUILabel::init(string _name, string _label, int _size)
{
    name = _name;
    kind = OFX_UI_WIDGET_LABEL; 
    label = _label; 		 				
    size = _size;		

    font = NULL;                 
    draw_back = OFX_UI_LABEL_DRAW_BACK; 
    draw_fill = true; 
    paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
    paddedRect->setParent(rect); 
}

void ofxUILabel::drawBack()
{
    if(draw_back)
    {
        drawBackLabel(); 
    }
}

void ofxUILabel::drawFill()
{
    if(draw_fill)
    {
        ofFill(); 
        ofSetColor(color_fill); 
        font->drawString(label, rect->getX()+xOffset, rect->getY()+rect->getHeight()); 
    }
}

void ofxUILabel::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofFill(); 
        ofSetColor(color_fill_highlight); 
        font->drawString(label, rect->getX()+xOffset, rect->getY()+rect->getHeight()); 
    }        
}	
        
void ofxUILabel::drawBackLabel()
{      
    ofFill(); 
    ofSetColor(color_back);     
    font->drawString(label, rect->getX()+1+xOffset, rect->getY()+rect->getHeight()+1);         
}

void ofxUILabel::drawString(float x, float y, string _string)
{
    if(visible)
    {
        font->drawString(_string, x, y); 
    }
}

void ofxUILabel::drawStringShadow(float x, float y, string _string)
{
    if(visible)
    {
        ofFill(); 
        ofSetColor(color_back);     
        font->drawString(_string, x+1, y+1);                     
    }
}

float ofxUILabel::getStringWidth(string s)
{
    return font->stringWidth(s); 
}

float ofxUILabel::getStringHeight(string s)
{
    return font->stringHeight(s); 
}

void ofxUILabel::setLabel(string _label)
{
    label = _label; 		
    if(autoSize)
    {
        float w = font->stringWidth(label); 
        float h = font->stringHeight(label); 		
        rect->width = w; 
        rect->height = h; 		 
        paddedRect->width = w+padding*3.0; 
        paddedRect->height = h+padding*2.0; 
        xOffset = 0;
    }
    else
    {
        while(getStringWidth(label) > rect->width-padding*4.0)
        {
            string::iterator it;
            it=label.begin();
            label.erase (it);                    
        }                        
        float w = font->stringWidth(label); 
        float h = font->stringHeight(label); 		
        rect->height = h; 		             
        paddedRect->height = h+padding*2.0;             
        paddedRect->width = rect->width+padding*2.0;
        xOffset = rect->width*.5 - w*.5;
    }
}
    
string ofxUILabel::getLabel()
{
    return label; 
}

void ofxUILabel::setFont(ofTrueTypeFont *_font)
{
    font = _font; 
    setLabel(label); 
}

int ofxUILabel::getSize()
{
    return size; 
}

void ofxUILabel::focus()
{
    draw_fill_highlight = true; 
    draw_fill = false; 
}

void ofxUILabel::unfocus()
{
    draw_fill_highlight	= false; 		
    draw_fill = true; 
}
