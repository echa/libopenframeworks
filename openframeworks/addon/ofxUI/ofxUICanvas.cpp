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

#include "ofxUICanvas.h"

ofxUICanvas::~ofxUICanvas() 
{
    delete GUIevent; 
    if(!hasSharedResources)
    {
        delete font_large; 
        delete font_medium;
        delete font_small;		
    }
    for(int i = 0; i < widgets.size(); i++)
    {
        ofxUIWidget *w = widgets[i]; 
        delete w; 
    }
    widgets.clear(); 
}

ofxUICanvas::ofxUICanvas(float x, float y, float w, float h) 
{
    rect = new ofxUIRectangle(x,y,w,h);        
    init(w,h);
}

ofxUICanvas::ofxUICanvas(float x, float y, float w, float h,
                         ofxUICanvas *sharedResources) 
{
    rect = new ofxUIRectangle(x,y,w,h);        
    init(w,h, sharedResources);
}

ofxUICanvas::ofxUICanvas() 
{
    float w = ofGetWidth(); 
    float h = ofGetHeight(); 
    rect = new ofxUIRectangle(0,0,w,h); 
    init(w,h);
    setDrawBack(false); 
}

ofxUICanvas::ofxUICanvas(ofxUICanvas *sharedResources) 
{
    float w = ofGetWidth(); 
    float h = ofGetHeight(); 
    rect = new ofxUIRectangle(0,0,w,h); 
    init(w,h, sharedResources);
    setDrawBack(false); 
}

void ofxUICanvas::init(int w, int h)
{
    name = "OFX_UI_WIDGET_CANVAS"; 
    kind = OFX_UI_WIDGET_CANVAS; 
    
    enable(); 
    
    enable_highlight_outline = false; 
    enable_highlight_fill = false; 
    
    GUIevent = new ofxUIEventArgs(this); 
    
    paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
    paddedRect->setParent(rect);
    
    font_large = new ofTrueTypeFont();
    font_medium = new ofTrueTypeFont();
    font_small = new ofTrueTypeFont();
    
    fontName = OFX_UI_FONT_NAME;
    loadFont(fontName,true, true, false, 0.0, OFX_UI_FONT_RESOLUTION);
            
    font = font_medium; 
    lastAdded = NULL; 
    uniqueIDs = 0;         
    widgetSpacing = OFX_UI_GLOBAL_WIDGET_SPACING; 
    hasKeyBoard = false; 
}

void ofxUICanvas::init(int w, int h, ofxUICanvas *sharedResources)
{
    name = "OFX_UI_WIDGET_CANVAS"; 
    kind = OFX_UI_WIDGET_CANVAS; 
    
    enable(); 
    
    enable_highlight_outline = false; 
    enable_highlight_fill = false; 
    
    GUIevent = new ofxUIEventArgs(this); 
    
    paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
    paddedRect->setParent(rect);

    hasSharedResources = true; 
    font_large = sharedResources->getFontLarge();
    font_medium = sharedResources->getFontMedium();
    font_small = sharedResources->getFontSmall();
    
    fontName = OFX_UI_FONT_NAME;
//        setFont(fontName,true, true, false, 0.0, OFX_UI_FONT_RESOLUTION);
    
    font = font_medium; 
    lastAdded = NULL; 
    uniqueIDs = 0;         
    widgetSpacing = OFX_UI_GLOBAL_WIDGET_SPACING; 
    hasKeyBoard = false; 
}    

void ofxUICanvas::saveSettings(string fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings(); 
    for(int i = 0; i < widgetsWithState.size(); i++)
    {                
        int index = XML->addTag("Widget");
        if(XML->pushTag("Widget", index))
        {
            XML->setValue("Kind", widgetsWithState[i]->getKind(), 0);
            XML->setValue("Name", widgetsWithState[i]->getName(), 0);
            writeSpecificWidgetData(widgetsWithState[i], XML); 
        }
        XML->popTag();                            
    }
    XML->saveFile(fileName);                
    delete XML; 
}

void ofxUICanvas::writeSpecificWidgetData(ofxUIWidget *widget,
                                          ofxXmlSettings *XML)
{
    int kind = widget->getKind();        
    switch (kind) {
        case OFX_UI_WIDGET_TOGGLE:
        {
            ofxUIToggle *toggle = (ofxUIToggle *) widget; 
            XML->setValue("Value", (toggle->getValue() ? 1 : 0), 0);                
        }
            break;
            
        case OFX_UI_WIDGET_BILABELSLIDER:
        case OFX_UI_WIDGET_MINIMALSLIDER:                
        case OFX_UI_WIDGET_SLIDER_H:
        case OFX_UI_WIDGET_SLIDER_V:
        {
            ofxUISlider *slider = (ofxUISlider *) widget; 
            XML->setValue("Value", slider->getScaledValue(), 0); 
        }
            break;

        case OFX_UI_WIDGET_RSLIDER_H:
        case OFX_UI_WIDGET_RSLIDER_V:
        {
            ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) widget; 
            XML->setValue("HighValue", rslider->getScaledValueHigh(), 0); 
            XML->setValue("LowValue", rslider->getScaledValueLow(), 0);                 
        }
            break;

        case OFX_UI_WIDGET_NUMBERDIALER:
        {
            ofxUINumberDialer *numdialer = (ofxUINumberDialer *) widget; 
            XML->setValue("Value", numdialer->getValue(), 0); 
        }
            break;

        case OFX_UI_WIDGET_2DPAD:
        {
            ofxUI2DPad *pad = (ofxUI2DPad *) widget; 
            XML->setValue("XValue", pad->getScaledValue().x, 0); 
            XML->setValue("YValue", pad->getScaledValue().y, 0);                 
        }
            break;

        case OFX_UI_WIDGET_TEXTINPUT:
        {
            ofxUITextInput *textInput = (ofxUITextInput *) widget; 
            XML->setValue("Value", textInput->getTextString(), 0);                 
        }
            break;
            
        case OFX_UI_WIDGET_LABELTOGGLE:
        {
            ofxUILabelToggle *ltoggle = (ofxUILabelToggle *) widget; 
            XML->setValue("Value", (ltoggle->getValue() ? 1 : 0), 0);                
        }
            break;

        case OFX_UI_WIDGET_IMAGETOGGLE:
        {
            ofxUIImageToggle *itoggle = (ofxUIImageToggle *) widget; 
            XML->setValue("Value", (itoggle->getValue() ? 1 : 0), 0);                
        }
            break;
            
        case OFX_UI_WIDGET_ROTARYSLIDER:
        {
            ofxUIRotarySlider *rotslider = (ofxUIRotarySlider *) widget;
            XML->setValue("Value", rotslider->getScaledValue(), 0); 
        }
            break;

        default:
            break;
    }
}

