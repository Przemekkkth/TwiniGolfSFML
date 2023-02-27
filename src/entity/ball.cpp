#include "ball.h"
#include <vector>
#include <cmath>
#include <SFML/Window/Mouse.hpp>

Ball::Ball(sf::Vector2f p_pos, sf::Texture* p_tex, sf::Texture* p_pointTex, sf::Texture* p_powerMTexFG, sf::Texture* p_powerMTexBG, int p_index)
: Entity(p_pos, p_tex)
{
    index = p_index;
    points.push_back(Entity(sf::Vector2f(-64, -64), p_pointTex));
    powerBar.push_back(Entity(sf::Vector2f(-64, -64), p_powerMTexBG));
    powerBar.push_back(Entity(sf::Vector2f(-64, -64), p_powerMTexFG));
}

Ball::Ball() : Entity()
{

}

void Ball::init(sf::Vector2f p_pos, sf::Texture *p_tex, sf::Texture *p_pointTex, sf::Texture *p_powerMTexFG, sf::Texture *p_powerMTexBG, int p_index)
{
    index = p_index;
    points.push_back(Entity(sf::Vector2f(-64, -64), p_pointTex));
    powerBar.push_back(Entity(sf::Vector2f(-64, -64), p_powerMTexBG));
    powerBar.push_back(Entity(sf::Vector2f(-64, -64), p_powerMTexFG));
    setPos(p_pos.x, p_pos.y);
    setTex(p_tex);
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

void Ball::update(sf::Time deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile> tiles,std::vector<Hole> holes)//, Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx, Mix_Chunk* holeSfx)
{
    if (win)
    {
        if (getPos().x < target.x)
        {
            setPos(getPos().x += 0.1*deltaTime.asSeconds(), getPos().y);
        }
        else if (getPos().x > target.x)
        {
            setPos(getPos().x -= 0.1*deltaTime.asSeconds(), getPos().y);
        }
        if (getPos().y < target.y)
        {
            setPos(getPos().x, getPos().y += 0.1*deltaTime.asSeconds());
        }
        else if (getPos().y > target.y)
        {
            setPos(getPos().x, getPos().y -= 0.1*deltaTime.asSeconds());
        }
        setScale(getScale().x - 0.001*deltaTime.asSeconds(), getScale().y - 0.001*deltaTime.asSeconds());
        return;
    }

    for (Hole h : holes)
    {
        if (getPos().x + 4 > h.getPos().x && getPos().x + 16 < h.getPos().x + 20 && getPos().y + 4 > h.getPos().y && getPos().y + 16 < h.getPos().y + 20)
        {
            //Mix_PlayChannel(-1, holeSfx, 0);
            setWin(true);
            target.x = h.getPos().x ;
            target.y = h.getPos().y + 3;
        }
    }

    if (mousePressed && canMove)
    {
        //Mix_PlayChannel(-1, chargeSfx, 0);
        playedSwingFx = false;
        int mouseX = 0;
        int mouseY = 0;
        //SDL_GetMouseState(&mouseX, &mouseY);
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        mouseX = mousePos.x;
        mouseY = mousePos.y;

        setInitialMousePos(mouseX, mouseY);
    }
    if (mouseDown && canMove)
    {

        int mouseX = 0;
        int mouseY = 0;
        //SDL_GetMouseState(&mouseX, &mouseY);
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        mouseX = mousePos.x;
        mouseY = mousePos.y;
        setVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        setLaunchedVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        velocity1D = std::sqrt(std::pow(std::abs(getVelocity().x), 2) + std::pow(std::abs(getVelocity().y), 2));
        launchedVelocity1D = velocity1D;

        points.at(0).setPos(getPos().x, getPos().y + 8 - 32);
        points.at(0).setAngle(std::atan2(velocity.y, velocity.x)*(180/3.1415) + 90);

        dirX = velocity.x/std::abs(velocity.x);
        dirY = velocity.y/std::abs(velocity.y);

        powerBar.at(0).setPos(getPos().x + 32 + 8, getPos().y - 32);
        powerBar.at(1).setPos(getPos().x + 32 + 8 + 4, getPos().y - 32 + 4 + 32 - 32*powerBar.at(1).getScale().y);
        if (velocity1D > 1)
        {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
        powerBar.at(1).setScale(1, velocity1D/1);
    }
    else
    {
        if (!playedSwingFx)
        {
            //Mix_PlayChannel(-1, swingSfx, 0);
            playedSwingFx = true;
            strokes++;
        }
        points.at(0).setPos(-64, -64);
        powerBar.at(0).setPos(-64, -64);
        powerBar.at(1).setPos(-64, -64);
        canMove = false;
        setPos(getPos().x + getVelocity().x*deltaTime.asSeconds(), getPos().y + getVelocity().y*deltaTime.asSeconds());
        if (getVelocity().x > 0.0001 || getVelocity().x < -0.0001 || getVelocity().y > 0.0001 || getVelocity().y < -0.0001)
        {
            //float xDir = velocity.x/abs(velocity.x);
            //float yDir = velocity.y/abs(velocity.y);

            //velocity.x = (abs(velocity.x) - friction*deltaTime.asSeconds())*xDir;
            //velocity.y = (abs(velocity.y) - friction*deltaTime.asSeconds())*yDir;
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
            //SDL_GetMouseState(&mouseX, &mouseY);
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

        for (Tile& t : tiles)
        {
            float newX = getPos().x + getVelocity().x*deltaTime.asSeconds();
            float newY = getPos().y;
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().width && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().height - 3)
            {
                setVelocity(getVelocity().x*-1, getVelocity().y);
                dirX *= -1;
            }

            newX = getPos().x;
            newY = getPos().y + getVelocity().y*deltaTime.asSeconds();
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().width && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().height - 3)
            {
                setVelocity(getVelocity().x, getVelocity().y*-1);
                dirY *= -1;
            }
        }
    }

}
