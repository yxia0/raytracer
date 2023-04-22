/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"
#include "math/geometry.h"

namespace rt
{

    class PointLight : public LightSource
    {

    public:
        PointLight(){};
        PointLight(Vec3f position, Vec3f is, Vec3f id) : position(position), is(is), id(id){};
        ~PointLight(){};

        Vec3f getPos() const { return position; }
        Vec3f getIs() const { return is; }
        Vec3f getId() const { return id; }

    private:
        Vec3f position;
        Vec3f is;
        Vec3f id;
    };

} // namespace rt

#endif /* POINTLIGHT_H_ */
