#pragma once
//#undef Success

// file io
#include <pcl/io/pcd_io.h>

// transform
#include <pcl/common/transforms.h>

// thresold
#include <pcl/filters/passthrough.h>

// outlier removal
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/radius_outlier_removal.h>

// segmentation
#include <pcl/sample_consensus/model_types.h>

// downsample
#include <pcl/filters/voxel_grid.h>

// segmentation
#include <pcl/ModelCoefficients.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/filters/extract_indices.h>

// triangulate
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/surface/grid_projection.h>
#include <pcl/Vertices.h>

// mls
#include <pcl/surface/mls.h>
#include <pcl/io/pcd_io.h>

#include <pcl/search/pcl_search.h>

// grabber

#include <pcl/io/grabber.h>
#include <pcl/io/openni_grabber.h>

// inlcude OF headers last
#include "ofUtils.h"
#include "ofMatrix4x4.h"
#include "ofVec3f.h"
#include "ofMesh.h"
#include "ofxPCLTypes.h"
#include "ofxPCLUtility.h"
#include "ofxPCLGrabber.h"
#include "ofxPCLTree.h"



namespace ofxPCL
{

//
// file io
//
template <typename T>
inline void loadPointCloud(string path, T cloud)
{
	path = ofToDataPath(path);

	if (pcl::io::loadPCDFile<typename T::element_type::PointType>(path.c_str(), *cloud) == -1)
		ofLogError("Couldn't read file: " + path);
}

template <typename T>
inline void savePointCloud(string path, T cloud)
{
	if (cloud->points.empty()) return;

	path = ofToDataPath(path);
	pcl::io::savePCDFileBinary(path.c_str(), *cloud);
}

//
// transform
//
template <typename T>
void transform(T cloud, ofMatrix4x4 matrix)
{
	if (cloud->points.empty()) return;

	Eigen::Matrix4f mat;
	memcpy(&mat, matrix.getPtr(), sizeof(float) * 16);
	pcl::transformPointCloud(*cloud, *cloud, mat);
}

//
// threshold
//
template <typename T>
inline void threshold(T cloud, const char *dimension, float min, float max)
{
	if (cloud->points.empty()) return;

	pcl::PassThrough<typename T::element_type::PointType> pass;
	pass.setInputCloud(cloud);
	pass.setFilterFieldName(dimension);
	pass.setFilterLimits(min, max);
	pass.filter(*cloud);
}

//
// downsample
//
template <typename T>
inline void downsample(T cloud, ofVec3f resolution = ofVec3f(1, 1, 1))
{
	if (cloud->points.empty()) return;

	pcl::VoxelGrid<typename T::element_type::PointType> sor;
	sor.setInputCloud(cloud);
	sor.setLeafSize(resolution.x, resolution.y, resolution.z);
	sor.filter(*cloud);
}

//
// outlier removal
//
template <typename T>
inline void statisticalOutlierRemoval(T cloud, int nr_k = 50, double std_mul = 1.0)
{
	if (cloud->points.empty()) return;

	pcl::StatisticalOutlierRemoval<typename T::element_type::PointType> sor;
	sor.setInputCloud(cloud);
	sor.setMeanK(nr_k);
	sor.setStddevMulThresh(std_mul);
	sor.filter(*cloud);
}

template <typename T>
inline void radiusOutlierRemoval(T cloud, double radius, int num_min_points)
{
	if (cloud->points.empty()) return;

	pcl::RadiusOutlierRemoval<typename T::element_type::PointType> outrem;
	outrem.setInputCloud(cloud);
	outrem.setRadiusSearch(radius);
	outrem.setMinNeighborsInRadius(num_min_points);
	outrem.filter(*cloud);
}

//
// segmentation
//
template <typename T>
inline vector<T> segmentation(T cloud, const pcl::SacModel model_type = pcl::SACMODEL_PLANE, const float distance_threshold = 1, const int min_points_limit = 10, const int max_segment_count = 30)
{
	vector<T> result;

	if (cloud->points.empty()) return result;

	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices());

	pcl::SACSegmentation<typename T::element_type::PointType> seg;
	seg.setOptimizeCoefficients(false);

	seg.setModelType(model_type);
	seg.setMethodType(pcl::SAC_RANSAC);
	seg.setDistanceThreshold(distance_threshold);
	seg.setMaxIterations(500);

	T temp(new typename T::element_type(*cloud));
	const size_t original_szie = temp->points.size();

	pcl::ExtractIndices<typename T::element_type::PointType> extract;

