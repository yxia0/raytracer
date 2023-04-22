/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "math/geometry.h"
#include "lights/PointLight.h"

namespace rt
{

    class Material
    {
    public:
        Material(){};
        Material(float ks, float kd, float kr, float kt, float ior,
                 float specularexponent, Vec3f diffusecolor) : ks(ks), kd(kd), kr(kr), kt(kt),
                                                               ior(ior), specularexponent(specularexponent), diffusecolor(diffusecolor){};
        // getter
        float getKs();
        float getKd();
        float getKr();
        float getKt();
        float getIor();
        float getSpecularExp();
        Vec3f getColor();

        Vec3f reflectColor();
        Vec3f refractColor();
        void printMaterial();

    private:
        // default material settings
        float ks;  // specular multiplier
        float kd;  // diffuse multiplier
        float kr;  // reflection multiplier
        float kt;  // refraction multiplier
        float ior; // index of refraction
        float specularexponent;
        Vec3f diffusecolor;
    };

} // namespace rt

#endif /* MATERIAL_H_ */
