/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"
#include "core/Material.h"

namespace rt
{

	/*
	 * Ray structure definition
	 */
	enum RayType
	{
		PRIMARY,
		SECONDARY,
		SHADOW
	};

	struct Ray
	{

		RayType raytype;

		//----------Ray variables to be filled------
		Vec3f orig; /* ray origin */
		Vec3f dir;	/* ray direction - unit vector */
		Vec3f pix_center;
		bool can_refract;
	};

	struct Hit
	{
		double t;
		Vec3f point;		// point where ray hits a shape
		Vec3f normal;		// surface normal of hit point
		bool enter_object;	// if the ray is entering the object or leaving
		Material *material; // pointer to material object
	};
}

#endif /* CORE_RAYHITSTRUCTS_H_ */
