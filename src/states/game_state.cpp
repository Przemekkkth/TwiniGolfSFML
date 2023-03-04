#include "game_state.h"
#include "../SFX/music_player.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

int GameState::choosenLevel = 0;
sf::String GameState::score;

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts, *context.sounds)
, mPlayer(*context.player)
{

}

void GameState::draw()
{
    mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);
    if(mWorld.isWinActivated())
    {
        requestStackPop();
        requestStackPush(States::Win);
    }
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::BackSpace)
        {
            requestStackPop();
            requestStackPush(States::Menu);
        }
    }

    mWorld.processInput(event);
    return true;
}
