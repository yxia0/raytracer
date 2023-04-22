/*
 * Shape.cpp
 *
 */
#include "Shape.h"

namespace rt
{
    void Shape::addMaterial(Material *material)
    {
        this->material = material;
    }

    Material *Shape::getMaterial()
    {
        return this->material;
    }

} // namespace rt
