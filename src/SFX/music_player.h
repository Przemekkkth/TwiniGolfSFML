#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "../utils/resource_holder.h"
#include "../utils/resource_identifiers.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


class MusicPlayer : private sf::NonCopyable
{
    public:
                                    MusicPlayer();

        void						play(Music::ID theme);
        void						stop();

        void						setPaused(bool paused);
        void						setVolume(float volume);

        sf::Music::Status           status();
    private:
        sf::Music							mMusic;
        std::map<Music::ID, std::string>	mFilenames;
        float								mVolume;
};


#endif // MUSICPLAYER_H
