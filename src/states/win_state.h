#ifndef WINSTATE_H
#define WINSTATE_H
#include "state.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class WinState : public State
{
public:
                        WinState(StateStack& stack, Context context);
    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);

private:
    sf::Sprite mTitleSprite;
    sf::Text   mInfoText;
    sf::Text   mPressText;

    bool				mShowText;
    sf::Time			mTextEffectTime;
};

#endif // WINSTATE_H
