#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

namespace Core
{
    class Preferences
    {
        public:
            Preferences() {}

            int get(std::string preference);
            void set(std::string preference, int value);
        //private: //TODO: fix this
            std::map<std::string, int> preferences;

        private:
            //AnimState::AnimState mAnimState;
    };
}

#endif
