#ifndef APPLICATION_H
#define APPLICATION_H

#include "utils/resource_holder.h"
#include "utils/resource_identifiers.h"
#include "player.h"
#include "states/state_stack.h"
#include "SFX/music_player.h"
#include "SFX/sound_player.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application
{
    public:
                                Application();
        void					run();


    private:
        void					processInput();
        void					update(sf::Time dt);
        void					render();

        void					registerStates();


    private:
        static const sf::Time	TimePerFrame;

        sf::RenderWindow		mWindow;
        TextureHolder			mTextures;
        FontHolder				mFonts;
        Player					mPlayer;

        MusicPlayer				mMusic;
        SoundPlayer				mSounds;
        StateStack				mStateStack;

        sf::Text				mStatisticsText;
        sf::Time				mStatisticsUpdateTime;
        std::size_t				mStatisticsNumFrames;
};


#endif // APPLICATION_H
