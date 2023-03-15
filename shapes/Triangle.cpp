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
        Vec3f v_n = (vertices[2] - vertices[1]).crossProduct(vertices[1] - vertices[0]);
        float A = v_n.norm();
        Vec3f n = v_n / A;
        float u = ((vertices[2] - vertices[1]).crossProduct(P - vertices[1])).dotProduct(n) / A;
        float v = ((vertices[0] - vertices[2]).crossProduct(P - vertices[2])).dotProduct(n) / A;

        if (u >= 0 & v >= 0 & (u + v) <= 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace rt
