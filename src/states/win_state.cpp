#include "win_state.h"

WinState::WinState(StateStack& stack, Context context)
: State(stack, context)
{

}

void WinState::draw()
{

}

bool WinState::update(sf::Time dt)
{

    return true;
}

bool WinState::handleEvent(const sf::Event &event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}