void ofxUICanvas::loadSettings(string fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings(); 
    XML->loadFile(fileName); 
    int widgetTags = XML->getNumTags("Widget"); 
    for(int i = 0; i < widgetTags; i++)
    {
        XML->pushTag("Widget", i);
        string name = XML->getValue("Name", "NULL", 0);
        ofxUIWidget *widget = getWidget(name); 
        if(widget != NULL)
        {
            loadSpecificWidgetData(widget, XML); 
            triggerEvent(widget); 
        }
        XML->popTag(); 
    }
    hasKeyBoard = false;                
    delete XML; 
}

void ofxUICanvas::loadSpecificWidgetData(ofxUIWidget *widget,
                                         ofxXmlSettings *XML)
{
    int kind = widget->getKind();        
    switch (kind) 
    {
        case OFX_UI_WIDGET_TOGGLE:
        {
            ofxUIToggle *toggle = (ofxUIToggle *) widget; 
            int value = XML->getValue("Value", (toggle->getValue() ? 1 : 0), 0);                             
            toggle->setValue((value ? 1 : 0)); 
        }
            break;
            
        case OFX_UI_WIDGET_BILABELSLIDER:    
        case OFX_UI_WIDGET_MINIMALSLIDER:
        case OFX_UI_WIDGET_SLIDER_H:
        case OFX_UI_WIDGET_SLIDER_V:
        {
            ofxUISlider *slider = (ofxUISlider *) widget; 
            float value = XML->getValue("Value", slider->getScaledValue(), 0);            
            slider->setValue(value); 
        }
            break;
            
        case OFX_UI_WIDGET_RSLIDER_H:
        case OFX_UI_WIDGET_RSLIDER_V:
        {
            ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) widget; 
            float valueHigh = XML->getValue("HighValue", rslider->getScaledValueHigh(), 0); 
            float valueLow = XML->getValue("LowValue", rslider->getScaledValueLow(), 0); 
            rslider->setValueHigh(valueHigh);
            rslider->setValueLow(valueLow);
        }
            break;
            
        case OFX_UI_WIDGET_NUMBERDIALER:
        {
            ofxUINumberDialer *numdialer = (ofxUINumberDialer *) widget; 
            float value = XML->getValue("Value", numdialer->getValue(), 0);             
            numdialer->setValue(value);                 
        }
            break;
            
        case OFX_UI_WIDGET_2DPAD:
        {
            ofxUI2DPad *pad = (ofxUI2DPad *) widget; 
            float valueX = XML->getValue("XValue", pad->getScaledValue().x, 0); 
            float valueY = XML->getValue("YValue", pad->getScaledValue().y, 0); 
            pad->setValue(ofPoint(valueX, valueY)); 
        }
            break;
            
        case OFX_UI_WIDGET_TEXTINPUT:
        {
            ofxUITextInput *textInput = (ofxUITextInput *) widget; 
            string value = XML->getValue("Value", textInput->getTextString(), 0);             
            textInput->setTextString(value); 
        }
            break;
            
        case OFX_UI_WIDGET_LABELTOGGLE:
        {
            ofxUILabelToggle *ltoggle = (ofxUILabelToggle *) widget; 
            int value = XML->getValue("Value", (ltoggle->getValue() ? 1 : 0), 0);                         
            ltoggle->setValue((value ? 1 : 0)); 
        }
            break;
            
        case OFX_UI_WIDGET_IMAGETOGGLE:
        {
            ofxUIImageToggle *itoggle = (ofxUIImageToggle *) widget; 
            int value = XML->getValue("Value", (itoggle->getValue() ? 1 : 0), 0);                        
            itoggle->setValue((value ? 1 : 0)); 
        }
            break;
            
        case OFX_UI_WIDGET_ROTARYSLIDER:
        {
            ofxUIRotarySlider *rotslider = (ofxUIRotarySlider *) widget;
            float value = XML->getValue("Value", rotslider->getScaledValue(), 0);            
            rotslider->setValue(value); 
        }
            break;
            
        default:
            break;
    }        
}
 
