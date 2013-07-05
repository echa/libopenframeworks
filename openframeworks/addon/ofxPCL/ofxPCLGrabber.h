#pragma once

#include <pcl/io/grabber.h>
#include <pcl/io/openni_grabber.h>

#include "ofxPCLTypes.h"
#include "ofxPCLUtility.h"

#include "ofMesh.h"

namespace ofxPCL
{

class grabber
{
	void cloud_cb_(const ofxPCL::ColorAPointCloudConst &cloud);
	
	pcl::Grabber* interface;
	ofxPCL::ColorAPointCloud bufferCloud;
	
	boost::function<void (const ColorAPointCloudConst&)> f;
	boost::signals2::connection c;

public:
	int open();
	int close();
	void getMesh(ofMesh&);
//	void getCloud(ColorPointCloud&);
	void getCloud(ColorAPointCloud&);
};

}
