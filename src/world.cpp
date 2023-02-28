#include "world.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include "states/game_state.h"
#include <iostream>

World::World(sf::RenderWindow& outputTarget, FontHolder& fonts, SoundPlayer& sounds)
    : mTarget(outputTarget)
    , mTextures()
    , mFonts(fonts)
    , mSounds(sounds)

{
    loadTextures();

    balls[0] = {Ball(sf::Vector2f(0, 0), &mTextures.get(Textures::Ball), &mTextures.get(Textures::Point), &mTextures.get(Textures::Powermeter_FG), &mTextures.get(Textures::Powermeter_BG), 0)};
    balls[1] = {Ball(sf::Vector2f(0, 0), &mTextures.get(Textures::Ball), &mTextures.get(Textures::Point), &mTextures.get(Textures::Powermeter_FG), &mTextures.get(Textures::Powermeter_BG), 1)};
    holes = {Hole(sf::Vector2f(0, 0), &mTextures.get(Textures::Hole)), Hole(sf::Vector2f(0, 0), &mTextures.get(Textures::Hole))};

    level = 0;
    tiles = loadTiles(level);
    gameRunning = true;
    mouseDown = false;
    mousePressed = false;

    swingPlayed = false;
    secondSwingPlayed = false;

    loadLevel(3);
}

void World::update(sf::Time time)
{
    //std::cout << "Time " << time.asSeconds();
    for (Ball& b : balls)
    {
        b.update(time, mouseDown, mousePressed, tiles, holes);//, chargeSfx, swingSfx, holeSfx);
    }
    if (balls[0].getScale().x < -1 && balls[1].getScale().x < -1)
    {
        level++;
        loadLevel(level);
    }
}

void World::draw()
{
    mTarget.clear();
    sf::Sprite bgSprite(mTextures.get(Textures::BG));
    mTarget.draw(bgSprite);

    for (Hole& h : holes)
    {
        mTarget.draw(h);
    }
    for (Ball& b : balls)
    {
        if (!b.isWin())
        {
            sf::Sprite ballShadow;
            ballShadow.setTexture(mTextures.get(Textures::Ball_Shadow));
            ballShadow.setPosition(b.getPos().x, b.getPos().y+4);
            ballShadow.setRotation(b.getAngle());
            mTarget.draw(ballShadow);
        }
        for (Entity& e : b.getPoints())
        {
            mTarget.draw(e);
        }
        mTarget.draw(b);
    }
    for (Tile& t : tiles)
    {
        mTarget.draw(t);
    }
    for (Ball& b : balls)
    {
        for (Entity& e : b.getPowerBar())
        {
            //window.render(e);
            mTarget.draw(e);
        }
        //window.render(b.getPowerBar().at(0).getPos().x, b.getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);
        sf::Sprite powermeterOverlaySprite;
        powermeterOverlaySprite.setPosition(b.getPowerBar().at(0).getPos().x, b.getPowerBar().at(0).getPos().y);
        mTarget.draw(powermeterOverlaySprite);
    }

    mTarget.display();
}

void World::processInput(const sf::Event &event)
{
    mousePressed = false;
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Button::Left)
        {
            std::cout << "Mouse Pressed " << std::endl;
            mouseDown = true;
            mousePressed = true;
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Button::Left)
        {
            std::cout << "Mouse Released " << std::endl;
            mouseDown = false;
        }
    }
}

void World::loadTextures()
{
    //mTextures.load(Textures::Blocks,             "res/blocks.png");
    mTextures.load(Textures::Ball,               "res/sprite/ball.png");
    mTextures.load(Textures::Hole,               "res/sprite/hole.png");
    mTextures.load(Textures::Point,              "res/sprite/point.png");
    mTextures.load(Textures::Tile_Dark32,        "res/sprite/tile32_dark.png");
    mTextures.load(Textures::Tile_Dark64,        "res/sprite/tile64_dark.png");
    mTextures.load(Textures::Tile_Light32,       "res/sprite/tile32_light.png");
    mTextures.load(Textures::Tile_Light64,       "res/sprite/tile64_light.png");
    mTextures.load(Textures::Ball_Shadow,        "res/sprite/ball_shadow.png");
    mTextures.load(Textures::BG,                 "res/sprite/bg.png");
    mTextures.load(Textures::UI_BG,              "res/sprite/UI_bg.png");
    mTextures.load(Textures::LevelText,          "res/sprite/levelText_bg.png");
    mTextures.load(Textures::Powermeter_FG,      "res/sprite/powermeter_fg.png");
    mTextures.load(Textures::Powermeter_BG,      "res/sprite/powermeter_bg.png");
    mTextures.load(Textures::Powermeter_Overlay, "res/sprite/powermeter_overlay.png");
    mTextures.load(Textures::Logo,               "res/sprite/logo.png");
    mTextures.load(Textures::Click2Start,        "res/sprite/click2start.png");
    mTextures.load(Textures::End,                "res/sprite/end.png");
    mTextures.load(Textures::Splsh_BG,           "res/sprite/splashBg.png");
}

