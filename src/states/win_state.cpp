#include "win_state.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../utils/resource_holder.h"
#include "game_state.h"

WinState::WinState(StateStack& stack, Context context)
    : State(stack, context), mShowText(true), mTextEffectTime(sf::Time::Zero)
{
    mTitleSprite.setTexture(context.textures->get(Textures::Title));
    mTitleSprite.setPosition(30, 30);

    mInfoText.setFont(context.fonts->get(Fonts::Main));
    mInfoText.setCharacterSize(32);
    mInfoText.setFillColor(sf::Color::White);
    mInfoText.setString("          Congratulation !!! \n"
                        "You are master of Twini-Golf");
    mInfoText.setOrigin(mInfoText.getLocalBounds().width/2,
                        mInfoText.getLocalBounds().height/2);
    mInfoText.setPosition(320, 240);

    mResult.setFont(context.fonts->get(Fonts::Main));
    mResult.setCharacterSize(24);
    mResult.setFillColor(sf::Color::White);
    mResult.setString("Result: " + GameState::score);
    mResult.setOrigin(mResult.getLocalBounds().width/2, mResult.getLocalBounds().height/2);
    mResult.setPosition(320, 300);

    mPressText.setFont(context.fonts->get(Fonts::Main));
    mPressText.setCharacterSize(24);
    mPressText.setString("Press any key to go menu");
    mPressText.setOrigin(mPressText.getLocalBounds().width/2.0f,
                         mPressText.getLocalBounds().height/2.0f);
    mPressText.setPosition(320, 400);
}

void WinState::draw()
{
    sf::RenderWindow* renderWindow = getContext().window;
    renderWindow->draw(mTitleSprite);
    renderWindow->draw(mResult);
    renderWindow->draw(mInfoText);
    if (mShowText)
        renderWindow->draw(mPressText);
}

bool WinState::update(sf::Time dt)
{
    mTextEffectTime += dt;

    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }

    return true;
}

bool WinState::handleEvent(const sf::Event &event)
{
    // If any key is released, trigger the menu screen
    if (event.type == sf::Event::KeyReleased)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}

