/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

using namespace rapidjson;

namespace rt
{

	class Camera
	{
	public:
		//
		// Constructors
		//
		Camera(){};
		Camera(int height, int width, int fov);
		Camera(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up);
		//
		// Destructor
		//
		virtual ~Camera();

		//
		// factory function : returns camera instance dynamically based on camera specifications
		//
		static Camera *createCamera(Value &cameraSpecs);

		//
		// print function (to be implemented by the subclasses )
		//
		virtual void printCamera() = 0;

		//
		// other camera functions (to complete)
		//

		virtual Ray getRay(int hIndex, int wIndex) = 0;

		//
		// Getters and Setters
		//
		int getHeight() const { return height; }

		void setHeight(int height) { this->height = height; }

		int getWidth() const { return width; }

		void setWidth(int width) { this->width = width; }

		void setPosition(Vec3f position) { this->position = position; }

		void setLookAt(Vec3f lookat) { this->lookat = lookat; }

		void setUp(Vec3f up) { this->up = up; }

	protected:
		//
		// camera members
		//
		int height;
		int width;
		int fov; // field of view

		Vec3f position;
		Vec3f lookat;
		Vec3f up;
	};

} // namespace rt

#endif /* CAMERA_H_ */
