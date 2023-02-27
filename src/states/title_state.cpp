#include "title_state.h"
#include "../utils/resource_holder.h"
#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context)
, mText()
, mShowText(true)
, mTextEffectTime(sf::Time::Zero)
{
    mTitleSprite.setTexture(context.textures->get(Textures::PolyominoString));
    mTitleSprite.setPosition(30, 30);

    mSFMLlogoSprite.setTexture(context.textures->get(Textures::SFMLlogo));
    mSFMLlogoSprite.setOrigin(mSFMLlogoSprite.getLocalBounds().width/2.0f,
                              mSFMLlogoSprite.getLocalBounds().height/2.0f);
    mSFMLlogoSprite.setPosition(300,300);

    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString("Press any key to start");
    mText.setOrigin(mText.getLocalBounds().width/2.0f,
                    mText.getLocalBounds().height/2.0f);

    mText.setPosition(context.window->getView().getSize().x / 2.f, 550.0f);
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(mTitleSprite);
    window.draw(mSFMLlogoSprite);
    if (mShowText)
        window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;

    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}
