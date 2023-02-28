#ifndef TILE_H
#define TILE_H
#include "entity.h"
#include "../utils/resource_identifiers.h"

class Tile : public Entity
{
public:
    enum Type{ Dark32, Dark64, Light32, Light64,};
    Tile(const TextureHolder& textures, sf::Vector2f point, Type type);
    virtual ~Tile(){}
};

#endif // TILE_H