ofTrueTypeFont* ofxUICanvas::getFontLarge()
{
    return font_large;
}    

ofTrueTypeFont* ofxUICanvas::getFontMedium()
{
    return font_medium;
}

ofTrueTypeFont* ofxUICanvas::getFontSmall()
{
    return font_small;
}

//Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
bool ofxUICanvas::loadFont(string filename,
                           bool _bAntiAliased, bool _bFullCharacterSet,
                           bool makeContours, float simplifyAmt,
                           int dpi) 
{
    bool large = updateFont(OFX_UI_FONT_LARGE, filename,
                            OFX_UI_FONT_LARGE_SIZE, _bAntiAliased,
                            _bFullCharacterSet, makeContours,
                            simplifyAmt, dpi);
    bool medium = updateFont(OFX_UI_FONT_MEDIUM, filename,
                             OFX_UI_FONT_MEDIUM_SIZE, _bAntiAliased,
                             _bFullCharacterSet, makeContours, simplifyAmt,
                             dpi);
    bool small = updateFont(OFX_UI_FONT_SMALL, filename,
                            OFX_UI_FONT_SMALL_SIZE, _bAntiAliased,
                            _bFullCharacterSet, makeContours, simplifyAmt, dpi);
    bool successful = large && medium && small;
    if( successful ) fontName = filename;
    return successful;
}

void ofxUICanvas::setFontSize(ofxWidgetFontType _kind, int _size,
                              int _resolution)
{
    switch(_kind)
    {
        case OFX_UI_FONT_LARGE:
            if(font_large != NULL)
            {
                delete font_large;          
            }
            font_large = new ofTrueTypeFont(); 
            font_large->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				            
            break; 

        case OFX_UI_FONT_MEDIUM:
            if(font_medium != NULL)
            {
                delete font_medium;          
            }
            font_medium = new ofTrueTypeFont(); 
            font_medium->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				                            
            break; 

        case OFX_UI_FONT_SMALL:
            if(font_small != NULL)
            {
                delete font_small;          
            }
            font_small = new ofTrueTypeFont(); 
            font_small->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				                            
            break; 
    }
}

void ofxUICanvas::setWidgetSpacing(float _widgetSpacing)
{
    widgetSpacing = _widgetSpacing; 
}

float ofxUICanvas::getWidgetSpacing()
{
    return widgetSpacing;
}

bool ofxUICanvas::isEnabled()
{
    return enabled; 
}

void ofxUICanvas::setVisible(bool _visible)
{
    visible = _visible; 
    if(visible)
    {
        enable();
    }
    else
    {
        disable();
    }
}


void ofxUICanvas::toggleVisible()
{
    if(isEnabled())
    {
        disable(); 
    }
    else {
        enable(); 
    }
}

bool ofxUICanvas::hasKeyboardFocus()
{
    return hasKeyBoard; 
}

void ofxUICanvas::enable()
{
    enabled = true; 
    enableAppEventCallbacks();        
#ifdef TARGET_OPENGLES
    enableTouchEventCallbacks();
#else
    enableMouseEventCallbacks();
    enableKeyEventCallbacks();
    enableWindowEventCallbacks(); 
#endif                		
}

void ofxUICanvas::disable()
{
    enabled = false; 
    disableAppEventCallbacks();        
#ifdef TARGET_OPENGLES
    disableTouchEventCallbacks();
#else
    disableMouseEventCallbacks();
    disableKeyEventCallbacks();
    disableWindowEventCallbacks(); 
#endif                		
}

//App Callbacks
void ofxUICanvas::enableAppEventCallbacks()
{
    ofAddListener(ofEvents.update, this, &ofxUICanvas::onUpdate);
    ofAddListener(ofEvents.draw, this, &ofxUICanvas::onDraw);
    ofAddListener(ofEvents.exit, this, &ofxUICanvas::onExit);
}

//App Callbacks
void ofxUICanvas::disableAppEventCallbacks()
{
    ofRemoveListener(ofEvents.update, this, &ofxUICanvas::onUpdate);
    ofRemoveListener(ofEvents.draw, this, &ofxUICanvas::onDraw);
    ofRemoveListener(ofEvents.exit, this, &ofxUICanvas::onExit);
}

#ifdef TARGET_OPENGLES