std::vector<Tile> World::loadTiles(int level)
{
    std::vector<Tile> temp = {};
    switch(level)
    {
        case 0:
            temp.push_back(Tile(sf::Vector2f(64*3, 64*3), &mTextures.get(Textures::Tile_Dark64)));
            temp.push_back(Tile(sf::Vector2f(64*4, 64*3), &mTextures.get(Textures::Tile_Dark64)));

            temp.push_back(Tile(sf::Vector2f(64*0, 64*3), &mTextures.get(Textures::Tile_Dark64)));
            temp.push_back(Tile(sf::Vector2f(64*1, 64*3), &mTextures.get(Textures::Tile_Dark64)));

            temp.push_back(Tile(sf::Vector2f(64*3 + 64*5, 64*3), &mTextures.get(Textures::Tile_Light64)));
            temp.push_back(Tile(sf::Vector2f(64*4 + 64*5, 64*3), &mTextures.get(Textures::Tile_Light64)));

            temp.push_back(Tile(sf::Vector2f(64*0 + 64*5, 64*3), &mTextures.get(Textures::Tile_Light64)));
            temp.push_back(Tile(sf::Vector2f(64*1 + 64*5, 64*3), &mTextures.get(Textures::Tile_Light64)));
        break;
        case 1:
            temp.push_back(Tile(sf::Vector2f(64*2, 64*3), &mTextures.get(Textures::Tile_Dark64)));

            temp.push_back(Tile(sf::Vector2f(64*4 + 64*5, 64*3), &mTextures.get(Textures::Tile_Light64)));
        break;
        case 2:
            temp.push_back(Tile(sf::Vector2f(32*1 + 32*10 + 16, 32*5), &mTextures.get(Textures::Tile_Light32)));
        break;
        case 3:
            temp.push_back(Tile(sf::Vector2f(32*4, 32*7), &mTextures.get(Textures::Tile_Dark64)));
            temp.push_back(Tile(sf::Vector2f(32*3, 32*5), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*6, 32*3), &mTextures.get(Textures::Tile_Dark32)));

            temp.push_back(Tile(sf::Vector2f(32*4 + 64*5, 32*2), &mTextures.get(Textures::Tile_Light64)));
            temp.push_back(Tile(sf::Vector2f(32*3 + 32*10, 32*6), &mTextures.get(Textures::Tile_Light32)));
            temp.push_back(Tile(sf::Vector2f(32*6 + 32*10, 32*9), &mTextures.get(Textures::Tile_Light32)));
        break;
        case 4:
            temp.push_back(Tile(sf::Vector2f(32*3, 32*1), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*1, 32*3), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*5, 32*3), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*3, 32*5), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*7, 32*5), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*7, 32*10), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*3, 32*10), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*5, 32*12), &mTextures.get(Textures::Tile_Dark32)));
            temp.push_back(Tile(sf::Vector2f(32*7, 32*10), &mTextures.get(Textures::Tile_Dark32)));

            //temp.push_back(Tile(Vector2f(32*4, 32*7), &mTextures.get(Textures::Tile_Dark64)));
            temp.push_back(Tile(sf::Vector2f(32*8, 32*7), &mTextures.get(Textures::Tile_Dark64)));

            temp.push_back(Tile(sf::Vector2f(32*2 + 32*10, 32*2), &mTextures.get(Textures::Tile_Light32)));
            temp.push_back(Tile(sf::Vector2f(32*5 + 32*10, 32*11), &mTextures.get(Textures::Tile_Light32)));

            temp.push_back(Tile(sf::Vector2f(32*3 + 32*10, 32*1), &mTextures.get(Textures::Tile_Light64)));
            temp.push_back(Tile(sf::Vector2f(32*8 + 32*10, 32*6), &mTextures.get(Textures::Tile_Light64)));
            temp.push_back(Tile(sf::Vector2f(32*3 + 32*10, 32*11), &mTextures.get(Textures::Tile_Light64)));
        break;
    }
    return temp;
}

void World::loadLevel(int level)
{
    if (level > 4)
    {
        state = 2;
        return;
    }
    balls[0].setVelocity(0, 0);
    balls[1].setVelocity(0,0);
    balls[0].setScale(1, 1);
    balls[1].setScale(1, 1);
    balls[0].setWin(false);
    balls[1].setWin(false);

    tiles = loadTiles(level);

    switch (level)
    {
        case 0:
            balls[0].setPos(24 + 32*4, 24 + 32*11);
            balls[1].setPos(24 + 32*4 + 32*10, 24 + 32*11);

            holes.at(0).setPos(24 + 32*4, 22 + 32*2);
            holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*2);
        break;
        case 1:
            balls[0].setPos(24 + 32*4, 24 + 32*11);
            balls[1].setPos(24 + 32*4 + 32*10, 24 + 32*11);

            holes.at(0).setPos(24 + 32*4, 22 + 32*2);
            holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*2);
        break;
        case 2:
            balls[0].setPos(8 + 32*7, 8 + 32*10);
            balls[1].setPos(8 + 32*7 + 32*10, 8 + 32*10);

            holes.at(0).setPos(8 + 32*2, 6 + 32*5);
            holes.at(1).setPos(8 + 32*4 + 32*10, 6 + 32*3);
        break;
        case 3:
            balls[0].setPos(24 + 32*4, 24 + 32*5);
            balls[1].setPos(24 + 32*4 + 32*10, 24 + 32*4);

            holes.at(0).setPos(24 + 32*4, 22 + 32*1);
            holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*11);
        break;
        case 4:
            balls[0].setPos(24 + 32*2, 24 + 32*12);
            balls[1].setPos(24 + 32*0 + 32*10, 24 + 32*5);

            holes.at(0).setPos(24 + 32*1, 22 + 32*1);
            holes.at(1).setPos(24 + 32*0 + 32*10, 22 + 32*7);
        break;
    }
}

