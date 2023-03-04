#ifndef LEVELSTATE_H
#define LEVELSTATE_H
#include "state.h"
#include <SFML/Graphics/Sprite.hpp>
#include "../GUI/container.h"

class LevelState : public State
{
public:
    LevelState(StateStack& stack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event &event) override;
private:
    sf::Sprite              mTitleStringSprite;
    GUI::Container			mGUIContainer;
};

#endif // LEVELSTATE_H
