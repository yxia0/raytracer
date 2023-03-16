/*
 * RayTracer.cpp
 *
 */
#include <algorithm>
#include "RayTracer.h"

namespace rt
{

	/**
	 * @brief Generate rays according to camera and display to ray trace scene
	 *
	 * @param camera the camera viewing the scene
	 * @param scene the scene to render, including objects and lightsources
	 * @param nbounces the number of bounces to consider for raytracing
	 *
	 * @return a pixel buffer containing pixel values in linear RGB format
	 */
	Vec3f *RayTracer::render(Camera *camera, Scene *scene, int nbounces)
	{

		const int width = camera->getWidth();
		const int height = camera->getHeight();

		Vec3f *pixelbuffer = new Vec3f[width * height];
		auto objects = scene->getShapes();
		auto lights = scene->getLights();
		auto object = objects[0];
		auto light = lights[0];
		object->printShape(); // for debugging

		for (size_t i = 0; i < height; i++)
		{
			std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
			for (size_t j = 0; j < width; j++)
			{
				Ray r = camera->shoot(i, j);
				pixelbuffer[i * width + j] = trace(r, object, light);
			}
		}
		std::cerr << "\nDone.\n";

		return pixelbuffer;
	}

	/**
	 * @brief Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
	 *
	 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
	 *
	 * @return the tonemapped image
	 */
	Vec3f *RayTracer::tonemap(Vec3f *pixelbuffer, int bufferSize)
	{

		//---------tonemapping function to be filled--------
		for (size_t i = 0; i < bufferSize; i++)
		{
			pixelbuffer[i] *= 225;
		}

		return pixelbuffer;
	}

	// Vec3f RayTracer::castRay(Ray ray, std::vector<Shape *> shapes)
	// {
	// 	for (size_t i = 0; i < shapes.size(); i++)
	// 	{
	// 		if (shapes[i]->intersect(ray))
	// 		{
	// 			return Vec3f(0.0, 0.8, 0.8);
	// 		}
	// 		else
	// 		{
	// 			return Vec3f(0.01, 0.01, 0.01);
	// 		}
	// 	}
	// }

	/**
	 * @brief Trace ray and return color.
	 * Find first intersection for t>O and shade it.
	 *
	 * @param ray a ray vector
	 * @param shape a hittable object
	 * @return Vec3f color vector
	 */
	Vec3f RayTracer::trace(Ray ray, Shape *shape, PointLight *light)
	{

		Hit hit;
		hit = intersect(ray, shape);
		/** TODO: negation of normal */
		if (ray.dir.dotProduct(hit.normal) > 0)
		{
			hit.normal *= -1;
		}

		if (hit.t != INFINITY)
		{
			return shade(ray, hit, light);
		}
		else
		{
			// TODO: background color
			return Vec3f(0.01, 0.01, 0.01);
		}

		// if (hit.t == -1 * INFINITY)
		// {
		// 	return Vec3f(0.01, 0.01, 0.01);
		// }
		// else
		// {
		// 	return Vec3f(0.0, 0.8, 0.8);
		// }
	}

	/**
	 * @brief Return color at a hit point
	 *
	 * @param hit a hit record
	 * @return Vec3f color
	 */
	Vec3f RayTracer::shade(Ray ray, Hit hit, PointLight *light)
	{
		// add light source
		Vec3f light_dir = (light->getPos() - hit.point).normalize();
		/* Compute diffuse TODO: for all lights */
		Vec3f diffuse_intensity = light->getId() * fmax(0.f, light_dir.dotProduct(hit.normal));
		/* Compute specular - recursion */
		Vec3f view_dir = (ray.pix_center - hit.point).normalize();
		Vec3f bisector = (light_dir + view_dir).normalize();
		Vec3f specular_intensity = light->getIs() *
								   powf(fmax(0.f, hit.normal.dotProduct(bisector)), 16);
		// exponent - shininess

		return Vec3f(0.1, 0.3, 0.4) * diffuse_intensity * 0.6 + specular_intensity * 0.3;
		// return Vec3f(0.4, 0.3, 0.4);
	}

	/**
	 * @brief Compute intersection record hit of ray with hittable
	 * object shape
	 *
	 * @param ray a ray vector
	 * @param shape a hittable object
	 * @return Hit a hit record
	 * TODO: this will be extended to a list of hit records
	 */
	Hit RayTracer::intersect(Ray ray, Shape *shape)
	{
		/** TODO: loop over shapes */
		return shape->intersect(ray);
	}

} // namespace rt