//Touch Callbacks
void ofxUICanvas::enableTouchEventCallbacks()
{
    ofAddListener(ofEvents.touchUp, this, &ofxUICanvas::onTouchUp);
    ofAddListener(ofEvents.touchDown, this, &ofxUICanvas::onTouchDown);
    ofAddListener(ofEvents.touchMoved, this, &ofxUICanvas::onTouchMoved);
    ofAddListener(ofEvents.touchCancelled, this, &ofxUICanvas::onTouchCancelled);
    ofAddListener(ofEvents.touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
}	

void ofxUICanvas::disableTouchEventCallbacks()
{
    ofRemoveListener(ofEvents.touchUp, this, &ofxUICanvas::onTouchUp);
    ofRemoveListener(ofEvents.touchDown, this, &ofxUICanvas::onTouchDown);
    ofRemoveListener(ofEvents.touchMoved, this, &ofxUICanvas::onTouchMoved);
    ofRemoveListener(ofEvents.touchCancelled, this, &ofxUICanvas::onTouchCancelled);
    ofRemoveListener(ofEvents.touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
}	

#else // TARGET_OPENGLES

//Mouse Callbacks
void ofxUICanvas::enableMouseEventCallbacks()
{
    ofAddListener(ofEvents.mouseReleased, this, &ofxUICanvas::onMouseReleased);
    ofAddListener(ofEvents.mousePressed, this, &ofxUICanvas::onMousePressed);
    ofAddListener(ofEvents.mouseMoved, this, &ofxUICanvas::onMouseMoved);
    ofAddListener(ofEvents.mouseDragged, this, &ofxUICanvas::onMouseDragged);
}

//Mouse Callbacks
void ofxUICanvas::disableMouseEventCallbacks()
{
    ofRemoveListener(ofEvents.mouseReleased, this, &ofxUICanvas::onMouseReleased);
    ofRemoveListener(ofEvents.mousePressed, this, &ofxUICanvas::onMousePressed);
    ofRemoveListener(ofEvents.mouseMoved, this, &ofxUICanvas::onMouseMoved);
    ofRemoveListener(ofEvents.mouseDragged, this, &ofxUICanvas::onMouseDragged);
}

//KeyBoard Callbacks
void ofxUICanvas::enableKeyEventCallbacks()
{
    ofAddListener(ofEvents.keyPressed, this, &ofxUICanvas::onKeyPressed);
    ofAddListener(ofEvents.keyReleased, this, &ofxUICanvas::onKeyReleased);
}

//KeyBoard Callbacks
void ofxUICanvas::disableKeyEventCallbacks()
{
    ofRemoveListener(ofEvents.keyPressed, this, &ofxUICanvas::onKeyPressed);
    ofRemoveListener(ofEvents.keyReleased, this, &ofxUICanvas::onKeyReleased);
}


//Window Resize Callback
void ofxUICanvas::enableWindowEventCallbacks()
{
    ofAddListener(ofEvents.windowResized, this, &ofxUICanvas::onWindowResized);        
}

//Window Resize Callback
void ofxUICanvas::disableWindowEventCallbacks()
{
    ofRemoveListener(ofEvents.windowResized, this, &ofxUICanvas::onWindowResized);        
}

#endif	// TARGET_OPENGLES


void ofxUICanvas::onUpdate(ofEventArgs& /*data*/)
{
    update();
}

void ofxUICanvas::onDraw(ofEventArgs& /*data*/)
{
    draw();
}

void ofxUICanvas::onExit(ofEventArgs& /*data*/)
{
    exit();
}

void ofxUICanvas::update()
{		
    for(int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->update(); 	
    }		
}
 
void ofxUICanvas::draw()
{
    ofPushStyle(); 
    glDisable(GL_DEPTH_TEST);       
    glDisable(GL_LIGHTING);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
    ofSetRectMode(OF_RECTMODE_CORNER);         
    ofSetLineWidth(1.0);         
    
    drawPadded();
    
    drawPaddedOutline(); 
    
    drawBack(); 
    
    drawFill(); 
    
    drawFillHighlight(); 
    
    drawOutline(); 
    
    drawOutlineHighlight();

    for(int i = widgets.size()-1; i >= 0; i--)
    {
        if(widgets[i]->isVisible())
        {
            widgets[i]->draw(); 	
        }
    }
    
    glDisable(GL_DEPTH_TEST); 
    ofPopStyle();         
}

void ofxUICanvas::exit()
{
}	
    
#ifdef TARGET_OPENGLES

void ofxUICanvas::onTouchDown(ofTouchEventArgs &data)
{
    touchDown(data); 
}

void ofxUICanvas::onTouchMoved(ofTouchEventArgs &data) 
{
    touchMoved(data); 
}

void ofxUICanvas::onTouchUp(ofTouchEventArgs &data) 
{
    touchUp(data); 
}

void ofxUICanvas::onTouchDoubleTap(ofTouchEventArgs &data)
{
    touchDoubleTap(data); 
}

void ofxUICanvas::onTouchCancelled(ofTouchEventArgs &data)
{
    touchCancelled(data); 
}

void ofxUICanvas::touchDown(ofTouchEventArgs& touch) 
{		
    if(rect->inside(touch.x, touch.y))
    {
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchDown(touch); 
        }
    }
}

void ofxUICanvas::touchMoved(ofTouchEventArgs& touch) 
{
    for(int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i]->isVisible())	widgets[i]->touchMoved(touch);
    }
}

void ofxUICanvas::touchUp(ofTouchEventArgs& touch) 
{
    for(int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i]->isVisible())	widgets[i]->touchUp(touch); 
    }
}

void ofxUICanvas::touchDoubleTap(ofTouchEventArgs& touch) 
{
    if(rect->inside(touch.x, touch.y))
    {
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchDoubleTap(touch); 
        }
    }		
}

void ofxUICanvas::touchCancelled(ofTouchEventArgs& touch) 
{		
    if(rect->inside(touch.x, touch.y))
    {
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchCancelled(touch); 
        }
    }	
}

#else	

void ofxUICanvas::onMouseReleased(ofMouseEventArgs& data) 
{ 
    mouseReleased(data.x, data.y, data.button); 
}

void ofxUICanvas::onMousePressed(ofMouseEventArgs& data) 
{ 
    mousePressed(data.x, data.y, data.button); 
}

void ofxUICanvas::onMouseMoved(ofMouseEventArgs& data) 
{ 
    mouseMoved(data.x, data.y); 
}

