/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "lights/PointLight.h"
#include "core/Shape.h"

using namespace rapidjson;

namespace rt
{

	class Scene
	{
	public:
		Scene(){};

		void createScene(Value &scenespecs);
		std::vector<Shape *> getShapes();
		std::vector<PointLight *> getLights();

	private:
		std::vector<PointLight *> lights;
		std::vector<Shape *> shapes;
		Vec3f backgroundcolor;

		void readBGColor(Value &scenespecs);
		void readLightSource(Value &scenespecs);
		void readShapes(Value &scenespecs);
		Vec3f readVec(Value &sepcs, char *name);
	};

} // namespace rt

#endif /* SCENE_H_ */
