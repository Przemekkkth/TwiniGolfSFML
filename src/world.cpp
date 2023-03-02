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

    balls[0] = {new Ball(mTextures, sounds, 0)};
    balls[1] = {new Ball(mTextures, sounds, 1)};
    holes = { new Hole(mTextures, sf::Vector2f(0.0f, 0.0f)), new Hole(mTextures, sf::Vector2f(0.0f, 0.0f))};


    level = 0;
    tiles = loadTiles(level);
    gameRunning = true;
    mouseDown = false;
    mousePressed = false;

    swingPlayed = false;
    secondSwingPlayed = false;

    loadLevel(6);
}

World::~World()
{
    for(auto tile: tiles)
    {
        delete tile;
    }
    tiles.clear();

    for(auto hole : holes)
    {
        delete hole;
    }
    holes.clear();

    delete balls[0];
    delete balls[1];
}

void World::update(sf::Time time)
{
    if (!swingPlayed)
    {
        mSounds.play(SoundEffect::Swing);
        swingPlayed = true;
    }
    if (!secondSwingPlayed)
    {
        mSounds.play(SoundEffect::Swing);
        secondSwingPlayed = true;
    }
    for (Ball* b : balls)
    {
        b->update(time, mouseDown, mousePressed, tiles, holes);
    }
    if (balls[0]->getScale().x < 0.0f && balls[1]->getScale().x < 0.0f)
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

    for (Hole* h : holes)
    {
        mTarget.draw(*h);
    }
    for (Ball* b : balls)
    {
        if (!b->isWin())
        {
            sf::Sprite ballShadow;
            ballShadow.setTexture(mTextures.get(Textures::Ball_Shadow));
            ballShadow.setPosition(b->getPos().x, b->getPos().y+4);
            ballShadow.setRotation(b->getAngle());
            mTarget.draw(ballShadow);
        }

        mTarget.draw(*b->getPoint());
        mTarget.draw(*b);
    }
    for (Tile* t : tiles)
    {
        mTarget.draw(*t);
    }
    for(Ball* b : balls)
    {
        mTarget.draw(*b->getPowerBar());
    }

    drawUI();
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
            mSounds.play(SoundEffect::Swing);
        }
    }
}

bool World::isWinActivated()
{
    if(state == 2)
    {
        return true;
    }
    return false;
}

void World::loadTextures()
{
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
}

void World::loadFonts()
{

}

void World::drawUI()
{
    sf::Sprite levelBGLeftTex;
    levelBGLeftTex.setTexture(mTextures.get(Textures::LevelText));
    levelBGLeftTex.setPosition(640/4 - 132/2, 480 - 32);
    mTarget.draw(levelBGLeftTex);

    sf::Text levelTextBlack0;
    levelTextBlack0.setFont(mFonts.get(Fonts::Main));
    levelTextBlack0.setCharacterSize(24);
    levelTextBlack0.setFillColor(sf::Color::Black);
    levelTextBlack0.setString(getLevelText(0));
    levelTextBlack0.setOrigin(levelTextBlack0.getLocalBounds().width/2.0f, levelTextBlack0.getLocalBounds().height/2.0f);
    levelTextBlack0.setPosition(160, 467);
    mTarget.draw(levelTextBlack0);

    sf::Text levelTextWhite0;
    levelTextWhite0.setFont(mFonts.get(Fonts::Main));
    levelTextWhite0.setCharacterSize(24);
    levelTextWhite0.setFillColor(sf::Color::White);
    levelTextWhite0.setString(getLevelText(0));
    levelTextWhite0.setOrigin(levelTextWhite0.getLocalBounds().width/2.0f, levelTextWhite0.getLocalBounds().height/2.0f);
    levelTextWhite0.setPosition(160, 464);
    mTarget.draw(levelTextWhite0);

    sf::Sprite levelBGRightTex;
    levelBGRightTex.setTexture(mTextures.get(Textures::LevelText));
    levelBGRightTex.setPosition(640/2 + 640/4 - 132/2, 480 - 32);
    mTarget.draw(levelBGRightTex);

    sf::Text levelTextBlack1;
    levelTextBlack1.setFont(mFonts.get(Fonts::Main));
    levelTextBlack1.setCharacterSize(24);
    levelTextBlack1.setFillColor(sf::Color::Black);
    levelTextBlack1.setString(getLevelText(1));
    levelTextBlack1.setOrigin(levelTextBlack1.getLocalBounds().width/2.0f, levelTextBlack1.getLocalBounds().height/2.0f);
    levelTextBlack1.setPosition(480, 467);
    mTarget.draw(levelTextBlack1);

    sf::Text levelTextWhite1;
    levelTextWhite1.setFont(mFonts.get(Fonts::Main));
    levelTextWhite1.setCharacterSize(24);
    levelTextWhite1.setFillColor(sf::Color::White);
    levelTextWhite1.setString(getLevelText(1));
    levelTextWhite1.setOrigin(levelTextWhite1.getLocalBounds().width/2.0f, levelTextWhite1.getLocalBounds().height/2.0f);
    levelTextWhite1.setPosition(480, 464);
    mTarget.draw(levelTextWhite1);

    sf::Sprite uiBGTex;
    uiBGTex.setTexture(mTextures.get(Textures::UI_BG));
    uiBGTex.setPosition(640/2 - 196/2, 0);
    mTarget.draw(uiBGTex);

    sf::Text strokeBlackText;
    strokeBlackText.setFont(mFonts.get(Fonts::Main));
    strokeBlackText.setCharacterSize(24);
    strokeBlackText.setFillColor(sf::Color::Black);
    strokeBlackText.setString(getStrokeText());
    strokeBlackText.setOrigin(strokeBlackText.getLocalBounds().width/2.0f, strokeBlackText.getLocalBounds().height/2.0f);
    strokeBlackText.setPosition(320, 16);
    mTarget.draw(strokeBlackText);

    sf::Text strokeWhiteText;
    strokeWhiteText.setFont(mFonts.get(Fonts::Main));
    strokeWhiteText.setCharacterSize(24);
    strokeWhiteText.setFillColor(sf::Color::White);
    strokeWhiteText.setString(getStrokeText());
    strokeWhiteText.setOrigin(strokeWhiteText.getLocalBounds().width/2.0f, strokeWhiteText.getLocalBounds().height/2.0f);
    strokeWhiteText.setPosition(320, 13);
    mTarget.draw(strokeWhiteText);
}

