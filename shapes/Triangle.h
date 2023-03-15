/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"
#include "core/RayHitStructs.h"
#include "math/geometry.h"

namespace rt
{

    class Triangle : public Shape
    {

    public:
        Triangle(){};
        Triangle(Vec3f v0, Vec3f v1, Vec3f v2);
        ~Triangle(){};

        Hit intersect(Ray ray);
        void printShape();

    private:
        Vec3f *vertices;
        Vec3f calcNormal(Vec3f P);
        bool insideTriangle(Vec3f P);
    };

} // namespace rt

#endif /* TRIANGLE_H_ */
