#include "translation.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "../game/Amos.h"

#include "../game/legion.h"
#include "../game/lgn_wczytaj.h"
#include "../game/utl_locale.h"

#include "rapidjson/document.h"
#include <algorithm>

namespace Core
{
    bool StringTable::initialised = false;

//private: //TODO: fix this
    std::map<std::string, std::string> StringTable::strings;

	bool StringTable::GetString(Rocket::Core::String& translated, const Rocket::Core::String& input)
	{
	    if (input == "")
        {
            return false;
        }

	    if (!StringTable::initialised)
        {
            StringTable::Initialise();
        }

        std::map<std::string, std::string>::iterator it;
        Rocket::Core::String input2 = Rocket::Core::StringUtilities::StripWhitespace(input);

        it = StringTable::strings.find(input2.CString());

        if (it == strings.end())
        {
            return false;
        }

        translated = Rocket::Core::String(it->second.c_str());

		return true;
	}

	void StringTable::Initialise()
	{
	    StringTable::initialised = true;
        std::string language_suffix = gs_language.c_str();
	    std::transform(language_suffix.begin(), language_suffix.end(), language_suffix.begin(), ::tolower);
        astr json_path = KAT_S + "data/json/translations." + language_suffix + ".json";

        ifstream jsonFile(json_path.c_str());

        if (!jsonFile) {
            return;
        }

        vector<char> buffer((istreambuf_iterator<char>(jsonFile)), istreambuf_iterator<char>());
        buffer.push_back('\0');

        rapidjson::Document d;
        d.Parse<0>(&buffer[0]);
        const rapidjson::Value& a = d["strings"];

        for (rapidjson::Value::ConstMemberIterator itr = a.MemberBegin(); itr != a.MemberEnd(); ++itr)
        {
            StringTable::strings[itr->name.GetString()] = itr->value.GetString();
        }
	}
}
