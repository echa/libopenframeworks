// Example from http://pointclouds.org/documentation/tutorials/greedy_projection.php

#include <iostream>
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	grabber.open();
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(0);
	
	cam.begin();
	ofScale(100, -100, -100);
	ofTranslate(0, 0, -1);
	glEnable(GL_DEPTH_TEST);
	
	grabber.getMesh(curMesh);
	curMesh.drawVertices();
	
	cam.end();
}

//--------------------------------------------------------------
void testApp::exit()
{
	grabber.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
	
}
