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
	bool Sphere::intersect(Ray ray)
	{

		// Hit h;
		// TODO

		/* t^2 * b⋅b+2tb⋅(O−C)+(O−C)⋅(O−C)−r^2=0 */
		Vec3f oc = ray.orig - center;
		float a = ray.dir.dotProduct(ray.dir);
		float b = 2.0 * oc.dotProduct(ray.dir);
		float c = oc.dotProduct(oc) - radius * radius;
		float discriminant = b * b - 4.0 * a * c;

		if (discriminant < 0)
		{
			return false;
		}
		else
		{
			// float t = (-b - sqrt(discriminant)) / (2.0 * a);
			// h.point = ray.orig - t * ray.dir;
			return true;
		}
	}

	void Sphere::printShape()
	{
		printf("I am a sphere! \n");
		std::cerr << "center:" << center << std::endl;
		printf("radius: %f\n", radius);
	}

} // namespace rt
