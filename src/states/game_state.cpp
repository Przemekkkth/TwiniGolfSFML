#include "game_state.h"
#include "../SFX/music_player.h"
#include <SFML/Graphics/RenderWindow.hpp>

int GameState::choosenLevel = 4;
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
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause);

    //Uncomment if you want to make screenshot after P
//    if(event.key.code == sf::Keyboard::P)
//    {
//        sf::RenderWindow& window = *getContext().window;
//        static int index = 0;
//        sf::Texture texture;
//        texture.create(window.getSize().x, window.getSize().y);
//        texture.update(window);
//        std::string filename = "gameover" + std::to_string(index) + ".png";
//        if (texture.copyToImage().saveToFile(filename))
//        {
//            index++;
//        }
//    }
    mWorld.processInput(event);
    return true;
}
