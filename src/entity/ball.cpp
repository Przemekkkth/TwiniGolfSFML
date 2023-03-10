#include "ball.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/Window/Mouse.hpp>
#include "../SFX/sound_player.h"

Ball::Ball(const TextureHolder &textures, SoundPlayer &sounds, int _index)
    : mSound(sounds)
{
    setTex(textures.get(Textures::Ball));
    index = _index;
    point = new Point(textures);
    powerBar = new PowerBar(textures);

}


void Ball::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Ball::setLaunchedVelocity(float x, float y)
{
    launchedVelocity.x = x;
    launchedVelocity.y = y;
}

void Ball::setInitialMousePos(float x, float y)
{
    initialMousePos.x = x;
    initialMousePos.y = y;
}

void Ball::setWin(bool p_win)
{
    win = p_win;
}

void Ball::update(sf::Time deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile*> tiles,std::vector<Hole*> holes)
{
    deltaTime = sf::seconds(5.0f);
    if (win)
    {
        if (getPos().x < target.x)
        {
            setPos(getPos().x + 0.1*speed, getPos().y);
        }
        else if (getPos().x > target.x)
        {
            setPos(getPos().x - 0.1*speed, getPos().y);
        }
        if (getPos().y < target.y)
        {
            setPos(getPos().x, getPos().y + 0.1*speed);
        }
        else if (getPos().y > target.y)
        {
            setPos(getPos().x, getPos().y - 0.1*speed);
        }
        setScale(getScale().x - 0.001*speed, getScale().y - 0.001*speed);
        if(getScale().x < 0.001f)
        {
            setScale(-0.001f, getScale().y);
        }
        if(getScale().y < 0.001f)
        {
            setScale(getScale().x, -0.001f);
        }

        return;
    }

    for (Hole* h : holes)
    {
        if (getPos().x + 4 > h->getPos().x && getPos().x + 16 < h->getPos().x + 20 && getPos().y + 4 > h->getPos().y && getPos().y + 16 < h->getPos().y + 20)
        {
            mSound.play(SoundEffect::Hole);
            setWin(true);
            target.x = h->getPos().x ;
            target.y = h->getPos().y + 3;
        }
    }

    if (mousePressed && canMove)
    {
        mSound.play(SoundEffect::Charge);
        playedSwingFx = false;
        int mouseX = 0;
        int mouseY = 0;
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        mouseX = mousePos.x;
        mouseY = mousePos.y;

        setInitialMousePos(mouseX, mouseY);
    }
    if (mouseDown && canMove)
    {

        int mouseX = 0;
        int mouseY = 0;
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        mouseX = mousePos.x;
        mouseY = mousePos.y;
        setVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        setLaunchedVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        velocity1D = std::sqrt(std::pow(std::abs(getVelocity().x), 2) + std::pow(std::abs(getVelocity().y), 2));
        launchedVelocity1D = velocity1D;

        point->setPos(getPos().x + 8, getPos().y + 8 );// + 8 - 32);
        point->setAngle(std::atan2(velocity.y, velocity.x)*(180/3.1415) + 90);

        dirX = velocity.x/std::abs(velocity.x);
        dirY = velocity.y/std::abs(velocity.y);

        powerBar->setPos(getPos().x + 32 +  8, getPos().y - 32);
        if (velocity1D > 1)
        {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
        powerBar->setFGScale(1, velocity1D/1);
    }
    else
    {
        if (!playedSwingFx)
        {
            mSound.play(SoundEffect::Swing);
            playedSwingFx = true;
            strokes++;
        }
        point->setPos(-64, -64);
        powerBar->setPos(-64, -64);

        canMove = false;
        setPos(getPos().x + getVelocity().x*deltaTime.asSeconds(), getPos().y + getVelocity().y*deltaTime.asSeconds());
        if (getVelocity().x > 0.0001 || getVelocity().x < -0.0001 || getVelocity().y > 0.0001 || getVelocity().y < -0.0001)
        {
            if (velocity1D > 0)
            {
                velocity1D -= friction*deltaTime.asSeconds();
            }
            else
            {
                velocity1D = 0;
            }
            velocity.x = (velocity1D/launchedVelocity1D)*std::abs(launchedVelocity.x)*dirX;
            velocity.y = (velocity1D/launchedVelocity1D)*std::abs(launchedVelocity.y)*dirY;


        }
        else
        {
            setVelocity(0,0);
            int mouseX = 0;
            int mouseY = 0;
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            mouseX = mousePos.x;
            mouseY = mousePos.y;
            setInitialMousePos(mouseX, mouseY);
            canMove = true;
        }

        if (getPos().x + getCurrentFrame().width > 640/(2 - index))
        {
            setVelocity(-std::abs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        else if (getPos().x < 0 + (index*320))
        {
            setVelocity(std::abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        else if (getPos().y + getCurrentFrame().height > 480)
        {
            setVelocity(getVelocity().x, -std::abs(getVelocity().y));
            dirY = -1;
        }
        else if (getPos().y < 0)
        {
            setVelocity(getVelocity().x, std::abs(getVelocity().y));
            dirY = 1;
        }

        for (Tile* t : tiles)
        {
            float newX = getPos().x + getVelocity().x*deltaTime.asSeconds();
            float newY = getPos().y;
            if (newX + 16 > t->getPos().x && newX < t->getPos().x + t->getCurrentFrame().width && newY + 16 > t->getPos().y && newY < t->getPos().y + t->getCurrentFrame().height - 3)
            {
                setVelocity(getVelocity().x*-1, getVelocity().y);
                dirX *= -1;
            }

            newX = getPos().x;
            newY = getPos().y + getVelocity().y*deltaTime.asSeconds();
            if (newX + 16 > t->getPos().x && newX < t->getPos().x + t->getCurrentFrame().width && newY + 16 > t->getPos().y && newY < t->getPos().y + t->getCurrentFrame().height - 3)
            {
                setVelocity(getVelocity().x, getVelocity().y*-1);
                dirY *= -1;
            }
        }
    }

}
