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
                gold(0) {}

        //private: //TODO: fix this
            std::string playerName;
            int gold;

        private:
            //AnimState::AnimState mAnimState;
    };
}

#endif
