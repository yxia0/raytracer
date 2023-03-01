/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"

namespace rt
{

	class Pinhole : public Camera
	{
	public:
		//
		// Constructors
		//
		Pinhole(){};
		Pinhole(int width, int height, int fov);

		//
		// Destructor
		//
		~Pinhole(){};

		//
		// print function (implementing abstract function of base class)
		//
		void printCamera();

		// get ray function
		Ray getRay(int hIndex, int wIndex);

	private:
		Vec3f lower_left_corner;
		Vec3f xDir;
		Vec3f yDir;
	};

} // namespace rt

#endif /* PINHOLE_H_ */
