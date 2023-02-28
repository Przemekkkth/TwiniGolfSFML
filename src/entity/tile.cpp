#include "tile.h"
#include "../utils/resource_holder.h"

Tile::Tile(const TextureHolder &textures, sf::Vector2f point, Type type)
{
    if(type == Dark32)
    {
        setTex(textures.get(Textures::Tile_Dark32));
    }
    else if(type == Dark64)
    {
        setTex(textures.get(Textures::Tile_Dark64));
    }
    else if(type == Light32)
    {
        setTex(textures.get(Textures::Tile_Light32));
    }
    else if(type == Light64)
    {
        setTex(textures.get(Textures::Tile_Light64));
    }
    setPos(point.x, point.y);
}
