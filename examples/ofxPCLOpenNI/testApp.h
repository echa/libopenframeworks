#pragma once

// always include PCL first!
#include "ofxPCL.h"
//#include "ofxPCLTypes2.h"
//#include "ofxPCLUtility2.h"
#include "ofMain.h"

class testApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofEasyCam cam;
	ofVboMesh curMesh;
	ofxPCL::grabber grabber;
};
