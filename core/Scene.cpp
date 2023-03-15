/*
 * Scene.cpp
 *
 */
#include <iostream>

#include "math/geometry.h"
#include "Scene.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "shapes/Triangle.h"

namespace rt
{

	/**
	 * @brief Retrun the shapes vector
	 *
	 * @return shapes a vector containing shape objects in a scene
	 */
	std::vector<Shape *> Scene::getShapes()
	{
		return shapes;
	}

	std::vector<PointLight *> Scene::getLights()
	{
		return lights;
	}

	/**
	 * @brief Parses json scene object to generate scene to render
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void
	Scene::createScene(Value &scenespecs)
	{
		// parse json object to populate scene
		readBGColor(scenespecs);
		readLightSource(scenespecs);
		readShapes(scenespecs);
	}

	/**
	 * @brief Parses json scene object and populate background color
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void Scene::readBGColor(Value &scenespecs)
	{
		if (!scenespecs.HasMember("backgroundcolor"))
		{
			std::cerr << "Background color not defined" << std::endl;
		}
		else
		{
			backgroundcolor = readVec(scenespecs, "backgroundcolor");
			std::cerr << "Background Color: " << backgroundcolor << std::endl;
		}
	}

	/**
	 * @brief Parses json scene object and generate light source objects
	 * to be included in the scene
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void Scene::readLightSource(Value &scenespecs)
	{
		if (!scenespecs.HasMember("lightsources"))
		{
			std::cout << "Light sources not defined" << std::endl;
		}
		else if (scenespecs["lightsources"].Size() == 0)
		{
			std::cerr << "Lights are not included in the scene" << std::endl;
		}
		else
		{
			Value &objects = scenespecs["lightsources"];
			for (size_t i = 0; i < objects.Size(); i++)
			{
				std::string shapeType = objects[i].GetObject()["type"].GetString();
				if (shapeType.compare("pointlight") == 0)
				{
					Vec3f position = readVec(objects[i], "position");
					Vec3f is = readVec(objects[i], "is");
					Vec3f id = readVec(objects[i], "id");
					lights.push_back(new PointLight(position, is, id));
					std::cout << "...PointLight is created..." << std::endl;
				}
				else if (shapeType.compare("arealight") == 0)
				{
					std::cout << "Area light is not implemented" << std::endl;
				}
			}
		}
	}

	/**
	 * @brief Parses json scene object and generate shape objects
	 * to be included in the scene
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void Scene::readShapes(Value &scenespecs)
	{
		if (!scenespecs.HasMember("shapes"))
		{
			std::cerr << "Shape category not specified" << std::endl;
		}
		else if (scenespecs["shapes"].Size() == 0)
		{
			std::cerr << "Shapes not included in the scene" << std::endl;
		}
		else
		{
			Value &objects = scenespecs["shapes"];
			for (size_t i = 0; i < objects.Size(); i++)
			{

				std::string shapeType = objects[i].GetObject()["type"].GetString();

				if (shapeType.compare("sphere") == 0)
				{
					//  get center
					Vec3f center = readVec(objects[i], "center");
					shapes.push_back(new Sphere(center, objects[i].GetObject()["radius"].GetFloat()));
					std::cout << "...Sphere is created..." << std::endl;
				}
				else if (shapeType.compare("plane") == 0)
				{
					// get four vertices
					Vec3f v0 = readVec(objects[i], "v0");
					Vec3f v1 = readVec(objects[i], "v1");
					Vec3f v2 = readVec(objects[i], "v2");
					Vec3f v3 = readVec(objects[i], "v3");
					shapes.push_back(new Plane(v0, v1, v2, v3));
					std::cout << "...Plane is created..." << std::endl;
				}
				else if (shapeType.compare("triangle") == 0)
				{
					// get three vertices
					Vec3f v0 = readVec(objects[i], "v0");
					Vec3f v1 = readVec(objects[i], "v1");
					Vec3f v2 = readVec(objects[i], "v2");
					shapes.push_back(new Triangle(v0, v1, v2));
					std::cout << "...Triangle is created..." << std::endl;
				}
			}
		}
	}

	Vec3f Scene::readVec(Value &sepcs, char *name)
	{
		const Value &o = sepcs.GetObject()[name];

		float x = o[0].GetFloat();
		float y = o[1].GetFloat();
		float z = o[2].GetFloat();
		Vec3f vec(x, y, z);
		return vec;
	}

} // namespace rt
