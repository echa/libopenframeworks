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

#ifndef OFXUI_WIDGET
#define OFXUI_WIDGET

#include "ofxUIRectangle.h"
#include "ofxUIdefs.h"

class ofxUIWidget           
{
public:
    ofxUIWidget();
    virtual ~ofxUIWidget();
    virtual void update();
    virtual void draw();
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void drawFill();
    virtual void drawFillHighlight();
    virtual void drawPadded();
    virtual void drawPaddedOutline();    
    
#ifdef TARGET_OPENGLES          //iOS Mode
    void touchDown(ofTouchEventArgs& touch);
    void touchMoved(ofTouchEventArgs& touch);
    void touchUp(ofTouchEventArgs& touch);
    void touchCancelled(ofTouchEventArgs& touch);
    void touchDoubleTap(ofTouchEventArgs& touch);
#endif

	virtual void mouseMoved(int x, int y ) {}
	virtual void mouseDragged(int x, int y, int button) {}
	virtual void mousePressed(int x, int y, int button) {}
	virtual void mouseReleased(int x, int y, int button) {}
    
	virtual void keyPressed(int key) {}
	virtual void keyReleased(int key) {}
	virtual void windowResized(int w, int h) {}           		
    
	virtual void setParent(ofxUIWidget *_parent);
	virtual void setRectParent(ofxUIRectangle *_prect);
	virtual ofxUIWidget* getParent();
	virtual ofxUIRectangle* getRect();
	virtual void setName(string _name);
	virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
	virtual void setDrawBack(bool _draw_back);
	virtual void setDrawOutline(bool _draw_outline);
	virtual void setDrawFill(bool _draw_fill);
	virtual void setDrawFillHighLight(bool _draw_fill_highlight);
	virtual void setDrawOutlineHighLight(bool _draw_outline_hightlight);
	virtual void setColorBack(ofColor _color_back);
	virtual void setColorOutline(ofColor _color_outline);
	virtual void setColorOutlineHighlight(ofColor _color_outline_highlight);
	virtual void setColorFill(ofColor _color_fill);
	virtual void setColorFillHighlight(ofColor _color_fill_highlight);
    virtual void setColorPadded(ofColor _color_padded_rect);
    virtual void setColorPaddedOutline(ofColor _color_padded_rect_outline);

	ofColor& getColorPadded();
	ofColor& getColorPaddedOutline();
	ofColor& getColorBack();
	ofColor& getColorOutline();
	ofColor& getColorOutlineHighlight();
	ofColor& getColorFill();
	ofColor& getColorFillHighlight();

    virtual int getKind();
	virtual void setFont(ofTrueTypeFont *_font);
    virtual void setVisible(bool _visible);
    virtual bool isVisible();
    virtual void toggleVisible();
    virtual bool isHit(float x, float y);
	virtual string getName();
	virtual void triggerEvent(ofxUIWidget *child);
    virtual void triggerSelf();
	virtual void setPadding(float _padding);
	virtual float getPadding();
	virtual ofxUIRectangle *getPaddingRect();
    virtual void stateChange() {}
    void setID(int _id);
    int getID();

protected:    
	ofxUIWidget *parent; 
	ofxUIRectangle *rect; 	
	ofTrueTypeFont *font; 	
	
    string name;            //State Properties
	int kind; 
	bool visible; 
    int id;     
    bool hit; 
    int state; 
    
	bool draw_back;         //Rendering Properties 
	bool draw_outline; 
	bool draw_outline_highlight; 
	bool draw_fill; 
	bool draw_fill_highlight; 

	ofColor color_back; 
	ofColor color_outline; 
	ofColor color_outline_highlight;	
	ofColor color_fill; 
	ofColor color_fill_highlight; 

	float padding;          //Spacing/Padding Purposes
	ofxUIRectangle *paddedRect; 	

	bool draw_padded_rect; 
	bool draw_padded_rect_outline;     
    ofColor color_padded_rect; 
	ofColor color_padded_rect_outline;
    
#ifdef TARGET_OPENGLES          //iOS Mode
    int touchId;     
#endif
    
    bool dead; 
};

#endif
