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
#include "core/LightSource.h"
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

		Vec3f *render(Camera *camera, Scene *scene, int nbounces);
		static Vec3f *tonemap(Vec3f *pixelbuffer, int bufferSize);

	private:
		// default ray tracer settings
		int nbounces = 1;
		Vec3f background = Vec3f(0, 0, 0);
		// ray tracer functions
		Vec3f trace(Ray ray, std::vector<Shape *> shapes, std::vector<LightSource *> lights, int nbounces);
		Vec3f shade(Ray ray, Hit hit, std::vector<LightSource *> lights, std::vector<Shape *> shapes);
		Hit intersect(Ray ray, std::vector<Shape *> shapes);
		Vec3f shadowAttenuation(PointLight *light, Hit hit, std::vector<Shape *> shapes);
		Ray createReflectRay(Ray ray, Hit hit);
		Ray createRefractRay(Ray ray, Hit hit);
		bool isShadow(Ray shadow_ray, std::vector<Shape *> shapes, float light_distance);
		Vec3f diffuseColor(PointLight *light, Hit hit);
		Vec3f specularColor(Ray ray, PointLight *light, Hit hit);
	};

} // namespace rt

#endif /* RAYTRACER_H_ */
