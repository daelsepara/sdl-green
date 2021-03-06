#ifndef __CODEWORDS__HPP__
#define __CODEWORDS__HPP__

#include <map>

namespace Codeword
{
    enum class Type
    {
        NONE = -1,
        BULLHORN,
        CRABCLAW,
        SCORPION,
        SPECULUM,
        TWINHEAD,
        WATERBEARER,
        WINDFACE
    };

    std::map<Codeword::Type, const char *> Descriptions = {
        {Codeword::Type::BULLHORN, "Bullhorn"},
        {Codeword::Type::CRABCLAW, "Crabclaw"},
        {Codeword::Type::SCORPION, "Scorpion"},
        {Codeword::Type::SPECULUM, "Speculum"},
        {Codeword::Type::TWINHEAD, "Twinhead"},
        {Codeword::Type::WATERBEARER, "Waterbearer"},
        {Codeword::Type::WINDFACE, "Wind in your face"}};

    std::vector<Codeword::Type> Invisible = {Codeword::Type::WINDFACE};

    bool IsInvisible(Codeword::Type codeword)
    {
        auto invisible = false;

        for (auto i = 0; i < Codeword::Invisible.size(); i++)
        {
            if (Codeword::Invisible[i] == codeword)
            {
                invisible = true;

                break;
            }
        }

        return invisible;
    }

} // namespace Codeword
#endif
