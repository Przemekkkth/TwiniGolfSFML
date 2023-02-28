#ifndef WORLD_H
#define WORLD_H
#include "utils/resource_holder.h"
#include "utils/resource_identifiers.h"
#include "SFX/sound_player.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "entity/ball.h"
#include "entity/hole.h"
#include "entity/tile.h"
#include <vector>
#include <array>
#include <queue>


// Forward declaration
namespace sf
{
    class RenderTarget;
    class Event;
}

class World : private sf::NonCopyable
{
    public:
                                            World(sf::RenderWindow& outputTarget, FontHolder& fonts, SoundPlayer& sounds);
                                            ~World();
                                            void								update(sf::Time);
        void								draw();

        void processInput(const sf::Event& event);

    private:
        void								loadTextures();

    private:
        sf::RenderWindow&					mTarget;
        TextureHolder						mTextures;
        FontHolder&							mFonts;
        SoundPlayer&						mSounds;

        Ball *balls[2];
        std::vector<Hole*> holes;
        std::vector<Tile*> tiles;
        std::vector<Tile*> loadTiles(int level);
        bool gameRunning, mouseDown, mousePressed, swingPlayed, secondSwingPlayed;
        int level;
        int state;
        void loadLevel(int level);
        const char* getStrokeText();
        const char* getLevelText(int state);
};
#endif // WORLD_H
