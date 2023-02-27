#ifndef HOLE_H
#define HOLE_H
#include "entity.h"

class Hole : public Entity
{
public:
    Hole(sf::Vector2f p_pos, sf::Texture* p_tex);
};

#endif // HOLE_H