void ofxUICanvas::onMouseDragged(ofMouseEventArgs& data) 
{ 
    mouseDragged(data.x, data.y, data.button); 
}

void ofxUICanvas::mouseMoved(int x, int y ) 
{
    if(rect->inside(x, y))
    {
        for(int i = 0; i < widgets.size(); i++)
        {                
            if(widgets[i]->isVisible()) widgets[i]->mouseMoved(x, y); 
        }
    }	
}

void ofxUICanvas::mouseDragged(int x, int y, int button) 
{		
    for(int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i]->isVisible())	widgets[i]->mouseDragged(x, y, button); 
    }                
}

void ofxUICanvas::mousePressed(int x, int y, int button) 
{
    if(rect->inside(x, y))
    {
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible()) widgets[i]->mousePressed(x, y, button); 
        }
    }		
}

void ofxUICanvas::mouseReleased(int x, int y, int button) 
{		        
    for(int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i]->isVisible()) widgets[i]->mouseReleased(x, y, button); 
    }    
}	

void ofxUICanvas::onKeyPressed(ofKeyEventArgs& data)
{
    keyPressed(data.key); 
}

void ofxUICanvas::onKeyReleased(ofKeyEventArgs& data)
{
    keyReleased(data.key); 
}	

void ofxUICanvas::keyPressed(int key) 
{
    for(int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->keyPressed(key); 
    }		
}

void ofxUICanvas::keyReleased(int key) 
{
    for(int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->keyReleased(key); 
    }	
}

void ofxUICanvas::onWindowResized(ofResizeEventArgs& data) 
{ 
    windowResized(data.width, data.height); 
} 	

void ofxUICanvas::windowResized(int w, int h) 
{
    for(int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->windowResized(w, h); 
    }
}

#endif	

bool ofxUICanvas::isHit(float x, float y)
{
    if(isEnabled())
    {
        return rect->inside(x, y);
    }
    else
    {
        return false; 
    }
}

ofxUIWidget* ofxUICanvas::getWidgetHit(float x, float y)
{
    if(isEnabled() && rect->inside(x, y))
    {
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isHit(x, y))
            {
                return widgets[i]; 
            }
        }
        return NULL;
    }
    else
    {
        return NULL; 
    }        
}


void ofxUICanvas::stateChange()
{        
    switch (state) 
    {
        case OFX_UI_STATE_NORMAL:
        {            
            draw_fill_highlight = false;             
            draw_outline_highlight = false;             
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;        
            if(enable_highlight_outline)
            {
                draw_outline_highlight = true;                         
            }
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            if(enable_highlight_fill)
            {
                draw_fill_highlight = true;     				
            }
            draw_outline_highlight = false;             
        }
            break;
        case OFX_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;            
            draw_outline_highlight = false;                         
        }
            break;            
            
        default:
            break;
    }        
}

void ofxUICanvas::autoSizeToFitWidgets()
{        
    float maxWidth = 0;
    float maxHeight = 0;

    for(int i = 0; i < widgets.size(); i++)
    {
        ofxUIRectangle* wr = widgets[i]->getRect(); 
        float widgetwidth = wr->x+wr->getWidth();

        float widgetheight = wr->y+wr->getHeight();
        
        if(widgetwidth > maxWidth)
        {
            maxWidth = wr->x+widgets[i]->getPaddingRect()->getWidth();
        }                        
        if(widgetheight > maxHeight)
        {
            maxHeight = wr->y+widgets[i]->getPaddingRect()->getHeight();                                                                        
        }                                    
    }
    
    rect->width = maxWidth;            
    rect->height = maxHeight;          
    paddedRect->width = rect->width+padding*2.0;
    paddedRect->height = rect->height+padding*2.0;        
}

