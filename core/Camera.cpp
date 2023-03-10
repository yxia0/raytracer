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
		// TODO: delete in the end
		position = Vec3f(0.0, 0.0, 0.0);
		lookat = Vec3f(0.0, 0.0, -0.1);
		up = Vec3f(0.0, 1.0, 0.0);
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
		// TODO: parse postion, lookat, up
		if (cameraType.compare("pinhole") == 0)
		{
			if (cameraSpecs.HasMember("position"))
			{
				// TODO: make into a function
				// get position
				const Value &p = cameraSpecs.GetObject()["position"];
				float px = p[0].GetFloat();
				float py = p[1].GetFloat();
				float pz = p[2].GetFloat();
				Vec3f Position(px, py, pz);

				// get lookat
				const Value &l = cameraSpecs.GetObject()["lookat"];
				float lx = p[0].GetFloat();
				float ly = p[1].GetFloat();
				float lz = p[2].GetFloat();
				Vec3f Lookat(lx, ly, lz);

				// get up
				const Value &u = cameraSpecs.GetObject()["up"];
				float ux = p[0].GetFloat();
				float uy = p[1].GetFloat();
				float uz = p[2].GetFloat();
				Vec3f Up(ux, uy, uz);

				return new Pinhole(cameraSpecs["width"].GetInt(),
								   cameraSpecs["height"].GetInt(),
								   cameraSpecs["fov"].GetInt(),
								   Position,
								   Lookat,
								   Up);
			}
			else
			{
				return new Pinhole(cameraSpecs["width"].GetInt(),
								   cameraSpecs["height"].GetInt(),
								   cameraSpecs["fov"].GetInt());
			}
		}
		else if (cameraType.compare("thinlens") == 0)
		{
			return new ThinLens();
		}

		return 0;
	}

} // namespace rt
