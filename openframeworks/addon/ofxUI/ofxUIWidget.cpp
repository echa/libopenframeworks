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

#include "ofxUIWidget.h"

ofxUIWidget::ofxUIWidget() 
{        
    name = "base"; 
    id = -1; 
    hit = false; 
    visible = true; 
#ifdef TARGET_OPENGLES
    touchId = -1; 
#endif
    
    state = OFX_UI_STATE_NORMAL; 
    draw_back = true; 
    draw_outline = false; 
    draw_fill = false; 
    draw_fill_highlight = false;
    draw_outline_highlight = false;         

    padding = OFX_UI_GLOBAL_PADDING; 
    draw_padded_rect = OFX_UI_DRAW_PADDING; 						
    draw_padded_rect_outline = OFX_UI_DRAW_PADDING_OUTLINE; 						        
    
    color_back = OFX_UI_COLOR_BACK;								//the rect's back color
    color_outline = OFX_UI_COLOR_OUTLINE;						//the rect's outline color 
    color_outline_highlight = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;   //the rect's onMouseOver outline highlight color         
    color_fill = OFX_UI_COLOR_FILL;								//the rect's fill color 
    color_fill_highlight = OFX_UI_COLOR_FILL_HIGHLIGHT;         //the rect's onMouseDown highlight color 

    color_padded_rect = OFX_UI_COLOR_PADDED;
    color_padded_rect_outline = OFX_UI_COLOR_PADDED_OUTLINE;     
    
    dead = false; 
}

ofxUIWidget::~ofxUIWidget() 
{
    if(rect != NULL)
    {
        delete rect; 
    }
    if(paddedRect != NULL)
    {
        delete paddedRect; 
    }
}

void  ofxUIWidget::update()
{}

void ofxUIWidget::draw() 
{
    ofPushStyle(); 
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
    
    drawPadded();
    drawPaddedOutline();        

    drawBack();
    
    drawOutline();
    drawOutlineHighlight();
    
    drawFill();
    drawFillHighlight();
    
    ofPopStyle();
}

void ofxUIWidget::drawBack()
{
    if(draw_back)
    {
        ofFill(); 
        ofSetColor(color_back); 
        rect->draw(); 
    }
}

void ofxUIWidget::drawOutline()
{
    if(draw_outline)
    {
        ofNoFill();
        ofSetColor(color_outline); 
        rect->draw(); 
    } 
}

void ofxUIWidget::drawOutlineHighlight() 
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ofSetColor(color_outline_highlight); 
        rect->draw();          
    }
}    

void ofxUIWidget::drawFill()
{
    if(draw_fill)
    {
        ofFill(); 
        ofSetColor(color_fill); 
        rect->draw(); 
    }
}

void ofxUIWidget::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofFill(); 
        ofSetColor(color_fill_highlight); 
        rect->draw(); 
    }    
}

void ofxUIWidget::drawPadded()
{
    if(draw_padded_rect)
    {
        ofFill();
        ofSetColor(color_padded_rect); 
        paddedRect->draw(); 
    }                
}

void ofxUIWidget::drawPaddedOutline()
{
    if(draw_padded_rect_outline)
    {
        ofNoFill();
        ofSetColor(color_padded_rect_outline); 
        paddedRect->draw(); 
    }                
}     


#ifdef TARGET_OPENGLES          //iOS Mode
void ofxUIWidget::touchDown(ofTouchEventArgs& touch)
{
    if(touchId == -1)
    {    
        this->mousePressed(touch.x, touch.y, 0);
        if(hit)
        {
            touchId = touch.id;    
        }            
    }    
}

void ofxUIWidget::touchMoved(ofTouchEventArgs& touch) 
{
    if(touchId == touch.id)
    {
        this->mouseDragged(touch.x, touch.y, 0); 
    }       
}

void ofxUIWidget::touchUp(ofTouchEventArgs& touch) 
{
    if(touchId == touch.id)
    {
        this->mouseReleased(touch.x, touch.y, 0); 
        touchId = -1;                      
    }
}

void ofxUIWidget::touchCancelled(ofTouchEventArgs& touch) 
{
    if(touchId == touch.id)
    {
        this->mouseReleased(touch.x, touch.y, 0); 
        touchId = -1;                
    }
}         

void ofxUIWidget::touchDoubleTap(ofTouchEventArgs& touch)
{
}
#endif // TARGET_OPENGLES

