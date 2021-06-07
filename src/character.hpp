#ifndef __CHARACTER__HPP__
#define __CHARACTER__HPP__

#include <string>
#include <vector>

#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"

namespace Character
{
    enum class Type
    {
        CUSTOM = 0,
        DUELLIST,
        RANGER,
        MONK,
        SORCERERS_APPRENTICE,
        STARVELING,
        TRAVELLER,
        THIEF
    };

    class Base
    {
    public:
        std::string Name = "";

        std::string Description = "";

        Character::Type Type = Character::Type::CUSTOM;

        int Life = 10;

        int Money = 10;

        int ITEM_LIMIT = 8;

        int MAX_LIFE_LIMIT = 10;

        int SKILLS_LIMIT = 4;

        std::vector<Skill::Base> Skills = std::vector<Skill::Base>();

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        std::vector<Codeword::Type> Codewords = std::vector<Codeword::Type>();

        std::vector<Item::Base> LostItems = std::vector<Item::Base>();

        std::vector<Skill::Base> LostSkills = std::vector<Skill::Base>();

        int LostMoney = 0;

        int StoryID = 0;

#if defined(_WIN32) || defined(__arm__)
        long long Epoch = 0;
#else
        long Epoch = 0;
#endif

        int LifePointsLost = 0;
        int ZorolotlWounds = 0;
        
        Base()
        {
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, int life, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Life = life;
            MAX_LIFE_LIMIT = life;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, std::vector<Codeword::Type> codewords, int life, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Codewords = codewords;
            Life = life;
            MAX_LIFE_LIMIT = life;
            Money = money;
        }
    };

    auto DUELLIST = Character::Base("The Duellist", Character::Type::DUELLIST, "As a professional duellist you have upset too many people by winning the spoils of your contests, and you must move on.", {Skill::AGILITY, Skill::FOLKLORE, Skill::ROGUERY, Skill::SWORDPLAY}, {Item::SWORD}, 10, 10);
    auto RANGER = Character::Base("The Ranger", Character::Type::RANGER, "Being loyal to the traditional values of your forefathers, you must protect those forced to journey off the road.", {Skill::ARCHERY, Skill::STREETWISE, Skill::SWORDPLAY, Skill::WILDERNESS_LORE}, {Item::LONGBOW, Item::SWORD}, 11, 10);
    auto MONK = Character::Base("The Monk", Character::Type::MONK, "The monks who taught you skills have been driven out and you are persecuted for your faith. Life is harsh but you endure all hardships.", {Skill::AGILITY, Skill::SPELLS, Skill::UNARMED_COMBAT, Skill::WILDERNESS_LORE}, {Item::MAGIC_WAND}, 11, 8);
    auto SORCERERS_APPERNTICE = Character::Base("The Sorcerer's Apprentice", Character::Type::SORCERERS_APPRENTICE, "Sold to a warlock when you were a child, your knowledge eventually outstripped your master's.", {Skill::CHARMS, Skill::FOLKLORE, Skill::SPELLS, Skill::WILDERNESS_LORE}, {Item::MAGIC_AMULET, Item::MAGIC_WAND}, 9, 12);
    auto STARVELING = Character::Base("The Starveling", Character::Type::STARVELING, "Orphaned in childhood, you made your way half-starved to the city. You learned what it takes to survive in the uncaring world, but now you want to seek something worthwhile in your life.", {Skill::CUNNING, Skill::ROGUERY, Skill::STREETWISE, Skill::UNARMED_COMBAT}, {}, 10, 15);
    auto THIEF = Character::Base("The Thief", Character::Type::THIEF, "You are secretive and restless, always just one ahead of the hangman's noose. Your latest exploit has made the city too dangerous for you and you must lie low.", {Skill::AGILITY, Skill::ARCHERY, Skill::CUNNING, Skill::ROGUERY}, {Item::LONGBOW, Item::JEWEL, Item::JEWEL}, 10, 16);
    auto TRAVELLER = Character::Base("The Traveller", Character::Type::TRAVELLER, "You never knew your father, and your mother mislaid you among the carts of a slaver's caravan. Cities make you ill; you can only breath freely on the open road.", {Skill::FOLKLORE, Skill::ROGUERY, Skill::SWORDPLAY, Skill::WILDERNESS_LORE}, {Item::SWORD}, 10, 10);
    auto CUSTOM = Character::Base("Custom Character", Character::Type::CUSTOM, "This is a player generated character.", {}, {}, 10);

    std::vector<Character::Base> Classes = {Character::DUELLIST, Character::RANGER, Character::MONK, Character::SORCERERS_APPERNTICE, Character::STARVELING, Character::THIEF, Character::TRAVELLER};

    int FIND_ITEM(Character::Base &player, Item::Type item)
    {
        auto found = -1;

        if (player.Items.size() > 0)
        {
            for (auto i = 0; i < player.Items.size(); i++)
            {
                if (player.Items[i].Type == item && player.Items[i].Charge != 0)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = -1;

        if (player.Skills.size() > 0)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    bool VERIFY_ITEMS(Character::Base &player, std::vector<Item::Type> items)
    {
        auto found = 0;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                auto result = Character::FIND_ITEM(player, items[i]);

                if (result >= 0)
                {
                    found++;
                }
            }
        }

        return found >= items.size();
    }

    int COUNT_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        auto found = 0;

        for (auto i = 0; i < items.size(); i++)
        {
            if (Character::FIND_ITEM(player, items[i].Type) >= 0)
            {
                found++;
            }
        }

        return found;
    }