void ofxUICanvas::addWidget(ofxUIWidget *widget)
{
    if(widget->getKind() == OFX_UI_WIDGET_LABEL)
    {
        ofxUILabel *label = (ofxUILabel *) widget;
        setLabelFont(label); 
    }
    else if(widget->getKind() == OFX_UI_WIDGET_SLIDER_H || widget->getKind() == OFX_UI_WIDGET_SLIDER_V || widget->getKind() == OFX_UI_WIDGET_BILABELSLIDER || widget->getKind() == OFX_UI_WIDGET_MINIMALSLIDER)
    {
        ofxUISlider *slider = (ofxUISlider *) widget;
        ofxUILabel *label = (ofxUILabel *) slider->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 				

        if(widget->getKind() == OFX_UI_WIDGET_BILABELSLIDER)
        {
            ofxUIBiLabelSlider *biSlider = (ofxUIBiLabelSlider *) widget;
            ofxUILabel *rlabel = (ofxUILabel *) biSlider->getRightLabel();
            setLabelFont(rlabel); 			
            pushbackWidget(rlabel); 				                
        }
        
        widgetsWithState.push_back(widget);                         
    }
    else if(widget->getKind() == OFX_UI_WIDGET_2DPAD)		
    {
        ofxUI2DPad *pad = (ofxUI2DPad *) widget;
        ofxUILabel *label = (ofxUILabel *) pad->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 				

        widgetsWithState.push_back(widget);             
    }		
    else if(widget->getKind() == OFX_UI_WIDGET_IMAGE)		
    {
        ofxUIImage *image = (ofxUIImage *) widget;
        ofxUILabel *label = (ofxUILabel *) image->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 				
    }				
    else if(widget->getKind() == OFX_UI_WIDGET_RSLIDER_H || widget->getKind() == OFX_UI_WIDGET_RSLIDER_V)
    {
        ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) widget;
        ofxUILabel *label = (ofxUILabel *) rslider->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 			
        
        widgetsWithState.push_back(widget);                         
    }		
    else if(widget->getKind() == OFX_UI_WIDGET_ROTARYSLIDER)
    {
        ofxUIRotarySlider *rslider = (ofxUIRotarySlider *) widget;
        ofxUILabel *label = (ofxUILabel *) rslider->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 				
        
        widgetsWithState.push_back(widget);                         
    }		
    else if(widget->getKind() == OFX_UI_WIDGET_BUTTON || widget->getKind() ==  OFX_UI_WIDGET_LABELBUTTON || widget->getKind() == OFX_UI_WIDGET_LABELTOGGLE)
    {
        ofxUIButton *button = (ofxUIButton *) widget;
        ofxUILabel *label = (ofxUILabel *) button->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 		
        if(widget->getKind() != OFX_UI_WIDGET_BUTTON && widget->getKind() != OFX_UI_WIDGET_LABELBUTTON)
        {
            widgetsWithState.push_back(widget);                         
        }
    }
    else if(widget->getKind() == OFX_UI_WIDGET_DROPDOWNLIST)            
    { 
        ofxUIDropDownList *list = (ofxUIDropDownList *) widget;
        ofxUILabel *label = (ofxUILabel *) list->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 		
        
        vector<ofxUILabelToggle *> toggles = list->getToggles(); 
        for(int i = 0; i < toggles.size(); i++)
        {
            ofxUILabelToggle *t = toggles[i]; 
            ofxUILabel *l2 = (ofxUILabel *) t->getLabel();
            setLabelFont(l2); 	
            pushbackWidget(l2); 					
            pushbackWidget(t); 

            widgetsWithState.push_back(t);             
        }            
    }
    else if(widget->getKind() == OFX_UI_WIDGET_TEXTINPUT)
    {
        ofxUITextInput *textinput = (ofxUITextInput *) widget;
        ofxUILabel *label = (ofxUILabel *) textinput->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 	
        
        widgetsWithState.push_back(widget);             
    }		
    else if(widget->getKind() == OFX_UI_WIDGET_NUMBERDIALER)
    {
        ofxUINumberDialer *numberDialer = (ofxUINumberDialer *) widget;
        ofxUILabel *label = (ofxUILabel *) numberDialer->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 			
        
        widgetsWithState.push_back(widget);                         
    }		        
    else if(widget->getKind() == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) widget;
        ofxUILabel *label = (ofxUILabel *) toggle->getLabel();
        setLabelFont(label); 			
        pushbackWidget(label); 			
        
        widgetsWithState.push_back(widget);                         
    }
    else if(widget->getKind() == OFX_UI_WIDGET_RADIO)
    {
        ofxUIRadio *radio = (ofxUIRadio *) widget;
        ofxUILabel *label = (ofxUILabel *) radio->getLabel();			
        setLabelFont(label); 
        pushbackWidget(label); 				
        
        vector<ofxUIToggle *> toggles = radio->getToggles(); 
        
        for(int i = 0; i < toggles.size(); i++)
        {
            ofxUIToggle *t = toggles[i]; 
            ofxUILabel *l2 = (ofxUILabel *) t->getLabel();
            setLabelFont(l2); 	
            pushbackWidget(t); 
            pushbackWidget(l2);
            
            widgetsWithState.push_back(t);                             
        }
    }
    else if(widget->getKind() == OFX_UI_WIDGET_TOGGLEMATRIX)
    {
        ofxUIToggleMatrix *matrix = (ofxUIToggleMatrix *) widget;
        ofxUILabel *label = (ofxUILabel *) matrix->getLabel();			
        setLabelFont(label); 
        pushbackWidget(label); 				
        
        vector<ofxUIToggle *> toggles = matrix->getToggles(); 
        
        for(int i = 0; i < toggles.size(); i++)
        {
            ofxUIToggle *t = toggles[i]; 
            ofxUILabel *l2 = (ofxUILabel *) t->getLabel();
            setLabelFont(l2); 	
            pushbackWidget(t); 
            pushbackWidget(l2); 			
            
            widgetsWithState.push_back(t);                             
        }
    }
    else if(widget->getKind() == OFX_UI_WIDGET_FPS)
    {
        ofxUILabel *fps = (ofxUILabel *) widget;
        setLabelFont(fps); 
    }
    else if(widget->getKind() == OFX_UI_WIDGET_IMAGETOGGLE)
    {
        widgetsWithState.push_back(widget);              
    }

    widget->setParent(this); 
    widget->setRectParent(this->rect); 		
    pushbackWidget(widget); 	
}

ofxUIWidget* ofxUICanvas::addWidgetDown(ofxUIWidget *widget,
                                        ofxWidgetAlignment align)
{
    addWidget(widget); 
    ofxUIRectangle *widgetRect = widget->getRect();         
    if(lastAdded != NULL)
    {
        ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect(); 
        widgetRect->y = lastPaddedRect->getY()+lastPaddedRect->getHeight()-rect->getY()+widgetSpacing; 
    }
    else 
    {
        widgetRect->y = widgetSpacing; 
    }
    switch(align)
    {
        case OFX_UI_ALIGN_LEFT: 
            widgetRect->x = widgetSpacing;             
            break;                    
        case OFX_UI_ALIGN_FREE: 
            
            break; 
        case OFX_UI_ALIGN_RIGHT: 
            widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing; 
            break;                     
    }                           
    lastAdded = widget; 
    return widget;
}

