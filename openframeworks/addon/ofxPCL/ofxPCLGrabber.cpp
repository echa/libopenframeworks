#include "ofxPCL.h"

namespace ofxPCL
{

void grabber::cloud_cb_(const ofxPCL::ColorAPointCloudConst &cloud)
{
	if( cloud ) {
		bufferCloud = cloud->makeShared();
	}
}

int grabber::open()
{
	// create a new grabber for OpenNI devices
	interface = new pcl::OpenNIGrabber();
	
	// make callback function from member function
	f = boost::bind (&grabber::cloud_cb_, this, _1);
	
	// connect callback function for desired signal. In this case its a point cloud with color values
	c = interface->registerCallback (f);
	
	// start receiving point clouds
	interface->start ();
	
	return 0;
}

int grabber::close()
{
	// stop the grabber
	interface->stop ();
	
	return 0;
}
	
void grabber::getMesh(ofMesh& mesh)
{
	ofxPCL::ColorAPointCloud cloud;
	
	if( bufferCloud ) {
		cloud = bufferCloud;
		if( cloud->size() > 0 ) {
			convert(cloud, mesh);
		}
	}
}

//void grabber::getCloud(ColorPointCloud& cloud)
//{
//	if( bufferCloud ) {
//		cloud = bufferCloud;
//	}
//}

void grabber::getCloud(ColorAPointCloud& cloud)
{
	if( bufferCloud ) {
		cloud = bufferCloud;
	}
}

}
