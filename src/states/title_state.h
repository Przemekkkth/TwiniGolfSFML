#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "state.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
    public:
                            TitleState(StateStack& stack, Context context);

        virtual void		draw();
        virtual bool		update(sf::Time dt);
        virtual bool		handleEvent(const sf::Event& event);


    private:
        sf::Sprite mTitleSprite, mSFMLlogoSprite;
        sf::Text			mText;

        bool				mShowText;
        sf::Time			mTextEffectTime;
};
#endif // TITLESCREEN_H
