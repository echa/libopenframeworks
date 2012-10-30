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

#include "ofxUIToggleMatrix.h"

ofxUIToggleMatrix::ofxUIToggleMatrix(float x, float y, float w, float h,
                                     int _rows, int _cols, string _name)
{
    rect = new ofxUIRectangle(x,y,w,h); 
    init(w, h, _rows, _cols, _name); 
}

ofxUIToggleMatrix::ofxUIToggleMatrix(float w, float h, int _rows, int _cols,
                                     string _name)
{
    rect = new ofxUIRectangle(0,0,w,h); 
    init(w, h, _rows, _cols, _name); 
}    

void ofxUIToggleMatrix::init(float w, float h, int _rows, int _cols,
                             string _name)
{
    name = _name; 		
    kind = OFX_UI_WIDGET_TOGGLEMATRIX; 		
    rows = _rows; 
    cols = _cols; 
    draw_back = false;  
    paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
    paddedRect->setParent(rect); 
    
    label = new ofxUILabel(0,0,(name+" LABEL"), name, OFX_UI_FONT_SMALL); 
    label->setParent(label); 
    label->setRectParent(rect); 
    
    ofPoint pos = ofPoint(0,0); 
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {            
            ofxUIToggle *toggle = new ofxUIToggle(pos.x,pos.y, w, h, false, (name+"("+ofToString(i,0)+","+ofToString(j,0)+")")); 
            toggle->setLabelVisible(false); 
            toggles.push_back(toggle);                 
            pos.x += w+padding; 
        }
        pos.y += h+padding; 
        pos.x = 0;
    }
    allowMultiple = true;  
}

void ofxUIToggleMatrix::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect; 
    label->setDrawPadding(false);
    for(int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i]; 			
        t->setDrawPadding(false);             
    }        
}

void ofxUIToggleMatrix::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline; 
    label->setDrawPaddingOutline(false);
    for(int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i]; 			
        t->setDrawPaddingOutline(false);             
    }        
}  

ofxUILabel* ofxUIToggleMatrix::getLabel()
{
    return label; 
}

void ofxUIToggleMatrix::setVisible(bool _visible)
{
    visible = _visible; 
    label->setVisible(visible);         
    for(int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i]; 			
        t->setVisible(visible);             
    }
}

void ofxUIToggleMatrix::activateToggle(string _name)
{
    for(int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i]; 			
        if(!(t->getName().compare(_name.c_str())))
        {
            t->setValue(true); 					
        }
        else 
        {
            t->setValue(false); 
        }			
    }
}

void ofxUIToggleMatrix::setParent(ofxUIWidget *_parent)
{
    parent = _parent; 
    ofxUIRectangle *labelrect = label->getRect(); 

    float tWidth = cols*(toggles[0]->getRect()->width)+cols*padding; 
    float tHeight = rows*(toggles[0]->getRect()->height)+rows*padding; 

    for(int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i]; 			
        t->setParent(this); 
        t->getRect()->setParent(this->getRect()); 
    }
    
    labelrect->x = 0; 
    labelrect->y = tHeight+padding; 

    tWidth+=padding; 
    if(label->getPaddingRect()->width > tWidth)
    {
        tWidth = label->getPaddingRect()->width; 
    }
    
    paddedRect->width = tWidth; 	
    paddedRect->height = tHeight+padding+label->getPaddingRect()->height; 			
}	

void ofxUIToggleMatrix::setAllToggles(bool _value)
{
    for(int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i]; 			
        t->setValue(_value);
    }        
}

void ofxUIToggleMatrix::setAllTogglesAndTrigger(bool _value)
{
    for(int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i]; 			
        t->setValue(_value);
    }        
    
    for(int i = 0; i < toggles.size(); i++)
    {
        triggerEvent(toggles[i]); 
    }        
}

void ofxUIToggleMatrix::setToggle(int x, int y, bool _value)
{
    if(x*y < toggles.size())
    {
        toggles[x+y*rows]->setValue(_value);
    }
}

void ofxUIToggleMatrix::setToggleAndTrigger(int x, int y, bool _value)
{
    setToggle(x,y,_value); 
    triggerEvent(toggles[x+y*rows]); 
    
}

vector<ofxUIToggle *> ofxUIToggleMatrix::getToggles()
{
    return toggles; 
}

void ofxUIToggleMatrix::triggerEvent(ofxUIWidget *child)
{
    if(!allowMultiple)
    {
        activateToggle(child->getName().c_str()); 
    }
    if(parent != NULL)
    {
        parent->triggerEvent(child); 
    }
}	

void ofxUIToggleMatrix::setAllowMultiple(bool _allowMultiple)
{
    allowMultiple = _allowMultiple; 
}