std::vector<Tile *> World::loadTiles(int level)
{
    std::vector<Tile*> temp = {};
    switch(level)
    {
        case 0:
            temp.push_back(new Tile(mTextures, sf::Vector2f(64*3, 64*3), Tile::Type::Dark64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(64*4, 64*3), Tile::Type::Dark64));

            temp.push_back(new Tile(mTextures, sf::Vector2f(64*0, 64*3), Tile::Type::Dark64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(64*1, 64*3), Tile::Type::Dark64));

            temp.push_back(new Tile(mTextures, sf::Vector2f(64*3 + 64*5, 64*3), Tile::Type::Light64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(64*4 + 64*5, 64*3), Tile::Type::Light64));

            temp.push_back(new Tile(mTextures, sf::Vector2f(64*0 + 64*5, 64*3), Tile::Type::Light64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(64*1 + 64*5, 64*3), Tile::Type::Light64));
        break;
        case 1:
            temp.push_back(new Tile(mTextures, sf::Vector2f(64*2, 64*3), Tile::Type::Dark64));

            temp.push_back(new Tile(mTextures, sf::Vector2f(64*4 + 64*5, 64*3), Tile::Type::Light64));
        break;
        case 2:
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*1 + 32*10 + 16, 32*5), Tile::Type::Light32));
        break;
        case 3:
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*4, 32*7), Tile::Type::Dark64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*3, 32*5), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*6, 32*3), Tile::Type::Dark32));

            temp.push_back(new Tile(mTextures, sf::Vector2f(32*4 + 64*5, 32*2), Tile::Type::Light64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*3 + 32*10, 32*6), Tile::Type::Light32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*6 + 32*10, 32*9), Tile::Type::Light32));
        break;
        case 4:
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*3, 32*1), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*1, 32*3), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*5, 32*3), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*3, 32*5), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*7, 32*5), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*7, 32*10), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*3, 32*10), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*5, 32*12), Tile::Type::Dark32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*7, 32*10), Tile::Type::Dark32));

            temp.push_back(new Tile(mTextures, sf::Vector2f(32*8, 32*7), Tile::Type::Dark64));

            temp.push_back(new Tile(mTextures, sf::Vector2f(32*2 + 32*10, 32*2), Tile::Type::Light32));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*5 + 32*10, 32*11), Tile::Type::Light32));

            temp.push_back(new Tile(mTextures, sf::Vector2f(32*3 + 32*10, 32*1), Tile::Type::Light64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*8 + 32*10, 32*6), Tile::Type::Light64));
            temp.push_back(new Tile(mTextures, sf::Vector2f(32*3 + 32*10, 32*11), Tile::Type::Light64));
        break;
    case 5:
        //Left
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*0, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*1, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*2, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*3, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*4, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*5, 32*3), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*6, 32*3), Tile::Type::Dark32));

        temp.push_back(new Tile(mTextures, sf::Vector2f(32*3, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*4, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*5, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*6, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*7, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*8, 32*6), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*9, 32*6), Tile::Type::Dark32));

        temp.push_back(new Tile(mTextures, sf::Vector2f(32*0, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*1, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*2, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*6, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*7, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*8, 32*10), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*9, 32*10), Tile::Type::Dark32));

        //Right
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*0 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*1 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*2 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*3 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*4 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*5 + 32*10, 32*3), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*6 + 32*10, 32*3), Tile::Type::Light32));

        temp.push_back(new Tile(mTextures, sf::Vector2f(32*3 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*4 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*5 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*6 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*7 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*8 + 32*10, 32*6), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*9 + 32*10, 32*6), Tile::Type::Light32));

        temp.push_back(new Tile(mTextures, sf::Vector2f(32*0 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*1 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*2 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*6 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*7 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*8 + 32*10, 32*10), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*9 + 32*10, 32*10), Tile::Type::Light32));
        break;
     case 6:
        //Left
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*4, 32*6), Tile::Type::Dark64));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*2, 32*4), Tile::Type::Dark32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*7, 32*9), Tile::Type::Dark32));
        //Right
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*4 + 32*10, 32*6), Tile::Type::Light64));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*2 + 32*10, 32*4), Tile::Type::Light32));
        temp.push_back(new Tile(mTextures, sf::Vector2f(32*7 + 32*10, 32*9), Tile::Type::Light32));

        break;
    }
    return temp;
}

