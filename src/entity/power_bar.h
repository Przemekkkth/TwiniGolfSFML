#ifndef POWERBAR_H
#define POWERBAR_H
#include "entity.h"
#include "../utils/resource_identifiers.h"

class PowerBar : public Entity
{
public:
    PowerBar(const TextureHolder& textHolder);

    // Drawable interface
    sf::Texture overlayTex, foregroundTex;
    void setFGScale(float x, float y);
    sf::Vector2f getFGScale() const;
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    sf::Vector2f fgScale = sf::Vector2f(1, 1);
};

#endif // POWERBAR_H
