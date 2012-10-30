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

#ifndef OFXUI_CANVAS
#define OFXUI_CANVAS

#include "ofxUIWidget.h"
#include "ofxUILabel.h"
#include "ofxUIEventArgs.h"
#include "ofxXmlSettings.h" //Using ofxXmlSettings to save and load state
#include <vector>
#include <map>

class ofxUICanvas : public ofxUIWidget
{    
public:	
    ofxUICanvas();
    ofxUICanvas(float x, float y, float w, float h);
    ofxUICanvas(float x, float y, float w, float h,
                ofxUICanvas *sharedResources);
    ofxUICanvas(ofxUICanvas *sharedResources);
    virtual ~ofxUICanvas();
    
    void init(int w, int h);
    void init(int w, int h, ofxUICanvas *sharedResources);
    void saveSettings(string fileName);
    void writeSpecificWidgetData(ofxUIWidget *widget, ofxXmlSettings *XML);
    void loadSettings(string fileName);
    void loadSpecificWidgetData(ofxUIWidget *widget, ofxXmlSettings *XML);
    ofTrueTypeFont *getFontLarge();
    ofTrueTypeFont *getFontMedium();
    ofTrueTypeFont *getFontSmall();

    //Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
    bool loadFont(string filename,
                 bool _bAntiAliased = true,
                 bool _bFullCharacterSet = true,
                 bool makeContours = false,
                 float simplifyAmt = 0.0,
                 int dpi = OFX_UI_FONT_RESOLUTION);
    
    void setFontSize(ofxWidgetFontType _kind, int _size,
                    int _resolution = OFX_UI_FONT_RESOLUTION);

    void setWidgetSpacing(float _widgetSpacing);
    float getWidgetSpacing();
    bool isEnabled();
    virtual void setVisible(bool _visible);
	virtual void toggleVisible();
    bool hasKeyboardFocus();
	void enable();
	void disable();
	
	//App Callbacks
    void enableAppEventCallbacks();
	
	//App Callbacks
    void disableAppEventCallbacks();
	
#ifdef TARGET_OPENGLES	
	//Touch Callbacks
    void enableTouchEventCallbacks();
	void disableTouchEventCallbacks();
#else
	
	//Mouse Callbacks
    void enableMouseEventCallbacks();
    void disableMouseEventCallbacks();

	//KeyBoard Callbacks
	void enableKeyEventCallbacks();
	void disableKeyEventCallbacks();

    //Window Resize Callback
    void enableWindowEventCallbacks();
    void disableWindowEventCallbacks();
	
#endif	

    void onUpdate(ofEventArgs& data);
    void onDraw(ofEventArgs& data);
    void onExit(ofEventArgs& data);

    void update();
    void draw();
    void exit();
        
#ifdef TARGET_OPENGLES
	
    void onTouchDown(ofTouchEventArgs &data);
    void onTouchMoved(ofTouchEventArgs &data); 
    void onTouchUp(ofTouchEventArgs &data);
    void onTouchDoubleTap(ofTouchEventArgs &data);
	void onTouchCancelled(ofTouchEventArgs &data);
	void touchDown(ofTouchEventArgs& touch);   
	void touchMoved(ofTouchEventArgs& touch);
	void touchUp(ofTouchEventArgs& touch);
	void touchDoubleTap(ofTouchEventArgs& touch);
	void touchCancelled(ofTouchEventArgs& touch);
	
#else	
    
    void onMouseReleased(ofMouseEventArgs& data);
    void onMousePressed(ofMouseEventArgs& data);
    void onMouseMoved(ofMouseEventArgs& data);
    void onMouseDragged(ofMouseEventArgs& data);
	void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
	void onKeyPressed(ofKeyEventArgs& data);
    void onKeyReleased(ofKeyEventArgs& data);
    void keyPressed(int key);
    void keyReleased(int key);
    void onWindowResized(ofResizeEventArgs& data);
    void windowResized(int w, int h);
    
#endif	
	
    virtual bool isHit(float x, float y);
    ofxUIWidget* getWidgetHit(float x, float y);
    virtual void stateChange();
    void autoSizeToFitWidgets();
	void addWidget(ofxUIWidget *widget);
	ofxUIWidget* addWidgetDown(ofxUIWidget *widget,
	                           ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT);
	ofxUIWidget* addWidgetUp(ofxUIWidget *widget,
	                         ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT);
	ofxUIWidget* addWidgetRight(ofxUIWidget *widget);
    ofxUIWidget* addWidgetLeft(ofxUIWidget *widget);
    ofxUIWidget* addWidgetSouthOf(ofxUIWidget *widget, string referenceName);
    ofxUIWidget* addWidgetNorthOf(ofxUIWidget *widget, string referenceName);
    ofxUIWidget* addWidgetWestOf(ofxUIWidget *widget, string referenceName);
    ofxUIWidget* addWidgetEastOf(ofxUIWidget *widget, string referenceName);

	void setLabelFont(ofxUILabel *label);
	void triggerEvent(ofxUIWidget *child);
	void setWidgetColor(int _target, ofColor _color);
    ofxUIWidget* getWidget(string _name);
    void removeWidget(string _name);
    void removeWidget(ofxUIWidget *widget);
	virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawWidgetPadding(bool _draw_padded_rect);
	virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline);

    vector<ofxUIWidget*> getWidgets();
    vector<ofxUIWidget*> getWidgetsOfType(ofxWidgetType type);

	ofEvent<ofxUIEventArgs> newGUIEvent;
	
protected:    
    
    void pushbackWidget(ofxUIWidget *widget);
    //Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)    
    bool updateFont(ofxWidgetFontType _kind, string filename,
                    int fontsize, bool _bAntiAliased = true,
                    bool _bFullCharacterSet = false,
                    bool makeContours = false,
                    float simplifyAmt = 0.3,
                    int dpi = 0);

    void checkForKeyFocus(ofxUIWidget *child);
    
	ofTrueTypeFont*             font_large;
	ofTrueTypeFont*             font_medium;
	ofTrueTypeFont*             font_small;
	ofxUIEventArgs*             GUIevent;
    int                         state;
    bool                        hasSharedResources;
    map<string, ofxUIWidget*>   widgets_map;
	vector<ofxUIWidget*>        widgets;
	vector<ofxUIWidget*>        widgetsWithState;
	ofxUIWidget*                lastAdded;
	ofxUIWidget*                activeFocusedWidget;
	bool                        enable_highlight_outline;
	bool                        enable_highlight_fill;
	bool                        enabled;
    int                         uniqueIDs;
    bool                        hasKeyBoard;
    float                       widgetSpacing;
    string                      fontName;
};

#endif

