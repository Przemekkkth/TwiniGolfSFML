#ifndef POINT_H
#define POINT_H
#include "../utils/resource_identifiers.h"
#include "entity.h"

class Point : public Entity
{
public:
    Point(const TextureHolder& textures);
    virtual ~Point() {}
};

#endif // POINT_H
