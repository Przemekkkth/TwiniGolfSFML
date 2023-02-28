#include "hole.h"
#include "../utils/resource_holder.h"

Hole::Hole(const TextureHolder &textures, sf::Vector2f point)
{
    setTex(textures.get(Textures::Hole));
    setPos(point.x, point.y);
}