ofxUIWidget* ofxUICanvas::addWidgetUp(ofxUIWidget *widget,
                                      ofxWidgetAlignment align)
{
    addWidget(widget); 
    ofxUIRectangle *widgetRect = widget->getRect();                 
    if(lastAdded != NULL)
    {
        ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect(); 
        ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();                                     
        widgetRect->y = lastPaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();                                     
    }
    else 
    {
        widgetRect->y = widgetSpacing;             
    }
    switch(align)
    {
        case OFX_UI_ALIGN_LEFT: 
            widgetRect->x = widgetSpacing;             
            break;                    
        case OFX_UI_ALIGN_FREE: 
            
            break; 
        case OFX_UI_ALIGN_RIGHT: 
            widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing; 
            break;                     
    }          
    lastAdded = widget; 
    return widget;
}    

ofxUIWidget* ofxUICanvas::addWidgetRight(ofxUIWidget *widget)
{
    addWidget(widget); 	
    if(lastAdded != NULL)
    {
        ofxUIRectangle *lastRect = lastAdded->getRect(); 
        ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();                         
        ofxUIRectangle *widgetRect = widget->getRect(); 
        
        widgetRect->x = lastPaddedRect->getX()+lastPaddedRect->getWidth()-rect->getX()+widgetSpacing; 
        widgetRect->y = lastRect->getY()-rect->getY(); 
    }
    else 
    {
        ofxUIRectangle *widgetRect = widget->getRect(); 
        widgetRect->x = widgetSpacing; 
        widgetRect->y = widgetSpacing;                         
    }
    lastAdded = widget; 
    return widget; 	
}

ofxUIWidget* ofxUICanvas::addWidgetLeft(ofxUIWidget *widget)
{
    addWidget(widget); 	        
    if(lastAdded != NULL)
    {
        ofxUIRectangle *lastRect = lastAdded->getRect(); 
        ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();                         
        ofxUIRectangle *widgetRect = widget->getRect(); 
        ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();                         
        
        widgetRect->x = lastPaddedRect->getX()-widgetPaddedRect->getWidth()-rect->getX(); 
        widgetRect->y = lastRect->getY()-rect->getY(); 
    }
    else 
    {
        ofxUIRectangle *widgetRect = widget->getRect(); 
        widgetRect->x = widgetSpacing; 
        widgetRect->y = widgetSpacing;                         
    }
    lastAdded = widget;  	
    return widget;
}    

ofxUIWidget* ofxUICanvas::addWidgetSouthOf(ofxUIWidget *widget,
                                           string referenceName)
{
    addWidget(widget); 	
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
        ofxUIRectangle *referenceRect = referenceWidget->getRect();             
        ofxUIRectangle *widgetRect = widget->getRect(); 
        
        widgetRect->y = referencePaddedRect->getY()+referencePaddedRect->getHeight()-rect->getY()+widgetSpacing; 
        widgetRect->x = referenceRect->getX()-rect->getX();   
    }
    else 
    {
        ofxUIRectangle *widgetRect = widget->getRect(); 
        widgetRect->y = widgetSpacing; 
    }
    lastAdded = widget;  		
    return widget;
}    

ofxUIWidget* ofxUICanvas::addWidgetNorthOf(ofxUIWidget *widget,
                                           string referenceName)
{
    addWidget(widget); 	
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
        ofxUIRectangle *referenceRect = referenceWidget->getRect();             
        ofxUIRectangle *widgetRect = widget->getRect(); 
        ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();             
        
        widgetRect->y = referencePaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();             
        widgetRect->x = referenceRect->getX()-rect->getX();   
    }
    else 
    {
        ofxUIRectangle *widgetRect = widget->getRect(); 
        widgetRect->y = widgetSpacing; 
    }
    lastAdded = widget;  	        
    return widget;
}      

ofxUIWidget* ofxUICanvas::addWidgetWestOf(ofxUIWidget *widget,
                                          string referenceName)
{
    addWidget(widget); 	        
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
        ofxUIRectangle *referenceRect = referenceWidget->getRect();             			
        ofxUIRectangle *widgetRect = widget->getRect(); 
        ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();             
        
        widgetRect->y = referenceRect->getY()-rect->getY();                         
        widgetRect->x = referencePaddedRect->getX()-rect->getX()-widgetPaddedRect->getWidth();   
    }
    else 
    {			
        ofxUIRectangle *currentRect = widget->getRect(); 			
        currentRect->y = widgetSpacing; 
    }
    lastAdded = widget;  	
    return widget;
}        

ofxUIWidget* ofxUICanvas::addWidgetEastOf(ofxUIWidget *widget,
                                          string referenceName)
{
    addWidget(widget); 	        
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
        ofxUIRectangle *referenceRect = referenceWidget->getRect();             			
        ofxUIRectangle *widgetRect = widget->getRect(); 	            
        widgetRect->y = referenceRect->getY()-rect->getY();                         
        widgetRect->x = referencePaddedRect->getX()-rect->getX()+referencePaddedRect->getWidth()+widgetSpacing;   
    }
    else 
    {			
        ofxUIRectangle *currentRect = widget->getRect(); 			
        currentRect->y = widgetSpacing; 
    }
    lastAdded = widget;  	
    return widget;
}         


