/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "lights/PointLight.h"

namespace rt
{

	/*
	 * Raytracer class declaration
	 */
	class RayTracer
	{
	public:
		RayTracer(){};

		static Vec3f *render(Camera *camera, Scene *scene, int nbounces);
		static Vec3f *tonemap(Vec3f *pixelbuffer, int bufferSize);

	private:
		static Vec3f trace(Ray ray, Shape *shape, PointLight *light);
		// TODO: generalise to light
		static Vec3f shade(Ray ray, Hit hit, PointLight *light); // TODO: generalize to light
		static Hit intersect(Ray ray, Shape *shape);
	};

} // namespace rt

#endif /* RAYTRACER_H_ */
