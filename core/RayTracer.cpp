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

		this->background = scene->getBackground();
		this->nbounces = nbounces;

		const int width = camera->getWidth();
		const int height = camera->getHeight();

		Vec3f *pixelbuffer = new Vec3f[width * height];
		auto shapes = scene->getShapes();
		auto lights = scene->getLights();

		for (size_t i = 0; i < height; i++)
		{
			std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
			for (size_t j = 0; j < width; j++)
			{
				Ray r = camera->shoot(i, j);
				pixelbuffer[i * width + j] = trace(r, shapes, lights, 0);
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
		for (size_t i = 0; i < bufferSize; i++)
		{
			pixelbuffer[i] *= 225;
		}
		return pixelbuffer;
	}

	/**
	 * @brief Trace ray and return color.
	 * Find first intersection for t>O and shade it.
	 *
	 * @param ray a ray vector
	 * @param shape a hittable object
	 * @return Vec3f color vector
	 */
	Vec3f RayTracer::trace(Ray ray, std::vector<Shape *> shapes, std::vector<LightSource *> lights, int nbounces)
	{
		if (nbounces > this->nbounces)
		{
			return Vec3f(0, 0, 0);
		}

		Hit hit;
		hit = intersect(ray, shapes);
		Vec3f color = Vec3f(0, 0, 0);
		/** negation of normal */
		hit.enter_object = true;
		if (ray.dir.dotProduct(hit.normal) > 0)
		{
			hit.normal *= -1;
			hit.enter_object = false;
		}

		if (hit.t != INFINITY)
		{
			color = shade(ray, hit, lights, shapes); // direct illumination
			// reflection
			Ray reflect_ray = createReflectRay(ray, hit);
			color = color + hit.material->getKr() * trace(reflect_ray, shapes, lights, nbounces + 1);
			// refraction - assume scene environment is vaccum
			Ray refract_ray = createRefractRay(ray, hit);
			if (refract_ray.can_refract)
			{
				color += hit.material->getKt() * trace(refract_ray, shapes, lights, nbounces + 1);
			}
		}
		else
		{
			color += this->background;
		}

		return color;
	}

	/**
	 * @brief Return color at a hit point
	 *
	 * @param hit a hit record
	 * @return Vec3f color
	 */
	Vec3f RayTracer::shade(Ray ray, Hit hit, std::vector<LightSource *> lights, std::vector<Shape *> shapes)
	{
		if (hit.t == INFINITY)
		{
			return this->background;
		}

		Vec3f diffuse_color(0, 0, 0);
		Vec3f specular_color(0, 0, 0);
		Vec3f color(0, 0, 0);

		for (LightSource *light : lights)
		{
			Vec3f atten = shadowAttenuation((PointLight *)light, hit, shapes);
			diffuse_color += diffuseColor((PointLight *)light, hit);
			specular_color += specularColor(ray, (PointLight *)light, hit);
			color = color + atten * (diffuse_color + specular_color);
		}

		return color;
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
	Hit RayTracer::intersect(Ray ray, std::vector<Shape *> shapes)
	{
		Hit hit;
		hit.t = INFINITY; // current min t

		for (size_t i = 0; i < shapes.size(); i++)
		{
			Hit curr_hit = shapes[i]->intersect(ray);
			if (curr_hit.t < hit.t & curr_hit.t >= 0)
			{
				hit = curr_hit;
			}
		}
		return hit;
	}

	Vec3f RayTracer::shadowAttenuation(PointLight *light, Hit hit, std::vector<Shape *> shapes)
	{
		float light_distance = (light->getPos() - hit.point).norm();
		Vec3f light_dir = (light->getPos() - hit.point).normalize();

		// create shadow ray
		Ray shadow_ray;
		shadow_ray.orig = light_dir.dotProduct(hit.normal) < 0 ? hit.point - hit.normal * 1e-3 : hit.point + hit.normal * 1e-3;
		shadow_ray.dir = light_dir;

		if (!isShadow(shadow_ray, shapes, light_distance))
		{
			return Vec3f(1, 1, 1);
		}
		else
		{
			return Vec3f(0, 0, 0);
		}
	}

	bool RayTracer::isShadow(Ray shadow_ray, std::vector<Shape *> shapes, float light_distance)
	{
		Hit hit = intersect(shadow_ray, shapes);

		if (hit.t != INFINITY && (hit.point - shadow_ray.orig).norm() < light_distance)
		{
			return true;
		}
		return false;
	}

	Vec3f RayTracer::diffuseColor(PointLight *light, Hit hit)
	{
		Vec3f light_dir = (light->getPos() - hit.point).normalize();
		return light->getId() * fmax(0.f, light_dir.dotProduct(hit.normal)) * hit.material->getKd() * hit.material->getColor();
	}

	Vec3f RayTracer::specularColor(Ray ray, PointLight *light, Hit hit)
	{

		Vec3f light_dir = (light->getPos() - hit.point).normalize();
		Vec3f view_dir = (ray.pix_center - hit.point).normalize();
		Vec3f bisector = (light_dir + view_dir).normalize();

		return light->getIs() * powf(fmax(0.f, hit.normal.dotProduct(bisector)), hit.material->getSpecularExp()) * hit.material->getKs();
	}

	Ray RayTracer::createReflectRay(Ray ray, Hit hit)
	{
		Vec3f reflection_dir = (ray.dir - 2 * hit.normal * (hit.normal.dotProduct(ray.dir))).normalize();
		Vec3f reflection_point = reflection_dir.dotProduct(hit.normal) < 0 ? hit.point - hit.normal * 1e-3 : hit.point + hit.normal * 1e-3;

		Ray reflect_ray;
		reflect_ray.orig = reflection_point;
		reflect_ray.dir = reflection_dir;
		return reflect_ray;
	}

	Ray RayTracer::createRefractRay(Ray ray, Hit hit)
	{
		Ray refract_ray;
		float refraction_ratio = hit.enter_object ? (1.0 / hit.material->getIor()) : hit.material->getIor();
		double cos_theta = fmin(-ray.dir.normalize().dotProduct(hit.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		if (refraction_ratio * sin_theta > 1)
		{
			refract_ray.can_refract = false;
		}
		else
		{
			// can refract
			refract_ray.can_refract = true;
			Vec3f refract_ray_perp = refraction_ratio * (ray.dir.normalize() + cos_theta * hit.normal);
			Vec3f refract_ray_parallel = -sqrt(fabs(1.0 - refract_ray_perp.norm())) * hit.normal;
			refract_ray.dir = refract_ray_perp + refract_ray_parallel;
			refract_ray.orig = hit.point;
		}

		return refract_ray;
	}

} // namespace rt
