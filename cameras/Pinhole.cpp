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
	Pinhole::Pinhole(int width, int height, int fov) : Camera(width, height, fov)
	{
		initialize();
	}

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

		xDir = Vec3f(viewport_width, 0, 0);
		yDir = Vec3f(0, viewport_height, 0);
		top_left_corner = position - xDir * 0.5 + yDir * 0.5 - Vec3f(0, 0, focal_len);
		// TODO: positionable camera
		// double fovRadian = double(fov) * 3.14159265 / 180.0;
		// double screenWidth = 2 * tan(rfov / 2);
		// double screenHeight = aspectRatio * screenWidth;

		// Vec3f z = (position - lookat).normalize();
		// Vec3f x = (z.crossProduct(up)).normalize();
		// Vec3f y = x.crossProduct(z);

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
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
		std::cerr << "lower left corner:" << lower_left_corner << std::endl;
	}

	Ray Pinhole::shoot(int hIndex, int wIndex)
	{

		Ray r;

		double xp = (double(wIndex) + 0.5) / double(width);
		double yp = (double(hIndex) + 0.5) / double(width);

		r.raytype = PRIMARY;
		r.orig = position;
		r.pix_center = lower_left_corner + xDir * xp - yDir * yp; // camera position
		r.dir = (r.pix_center - position).normalize();			  // unit vector

		return r;
	}

} // namespace rt
