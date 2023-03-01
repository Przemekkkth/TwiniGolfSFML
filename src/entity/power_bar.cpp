#include "power_bar.h"
#include "../utils/resource_holder.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

PowerBar::PowerBar(const TextureHolder &textHolder)
{
    //BG
    setTex(textHolder.get(Textures::Powermeter_BG));
    //FG
    foregroundTex = textHolder.get(Textures::Powermeter_FG);
    //Overlay
    overlayTex = textHolder.get(Textures::Powermeter_Overlay);
}

void PowerBar::setFGScale(float x, float y)
{
    fgScale.x = x;
    fgScale.y = y;
}

sf::Vector2f PowerBar::getFGScale() const
{
    return fgScale;
}

void PowerBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite bgSprite;
    bgSprite.setTexture(tex);
    bgSprite.setOrigin(getOrigin());
    bgSprite.setPosition(getPos());
    bgSprite.setScale(getScale());
    bgSprite.setRotation(getAngle());
    target.draw(bgSprite, states);


    sf::Sprite overlaySprite;
    overlaySprite.setTexture(tex);
    overlaySprite.setOrigin(getOrigin());
    overlaySprite.setPosition(getPos());
    overlaySprite.setScale(getScale());
    overlaySprite.setRotation(getAngle());
    target.draw(overlaySprite, states);

    sf::Sprite fgSprite;
    fgSprite.setTexture(foregroundTex);
    fgSprite.setOrigin(getOrigin());
    fgSprite.setPosition(getPos().x+4, getPos().y+4+32-32*getFGScale().y);
    if( getFGScale().y < 0.25f)
    {
        fgSprite.setColor(sf::Color::Green);
    }
    else if( getFGScale().y > 0.25 && getFGScale().y < 0.75)
    {

        fgSprite.setColor(sf::Color::Yellow);
    }
    else
    {
        fgSprite.setColor(sf::Color::Red);
    }

    fgSprite.setScale(getFGScale());
    fgSprite.setRotation(getAngle());
    target.draw(fgSprite, states);


}
