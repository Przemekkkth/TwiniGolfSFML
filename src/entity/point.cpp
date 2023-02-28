#include "point.h"
#include "../utils/resource_holder.h"

Point::Point(const TextureHolder &textures)
{
    setTex(textures.get(Textures::Point));
    setOrigin(8,0);
}
