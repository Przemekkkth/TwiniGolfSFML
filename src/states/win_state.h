#ifndef WINSTATE_H
#define WINSTATE_H
#include "state.h"

class WinState : public State
{
public:
                        WinState(StateStack& stack, Context context);
    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);
};

#endif // WINSTATE_H
