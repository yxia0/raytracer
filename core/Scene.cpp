/*
 * Scene.cpp
 *
 */
#include <iostream>

#include "math/geometry.h"
#include "Scene.h"
#include "shapes/Sphere.h"

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

	/**
	 * @brief Parses json scene object to generate scene to render
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void Scene::createScene(Value &scenespecs)
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
	}

	/**
	 * @brief Parses json scene object and generate light source objects
	 * to be included in the scene
	 *
	 * @param scenespecs the json scene specificatioon
	 */
	void Scene::readLightSource(Value &scenespecs)
	{
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
					const Value &c = objects[i].GetObject()["center"];

					float x = c[0].GetFloat();
					float y = c[1].GetFloat();
					float z = c[2].GetFloat();
					Vec3f center(x, y, z);
					shapes.push_back(new Sphere(center, objects[i].GetObject()["radius"].GetFloat()));
					std::cout << "==Sphere is created in the scene==" << std::endl;
				}
				else if (shapeType.compare("plane") == 0)
				{
					std::cout << "Plane parsing is not implemented" << std::endl;
				}
				else if (shapeType.compare("triangle") == 0)
				{
					std::cout << "Triangle parsing is not implemented" << std::endl;
				}
			}
		}
	}

} // namespace rt
