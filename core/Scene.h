/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/Shape.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "shapes/Triangle.h"

#include "core/LightSource.h"
#include "lights/PointLight.h"

using namespace rapidjson;

namespace rt
{

	class Scene
	{
	public:
		Scene(){};

		void createScene(Value &scenespecs);
		Vec3f getBackground();
		std::vector<Shape *> getShapes();
		std::vector<LightSource *> getLights();

	private:
		std::vector<LightSource *> lights;
		std::vector<Shape *> shapes;
		Vec3f backgroundcolor;

		// read specs
		void readBGColor(Value &scenespecs);
		void readLightSource(Value &scenespecs);
		void readShapes(Value &scenespecs);

		// create lights
		PointLight *createPointLight(Value &specs);

		// create shapes
		Sphere *createSphere(Value &specs);
		Plane *createPlane(Value &specs);
		Triangle *createTriangle(Value &specs);

		// utils
		Vec3f readVec(Value &sepcs, char *name);
		float readFloat(Value &sepcs, char *name);
		void addMaterial(Value &sepcs, Shape *shape);
	};

} // namespace rt

#endif /* SCENE_H_ */
