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
		// TODO

		/* t^2 * b⋅b+2tb⋅(O−C)+(O−C)⋅(O−C)−r^2=0 */
		Vec3f oc = ray.orig - center;
		float a = ray.dir.dotProduct(ray.dir);
		float b = 2.0 * oc.dotProduct(ray.dir);
		float c = oc.dotProduct(oc) - radius * radius;
		float discriminant = b * b - 4.0 * a * c;

		if (discriminant < 0)
		{
			h.point = ray.orig - 1.0 * ray.dir;
			h.intersect = false;
		}
		else
		{
			float t = (-b - sqrt(discriminant)) / (2.0 * a);
			h.point = ray.orig - t * ray.dir;
			h.intersect = true;
		}

		return h;
	}

} // namespace rt