void ofxUICanvas::setLabelFont(ofxUILabel *label)
{
    switch(label->getSize())
    {
        case OFX_UI_FONT_LARGE:
            label->setFont(font_large); 					
            break; 
        case OFX_UI_FONT_MEDIUM:
            label->setFont(font_medium); 					
            break; 
        case OFX_UI_FONT_SMALL:
            label->setFont(font_small); 					
            break; 					
    }		
}

void ofxUICanvas::triggerEvent(ofxUIWidget *child)
{        
    checkForKeyFocus(child); 
    GUIevent->widget = child; 		
    ofNotifyEvent(newGUIEvent,*GUIevent,this);		
}
    
void ofxUICanvas::setWidgetColor(int _target, ofColor _color)
{
    switch (_target) 
    {
        case OFX_UI_WIDGET_COLOR_BACK:
            for(int i = 0; i < widgets.size(); i++)
            {
                widgets[i]->setColorBack(_color); 
            }				
            break;

        case OFX_UI_WIDGET_COLOR_OUTLINE:
            for(int i = 0; i < widgets.size(); i++)
            {
                widgets[i]->setColorOutline(_color); 
            }				
            break;
        
        case OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT:
            for(int i = 0; i < widgets.size(); i++)
            {
                widgets[i]->setColorOutlineHighlight(_color); 
            }				
            break;
        
        case OFX_UI_WIDGET_COLOR_FILL:
            for(int i = 0; i < widgets.size(); i++)
            {
                widgets[i]->setColorFill(_color); 
            }				
            break;
        
        case OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT:
            for(int i = 0; i < widgets.size(); i++)
            {
                widgets[i]->setColorFillHighlight(_color); 
            }					
            break;
            
        case OFX_UI_WIDGET_COLOR_PADDED:
            for(int i = 0; i < widgets.size(); i++)
            {
                widgets[i]->setColorPadded(_color); 
            }					
            break;
            
        case OFX_UI_WIDGET_COLOR_PADDED_OUTLINE:
            for(int i = 0; i < widgets.size(); i++)
            {
                widgets[i]->setColorPaddedOutline(_color); 
            }					
            break;                
            
        default:
            break;
    }
}

ofxUIWidget* ofxUICanvas::getWidget(string _name)
{
    return widgets_map[_name]; 
}

void ofxUICanvas::removeWidget(string _name)    
{
    //To Implement
}

void ofxUICanvas::removeWidget(ofxUIWidget *widget)
{
    //To Implement
}

void ofxUICanvas::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect; 
}

void ofxUICanvas::setDrawWidgetPadding(bool _draw_padded_rect)
{
    for(int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->setDrawPadding(_draw_padded_rect); 
    }		        
}

void ofxUICanvas::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline; 
}

void ofxUICanvas::setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline)
{
    for(int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->setDrawPaddingOutline(_draw_padded_rect_outline); 
    }		
}


vector<ofxUIWidget*> ofxUICanvas::getWidgets()
{
    return widgets;
}

vector<ofxUIWidget*> ofxUICanvas::getWidgetsOfType(ofxWidgetType type)
{
    vector<ofxUIWidget*> widgetToReturn; 
    for(int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i]->getKind() == type)
        {
            widgetToReturn.push_back(widgets[i]);
        }
    }	 
    return widgetToReturn;                                         
}

void ofxUICanvas::pushbackWidget(ofxUIWidget *widget)
{
    widget->setID(uniqueIDs); 
    uniqueIDs++;
    widgets.push_back(widget);    
    widgets_map[widget->getName()] = widget;                             
}

//Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)    
bool ofxUICanvas::updateFont(ofxWidgetFontType _kind,
                             string filename,
                             int fontsize,
                             bool _bAntiAliased,
                             bool _bFullCharacterSet,
                             bool makeContours,
                             float simplifyAmt,
                             int dpi)
{
    bool success = false;
    switch(_kind)
    {
        case OFX_UI_FONT_LARGE:
            if(font_large != NULL)
            {
                delete font_large;
            }
            font_large = new ofTrueTypeFont();
            success = font_large->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
            break;
            
        case OFX_UI_FONT_MEDIUM:
            if(font_medium != NULL)
            {
                delete font_medium;
            }
            font_medium = new ofTrueTypeFont();
            success = font_medium->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
            break;
            
        case OFX_UI_FONT_SMALL:
            if(font_small != NULL)
            {
                delete font_small;
            }
            font_small = new ofTrueTypeFont();
            success = font_small->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
            break;
    }
    return success;
}

void ofxUICanvas::checkForKeyFocus(ofxUIWidget *child)
{
    if(child->getKind() == OFX_UI_WIDGET_TEXTINPUT)
    {
        ofxUITextInput *textinput = (ofxUITextInput *) child;         
        switch(textinput->getTriggerType())
        {
            case OFX_UI_TEXTINPUT_ON_FOCUS:
            {
                hasKeyBoard = true; 
            }
                break; 
                
            case OFX_UI_TEXTINPUT_ON_ENTER:
            {
                hasKeyBoard = true; 
            }        
                break; 
                
            case OFX_UI_TEXTINPUT_ON_UNFOCUS:
            {
                hasKeyBoard = false; 
            }        
                break; 
                
            default:
            {
                hasKeyBoard = false; 
            }
                break;                     
        }
    }        
}

