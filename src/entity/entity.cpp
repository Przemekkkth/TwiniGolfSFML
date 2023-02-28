#include "entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Entity::Entity(sf::Vector2f p_pos, sf::Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
    currentFrame = sf::IntRect(0, 0, 32, 32);
}

Entity::Entity()
{
    pos = sf::Vector2f(0,0);
    tex = nullptr;
    currentFrame = sf::IntRect(0, 0, 32, 32);
}

sf::Texture* Entity::getTex()
{
    return tex;
}

void Entity::update(sf::Time dt)
{

}

void Entity::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}

void Entity::setAngle(float p_angle)
{
    angle = p_angle;
}

void Entity::setTex(sf::Texture *_tex)
{
    tex = _tex;
    sf::Vector2u size = tex->getSize();
    currentFrame = sf::IntRect(0,0, size.x, size.y);
}

void Entity::setScale(float w, float h)
{
    scale.x = w;
    scale.y = h;
}

sf::IntRect Entity::getCurrentFrame()
{
    return currentFrame;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sprite.setTexture(*tex);
    //sprite.setTextureRect(currentFrame);
    //sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    sprite.setPosition(pos);
    sprite.setScale(scale);
    sprite.setRotation(angle);
    target.draw(sprite, states);
}