void ofxUIWidget::setParent(ofxUIWidget *_parent)
{
    parent = _parent; 
}

void ofxUIWidget::setRectParent(ofxUIRectangle *_prect)
{
    rect->setParent(_prect); 
}

ofxUIWidget* ofxUIWidget::getParent()
{
    return parent; 
}

ofxUIRectangle* ofxUIWidget::getRect()
{
    return rect; 
}

void ofxUIWidget::setName(string _name)
{
    name = _name; 
}

void ofxUIWidget::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect; 
}

void ofxUIWidget::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline; 
}    

void ofxUIWidget::setDrawBack(bool _draw_back)
{
    draw_back = _draw_back; 
}

void ofxUIWidget::setDrawOutline(bool _draw_outline)
{
    draw_outline = _draw_outline; 
}

void ofxUIWidget::setDrawFill(bool _draw_fill)
{
    draw_fill = _draw_fill; 
}

void ofxUIWidget::setDrawFillHighLight(bool _draw_fill_highlight)
{
    draw_fill_highlight = _draw_fill_highlight; 
}

void ofxUIWidget::setDrawOutlineHighLight(bool _draw_outline_hightlight)
{
    draw_outline_highlight = draw_outline_highlight; 
}

void ofxUIWidget::setColorBack(ofColor _color_back)
{
    color_back = _color_back; 
}
    
void ofxUIWidget::setColorOutline(ofColor _color_outline)
{
    color_outline = _color_outline; 
}

void ofxUIWidget::setColorOutlineHighlight(ofColor _color_outline_highlight)
{
    color_outline_highlight = _color_outline_highlight; 
}	

void ofxUIWidget::setColorFill(ofColor _color_fill)
{
    color_fill = _color_fill; 
}

void ofxUIWidget::setColorFillHighlight(ofColor _color_fill_highlight)
{
    color_fill_highlight = _color_fill_highlight; 
}

void ofxUIWidget::setColorPadded(ofColor _color_padded_rect)
{
    color_padded_rect = _color_padded_rect; 
}

void ofxUIWidget::setColorPaddedOutline(ofColor _color_padded_rect_outline)
{
    color_padded_rect_outline = _color_padded_rect_outline; 
}

ofColor& ofxUIWidget::getColorPadded()
{
    return color_padded_rect;
}

ofColor& ofxUIWidget::getColorPaddedOutline()
{
    return color_padded_rect_outline;
}

ofColor& ofxUIWidget::getColorBack()
{
    return color_back; 
}

ofColor& ofxUIWidget::getColorOutline()
{
    return color_outline; 
}

ofColor& ofxUIWidget::getColorOutlineHighlight()
{
    return color_outline_highlight; 
}	

ofColor& ofxUIWidget::getColorFill()
{
    return color_fill; 
}

ofColor& ofxUIWidget::getColorFillHighlight()
{
    return color_fill_highlight; 
}

int ofxUIWidget::getKind()
{
    return kind; 
}

void ofxUIWidget::setFont(ofTrueTypeFont *_font)
{
    font = _font; 
}

void ofxUIWidget::setVisible(bool _visible)
{
    visible = _visible; 
}

bool ofxUIWidget::isVisible()
{
    return visible; 
}

void ofxUIWidget::toggleVisible()
{
    visible =! visible; 
}

bool ofxUIWidget::isHit(float x, float y)
{
    if(visible)
    {
        return paddedRect->inside(x, y);
    }
    else
    {
        return false; 
    }
}

string ofxUIWidget::getName()
{
    return name; 
}

void ofxUIWidget::triggerEvent(ofxUIWidget *child)
{
    if(parent != NULL)
    {
        parent->triggerEvent(child); 
    }
}

void ofxUIWidget::triggerSelf()
{
    if(parent != NULL)
    {
        parent->triggerEvent(this); 
    }        
}

void ofxUIWidget::setPadding(float _padding)
{
    padding = _padding; 
    paddedRect->set(rect->getX()-padding, rect->getY()-padding, rect->getWidth()+padding*2.0, rect->getHeight()+padding*2.0);
}

float ofxUIWidget::getPadding()
{
    return padding; 
}

ofxUIRectangle* ofxUIWidget::getPaddingRect()
{
    return paddedRect; 
}

void ofxUIWidget::setID(int _id)
{
    id = _id; 
}

int ofxUIWidget::getID()
{
    return id;
}
