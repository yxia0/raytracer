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

	std::vector<LightSource *> Scene::getLights()
	{
		return lights;
	}

	Vec3f Scene::getBackground()
	{
		return backgroundcolor;
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
					lights.push_back(createPointLight(objects[i]));
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
					shapes.push_back(createSphere(objects[i]));
					std::cout << "...Sphere is created..." << std::endl;
				}
				else if (shapeType.compare("plane") == 0)
				{
					shapes.push_back(createPlane(objects[i]));
					std::cout << "...Plane is created..." << std::endl;
				}
				else if (shapeType.compare("triangle") == 0)
				{
					shapes.push_back(createTriangle(objects[i]));
					std::cout << "...Triangle is created..." << std::endl;
				}
			}
			// for debug
			shapes.at(1)->getMaterial()->printMaterial();
		}
	}

	Vec3f Scene::readVec(Value &sepcs, char *name)
	{
		if (!sepcs.HasMember(name))
		{
			return Vec3f(0, 0, 0);
		}

		const Value &o = sepcs.GetObject()[name];
		float x = o[0].GetFloat();
		float y = o[1].GetFloat();
		float z = o[2].GetFloat();
		Vec3f vec(x, y, z);
		return vec;
	}

	float Scene::readFloat(Value &specs, char *name)
	{
		if (!specs.HasMember(name))
		{
			return 0.0;
		}
		float value = specs.GetObject()[name].GetFloat();
		return value;
	}

	void Scene::addMaterial(Value &specs, Shape *shape)
	{
		if (specs.HasMember("material"))
		{
			Value &spec = specs["material"];
			float ks = readFloat(spec, "ks");
			float kd = readFloat(spec, "kd");
			float kr = readFloat(spec, "kr");
			float kt = readFloat(spec, "kt");
			float ior = readFloat(spec, "ior");
			float specularexponent = readFloat(spec, "specularexponent");
			Vec3f diffusecolor = readVec(spec, "diffusecolor");

			Material *material = new Material(ks, kd, kr, kt, ior, specularexponent, diffusecolor);
			shape->addMaterial(material);
		}
		else
		{
			Material *material = new Material(0, 0, 0, 0, 0, 0, Vec3f(0, 0, 0));
			shape->addMaterial(material);
		}
	}

	Sphere *Scene::createSphere(Value &specs)
	{
		Vec3f center = readVec(specs, "center");
		float radius = readFloat(specs, "radius");
		Sphere *sphere = new Sphere(center, radius);
		addMaterial(specs, sphere);

		return sphere;
	}

	Plane *Scene::createPlane(Value &specs)
	{
		// get four vertices
		Vec3f v0 = readVec(specs, "v0");
		Vec3f v1 = readVec(specs, "v1");
		Vec3f v2 = readVec(specs, "v2");
		Vec3f v3 = readVec(specs, "v3");
		Plane *plane = new Plane(v0, v1, v2, v3);

		addMaterial(specs, plane);
		return plane;
	}

	Triangle *Scene::createTriangle(Value &specs)
	{
		// get three vertices
		Vec3f v0 = readVec(specs, "v0");
		Vec3f v1 = readVec(specs, "v1");
		Vec3f v2 = readVec(specs, "v2");
		Triangle *triangle = new Triangle(v0, v1, v2);
		addMaterial(specs, triangle);

		return triangle;
	}

	PointLight *Scene::createPointLight(Value &specs)
	{
		Vec3f position = readVec(specs, "position");
		Vec3f is = readVec(specs, "is");
		Vec3f id = readVec(specs, "id");
		return new PointLight(position, is, id);
	}

} // namespace rt
