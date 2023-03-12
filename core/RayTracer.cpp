/*
 * RayTracer.cpp
 *
 */
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

		int width, height;
		width = camera->getWidth();
		height = camera->getHeight();

		Vec3f *pixelbuffer = new Vec3f[width * height];
		auto objects = scene->getShapes();
		auto object = objects[0];
		object->printShape();

		//----------main rendering function to be filled------
		// TODO emit rays! Most outer loop
		// TODO cast ray on objects --> put into a function

		for (size_t i = 0; i < height; i++)
		{
			std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
			for (size_t j = 0; j < width; j++)
			{
				Ray r = camera->shoot(i, j);
				pixelbuffer[i + j * width] = trace(r, object);
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
	 * @brief Trace ray and return color
	 *
	 * @param ray a ray vector
	 * @param shape a hittable object
	 * @return Vec3f color vector
	 */
	Vec3f RayTracer::trace(Ray ray, Shape *shape)
	{

		Hit hit = shape->intersect(ray);
		if (hit.t == -1 * INFINITY)
		{
			return Vec3f(0.01, 0.01, 0.01);
		}
		else
		{
			return Vec3f(0.0, 0.8, 0.8);
		}
	}

	/**
	 * @brief Return color at a hit point
	 *
	 * @param hit a hit record
	 * @return Vec3f color
	 */
	Vec3f RayTracer::shade(Hit hit)
	{
	}

	/**
	 * @brief Compute intersection record hit of ray with hittable
	 * object shape
	 *
	 * @param ray a ray vector
	 * @param shape a hittable object
	 * @return Hit a hit record
	 */
	Hit RayTracer::intersect(Ray ray, Shape *shape)
	{
	}

} // namespace rt