	int segment_count = 0;
	while (temp->size() > original_szie * 0.3)
	{
		if (segment_count > max_segment_count) break;
		segment_count++;

		seg.setInputCloud(temp);
		seg.segment(*inliers, *coefficients);

		if (inliers->indices.size() < min_points_limit)
			break;

		T filterd_point_cloud(new typename T::element_type);

		extract.setInputCloud(temp);
		extract.setIndices(inliers);
		extract.setNegative(false);
		extract.filter(*filterd_point_cloud);

		if (filterd_point_cloud->points.size() > 0)
		{
			result.push_back(filterd_point_cloud);
		}

		extract.setNegative(true);
		extract.filter(*temp);
	}

	return result;
}

//
// normal estimation
//
template <typename T1, typename T2>
inline void normalEstimation(const T1 &cloud, T2 &output_cloud_with_normals)
{
	if (cloud->points.empty()) return;

	pcl::NormalEstimation<typename T1::element_type::PointType, NormalType> n;
	NormalPointCloud normals(new typename NormalPointCloud::element_type);

	KdTree<typename T1::element_type::PointType> kdtree(cloud);

	n.setInputCloud(cloud);
	n.setSearchMethod(kdtree.kdtree);
	n.setKSearch(20);
//	n.setRadiusSearch (0.1);
	n.compute(*normals);

	output_cloud_with_normals = T2(new typename T2::element_type);
	pcl::concatenateFields(*cloud, *normals, *output_cloud_with_normals);
}

//
// MLS
//
template <typename T1, typename T2>
void movingLeastSquares(const T1 &cloud, T2 &mls_points, float search_radius = 30)
{
	if (cloud->points.empty()) return;

	// Create a KD-Tree
	typename pcl::search::KdTree<typename T1::element_type::PointType>::Ptr tree (new pcl::search::KdTree<typename T1::element_type::PointType>);

	// Init object (second point type is for the normals, even if unused)
	typename pcl::MovingLeastSquares<typename T1::element_type::PointType, typename T2::element_type::PointType> mls;

	mls.setComputeNormals (true);

	// Set parameters
	mls.setInputCloud (cloud);
	mls.setPolynomialFit (true);
	mls.setSearchMethod (tree);
	mls.setSearchRadius (0.03);

	// Reconstruct
	mls.process (*mls_points);
}

//
// triangulate
//
template <typename T>
ofMesh triangulate(const T &cloud_with_normals, float search_radius = 30)
{
	ofMesh mesh;

	if (cloud_with_normals->points.empty()) return mesh;

	typename pcl::search::KdTree<typename T::element_type::PointType>::Ptr tree(new pcl::search::KdTree<typename T::element_type::PointType>);
	tree->setInputCloud(cloud_with_normals);

	typename pcl::GreedyProjectionTriangulation<typename T::element_type::PointType> gp3;
	pcl::PolygonMesh triangles;

	// Set the maximum distance between connected points (maximum edge length)
	gp3.setSearchRadius(search_radius);

	gp3.setMu(2.5);
	gp3.setMaximumNearestNeighbors(100);
	gp3.setMaximumSurfaceAngle(M_PI / 4); // 45 degrees
	gp3.setMinimumAngle(M_PI / 18); // 10 degrees
	gp3.setMaximumAngle(2 * M_PI / 3); // 120 degrees
	gp3.setNormalConsistency(false);

	gp3.setInputCloud(cloud_with_normals);
	gp3.setSearchMethod(tree);
	gp3.reconstruct(triangles);

	convert(cloud_with_normals, mesh);

	for (int i = 0; i < triangles.polygons.size(); i++)
	{
		pcl::Vertices &v = triangles.polygons[i];

		if (v.vertices.size() == 3)
			mesh.addTriangle(v.vertices[0], v.vertices[1], v.vertices[2]);
	}

	return mesh;
}

//
// GridProjection # dosen't work...?
//
template <typename T>
ofMesh gridProjection(const T &cloud_with_normals, float resolution = 1, int padding_size = 3)
{
	ofMesh mesh;

	if (cloud_with_normals->points.empty()) return mesh;

	typename pcl::KdTreeFLANN<typename T::element_type::PointType>::Ptr tree(new pcl::KdTreeFLANN<typename T::element_type::PointType>);
	tree->setInputCloud(cloud_with_normals);

	pcl::GridProjection<typename T::element_type::PointType> gp;
	pcl::PolygonMesh triangles;

	gp.setResolution(resolution);
	gp.setPaddingSize(padding_size);
	gp.setNearestNeighborNum(30);

	// Get result
	gp.setInputCloud(cloud_with_normals);
	gp.setSearchMethod(tree);
	gp.reconstruct(triangles);

	convert(cloud_with_normals, mesh);

	for (int i = 0; i < triangles.polygons.size(); i++)
	{
		pcl::Vertices &v = triangles.polygons[i];

		if (v.vertices.size() == 4)
		{
			mesh.addTriangle(v.vertices[0], v.vertices[1], v.vertices[2]);
			mesh.addTriangle(v.vertices[2], v.vertices[3], v.vertices[0]);
		}
	}

	return mesh;
}

}
