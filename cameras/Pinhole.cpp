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

		double aspectRatio = double(height) / double(width);
		double rfov = double(fov) * 3.14159265 / 180.0;
		double screenWidth = 2 * tan(rfov / 2);
		double screenHeight = aspectRatio * screenWidth;

		Vec3f z = (position - lookat).normalize();
		Vec3f x = (z.crossProduct(up)).normalize();
		Vec3f y = x.crossProduct(z);

		xDir = screenWidth * x;
		yDir = screenHeight * y;
		lower_left_corner = position - xDir * 0.5 - yDir * 0.5 - z;
	}

	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera()
	{
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
	}

	Ray Pinhole::getRay(int hIndex, int wIndex)
	{

		Ray r;

		double xp = (double(wIndex) + 0.5) / double(width);
		double yp = (double(hIndex) + 0.5) / double(width);

		r.raytype = PRIMARY;
		r.orig = position;
		r.dir = (lower_left_corner + xDir * xp + yDir * yp) - position;

		return r;
	}

} // namespace rt
