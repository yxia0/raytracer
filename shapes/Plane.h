/*
 * Plane.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "core/Shape.h"
#include "core/RayHitStructs.h"
#include "math/geometry.h"

namespace rt
{

    struct Polygon2D
    {
        Vec2f *polygon;
        Vec2f p; // intersection point
    };

    class Plane : public Shape
    {
    public:
        Plane(){};
        Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3);
        ~Plane(){};

        Hit intersect(Ray ray);
        void printShape();

    private:
        Vec3f *vertices;

        // helper functions for intersection
        Polygon2D projectTo2D(Vec3f intSecPoint, Vec3f normal);
        Polygon2D translate(Polygon2D polygon);
        bool insidePolygon(Polygon2D polygon);
        Vec3f calcNormal(Vec3f P);
    };

} // namespace rt

#endif /* PLANE_H_ */