    bool VERIFY_ITEMS_ANY(Character::Base &player, std::vector<Item::Base> items)
    {
        return Character::COUNT_ITEMS(player, items) > 0;
    }

    // Checks if player has the skill and the required item
    bool VERIFY_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    if (player.Skills[i].Requirement != Item::Type::NONE)
                    {
                        found = Character::VERIFY_ITEMS(player, {player.Skills[i].Requirement});
                    }
                    else
                    {
                        found = true;
                    }

                    break;
                }
            }
        }
        return found;
    }

    bool VERIFY_ANY_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (Character::VERIFY_SKILL(player, skills[i]))
                {
                    found = true;

                    break;
                }
            }
        }

        return found;
    }

    bool VERIFY_ALL_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        auto found = 0;

        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (Character::VERIFY_SKILL(player, skills[i]))
                {
                    found++;
                }
            }
        }

        return found == skills.size();
    }

    bool HAS_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    found = true;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_SKILL_ITEMS(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        auto found = 0;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE && items.size() > 0)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    for (auto j = 0; j < items.size(); j++)
                    {
                        if (Character::FIND_ITEM(player, items[j]) >= 0)
                        {
                            found++;
                        }
                    }
                }
            }
        }

        return found;
    }

    // verify that player has the skill and ANY of the items
    bool VERIFY_SKILL_ANY(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        return Character::FIND_SKILL_ITEMS(player, skill, items) > 0;
    }

    // verify that player has the skill and ALL of the items
    bool VERIFY_SKILL_ALL(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        return Character::FIND_SKILL_ITEMS(player, skill, items) == items.size();
    }

    bool VERIFY_SKILL_ITEM(Character::Base &player, Skill::Type skill, Item::Type item)
    {
        return Character::VERIFY_SKILL_ALL(player, skill, {item});
    }

    int FIND_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        auto found = -1;

        if (player.Codewords.size() > 0)
        {
            for (auto i = 0; i < player.Codewords.size(); i++)
            {
                if (player.Codewords[i] == codeword)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_CODEWORDS(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        auto found = 0;

        if (player.Codewords.size() > 0 && codewords.size() > 0)
        {
            for (auto i = 0; i < codewords.size(); i++)
            {
                auto result = Character::FIND_CODEWORD(player, codewords[i]);

                if (result >= 0)
                {
                    found++;
                }
            }
        }

        return found;
    }

    bool VERIFY_CODEWORDS_ANY(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        return Character::FIND_CODEWORDS(player, codewords) > 0;
    }

    bool VERIFY_CODEWORDS_ALL(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        return Character::FIND_CODEWORDS(player, codewords) == codewords.size();
    }

    bool VERIFY_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        return Character::VERIFY_CODEWORDS_ALL(player, {codeword});
    }

    bool VERIFY_LIFE(Character::Base &player, int threshold = 0)
    {
        return player.Life > threshold;
    }

    bool VERIFY_POSSESSIONS(Character::Base &player)
    {
        return player.Items.size() <= player.ITEM_LIMIT;
    }

    void GET_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        player.Items.insert(player.Items.end(), items.begin(), items.end());
    }

    void GET_CODEWORDS(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        for (auto i = 0; i < codewords.size(); i++)
        {
            if (!Character::VERIFY_CODEWORD(player, codewords[i]))
            {
                player.Codewords.push_back(codewords[i]);
            }
        }
    }

    void REMOVE_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        if (Character::VERIFY_CODEWORD(player, codeword))
        {
            auto result = FIND_CODEWORD(player, codeword);

            if (result >= 0)
            {
                player.Codewords.erase(player.Codewords.begin() + result);
            }
        }
    }

    void GET_UNIQUE_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        for (auto i = 0; i < items.size(); i++)
        {
            if (!Character::VERIFY_ITEMS(player, {items[i].Type}))
            {
                player.Items.push_back(items[i]);
            }
        }
    }

    void LOSE_ITEMS(Character::Base &player, std::vector<Item::Type> items)
    {
        if (player.Items.size() > 0 && items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                auto result = Character::FIND_ITEM(player, items[i]);

                if (result >= 0)
                {
                    player.Items.erase(player.Items.begin() + result);
                }
            }
        }
    }

    void LOSE_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                auto result = Character::FIND_SKILL(player, skills[i]);

                if (result >= 0)
                {
                    player.LostSkills.push_back(player.Skills[result]);

                    player.Skills.erase(player.Skills.begin() + result);
                }
            }
        }
    }

    void GAIN_LIFE(Character::Base &player, int life)
    {
        player.Life += life;

        if (player.Life < 0)
        {
            player.Life = 0;
        }
        else if (player.Life > player.MAX_LIFE_LIMIT)
        {
            player.Life = player.MAX_LIFE_LIMIT;
        }
    }

    void GAIN_MONEY(Character::Base &player, int money)
    {
        player.Money += money;

        if (player.Money < 0)
        {
            player.Money = 0;
        }
    }

    void LOSE_POSSESSIONS(Character::Base &player)
    {
        player.LostItems = player.Items;

        player.Items.clear();
    }

    void LOSE_ALL(Character::Base &player)
    {
        player.LostMoney = player.LostMoney;
        player.Money = 0;

        Character::LOSE_POSSESSIONS(player);
    }

} // namespace Character

#endif