void World::loadLevel(int level)
{
    if (level > 6)
    {
        state = 2;
        return;
    }
    balls[0]->setVelocity(0, 0);
    balls[1]->setVelocity(0,0);
    balls[0]->setScale(1, 1);
    balls[1]->setScale(1, 1);
    balls[0]->setWin(false);
    balls[1]->setWin(false);

    tiles = loadTiles(level);

    switch (level)
    {
        case 0:
            balls[0]->setPos(24 + 32*4, 24 + 32*11);
            balls[1]->setPos(24 + 32*4 + 32*10, 24 + 32*11);

            holes.at(0)->setPos(24 + 32*4, 22 + 32*2);
            holes.at(1)->setPos(24 + 32*4 + 32*10, 22 + 32*2);
        break;
        case 1:
            balls[0]->setPos(24 + 32*4, 24 + 32*11);
            balls[1]->setPos(24 + 32*4 + 32*10, 24 + 32*11);

            holes.at(0)->setPos(24 + 32*4, 22 + 32*2);
            holes.at(1)->setPos(24 + 32*4 + 32*10, 22 + 32*2);
        break;
        case 2:
            balls[0]->setPos(8 + 32*7, 8 + 32*10);
            balls[1]->setPos(8 + 32*7 + 32*10, 8 + 32*10);

            holes.at(0)->setPos(8 + 32*2, 6 + 32*5);
            holes.at(1)->setPos(8 + 32*4 + 32*10, 6 + 32*3);
        break;
        case 3:
            balls[0]->setPos(24 + 32*4, 24 + 32*5);
            balls[1]->setPos(24 + 32*4 + 32*10, 24 + 32*4);

            holes.at(0)->setPos(24 + 32*4, 22 + 32*1);
            holes.at(1)->setPos(24 + 32*4 + 32*10, 22 + 32*11);
        break;
        case 4:
            balls[0]->setPos(24 + 32*2, 24 + 32*12);
            balls[1]->setPos(24 + 32*0 + 32*10, 24 + 32*5);

            holes.at(0)->setPos(24 + 32*1, 22 + 32*1);
            holes.at(1)->setPos(24 + 32*0 + 32*10, 22 + 32*7);
        break;
        case 5:
            balls[0]->setPos(24 + 32*8, 24 + 32*12);
            holes.at(0)->setPos(24 + 32*1, 22 + 32*1);

            holes.at(1)->setPos(24 + 32*8 + 32*10, 24 + 32*12);
            balls[1]->setPos(24 + 32*0 + 32*10, 22 + 32*1);

        break;
    case 6:
        balls[0]->setPos(32*2+8, 32*9+8);
        holes.at(0)->setPos(32*7+8, 32*4+8);

        balls[1]->setPos(32*7+8 + 32*10, 32*4+8);
        holes.at(1)->setPos(32*2+8+32*10, 32*9+8);
    break;
    }
}

sf::String World::getStrokeText()
{
    int biggestStroke = 0;
    if (balls[1]->getStrokes() > balls[0]->getStrokes())
    {
        biggestStroke = balls[1]->getStrokes();
    }
    else
    {
        biggestStroke = balls[0]->getStrokes();
    }
    std::string s = std::to_string(biggestStroke);
    s = "STROKES: " + s;
    sf::String retVal = sf::String(s);
    return retVal;
}

sf::String World::getLevelText(int side)
{
    int tempLevel = (level + 1)*2 - 1;
    if (side == 1)
    {
        tempLevel++;
    }
    std::string s = std::to_string(tempLevel);
    s = "HOLE: " + s;
    sf::String retVal = sf::String(s);
    return retVal;
}

