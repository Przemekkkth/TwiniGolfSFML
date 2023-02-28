#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Entity : public sf::Drawable
{
public:
    Entity(sf::Vector2f p_pos, sf::Texture* p_tex);
    Entity();
    virtual ~Entity(){}
    sf::Vector2f& getPos();
    float getAngle();
    sf::Vector2f getScale();
    sf::Texture* getTex();
    sf::Vector2f getOrigin();

    void setPos(float x, float y);
    void setScale(float w, float h);
    void setAngle(float angle);
    void setTex(sf::Texture* _tex);
    void setOrigin(float x, float y);

    void update(sf::Time time);
    sf::IntRect getCurrentFrame();
private:
    sf::Vector2f pos;
    float angle = 0;
    sf::Vector2f origin = sf::Vector2f(0,0);
    sf::Vector2f scale = sf::Vector2f(1, 1);
    sf::IntRect currentFrame;
    sf::Texture* tex;

    // Drawable interface
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // ENTITY_H
