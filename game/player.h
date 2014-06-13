#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

namespace World
{
    class Player
    {
        public:
            Player(const std::string& name):
                playerName(name),
                gold(0),
                power(0),
                colour(0) {}

        //private: //TODO: fix this
            std::string playerName;
            int gold;
            int power;
            int colour;

        private:
            //AnimState::AnimState mAnimState;
    };
}

#endif
