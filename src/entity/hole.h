#ifndef HOLE_H
#define HOLE_H
#include "entity.h"
#include "../utils/resource_identifiers.h"

class Hole : public Entity
{
public:
    Hole(const TextureHolder& textures, sf::Vector2f point);
    virtual ~Hole(){}
};

#endif // HOLE_H
