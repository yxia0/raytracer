/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"

namespace rt
{

	//
	// Pinhole constructor (example)
	//

	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up) : Camera(width, height, fov, position, lookat, up)
	{
		initialize();
	};

	void Pinhole::initialize()
	{
		double aspectRatio = double(width) / double(height);
		double fovRadian = double(fov) * 3.14159265 / 180.0;

		// Experiment with basic setting
		// increase initial 2 -> zoom out effect
		// decrease focal length 1 -> zoom out effect
		double viewport_height = 2 * tan(fovRadian / 2);
		double viewport_width = aspectRatio * viewport_height;
		double focal_len = 1;

		// old camera default position
		xDir = Vec3f(viewport_width, 0, 0);
		yDir = Vec3f(0, viewport_height, 0);
		top_left_corner = position - xDir * 0.5 + yDir * 0.5 - Vec3f(0, 0, focal_len);
		// TODO: positionable camera
		// transformed coordinate
		// double fovRadian = double(fov) * 3.14159265 / 180.0;
		// double screenWidth = 2 * tan(rfov / 2);
		// double screenHeight = aspectRatio * screenWidth;

		// Vec3f zDir = (position - lookat).normalize();
		// // std::cout << "z direction is: " << zDir << std::endl;
		// xDir = (up.crossProduct(zDir)).normalize();
		// // std::cout << "x direction is: " << xDir << std::endl;
		// yDir = zDir.crossProduct(xDir);
		// // std::cout << "y direction is: " << yDir << std::endl;

		// top_left_corner = position - xDir * viewport_width * 0.5 + yDir * viewport_height * 0.5 - zDir;

		// Vec3f(0, 0, focal_len);

		// xDir = screenWidth * x;
		// yDir = screenHeight * y;
		// lower_left_corner = position - xDir * 0.5 - yDir * 0.5 - z;
	}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera()
	{
		printf("Pinhole camera specs: \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
		std::cerr << "position: " << position << std::endl;
		std::cerr << "lookat:" << lookat << std::endl;
		std::cerr << "up:" << up << std::endl;
	}

	Ray Pinhole::shoot(int hIndex, int wIndex)
	{

		Ray r;

		double xp = (double(wIndex) + 0.5) / double(width);
		double yp = (double(hIndex) + 0.5) / double(width);

		r.raytype = PRIMARY;
		r.orig = position;
		r.pix_center = top_left_corner + xDir * xp - yDir * yp; // camera position
		r.dir = (r.pix_center - position).normalize();			// unit vector

		return r;
	}

} // namespace rt
