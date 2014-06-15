#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <Rocket/Core/String.h>
#include <cstdio>
#include <map>

namespace Core
{
    class StringTable
    {
        public:
            StringTable() {}

            static bool GetString(Rocket::Core::String& translated, const Rocket::Core::String& input);

        //private: //TODO: fix this
            static std::map<std::string, std::string> strings;

        private:
            static void Initialise();
            //AnimState::AnimState mAnimState;
            static bool initialised;
    };
}

#endif
