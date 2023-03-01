/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt
{

	Camera::Camera(int height, int width, int fov) : height(height), width(width), fov(fov)
	{
		position = Vec3f(0.0, 0.0, 0.0);
		lookat = Vec3f(0.0, 0.0, -0.1);
		up = Vec3f(0.0, 1.0, 0.0);
	};

	Camera::~Camera(){};

	/**
	 * Factory function that returns camera subclass based on camera specifications
	 *
	 * @param cameraSpecs camera specifications json object
	 *
	 * @return camera subclass instance
	 *
	 */
	Camera *Camera::createCamera(Value &cameraSpecs)
	{

		// check if cameratype is defined

		if (!cameraSpecs.HasMember("type"))
		{
			std::cerr << "Camera type not specified" << std::endl;
			exit(-1);
		}

		std::string cameraType = cameraSpecs["type"].GetString();

		// return camera object based on camera specs
		// TODO: parse postion, lookat, up
		if (cameraType.compare("pinhole") == 0)
		{
			return new Pinhole(cameraSpecs["width"].GetInt(),
							   cameraSpecs["height"].GetInt(),
							   cameraSpecs["fov"].GetInt());
		}
		else if (cameraType.compare("thinlens") == 0)
		{
			return new ThinLens();
		}

		return 0;
	}

} // namespace rt
