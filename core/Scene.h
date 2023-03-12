/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
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

	private:
		std::vector<LightSource *> lightSources;
		std::vector<Shape *> shapes;

		void readBGColor(Value &scenespecs);
		void readLightSource(Value &scenespecs);
		void readShapes(Value &scenespecs);
	};

} // namespace rt

#endif /* SCENE_H_ */
