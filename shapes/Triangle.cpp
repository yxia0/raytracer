/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"

namespace rt
{

    Triangle::Triangle(Vec3f v0, Vec3f v1, Vec3f v2)
    {
        vertices = new Vec3f[3];
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
    }

    Hit Triangle::intersect(Ray ray)
    {
        // intersect with plane
        Hit hit;
        Vec3f normal;
        float t_hit;

        normal = calcNormal(vertices[0]);
        // find the ray-plane intersection xhit
        if (ray.dir.dotProduct(normal) == 0)
        {
            std::cout << "ray direction parallel to triangle plane" << std::endl;
            hit.t = INFINITY;
            return hit;
        }

        t_hit = (vertices[0] - ray.orig).dotProduct(normal) / ray.dir.dotProduct(normal);

        if (t_hit < 0)
        {
            hit.t = INFINITY;
            return hit;
        }

        Vec3f x_hit = ray.orig + t_hit * ray.dir;

        if (insideTriangle(x_hit))
        {
            hit.t = t_hit;
            hit.point = x_hit;
            hit.normal = calcNormal(hit.point);
        }
        else
        {
            hit.t = INFINITY;
        }

        return hit;
    }

    void Triangle::printShape()
    {
        printf("triangle: ");
        std::cout << "v0 " << vertices[0];
        std::cout << "v1 " << vertices[1];
        std::cout << "v2 " << vertices[2] << std::endl;
    }

    Vec3f Triangle::calcNormal(Vec3f P)
    {
        // calculate the normal of the plane
        return ((vertices[1] - P).crossProduct(vertices[2] - P)).normalize();
    }

    bool Triangle::insideTriangle(Vec3f P)
    {
        Vec3f v0 = vertices[2] - vertices[0];
        Vec3f v1 = vertices[1] - vertices[0];
        Vec3f v2 = P - vertices[0];

        float dot00 = v0.dotProduct(v0);
        float dot01 = v0.dotProduct(v1);
        float dot02 = v0.dotProduct(v2);
        float dot11 = v1.dotProduct(v1);
        float dot12 = v1.dotProduct(v2);

        // compute barycentric coordinates
        float denom = dot00 * dot11 - dot01 * dot01;
        float u = (dot11 * dot02 - dot01 * dot12) / denom;
        float v = (dot00 * dot12 - dot01 * dot02) / denom;

        return (u >= 0 & v >= 0 & (u + v) <= 1);
    }

} // namespace rt
