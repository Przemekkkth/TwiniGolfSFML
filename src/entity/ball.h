#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "hole.h"
#include "tile.h"
#include "../utils/resource_identifiers.h"
#include "../SFX/sound_player.h"
#include "point.h"
#include "power_bar.h"

class Ball : public Entity
{
public:
    Ball(const TextureHolder& textures, SoundPlayer &sounds, int _index);

    sf::Vector2f& getVelocity()
    {
        return velocity;
    }
    sf::Vector2f& getInitialMousePos()
    {
        return initialMousePos;
    }
    Point* getPoint()
    {
        return point;
    }
    PowerBar* getPowerBar() const
    {
        return powerBar;
    }

    int getStrokes()
    {
        return strokes;
    }
    bool isWin()
    {
        return win;
    }
    void setWin(bool p_win);
    void setInitialMousePos(float x, float y);
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    void update(sf::Time deltaTime, bool mouseDown, bool mousePressed, std::vector<Tile *> tiles, std::vector<Hole *> holes);//,Mix_Chunk* chargeSfx, Mix_Chunk* swingSfx, Mix_Chunk* holeSfx);
private:
    sf::Vector2f velocity;
    sf::Vector2f target;
    sf::Vector2f launchedVelocity;
    float velocity1D;
    float launchedVelocity1D;
    sf::Vector2f initialMousePos;
    bool canMove = true;
    bool playedSwingFx = true;
    int index;
    int strokes = 0;
    int dirX = 1;
    int dirY = 1;
    bool win = false;
    float friction = 0.001;
    Point* point;
    PowerBar* powerBar;
    SoundPlayer& mSound;
};

#endif // BALL_H
