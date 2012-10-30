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

#include "ofxUIRectangle.h"

ofxUIRectangle::ofxUIRectangle()
{
    x = y = width = height = 0.0f; 
    setParent(NULL);         
}

ofxUIRectangle::ofxUIRectangle(float _x, float _y, float _w, float _h)
{
    x = _x;
    y = _y;
    width = _w;
    height = _h;
    setParent(NULL); 
}

ofxUIRectangle::ofxUIRectangle(ofRectangle const & r)
{
    x = r.x;
    y = r.y;
    width = r.width;
    height = r.height;
    setParent(NULL); 
}

void ofxUIRectangle::setParent(ofxUIRectangle *_parent)
{
    parent = _parent; 
}

void ofxUIRectangle::setHeight(float _height)
{
    height = _height; 
}

void ofxUIRectangle::setWidth(float _width)
{
    width = _width; 
}

bool ofxUIRectangle::inside(ofPoint p)
{
    if(parent !=NULL)
    {
        return insideParent(p.x, p.y); 
    }
    else
    {
        return insideChild(p.x, p.y);
    }
}

bool ofxUIRectangle::inside(float px, float py)
{
    if(parent != NULL)
    {
        return insideParent(px,py); 
    }
    else
    {
        return insideChild(px,py); 
    }
}

bool ofxUIRectangle::insideChild(float px, float py)
{
    if( px > x && py > y && px < x + width && py < y + height ){
        return true;
    }
    return false;

}

bool ofxUIRectangle::insideParent(float px, float py)
{
    if( px > (x+parent->getX()) && py > (y+parent->getY()) && px < (x+parent->getX()) + width && py < (y+parent->getY()) + height )
    {
        return true;
    }
    return false;    
}

ofVec2f ofxUIRectangle::percentInside(float px, float py)
{
    if(parent != NULL)
    {
        return percentInsideParent(px,py); 
    }
    else
    {
        return percentInsideChild(px,py); 
    }		
}

ofVec2f ofxUIRectangle::percentInsideChild(float px, float py)
{
    return ofVec2f((px-x)/(width), (py-y)/(height)); 
}

ofVec2f ofxUIRectangle::percentInsideParent(float px, float py)
{		
    return ofVec2f((px-(x+parent->getX()))/(width), (py-(y+parent->getY()))/(height)); 
}

void ofxUIRectangle::draw()
{
    if(parent != NULL)
    {            
        ofRect(parent->getX()+x, parent->getY()+y, width, height); 
    }
    else
    {
        ofRect(x,y,width,height); 
    }
}

float ofxUIRectangle::getX()
{
    if(parent != NULL)
    {            
        return (x+parent->getX()); 
    }
    else
    {
        return x; 
    }		
}

float ofxUIRectangle::getY()
{
    if(parent != NULL)
    {            
        return (y+parent->getY()); 
    }
    else
    {
        return y; 
    }				
}

float ofxUIRectangle::getWidth()
{
    return width; 
}

float ofxUIRectangle::getHeight()
{
    return height; 
}
