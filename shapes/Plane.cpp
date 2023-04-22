/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"

namespace rt
{
    Plane::Plane(Vec3f v0, Vec3f v1, Vec3f v2, Vec3f v3)
    {
        vertices = new Vec3f[4];
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
        vertices[3] = v3;
    }

    Vec3f Plane::calcNormal(Vec3f P)
    {
        // calculate the normal of the plane
        return ((vertices[1] - P).crossProduct(vertices[3] - P)).normalize();
    }

    Polygon2D Plane::projectTo2D(Vec3f intSecPoint, Vec3f normal)
    {
        // project the plane to the 2D coordinate that has the largest parallel projection (image)
        // can we make this function better?
        Polygon2D p;
        p.polygon = new Vec2f[4];

        if (abs(normal.x) >= abs(normal.y) & abs(normal.x) >= abs(normal.z))
        {
            for (size_t i = 0; i < 4; i++)
            {
                p.polygon[i] = Vec2f(vertices[i].y, vertices[i].z);
            }
            p.p = Vec2f(intSecPoint.y, intSecPoint.z);
        }
        else if (abs(normal.y) >= abs(normal.x) & abs(normal.y) >= abs(normal.z))
        {
            for (size_t i = 0; i < 4; i++)
            {
                p.polygon[i] = Vec2f(vertices[i].z, vertices[i].x);
            }
            p.p = Vec2f(intSecPoint.z, intSecPoint.x);
        }
        else
        {
            for (size_t i = 0; i < 4; i++)
            {
                p.polygon[i] = Vec2f(vertices[i].x, vertices[i].y);
            }
            p.p = Vec2f(intSecPoint.x, intSecPoint.y);
        }

        return p;
    }

    Polygon2D Plane::translate(Polygon2D ploygon)
    {
        for (size_t i = 0; i < 4; i++)
        {
            ploygon.polygon[i] = ploygon.polygon[i] - ploygon.p;
        }

        return ploygon;
    }

    Hit Plane::intersect(Ray ray)
    {
        Hit hit;
        Vec3f normal;
        float t_hit;

        normal = calcNormal(vertices[0]);
        // find the ray-plane intersection xhit
        if (ray.dir.dotProduct(normal) == 0)
        {
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
        //  determine whether or not xhit falls inside or outside of the polygon
        // project to 2D
        Polygon2D plane2D = projectTo2D(x_hit, normal);
        // translate
        plane2D = translate(plane2D);
        if (insidePolygon(plane2D))
        {
            hit.t = t_hit;
            hit.point = x_hit;
            hit.normal = calcNormal(hit.point);
            hit.material = this->getMaterial();
        }
        else
        {
            hit.t = INFINITY;
        }

        return hit;
    }

    bool Plane::insidePolygon(Polygon2D polygon)
    {
        int NC = 0;

        for (size_t i = 0; i < 4; i++)
        {
            Vec2f p1 = polygon.polygon[i];
            Vec2f p2 = polygon.polygon[(i + 1) % 4];
            if ((p1.y < 0 ? -1 : 1) != (p2.y < 0 ? -1 : 1))
            {
                if (p1.x > 0 & p2.x > 0)
                {
                    NC++;
                }
                else if (p1.x > 0 | p2.x > 0)
                {
                    if ((p2.y * p1.x - p2.x * p1.y) / (p2.y - p1.y) > 0)
                    {
                        NC++;
                    }
                }
            }
        }
        return NC % 2 != 0;
    }

    void Plane::printShape()
    {
        printf("plane: ");
        std::cout << "v0 " << vertices[0];
        std::cout << "v1 " << vertices[1];
        std::cout << "v2 " << vertices[2];
        std::cout << "v3 " << vertices[3] << std::endl;
    }

}