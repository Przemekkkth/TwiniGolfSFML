#include "menu_state.h"

#include "../GUI/button.h"
#include "../utils/resource_holder.h"
#include "../SFX/music_player.h"
#include "../application.h"
#include "game_state.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mGUIContainer()
{
    sf::Texture& texture = context.textures->get(Textures::Title);
    mTitleStringSprite.setTexture(texture);
    mTitleStringSprite.setPosition(30, 30);

    auto monominoButton = std::make_shared<GUI::Button>(context);
    monominoButton->setPosition(230, 200);
    monominoButton->setText("Play");
    monominoButton->setCallback([this] ()
    {
        GameState::choosenLevel = 3;
        requestStackPop();
        requestStackPush(States::Game);
    });


    auto levelsButton = std::make_shared<GUI::Button>(context);
    levelsButton->setPosition(230, 275);
    levelsButton->setText("Levels");
    levelsButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Levels);
    });

    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(230, 350);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });



    mGUIContainer.pack(monominoButton);
    mGUIContainer.pack(levelsButton);
    mGUIContainer.pack(exitButton);

}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mTitleStringSprite);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
}
