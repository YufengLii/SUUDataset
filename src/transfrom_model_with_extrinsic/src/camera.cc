#include "camera.h"

#include <fstream>

#include "mesh.h"

Camera::Camera()
{}

void Camera::LoadFromFile(const char* filename) {
	std::ifstream is(filename);
	is >> height_ >> width_;
	is >> fx_ >> fy_ >> cx_ >> cy_;
	std::cout << height_ << " "<< width_ << std::endl;
	std::cout << fx_ << " "<< fy_ << " "<< cx_ << " "<< cy_ << std::endl;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			is >> world2cam_(i, j);
		}
	}
	std::cout << world2cam_(0, 0) << " " << world2cam_(0, 1) << " " << world2cam_(0, 2) << " " << world2cam_(0, 3) << std::endl;
	std::cout << world2cam_(1, 0) << " "<< world2cam_(1, 1) << " "<< " "<< world2cam_(1, 2) << " "<< world2cam_(1, 3) << std::endl;
	std::cout << world2cam_(2, 0) << " "<< world2cam_(2, 1) << " "<< world2cam_(2, 2) << " "<< world2cam_(2, 3) << std::endl;
	std::cout << world2cam_(3, 0) << " "<< world2cam_(3, 1) << " "<< world2cam_(3, 2)<< " " << world2cam_(3, 3) << std::endl;

	is >> angle_;
	std::cout << angle_ << std::endl;

}

void Camera::ApplyExtrinsic(Mesh& mesh) {
	auto& vertices = mesh.GetVertices();

	// apply extrinsic transformation
	for (int i = 0; i < vertices.size(); ++i) {
		Eigen::Vector4d v(vertices[i][0], vertices[i][1], vertices[i][2], 1);
		v = world2cam_ * v;
		vertices[i] = Eigen::Vector3d(v[0],v[1],v[2]);
	}
}

// void Camera::ApplyIntrinsic(Mesh& mesh) {
// 	auto& vertices = mesh.GetVertices();

// 	// apply intrinsic projection
// 	for (int i = 0; i < vertices.size(); ++i) {
// 		Eigen::Vector3d v = vertices[i];
// 		if (v[2] != 0) {
// 			vertices[i] = Eigen::Vector3d((v[0]/v[2]*fx_+cx_)/width_ - 0.5,
// 				(v[1]/v[2]*fy_+cy_)/height_-0.5,v[2]);
// 		} else {
// 			vertices[i] = Eigen::Vector3d(0, 0, 0);
// 		}
// 	}
// }