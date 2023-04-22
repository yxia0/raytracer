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

	Camera::Camera(int height, int width, int fov) : height(height), width(width), fov(fov){
																					   // TODO: delete in the end

																				   };

	Camera::Camera(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up) : height(height), width(width), fov(fov), position(position), lookat(lookat), up(up){};

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
		if (cameraType.compare("pinhole") == 0)
		{
			// default camera position
			Vec3f position(0.0, 0.0, 0.0);
			Vec3f lookat(0.0, 0.0, -0.1);
			Vec3f up(0.0, 1.0, 0.0);

			if (cameraSpecs.HasMember("position"))
			{
				// get position
				const Value &p = cameraSpecs.GetObject()["position"];
				float px = p[0].GetFloat();
				float py = p[1].GetFloat();
				float pz = p[2].GetFloat();
				position = Vec3f(px, py, pz);
			}

			if (cameraSpecs.HasMember("lookat"))
			{
				// get lookat
				const Value &l = cameraSpecs.GetObject()["lookat"];
				float lx = l[0].GetFloat();
				float ly = l[1].GetFloat();
				float lz = l[2].GetFloat();
				lookat = Vec3f(lx, ly, lz);
			}

			if (cameraSpecs.HasMember("up"))
			{
				// get up
				const Value &u = cameraSpecs.GetObject()["up"];
				float ux = u[0].GetFloat();
				float uy = u[1].GetFloat();
				float uz = u[2].GetFloat();
				up = Vec3f(ux, uy, uz);
			}

			return new Pinhole(cameraSpecs["width"].GetInt(),
							   cameraSpecs["height"].GetInt(),
							   cameraSpecs["fov"].GetInt(),
							   position,
							   lookat,
							   up);
		}

		else if (cameraType.compare("thinlens") == 0)
		{
			return new ThinLens();
		}
		else
		{
			throw std::invalid_argument("Camera is not defined in the scene!");
		}

		return 0;
	}

} // namespace rt
