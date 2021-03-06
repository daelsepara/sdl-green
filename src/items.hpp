#ifndef __ITEMS__HPP__
#define __ITEMS__HPP__

#include <vector>

namespace Item
{
    enum class Type
    {
        NONE = -1,
        MAGIC_AMULET,
        MAGIC_WAND,
        SWORD,
        LONGBOW,
        JEWEL,
        MAPLE_FLUTE,
        TOADSTOOL_FLESH,
        EMERALD_RING_ELANOR,
        EMERALD_RING,
        POTION_CLOUDY_BLUE,
        POTION_RED_LIQUID,
        POTION_TARRY_BLACK,
        JAR_COLOURED_EARTH,
        JAR_WHITE_JELLY,
        ELVEN_DIRK,
        First = MAGIC_AMULET,
        Last = ELVEN_DIRK
    };

    class Base
    {
    public:
        std::string Name;
        std::string Description;

        Item::Type Type = Item::Type::NONE;

        int Charge = -1;

        Base()
        {
        }

        Base(const char *name, const char *description, Item::Type type)
        {
            Name = name;
            Description = description;
            Type = type;
        }

        Base(const char *name, const char *description, Item::Type type, int charge)
        {
            Name = name;
            Description = description;
            Type = type;
            Charge = charge;
        }
    };

    // Item defaults
    auto MAGIC_AMULET = Item::Base("MAGIC AMULET", "MAGIC AMULET", Item::Type::MAGIC_AMULET);
    auto MAGIC_WAND = Item::Base("MAGIC WAND", "MAGIC WAND", Item::Type::MAGIC_WAND);
    auto LONGBOW = Item::Base("LONGBOW", "LONGBOW", Item::Type::LONGBOW);
    auto SWORD = Item::Base("SWORD", "SWORD", Item::Type::SWORD);
    auto JEWEL = Item::Base("JEWEL", "JEWEL", Item::Type::JEWEL);
    auto MAPLE_FLUTE = Item::Base("MAPLE FLUTE", "MAPLE FLUTE", Item::Type::MAPLE_FLUTE);
    auto TOADSTOOL_FLESH = Item::Base("TOADSTOOL FLESH", "TOADSTOOL FLESH", Item::Type::TOADSTOOL_FLESH);
    auto EMERALD_RING_ELANOR = Item::Base("Elanor's EMERALD RING", "Elanor's EMERALD RING", Item::Type::EMERALD_RING_ELANOR);
    auto EMERALD_RING = Item::Base("EMERALD RING", "EMERALD RING", Item::Type::EMERALD_RING);
    auto POTION_CLOUDY_BLUE = Item::Base("CLOUDY BLUE POTION", "CLOUDY BLUE POTION", Item::Type::POTION_CLOUDY_BLUE);
    auto POTION_RED_LIQUID = Item::Base("POTION OF RED LIQUID", "POTION OF RED LIQUID", Item::Type::POTION_RED_LIQUID);
    auto POTION_TARRY_BLACK = Item::Base("TARRY BLACK POTION", "TARRY BLACK POTION", Item::Type::POTION_TARRY_BLACK);
    auto JAR_COLOURED_EARTH = Item::Base("JAR OF COLOURED EARTH", "JAR OF COLOURED EARTH", Item::Type::JAR_COLOURED_EARTH);
    auto JAR_WHITE_JELLY = Item::Base("JAR OF WHITE JELLY", "JAR OF WHITE JELLY", Item::Type::JAR_WHITE_JELLY);
    auto ELVEN_DIRK = Item::Base("ELVEN DIRK", "ELVEN DIRK", Item::Type::ELVEN_DIRK);

    std::vector<Item::Type> UniqueItems = {Item::Type::MAPLE_FLUTE, Item::Type::EMERALD_RING_ELANOR, Item::Type::EMERALD_RING};

    bool IsUnique(Item::Type item)
    {
        auto unique = false;

        for (auto i = 0; i < Item::UniqueItems.size(); i++)
        {
            if (Item::UniqueItems[i] == item)
            {
                unique = true;

                break;
            }
        }

        return unique;
    }

    void REMOVE(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    items.erase(items.begin() + i);

                    break;
                }
            }
        }
    }

    void ADD(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            auto found = 0;

            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    found++;
                }
            }

            if (found == 0)
            {
                items.push_back(item);
            }
        }
        else
        {
            items.push_back(item);
        }
    }

    bool VERIFY(std::vector<Item::Base> &items, Item::Base item)
    {
        auto has = false;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    has = true;

                    break;
                }
            }
        }

        return has;
    }

    int FIND(std::vector<int> list, int item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i] == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int FIND_TYPE(std::vector<Item::Base> list, Item::Type item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int COUNT_TYPES(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = 0;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found++;
            }
        }

        return found;
    }

    int FIND_LEAST(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = -1;

        auto min = 255;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                if (list[i].Charge < min)
                {
                    found = i;

                    min = list[i].Charge;
                }
            }
        }

        return found;
    }

} // namespace Item
#endif
