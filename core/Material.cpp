/*
 * Material.cpp
 *
 */
#include "Material.h"

namespace rt
{

    float Material::getKs()
    {
        return this->ks;
    }

    float Material::getKd()
    {
        return this->kd;
    }

    float Material::getKr()
    {
        return this->kr;
    }

    float Material::getKt()
    {
        return this->kt;
    }

    float Material::getIor()
    {
        return this->ior;
    }

    float Material::getSpecularExp()
    {
        return this->specularexponent;
    }

    Vec3f Material::getColor()
    {
        return this->diffusecolor;
    }

    Vec3f Material::reflectColor()
    {
    }

    Vec3f Material::refractColor()
    {
    }

    void Material::printMaterial()
    {
        printf("Matrial: ");
        std::cout << "specular mutiplier ks: " << ks << " ";
        std::cout << "diffuse multiplier kd: " << kd << " ";
        std::cout << "reflection multiplier kr: " << kr << " ";
        std::cout << "refraction multiplier kt " << kt << " ";
        std::cout << "refraction index ior: " << ior << " ";
        std::cout << "specula exponent: " << specularexponent << " ";
        std::cout << "shape color: " << diffusecolor << std::endl;
    }

} // namespace rt
