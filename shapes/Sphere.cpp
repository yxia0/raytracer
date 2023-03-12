/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"

namespace rt
{

	// Destructor
	Sphere::~Sphere()
	{ /*TODO*/
	}

	/**
	 * @brief Computes whether a ray hit the specific instance of
	 * a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 * @return Hit struct containing intersection information
	 */
	Hit Sphere::intersect(Ray ray)
	{

		Hit h;
		// step 1: check if there is intersection with sphere
		double t_close = ray.dir.dotProduct(center - ray.orig);
		Vec3f x_close = ray.orig + t_close * ray.dir;
		double dist_to_sph = (x_close - center).length();

		if (dist_to_sph > radius)
		{
			// no intersection
			h.t = -1 * INFINITY;
		}
		else if (dist_to_sph < radius)
		{
			// ray enter the sphere
			double a = sqrt(radius * radius - dist_to_sph * dist_to_sph);
			h.t = t_close - a;
			h.point = ray.orig + h.t * ray.dir;
		}
		else
		{
			// hit surface
			h.t = t_close;
			h.point = x_close;
		}

		return h;
	}

	void Sphere::printShape()
	{
		printf("sphere: ");
		std::cerr << "center " << center;
		printf(" radius %.2f\n", radius);
	}

} // namespace rt
