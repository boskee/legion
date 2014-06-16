#ifndef CITY_H
#define CITY_H

#include <iostream>

namespace World
{
    class City
    {
        public:
            City(const std::string& name):
                cityName(name) {}

        //private: //TODO: fix this
            std::string cityName;

        private:
            //AnimState::AnimState mAnimState;
    };
}

#endif
