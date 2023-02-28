#ifndef TILE_H
#define TILE_H
#include "entity.h"

class Tile : public Entity
{
public:
    Tile(sf::Vector2f p_pos, sf::Texture* p_tex);
    virtual ~Tile(){}
};

#endif // TILE_H
