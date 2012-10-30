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

#ifndef OFXUI_MOVING_GRAPH
#define OFXUI_MOVING_GRAPH

#include "ofxUIWidget.h"

class ofxUIMovingGraph : public ofxUIWidget
{
public:    
    ofxUIMovingGraph(float x, float y, float w, float h, vector<float> _buffer,
                     int _bufferSize, float _min, float _max, string _name);
    ofxUIMovingGraph(float w, float h, vector<float> _buffer, int _bufferSize,
                     float _min, float _max, string _name);
    virtual ~ofxUIMovingGraph() {}
    
    void init(float w, float h, vector<float> _buffer, int _bufferSize,
              float _min, float _max, string _name);
    
    virtual void drawFill();		        
	virtual void setParent(ofxUIWidget *_parent);
    void addPoint(float _point);
    vector<float>& getBuffer();
    void setBuffer(vector<float> _buffer);

protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    vector<float> buffer;
	float max, min, scale, inc; 
	int bufferSize; 
}; 

#endif
