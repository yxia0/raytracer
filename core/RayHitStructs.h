/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

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
	};

	struct Hit
	{

		Vec3f point; // point where ray hits a shape
		double t;
	};
}

#endif /* CORE_RAYHITSTRUCTS_H_ */
