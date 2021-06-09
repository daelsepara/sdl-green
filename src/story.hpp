#ifndef __STORY__HPP__
#define __STORY__HPP__

#include <vector>

#include "constants.hpp"
#include "controls.hpp"
#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"
#include "character.hpp"

namespace Choice
{
    enum class Type
    {
        NORMAL = 0, // No requirements
        ITEMS,
        GET_ITEMS,
        SKILL,
        CODEWORD,
        MONEY,
        LIFE,
        ANY_ITEM,
        ANY_SKILL,
        SKILL_ITEM,
        SKILL_ANY,
        SKILL_ALL,
        FIRE_WEAPON,
        LOSE_ITEMS,
        LOSE_MONEY,
        LOSE_ALL,
        LOSE_SKILLS,
        GET_CODEWORD,
        LOSE_CODEWORD,
        GAIN_MONEY,
        GIVE,
        BRIBE,
        TAKE,
        PAY_WITH,
        SELL
    };

    class Base
    {
    public:
        const char *Text = NULL;

        Choice::Type Type = Choice::Type::NORMAL;

        Skill::Type Skill = Skill::Type::NONE;

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        Codeword::Type Codeword = Codeword::Type::NONE;

        int Value = 0;

        int Destination = -1;

        Base(const char *text, int destination)
        {
            Text = text;
            Destination = destination;
        }

        Base(const char *text, int destination, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL_ITEM;
            Items = items;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::ITEMS;
            Items = items;
        }

        Base(const char *text, int destination, Skill::Type skill)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL;
            Skill = skill;
        }

        Base(const char *text, int destination, Codeword::Type codeword)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::CODEWORD;
            Codeword = codeword;
        }

        Base(const char *text, int destination, Choice::Type type, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type)
        {
            Text = text;
            Destination = destination;
            Type = type;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Skill = skill;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type, Codeword::Type codeword)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Codeword = codeword;
        }
    };
} // namespace Choice

namespace Story
{
    enum class Type
    {
        NORMAL = 0,
        GOOD,
        DOOM
    };

    enum class Controls
    {
        NONE = 0,
        STANDARD,
        SHOP,
        BUY_AND_SELL,
        SELL,
        TRADE
    };

    class Base
    {
    public:
        int ID = 0;

        const char *Text = NULL;

        const char *Title = NULL;

        const char *Bye = NULL;

        const char *Image = NULL;

        Story::Controls Controls = Story::Controls::NONE;

        std::vector<Choice::Base> Choices = std::vector<Choice::Base>();

        std::vector<std::pair<Item::Base, int>> Shop = std::vector<std::pair<Item::Base, int>>();
        std::vector<std::pair<Item::Base, int>> Sell = std::vector<std::pair<Item::Base, int>>();

        std::pair<Item::Base, Item::Base> Trade;

        // Player selects items to take up to a certain limit
        std::vector<Item::Base> Take = std::vector<Item::Base>();

        // Player selects items to lose
        std::vector<Item::Base> ToLose = std::vector<Item::Base>();

        int Limit = 0;

        int LimitSkills = 0;

        Story::Type Type = Story::Type::NORMAL;

        // Handle background events
        virtual int Background(Character::Base &player) { return -1; };

        // Handle events before story branches
        virtual void Event(Character::Base &player){};

        // Jump to next section
        virtual int Continue(Character::Base &player) { return -1; };

        Base()
        {
        }

        Base(int id)
        {
            ID = id;
        }

        Base(int id, const char *text, Story::Type type)
        {
            ID = id;
            Text = text;
            type = type;
        }

        Base(const char *text, Story::Type type)
        {
            Text = text;
            type = type;
        }
    };

    std::vector<Button> StandardControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exit.png", idx + 4, idx + 5, compact ? idx + 5 : 1, idx + 5, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> SellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/selling.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BuyAndSellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/selling.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> TradeControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::TRADE));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ExitControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/exit.png", compact ? idx : idx - 1, idx, compact ? idx : idx - 1, idx, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Choice::Base> FourDirections()
    {
        auto choices = std::vector<Choice::Base>();

        choices.push_back(Choice::Base("Head west", 43));
        choices.push_back(Choice::Base("Head east", 427));
        choices.push_back(Choice::Base("Head south-west", 70));
        choices.push_back(Choice::Base("Head south from here", 78));

        return choices;
    }

} // namespace Story

class NotImplemented : public Story::Base
{
public:
    NotImplemented()
    {
        ID = -1;

        Title = "Not implemented yet";

        Controls = Story::Controls::NONE;
    }
};

auto notImplemented = NotImplemented();

auto Stories = std::vector<Story::Base *>();

void *findStory(int id)
{
    Story::Base *story = &notImplemented;

    if (Stories.size() > 0)
    {
        for (auto i = 0; i < Stories.size(); i++)
        {
            if (((Story::Base *)Stories[i])->ID == id)
            {
                story = (Story::Base *)Stories[i];

                break;
            }
        }
    }

    return story;
}

class Prologue : public Story::Base
{
public:
    Prologue()
    {
        Title = "Green Blood: Prologue";

        Image = "images/vr-logo.png";

        ID = 0;

        Text = "Sickened by the ways of your fellow men and despairing of man's cruelty, you have quit the teeming city of Godorno, with its cesspools and plague pits, its beggars and abject slaves. You walk for days, revelling in the fresh air of the countryside. This is a green land of hills and dales, farmsteads and mills -- a veritable bread-basket that yields all its grains and fruit to the decadent city.\n\nAs you walk you have much time to think. Long ago your family told you how the star of destiny, purple Praxis, changed colour to the flaming gold of Moraine, God of War, at the moment of your birth. Even as Praxis flared with energy, so your mother's life waned. She died of exhaustion bringing you into the world, but her sisters looked after you until you were old enough, at eight, to go up to the dreaming spires of the academy at Hegalopolis.\n\nThe bookish scholars trained you in many things and all who taught there agreed you showed great promise. But when you were just fifteen years old, Gornild, the harsh overlord of Godorno, dissolved all the monasteries in the lands along the Marches, fearing their teachings would turn minds against his corrupt rule. You were forced to scratch out a miserable living just like the other poor folk of the city.\n\nThe cloistered life of the academy, with its politeness and order, gave you scant preparation for the life on the streets of Godorno. You developed the cunning of a sewer rat and the patience of the damned just staying alive from day to day, dodging the press gangs from the war galleys that carry young men off to fight the corsairs. Your cunning was great enough to avoid the fate of the galley slave and you have grown to maturity, strong, tough and determined.\n\nThe ways of the city folk revolt you. Your diligent study of history shows an ever churning cycle of oppressors and the downtrodden. Man is strapped to the wheel of fate to be alternately dragged to the heights and plunged again into the pits and windblasted depths of pain and want.\n\nAs you walk, every step that bears you away from the stench of the city is a step taken more lightly than the last. You resolve to return to the city only if you have changed things for the better. Yours is the nobleness of spirit that would lay down its life to better the lot of your fellow man. If Praxis robbed you of a mother's love, Praxis can repay the debt by shining brightly on your destiny.\n\nAs the miles pass with you deep in thought, your path takes you inexorably on towards the great forest beyond the lands of men. Your curiosity has been piqued by rumours and legends about the ancient Tree of Knowledge, a fabled tree hundreds of feet high, with golden bark and silver leaves. It is said to grow at the centre of the great Forest of Arden.\n\nFey sylvan elves are said to dwell there. The stories of what they look like and the fate that befalls those lost in the forest are too fantastically horrific to be true. Each fable tells a different story: of elves with six arms, of elves with scimitar blades in place of forearms, and of greenbark bows that can send an arrow from one horizon to the other and which always hit their mark. And there are stories of elves with jewels for eyes which melt when they cry, as they must when disturbed by man, for they keenly sense the tragedy of man's mortality.\n\nThough each story is fanciful and bizarre they all agree in one respect. No one who sees the elves lives to tell of it. There isn't a man alive who has glimpsed the splendid glory of Elvenhame, the city of the elves.\n\nYou no longer know whether it is the desire to see elves or your wish to change the world for the better that takes you on your quest. What, however, if you were to learn the knowledge of ages and return to the lands of men as a saviour? Your name would go down in history. Anything less magnificent than this noble quest for knowledge that will save mankind will not do. You will become a hero or die in the attempt.\n\nYou are on the road. It is approaching early evening and purple Praxis already beams out in the low dusk sky. As you stare at the star, it seems to wink out then flare bright golden yellow before resuming its purple form. It is a sign that your destiny awaits in the Forest of Arden.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 1; }
};

class Story001 : public Story::Base
{
public:
    Story001()
    {
        ID = 1;

        Text = "The road tops a ridge that is straddled by the ruins of a great wall, half covered in turf. The wall once marked the border between the lands of man and domain of the elves. Quickly you scramble up and over the blocks of fallen stone. Standing atop the ruin, you survey the outlands beyond.\n\nYour gaze sweeps across the broad patches of purple heather and yellow gorse that cover the inhospitable uplands. The air smells fresh; it is good to be free of the noisome taint of the sewers and plague pits of the city you have left behind. The road winds down into a valley, at the foot of which nestles Burg, a small town of neat white houses with roof of triangular grey slates. Here may be your last chance to talk with mankind before you are swallowed up by the depths of the great Forest of Arden.\n\nAs you walk towards the buildings through the tilled and reaped land of the valley, you pass gleaners -- peasants who search the ground for stalks of straw and seed spilled during the harvest. The townsfolk, seemingly wary of outsiders, keep out of your way. Ahead of you is an inn, the largest building in the town. Looking forward to perhaps your last night's sleep in a proper bed for many weeks, you make for this hostelry.\n\nThe inn seems surprisingly large for a town that is at the very edge of the wilderness. It must once have been a baronial hall built by a lord seeking to carve out a kingdom beyond the great wall. As you walk down the main street the ruddy sky is turning with the onset of twilight. What looked an inviting little town by day seems sombre and unwelcoming at nightfall. As you linger a moment outside the inn, there is a crack of thunder and it begins to pour with rain.\n\nInside the inn a young girl is lighting oil lamps with a taper. Until your eyes grow accustomed to the gloom you cannot make out who shares the common room with you, nor many details of the interior of the inn itself.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wait by the door until you can see better", 37));
        Choices.push_back(Choice::Base("Step in and warm yourself before the fire", 55));

        Controls = Story::Controls::STANDARD;
    }
};

class Story002 : public Story::Base
{
public:
    Story002()
    {
        ID = 2;

        Text = "\"It is the forest which cleans and purifies the air for all the world to breathe. Without the Forest of Arden all living things would choke, gag, and die. The trees absorb the foul air of man's pollution, his burning and wasting, and give it back to the world again clean, fresh and ready to breath. The stench and dross of the cities is purged and cleansed by the trees. The forest is the lifeblood of the world.\"\n\nThe old woman delivers these words very gravely, convincing you that she believes every word of what she is saying. All the time her eyes never leave yours.\n\n\"Ah, but I see I bore you. Enough of this idle prattle, I must take my rest. Good night to you.\"\n\nSo saying, she gets up and makes to leave you. You are about to protest that you are far from bored but realize she is only looking for a polite way to leave your company. You let her go and decide to take a room at the inn as well.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 333; }
};

class Story003 : public Story::Base
{
public:
    Story003()
    {
        ID = 3;

        Text = "A figure lies dead in the forest. Ants crawl in and out of its newly picked-clean eye sockets; beetles and rats gnaw at the remains. With a shock you realize the figure is wearing identical clothes to yours -- there isn't another pair of boots in the world quite like yours, made to order by a cobbler in Godorno.\n\n\"You are not wearing my ring,\" says Elanor. \"If you cannot trust me, I cannot aid you. You must find your own way and I must continue my search for the saviour of the forest. Begone and never come back, you weak-willed doubter.\"\n\nElanor and the owl disappear. You are on your own again.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 70; }
};

class Story004 : public Story::Base
{
public:
    Story004()
    {
        ID = 4;

        Text = "Valerian's voice is markedly different from the guttural speech of the Westermen, but there is no doubt he has thrown in his lot with them. It is plain that they depend upon him for their knowledge of the forest and its many dangers. They are planning how to destroy and burn the whole forest tree by tree. Valerian has convinced the chief of the Westermen that his realm will not be safe until every tree, every sapling and every bush in the forest has been razed to the ground.\n\n\"You wanted to tell me something of note, Valerian? Else why have I summoned all my advisers?\"\n\n\"Indeed, sire, I have a plan to destroy the forest at a stroke.\"\n\n\"What stroke?\"\n\n\"By killing the Tree of Life at the very centre of the forest. Slay the tree of Life, sire, and the whole forest, along with everything in it, will die.\"\n\n\"Well, your advice has been sound in the past, Valerian. I will do as you suggest and slay the Tree of Life.\"\n\nYou gained the codeword BULLHORN.";

        Choices.clear();
        Choices.push_back(Choice::Base("Interrupt and tell the chief that the death of the forest will mean death and destruction for the whole world, including him", 198));
        Choices.push_back(Choice::Base("Speak out of the pavilion and leave while the going is good", 38));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::BULLHORN});
    }
};

class Story005 : public Story::Base
{
public:
    Story005()
    {
        ID = 5;

        Image = "images/filler2.png";

        Text = "As Valerian stands up, he lets his cloak fall to the floor, revealing armour made of quilted leather -- light armour that wouldn't stop a sword thrust. He has no sword or obvious weapon to hand. Three small coloured pouches swing from his belt.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hold your ground", 27));
        Choices.push_back(Choice::Base("Close with him", 65));

        Controls = Story::Controls::STANDARD;
    }
};

class Story006 : public Story::Base
{
public:
    Story006()
    {
        ID = 6;

        Text = "You call out the dragon's name. Its great head rears slowly above you and its yellow-green eyes bore into yours. Its nostrils dilate as it sucks in a deep breath. Too late, you realize you lied to yourself about knowing the creature's name. There is a terrible whooshing sounds like the dragon's real name as it breathes acid and gas upon you. The torrent of gas and air rolls you across the ground and you are lucky to bang your head on a rock, sparing yourself a more painful death. The Forest of Arden is doomed.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story007 : public Story::Base
{
public:
    Story007()
    {
        ID = 7;

        Text = "You say the word and vanish. Your invisibility, however, doesn't help you deal with the Infernal Statue, whose sword is still chopping into the Tree of Life. You are wasting precious time. Which spell will you cast to help save the tree?";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Choking Fog", 346));
        Choices.push_back(Choice::Base("Cast Bafflement", 113));
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 64));
        Choices.push_back(Choice::Base("Cast Tower of Will", 186));

        Controls = Story::Controls::STANDARD;
    }
};

class Story008 : public Story::Base
{
public:
    Story008()
    {
        ID = 8;

        Text = "The Kwerrel is delighted with his shiny golden disks of metal, which he starts trying to weave into his hair. Now that he has got what he wants he scampers away, leaving you alone inside the bush. The archway back to the forest has reappeared so you make good your escape from the bush.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 406; }
};

class Story009 : public Story::Base
{
public:
    Story009()
    {
        ID = 9;

        Text = "\"I must test your fitness to be the forest's saviour,\" says Elanor. \"I hope you pass the test. You would not like to see the forest laid to waste would you?\"\n\nShe looks regal and yet kind, but her eyes never leave yours.";

        Choices.clear();
        Choices.push_back(Choice::Base("Reply that your reason for visiting the forest is to find the Tree of Knowledge and take some of its wisdom away with you to the lands of men", 24));
        Choices.push_back(Choice::Base("Say that the forest is too beautiful to be laid waste and you will try to save it", 40));

        Controls = Story::Controls::STANDARD;
    }
};

class Story010 : public Story::Base
{
public:
    Story010()
    {
        ID = 10;

        Text = "\"Then why have you disturbed my slumber? You have woken me a year early. Now I will feel sick for the next year.\"\n\nThe dragon rolls over and seems to be going back to sleep.";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack it", 59));
        Choices.push_back(Choice::Base("Try to steal its treasure", 79));
        Choices.push_back(Choice::Base("Continue your quest and leave the dragon to slumber", 49));

        Controls = Story::Controls::STANDARD;
    }
};

class Story011 : public Story::Base
{
public:
    Story011()
    {
        ID = 11;

        Text = "You know without doubt that your best plan is to call upon the dragon that has promised its help. Certain in the knowledge that it will obey you, you set off for the Bonehill to enlist its help.\n\nThe journey passes swiftly with the help of an elf to guide you, and you are soon at the dragon's lair.\n\nYou call out its name...";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 83; }
};

class Story012 : public Story::Base
{
public:
    Story012()
    {
        ID = 12;

        Text = "You tell Pozzo that to escape the forest he should make for a river and follow it to the sea. You know that there is a city or town at every river mouth for hundreds of miles around, and when he reaches one he can take ship for Godorno. He bids you farewell and says you may stay as his honoured guest at his in in Burg if you are ever travelling that way again. With that, he sets out to return to his beloved daughter.\n\nYou are soon safe back in the forest, and alone again. The awful sights and sounds of the Westermen camp are soon left far behind.";

        Choices = Story::FourDirections();

        Controls = Story::Controls::STANDARD;
    }
};

class Story013 : public Story::Base
{
public:
    Story013()
    {
        ID = 13;

        Text = "All is quiet behind you but you do not look back. The path is difficult, overgrown and boggy. Every now and then you are hard put to decide which way it leads, but by keeping fairly close to the great river you make progress for many hours until nightfall.\n\nThe noises of the forest seem to intensify with night: there is buzzing, clicking, croaking and the hoot of alone owl to keep you company. Finding a dry place to rest is not easy but at last you find a mound of earth on which you can settle down.";

        Choices.clear();
        Choices.push_back(Choice::Base("[CHARMS] turn your pendant (MAGIC AMULET) into a warning stone", 361, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Otherwise", 419));

        Controls = Story::Controls::STANDARD;
    }
};

class Story014 : public Story::Base
{
public:
    Story014()
    {
        ID = 14;

        Text = "\"Yes it would, more terrible than you can know. The stench and dross of the cities is purged and cleansed by the forest. The trees absorb the foul air of man's pollution, his burning and smelting, and give it back to the world again clean, fresh and ready to breathe. The forest is the lifeblood of the world; without it the world will choke, gag and die. The sin of man, his waste, his poisons, are made good again by the life force of nature. You feel something of this, don't you?\" The woman looks at you approvingly.\n\nSensing that you can trust her, you ask about the Tree of Knowledge.\n\n\"If you come to my bower in the forest I can take you to the Great Tree. But I must warn you that if you harm so much as a leaf on your way there you will never leave the forest. When you enter the forest follow the Burgstream to the great Sirion river and then walk down the eastern bank. My followers will bring me word of your progress.\"\n\nShe takes up her staff and taps it once on the table. Her gnarled old staff turns into a little flute, which she hands to you with the words, \"Blow this at need in the forest and my friends will help you.\"\n\nYou murmur your thanks and fall to wondering how she can make the animals of the forest do her bidding. As the fire burns down, the woman goes to sleep in her chair. Not wishing to disturb her, you take a room at the inn for the night.\n\nYou RECEIVED a MAPLE FLUTE.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::MAPLE_FLUTE});
    }

    int Continue(Character::Base &player) { return 333; }
};

class Story015 : public Story::Base
{
public:
    Story015()
    {
        ID = 15;

        Image = "images/filler3.png";

        Text = "The imp puts on the EMERALD RING as if it were a bracelet, and then tries to rip it off again. But the band of gold constricts until it is a perfect fit around his wrist.\n\n\"Alack, alack, I can never take this cursed thing off,\" the imp laments.\n\n\"Help me, and I will remove the ring.\"\n\n\"I am the Kwerrel, and the Kwerrel keeps no bargains.\"\n\n\"Then you are a prisoner of the Lady of the Forest's ring for ever and every being in the forest will know that you are not her friend,\" you say.\n\nQuailing at your words, the Kwerrel says, \"Take the flesh of the toadstool. Make an infusion with elderflower wine and give it to any being you wish to drug into sleep. They will sleep the sleep of the damned. Look, now I open the archway for you to leave.\"\n\nAs the imp speaks the gold ring grows and falls from his wrist to lie on the ground near the giant toadstool. You pick it up again, take a large piece of the flesh of the toadstool. Bidding the little imp goodbye, you walk back into the forest.\n\nYou RECEIVED a TOADSTOOL FLESH.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::TOADSTOOL_FLESH});
    }

    int Continue(Character::Base &player) { return 406; }
};

class Story016 : public Story::Base
{
public:
    Story016()
    {
        ID = 16;

        Text = "You walk across the room without looking to either side, pretending not to have heard the command.\n\nThe same voice rings out again, but the imperious tone now carries the sharp ring of anger: \"So you think you can come here and treat us as though we are beneath notice, do you? Are you deaf? Ignore Valerian, would you? I'll make you pay for your insolence.\"\n\nThere is a scramble as people leave the common room. Only the old woman in grey stays to watch the fight. It is too late to do anything but fight or run.";

        Choices.clear();
        Choices.push_back(Choice::Base("Run out of the inn without looking back", 117));
        Choices.push_back(Choice::Base("Fight", 5));

        Controls = Story::Controls::STANDARD;
    }
};

class Story017 : public Story::Base
{
public:
    Story017()
    {
        ID = 17;

        Text = "The odds are stacked against you as more and more guards pour into the pavilion. Together with the chief's advisers they easily overwhelm you, forcing you to your knees before the chief. The Westermen's leader reaches for his sword, draws it back and drives it into your heart, smiling evilly as he does so. As you die, so too do the hopes for saving the Forest of Arden.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story018 : public Story::Base
{
public:
    Story018()
    {
        ID = 18;

        Text = "As you voice acceptance of the duel, a hundred of the most wise and ancient looking elves appear silently from the trees at the edge of the clearing. They fan out, encircling you completely, and with their feet scrape a circle in the dirt at the clearing's edge.\n\nAll the elves are typical of their kind, with long wine-red hair and pale green skin that has a silvery bloom. Their clothes, in shades of green and brown, blends with the backdrop of the forest and makes it seem as if the very trees have walled you into the clearing. If you get beyond that ring, you feel it will only ever be as vanquisher of the elves' champion, whoever that might be.\n\n\"If you step outside the circle you have lost,\" states the King of the Elves. \"I will choose a champion from all elvenkind to face you.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Try out the potency of your magic against that of the immortal elves", 33, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SWORDPLAY] Try your skill with the sword against the champion of all the elves", 50, Skill::Type::SWORDPLAY));
        Choices.push_back(Choice::Base("[UNARMED COMBAT] Try to pit your body against one of the lithe quick elves", 63, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("Concede defeat: you have none of these skills", 163));

        Controls = Story::Controls::STANDARD;
    }
};

class Story019 : public Story::Base
{
public:
    Story019()
    {
        ID = 19;

        Text = "The dragon bats you out of the cavern and sends you rolling down the bank like a golden cannonball. You struggle to your feet while the ancient beast mocks you.\n\n\"It is a long time since I spied a golden turtle in these parts.\" He laughs and hisses as you stagger away from the Bonehill.\n\nWeighed down by gold, you have no chance of completing your quest unless you head back to Burg and find someone to remove the precious metal. No matter, you will be rich beyond your wildest dreams...";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 39; }
};

class Story020 : public Story::Base
{
public:
    Story020()
    {
        ID = 20;

        Text = "He points up at the sun shining down on the clearing. Spitting onto his finger, he flicks the saliva up into the air. To your astonishment, a green watery film covers the face of the sun. It lasts only an instant before being wiped away like the blinking of a giant celestial eye. The Elf King turns to you, and his feral smile is brimming with triumph. \"Can you do that, mortal? Make the sun go green?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Cast an illusion to achieve the desired effect and pass the Elf King's test", 232, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Admit defeat", 69));

        Controls = Story::Controls::STANDARD;
    }
};

class Story021 : public Story::Base
{
public:
    Story021()
    {
        ID = 21;

        Text = "With the dragon's help and the might of the elves, you feel you have a chance of defeating the forces of the Westermen and driving the threat of the evil from the forest. Full of confidence in your ability to call upon a powerful ally of the ancient times, you head towards the rowan trees at the edge of the forest.\n\nTravelling along routes that seem to come unbidden to you mind, you reach a clearing that seems strangely familiar. Was it perhaps, that you met the elves? Or does some horror of your travels lurk nearby in the undergrowth?\n\nSummoning up your courage, you call out to whoever or whatever will here: \"Elves! If you would win your freedom, come talk with a mortal who can deliver it. For I have secured us an ally equal to half the Westermen's forces -- a dragon whose very appearance will slay scores of them from sheer terror. Come forward and speak with me.\"\n\nThe words of your challenge die away, suffocated by the preternatural silence of the forest. You might have expected to hear the chirruping voice of a bird or the faint rustle of a woodmouse questing for beetles, yet there is nothing. Cursing the elves for their arrogance, you shout again, \"Come forward!\"\n\nSpittle flies from your lips and your face flushes with the violent passion of your request. Again you wait for a reply.\n\n\"Do you think that one dragon is enough, then, to beat your fellow men?\" says a cool voice from behind you.\n\nSpinning around, you see no more than inches from your face the eternally youthful face of an elf. Yet the penetrating eyes that are windows to the wisdom of countless centuries mark this elf out above all others. The Elf King has answered your call.\n\n\"One dragon is more than enough,\" you reply, \"with the forces of the elves a well. He will demoralize the Westermen, plunging them into chaos from which the deadly arrows of the elves will cruelly pluck them.\"\n\nHe smiles a cold smile, approving of the relish with which you describe the Westermen's deaths. \"Brave words indeed, for a mortal. But for elves to accede to your schemes and counsels, you must prove yourself worthy of our respect.\"\n\n\"How may I do that?\"\n\n\"Overcome my champion in a duel. Only then will we heed your words.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 215;
        }
        else if (Character::VERIFY_CODEWORD(player, Codeword::Type::SPECULUM))
        {
            return 309;
        }
        else
        {
            return 137;
        }
    }
};

class Story022 : public Story::Base
{
public:
    Story022()
    {
        ID = 22;

        Text = "The sprite inclines your own reflected face in an expression of deep meditation. \"I see your destiny,\" it says at last. \"You will either prove yourself a hero, saving the forest, or else you will allow venality and pride to lead you to your doom.\"\n\n\"Being a hero sounds the better option,\" you comment drily.\n\n\"In that case, you must seek Elanor the Grey Lady. Solitude has made her strange -- not quite elvish in her ways, but not human any longer either. But you should trust her, as she'll set you on the right path. Then you must find the elves. Convincing them to help you may prove a weighty task, for they are proud and aloof and wilfully headstrong. Next seek the camp of the Westermen to learn their plans. They will destroy the forest if they succeed, and only direct action can stop them. Perhaps you can dig up a worm to help you.\"\n\nThere is a long pause. You look expectantly at the reflection until it finally gives you a distinctly unhuman grin. \"Well, that is the prophecy,\" it concludes.";

        Choices.clear();
        Choices.push_back(Choice::Base("Keep your promise to break the mirror", 418));
        Choices.push_back(Choice::Base("Leave it intact for the time being", 105));

        Controls = Story::Controls::STANDARD;
    }
};

class Story023 : public Story::Base
{
public:
    Story023()
    {
        ID = 23;

        Text = "The Infernal Statue is belching steam as its sword arm rises and falls like a piston. As you do not wish to attack the steaming statue directly, what will you do?";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack the shieldbearers and bodyguards clustered around the great boiler", 203));
        Choices.push_back(Choice::Base("Try to get to the pipe that connects the Infernal Statue to the boiler", 397));

        Controls = Story::Controls::STANDARD;
    }
};

class Story024 : public Story::Base
{
public:
    Story024()
    {
        ID = 24;

        Image = "images/filler2.png";

        Text = "\"The hackers and burners, the men from the west, say the ants of the forest must be eradicated because they eat the farmers' crops,\" she says. \"What do you say?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Say the ants are indeed pests and should be wiped out", 51));
        Choices.push_back(Choice::Base("Reply that the forest would choke and die if there were no ants to eat the dead leaves and wood", 67));
        Choices.push_back(Choice::Base("[WILDERNESS LORE] Use your knowledge", 171, Skill::Type::WILDERNESS_LORE));

        Controls = Story::Controls::STANDARD;
    }
};

class Story025 : public Story::Base
{
public:
    Story025()
    {
        ID = 25;

        Image = "images/filler2.png";

        Text = "The Chief of the Westermen describes his favourite toy to you. His eyes are shining with enthusiasm as he describes a great steam-powered machine of metal armour inside which a man can ride. The suit is as large as a giant and as powerful as a steam hammer, it can smash men to pulp or rend them limb from limb. The chief believes it works by magic.\n\n\"It only has one weakness. Sever the line that connects it to the steam furnace and it dies. Only a real hero could stand up to The Steamer and do that, by the gods,\"\n\nAt that moment a visitor is announced. \"It is Valerian the Moon Druid, sire,\" says the herald. \"He says he has important news. Shall we let him come in?\"\n\n\"Aye, let him enter.\" The speech of Westermen sounds guttural and uncouth, but you can understand their dialect. The man who enters is the man you first saw in the inn at Burg. He is still dressed in the black travelling cloak, but his hood is thrown back to reveal his hatchet-like face and pointed black goatee beard. He bows before the chief, then wrinkles his nose and stares at you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Make your excuses and leave", 38));
        Choices.push_back(Choice::Base("Stay and hear what news Valerian brings", 4));

        Controls = Story::Controls::STANDARD;
    }
};

class Story026 : public Story::Base
{
public:
    Story026()
    {
        ID = 26;

        Text = "\"You have seen what will come to pass if you fail in your quest: death and nothing but death. Now let us see whether your future holds something different in store.\"\n\nElanor takes your hand and brushes the surface of the water with your fingertips. A new picture forms and your eyes grow round with wonder. Something that looks like a hill set between tall dark trees is stirring and turning to look at you. It is a dragon, the oldest of the ancient beasts, not quite immortal. Its red eyes contrast horribly with the smooth jade green scales of its body. It snorts and a cloud of green gas rolls towards you. You jerk back from the vision in horror, before you remember it is just a picture on the water. You see yourself darting away from the cloud. Later, the vision shows you riding astride the creature's back while it flexes it wings in flight.\n\n\"You must win over the dragon, the most powerful of the forest's denizens,\" says Elanor. \"Then it will fight for you against the Westermen.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 41; }
};

class Story027 : public Story::Base
{
public:
    Story027()
    {
        ID = 27;

        Text = "While you hold your ground, Valerian begins casting a spell.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Go onto the offensive", 169, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Prepare a defensive magic", 182, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Otherwise", 87));

        Controls = Story::Controls::STANDARD;
    }
};

class Story028 : public Story::Base
{
public:
    Story028()
    {
        ID = 28;

        Image = "images/pool.png";

        Text = "Fearing death at any moment, you plunge your dagger into the rubber hose that connects the great boiler to the Infernal Statue, which is still hacking chunks out of the Tree of Life. The hose breaks and the ends whip round with dreadful force. The Westermen coming to attack you are scythed off their feet by the hose, and you are bathed in a fog of hot steam.\n\nYou stagger out of the fog where you were safe, because it is unbearably hot, and watch as the Infernal Statue seems to run down like a clockwork toy. It bends, bows and then rolls down into the deep blue pool. The Westermen give a howl of dismay and begin to retreat, harried by the arrows of the elves.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 500; }
};

class Story029 : public Story::Base
{
public:
    Story029()
    {
        ID = 29;

        Text = "Valerian's attention is distracted by what the king is pointing out on the map. You inch quietly past the guards and towards the pavilion's porchway. Valerian looks up and his eyes narrow, then he cries out, \"There's something moving, they're getting away. I have the senses of a bat.\"\n\nHe points in your general direction. The guards peer from him to where you stand, unable to make you out.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast the Shield of Defense spell", 441));
        Choices.push_back(Choice::Base("Make a run for the forest", 451));

        Controls = Story::Controls::STANDARD;
    }
};

class Story030 : public Story::Base
{
public:
    Story030()
    {
        ID = 30;

        Text = "It will take two days to travel from Elvenhame to the Tree of Life. You delay as long as possible, mustering more than seven thousand elves, before setting out to defend the Tree of Life.\n\nThe elves fight bravely but they are outnumbered and in hand-to-hand fighting their lack of swords and armour proves a fatal weakness. Green blood flows everywhere.\n\nYou perish along with the last of the elves, vainly trying to protect their king. The death of so many immortal elves is the greatest disaster the world has ever witnessed. Nothing can now stop the Westermen reaching the Tree of Life: the Forest of Arden is doomed.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story031 : public Story::Base
{
public:
    Story031()
    {
        ID = 31;

        Text = "A grandiose gesture brings forth the Choking Fog about the machine. But why have you used this spell against a machine that doesn't breathe but is powered by steam? The steam rushing from vents in the head dissipates the fog and the Infernal Statue lurches to the Tree of Life once again, raising its sword arm to strike.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Bafflement", 113));
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 64));
        Choices.push_back(Choice::Base("Cast Tower of Will", 186));

        Controls = Story::Controls::STANDARD;
    }
};

class Story032 : public Story::Base
{
public:
    Story032()
    {
        ID = 32;

        Image = "images/filler3.png";

        Text = "There is another great whooshing exhalation behind you and you start to sprint. The gurgling sounds closer this time. The dragon must be chasing you. Straining your ears, you listen for sounds of the leviathan crashing through the ferns behind, over the rasping of your own breath and the thudding of your feet on the ground. You run until exhaustion overwhelms you but there are no sounds of pursuit now. It seems you have escaped the dragon.\n\nIf indeed you are near the Bonehill, the dragon's lair, you will need to travel for several days.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head west to regain your course", 43));
        Choices.push_back(Choice::Base("Continue north in your original direction", 127));

        Controls = Story::Controls::STANDARD;
    }
};

class Story033 : public Story::Base
{
public:
    Story033()
    {
        ID = 33;

        Image = "images/magic-duel.png";

        Text = "\"I choose to use magic to fight this duel,\" you say, confident that your power is enough to beat any elf.\n\nThe King of the Elves smiles when he hears your choice -- a cool smile that induces doubt and imbues you with fear. You realize you have never seen an elf smile before; the action transforms the king's face, making him look quite human all of a sudden.\n\n\"You think to pit your magic against that of the elves? I will be the champion of elvendom in this duel: I can fashion a spell as well as any other standing here. We will use no death magics. We have potions to revive us if we are wounded. Don't make me kill you; submit if you feel my power overmastering yours.\"\n\nWith that he gestures you to take up position inside the grassy circle.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stand with the wind in your face", -33, Choice::Type::GET_CODEWORD, Codeword::Type::WINDFACE));
        Choices.push_back(Choice::Base("Stand with the wind at your back", -33));

        Controls = Story::Controls::STANDARD;
    }
};

class Event033 : public Story::Base
{
public:
    Event033()
    {
        ID = -33;

        Image = "images/magic-duel.png";

        Text = "The Elf King walks solemnly to the other side of the circle and waits confidently.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay in position opposite him", 76));
        Choices.push_back(Choice::Base("Try getting out of the duel by telling the king you should be measured against your foes, the Westermen, instead of the elves you have come to help", 92));

        Controls = Story::Controls::STANDARD;
    }
};

class Story034 : public Story::Base
{
public:
    Story034()
    {
        ID = 34;

        Text = "You could not possibly be near the Bonehill, which is several days travel to the east. The whole character of the forest here is very different from the area near the Bonehill. You can however, at least investigate the area where the whooshing noise came from.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 68; }
};

class Story035 : public Story::Base
{
public:
    Story035()
    {
        ID = 35;

        Text = "Elanor, today dressed in a silver gown of gossamer silk, turns to look at you searchingly as you walk underneath the hawthorn arch. She smiles and asks if you are feeling brave today.\n\nYou sense a sombre urgency behind her words, and, imitating a courtly bow, you reply, \"My lady, I have never felt more heroic!\"\n\n\"Good. Do you dare to glimpse your future, my hero?\"\n\nYou have always avoided fortune-tellers. You have noticed that if a fortune-teller gives good news, people go away happy and expect good fortune to turn up on a plate without them lifting a finger. If the soothsayer prophesies misfortune a sense of helplessness comes over people and they all too often sink into a despairing inactivity which leads to their downfall through sloth. Thus their prophecy is self-fulfilling. It is a well-known fact in Godorno that those soothsayers who always give good auguries are never short of customers, leading you to conclude that they often lie, pretending to see happy events when they should be giving bad news, good fortune when they should be giving bad tidings.\n\nYour worry on this score, however, is soon gone. Looking in the basin of smooth clear water it seems as though an artist is hurriedly painting a picture of ghoulish horror.\"The water shows what will come to pass if you do not succeed in your quest,\" says Elanor.\n\nThe picture is complete now in terrible detail, as if you were actually looking at the burnt remains of the forest. The trees have been chopped down as far as the eye can see. An infernal engine of some kind belches black smoke. Two hundred paces away you see a forge where a gigantic cauldron is suspended over a bonfire; six men constantly feed the fire with wood and charcoal. All the men working there have very pale skins, their faces long and thin, like hatchets. They shout to each other over the din of the engine in a language you don't understand.\n\nTeams of horses harnessed together pull logs to where groups of men cut them up ready for burning. A row of children sit nearby; they are darker skinned than men and have been set to toil over sharpening the saws.\n\nWhere the trees have been felled and stripped, men are torching the underbrush. They seem intent on killing everything that lives in the forest. A pall of smoke hangs like a storm-cloud over the scene.\n\nThen the vision shifts and the men have gone, leaving behind nothing but the grey ashes of death. All that remains of the forest is a few blackened stumps.\n\nYou gained the codeword CRABCLAW.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::CRABCLAW});
    }

    int Continue(Character::Base &player) { return 26; }
};

class Story036 : public Story::Base
{
public:
    Story036()
    {
        ID = 36;

        Text = "The dragon yawns, its fangs raking the sky twenty feet apart. You can see the glands inside its throat that produce the acid and poison for its deadly breath. The ancient beast could kill you in a moment.";

        Choices.clear();
        Choices.push_back(Choice::Base("Flee", 165));
        Choices.push_back(Choice::Base("See what fate intends for you if you feel brave enough", 127));

        Controls = Story::Controls::STANDARD;
    }
};

class Story037 : public Story::Base
{
public:
    Story037()
    {
        ID = 37;

        Image = "images/dark-figures.png";

        Text = "The smoking lamps produce little light, but peering through the gloom you can see several circular tables set about the hall, three near the fire and four back in the shadows. Two men, one tall and the other short and stocky, hog the fire and are engaged in conversation. Several dark figures are seated at the tables. One of these seems to be shrouded in a black travelling cloak.\n\n\"You, stranger. Do you fear enemies here? Why skulk in the shadows like a rogue? Step nearer the fire so we may see your face.\"\n\nYou can't even tell who spoke to you but he doesn't sound friendly.";

        Choices.clear();
        Choices.push_back(Choice::Base("Obey the command", 108));
        Choices.push_back(Choice::Base("Ignore it", 16));
        Choices.push_back(Choice::Base("Leave the inn", 117));

        Controls = Story::Controls::STANDARD;
    }
};

class Story038 : public Story::Base
{
public:
    Story038()
    {
        ID = 38;

        Text = "Once you are a safe distance from the pavilion, you run for the edge of the trees, quickly hiding yourself in the depths of the forest. The awful sights and sounds of the Westermen camp are soon far behind.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_CODEWORDS_ALL(player, {Codeword::Type::WATERBEARER, Codeword::Type::BULLHORN}))
        {
            Choices.push_back(Choice::Base("Head west", 43));
            Choices.push_back(Choice::Base("Head east", 70));
            Choices.push_back(Choice::Base("Head south-west", 270));
            Choices.push_back(Choice::Base("Head south from here", 78));
        }
    }

    int Continue(Character::Base &player) { return 53; }
};

class Story039 : public Story::Base
{
public:
    Story039()
    {
        ID = 39;

        Text = "Your plight is hopeless. You will never stagger out of the great forest weighed down as you are. One of the dark denizens of the deepest dark tracts of wood will catch you and skin you for the exotic hide you now wear. You will never escape. Because of your greed, the Forest of Arden is doomed.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story040 : public Story::Base
{
public:
    Story040()
    {
        ID = 40;

        Text = "\"The hackers and burners, the men from the west, say the ants of the forest must be eradicated because the ants eat their crops. What do you say?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Say the ants are indeed pests and should be wiped out", 75));
        Choices.push_back(Choice::Base("Reply that the forest would choke and die if there were no ants to eat the dead leaves and wood", 67));
        Choices.push_back(Choice::Base("[WILDERNESS LORE] Use your knowledge", 171, Skill::Type::WILDERNESS_LORE));

        Controls = Story::Controls::STANDARD;
    }
};

class Story041 : public Story::Base
{
public:
    Story041()
    {
        ID = 41;

        Image = "images/smoking-man.png";

        Text = "Elanor takes your hand once more and brushes the surface of the water again. The water is icy to your touch this time. A shiver of indefinable apprehension runs through you.\n\nA new picture forms. Elves with bows throng the depths of the forest. They have pale green skin and hair the colour of rich red wine. They are sniping at the Westermen, unseen. Men fall in swathes, pierced by the elves' arrows, but the Westermen come on and on, advancing towards some unseen goal. The elves fall back; it seems they are looking to you to do something decisive.\n\nA terrible figure stalks into view. You can't tell whether it is a man or some infernal magical machine. It looks like a full suit of armour, large enough for a giant of a man, that hisses steam at the joints. It bears a great sword which whistles through the air as it strides mechanically towards you.\n\nThe vision fades.\n\n\"Your moment of truth, hero. You must be prepared to fight the smoking man. Remember this vision, saviour, it shows the way to success in your quest,\" she says.\n\nShe pauses before continuing, \"Tomorrow will be Midsummer's day. It is time for you to go in search of the elves. But, my hero you must be careful. Tell them you are a friend of mine and they might not kill you, for they sometimes shoot a man dead with a single arrow before the hapless wanderer knows he is being watched. Harm neither hide nor leaf of the forest. Only by your feeling for nature will the elves judge you. Aside from that they are impartial. You could be a saint or a murderer among men, yet it would count for nothing among the elves.\"\n\nWhen she is sure you know the way she bids you farewell with one last warning. \"The FLUTE will be of no use to you, for I cannot save you from the elves if you anger them. Farewell.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 70; }
};

class Story042 : public Story::Base
{
public:
    Story042()
    {
        ID = 42;

        Text = "You are in the dark about the plans of Westermen.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to find their camp and spy on it", 270));
        Choices.push_back(Choice::Base("Lead as many elves as you can muster in pitched battle against the Westermen", 30));

        Controls = Story::Controls::STANDARD;
    }
};

class Story043 : public Story::Base
{
public:
    Story043()
    {
        ID = 43;

        Text = "After several days of trekking west through the forest, and climbing towards uplands, you reach the edge of the Anvil Mountains. Climbing high above the treeline you can see the Forest of Arden laid out beneath you almost like a map. You should have turned south if you wanted to reach the Bonehill, or south-west if you wanted to search for the bower of the Lady of the Forest. As it is you have wasted too much time, and you are far out of your way.\n\nYou re-enter the forest, journeying along the paths between its great trees. After the few days, however, you start to find the fresh bodies of hundreds of elves among the trees. It is as though they have all been slain instantly in the act of doing everyday things -- some while eating their supper. Whatever has caused this terrible has bereft the forest of life: it is doomed and so are you.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story044 : public Story::Base
{
public:
    Story044()
    {
        ID = 44;

        Text = "You travel on until you reach the next obstacle in your path: a tributary of the Sirion that is spanned by a rope bridge, the only means of crossing the water. The bridge has clearly been tended to recently, as bushes have been hacked back from the stanchions between which it hangs. Tentatively, you step onto the bridge, which holds your weight but sags more and more as you approach its centre.\n\nWhen you are half-way across, a waterspout erupts from the river beneath you, out of which flails a mass of vegetation ringed with fibrous tentacles. The water was thrown up by an Embracer, which plucks you from the bridge.";

        Choices.clear();
        Choices.push_back(Choice::Base("[UNARMED COMBAT] Grab the tentacles", 61, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("[SWORDPLAY] slice through the tentacles", 81, Skill::Type::SWORDPLAY));
        Choices.push_back(Choice::Base("Do something else", 103));

        Controls = Story::Controls::STANDARD;
    }
};

class Story045 : public Story::Base
{
public:
    Story045()
    {
        ID = 45;

        Text = "If you are near the dragon and the Bonehill you will need to turn to the right and travel several days to the west.";

        Choices.clear();
        Choices.push_back(Choice::Base("Turn right and travel to the west", 43));
        Choices.push_back(Choice::Base("Investigate the area from where the whooshing noise came", 68));

        Controls = Story::Controls::STANDARD;
    }
};

class Story046 : public Story::Base
{
public:
    Story046()
    {
        ID = 46;

        Text = "Elanor, today dressed in a silver gown of gossamer silk, turns to look at you searchingly as you walk underneath the hawthorn arch. She smiles at you.\n\n\"Well, my hero, do you feel brave today? Is your resolve strong enough to do what is needed of you?\"\n\n\"I have never felt more heroic, my noble lady,\" you reply, although you know in your heart of hearts that you felt considerably braver while you were wearing Elanor's EMERALD RING.\n\n\"Good,\" she replies. \"Do you dare to glimpse your future, my hero?\"\n\nYou have always avoided fortune-tellers. You have noticed that if a fortune-teller gives good news, people go away content and expect good luck to come their way without the need to lift a finger. If bad lack is prophesied, a sense of helplessness afflicts the person and they might sink into a despairing activity which leads to poverty and ruin. Thus the prophecy is self-fulfilling. It is well known that those soothsayers who invariably give good auguries are never short of customers, leading you to conclude that they must be pretending to see happy events even when they should be predicting bad news, since they will simply say what people want to hear.\n\nYour doubts in Elanor's case are soon dispelled. Looking into the basin of smooth clear water it seems as though an unseen artist is hurriedly painting a picture of ghoulish horror.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 3; }
};

class Story047 : public Story::Base
{
public:
    Story047()
    {
        ID = 47;

        Text = "As you set foot on the hillock you are surprised by how hard the ground feels, although it yields slightly as if a layer of hard rock were resting on mud. The ground is smooth and has a sheen to it: it only looked like grass. The egret stops its cackling and flies off.";

        Choices.clear();
        Choices.push_back(Choice::Base("Step back off the mound", 56));
        Choices.push_back(Choice::Base("Climb onwards", 66));

        Controls = Story::Controls::STANDARD;
    }
};

class Story048 : public Story::Base
{
public:
    Story048()
    {
        ID = 48;

        Text = "Your sword cuts cleanly through the fibres, lopping the tentacles into pieces. The Embracer emits a piercing shriek and subsides once more into the river. You swim to the far bank before the man-eating monster can recover.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 13; }
};

class Story049 : public Story::Base
{
public:
    Story049()
    {
        ID = 49;

        Text = "Leaving the blasted valley behind you, you strike north through the forest in search of the camp of the dreaded Westermen. The ground becomes hillocky and uneven. The trees -- hollies and elders -- are smaller here; you walk on past ever more spindly and sickly trees until you are faced by an impenetrable wall of thorns that rises up like the great cupola dome on top of the cathedral in Godorno.\n\nYou skirt the wall, which seems in actuality to be one great bush of thorns. Here and there the denseness of the growing bushes has gathered the remains of dead animals and pushed them out to its perimeter. One little group of bones looks suspiciously like those of a man or elf mouldering on the ground.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 99; }
};

class Story050 : public Story::Base
{
public:
    Story050()
    {
        ID = 50;

        Image = "images/zorolotl.png";

        Text = "The King of the Elves momentarily looks disappointed. He then casts his eyes about him to find a champion. A tall old elf stands forward, the first elf you have seen who carries a sword, which is strapped to his back.\n\nHe draws the blade from over his head with a flourish: it is slim with sharp, wavy edges. He looks quizzically at his king, and asks, \"Do we fight to the death, lord? If so, have no fear for me.\"\n\n\"You will duel until one of you submits or is killed. If you survive we have two of the Lady of the Forest's potions to revive you if you are wounded.\"\n\nTo you he adds, \"Don't make Zorolotl kill you. You should submit when you feel his skill with the sword overmastering yours.\"\n\nZorolotl walks to one side of the grassy circle and waits confidently, his sword held aloft.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take up your position opposite him. You are prepared to fight", 437));
        Choices.push_back(Choice::Base("Try to get out of the duel by protesting you should be measured against your fores, the Westermen, not against the elves you have come to help", 92));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.ZorolotlWounds = 0;
        player.LifePointsLost = 0;
    }
};

class Story051 : public Story::Base
{
public:
    Story051()
    {
        ID = 51;

        Text = "\"I am sorry but you have failed the test. You must leave the forest. Begone.\"\n\nElanor strides determinedly away from you, saying as she departs, \"I will set all the birds and the beasts against you. You have four days to leave the forest, never to return.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow her", 85));
        Choices.push_back(Choice::Base("Let her go and follow your own destiny", 73));

        Controls = Story::Controls::STANDARD;
    }
};

class Story052 : public Story::Base
{
public:
    Story052()
    {
        ID = 52;

        Text = "Knowing that he has just repulsed your attempt to take over his mind and knowing you to be defenceless, the left-hand image moves. It is the real King of the Elves, and he casts a spell of his own with a dramatic gesture. A luminous green halo pops forth from his fingertips. As it darts toward you the halo grows, and it encircles your waist before you can move. Your legs feel as if they have turned to jelly: you cannot stop yourself collapsing to the ground.\n\n\"Submit, mortal, I have defeated you,\" cries the Elf king.";

        Choices.clear();
        Choices.push_back(Choice::Base("Submit", 255));
        Choices.push_back(Choice::Base("Fight on", 272));

        Controls = Story::Controls::STANDARD;
    }
};

class Story053 : public Story::Base
{
public:
    Story053()
    {
        ID = 53;

        Text = "Knowing what the Westermen plan for the Tree of Life, you determinedly hurry back to relay your information to the elves. Travelling along routes that seem to come unbidden to your mind, you reach a clearing that seems strangely familiar.\n\nYour arrival is anticipated. An elf is waiting to return you to Elvenhame so you might hold a council of war. With a guide, you quickly make it to the fabulous home of the forest dwellers.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 256; }
};

class Story054 : public Story::Base
{
public:
    Story054()
    {
        ID = 54;

        Text = "What is the dragon's name?";

        Choices.clear();
        Choices.push_back(Choice::Base("Gwelphstar", 6));
        Choices.push_back(Choice::Base("Garoshtar", 83));
        Choices.push_back(Choice::Base("Skardrig", 93));
        Choices.push_back(Choice::Base("Bethshebel", 102));

        Controls = Story::Controls::STANDARD;
    }
};

class Story055 : public Story::Base
{
public:
    Story055()
    {
        ID = 55;

        Image = "images/filler3.png";

        Text = "A tall man and his short and stocky companion move apart to allow you room in front of the roaring log fire. Both give you a sidelong glance. They look rough and weather-beaten men: the smaller of the two has a face like a bull-mastiff, the taller has the sly cunning look of a fox.";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell them who you are and why you have come to Burg", 72));
        Choices.push_back(Choice::Base("Remain silent", 94));

        Controls = Story::Controls::STANDARD;
    }
};

class Story056 : public Story::Base
{
public:
    Story056()
    {
        ID = 56;

        Image = "images/garoshtar.png";

        Text = "You step back off the mound, which begins to shake as if there was an earthquake. The ground you have stepped back onto is quite firm, but even so you can feel the vibrations rocking you slightly.\n\nThe whole of the green hillock suddenly rolls upwards and away from you, leaving you standing on the edge of a ledge with a twenty-foot drop. As the hillock moves it creases and splits apart.\n\nThe dragon, for that is what the hillock really is, moves slowly as it wakes from its slumber. Turning its great scaly neck like a corkscrew, the ancient creature looks back over its shoulder at you. Its smouldering red eyes, as terrifying as the portals to hell, gaze at you from a craggy face the size of a cart.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leap at its head to attack it before it is fully awake", 74));
        Choices.push_back(Choice::Base("Smile at it in the hope that it will not eat you, while preparing a spell", 36));

        Controls = Story::Controls::STANDARD;
    }
};

class Story057 : public Story::Base
{
public:
    Story057()
    {
        ID = 57;

        Text = "By the time you are directed to where the King of the Elves is preparing the defences, he is in position with his elven army in the trees around the Tree of Life itself.\n\nThe forest falls still. There are thousands of elves in the trees around the clearing but they make no sound. Even the animals and birds have fallen unnaturally silent. You look around and savour the beauty of this enchanted place, the fountain of all life. This may well be the last chance you ever have to revel in the natural glory of the Forest of Arden.\n\nThe sun breaks through the rolling clouds and bathes the clearing in brilliant light. The trumpets of the tree lilies swing round to greet the sun. You expect to hear the elves cheer at this good omen, but they remain grimly silent.\n\nThe oppressive din of the tramping of feet of thousands upon thousands of enemies grows inexorably closer. There is a crack like a firecracker as a tree is split and knocked to the ground by the passing of one of the great metallic monsters.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 434; }
};

class Story058 : public Story::Base
{
public:
    Story058()
    {
        ID = 58;

        Text = "\"A battle of wits?\" The Elf King rises to this like a cat confronted with a helpless mouse. \"Very well, let us set an impossible task. He who fails to achieve the task has lost the contest.\"\n\nYou are on the point of asserting that an impossible task by definition can never be achieved, but then you remember that elves abide by a contrary sort of logic. In any case, this is a test of your skill as a trickster. You nod your head. \"Agreed.\"\n\nThe Elf King looks about him, then picks up a stone from the ground. Plucking a thread from the hem of his robe, he holds it between thumb and forefinger and says, \"Be rigid.\" Instantly the thread staightens like a length of steel wire. \"Curl.\" adds the Elf King, and now the thread twists into a corkscrew shape. Finally, he says, \"Penetrate,\" and drives the thread into the stone. It winds right through as you might push a nail through a lump of butter. \"Return again to thread,\" says the Elf King, and he holds the stone up dangling on the limp thread.\n\nYou take it from him. \"And what am I to do?\"\n\n\"Withdraw the silk from the stone,\" he says, \"Then thread it back through.\"\n\n\"Easy enough.\" You pull out the thread, then go over to a tree where you moisten the end with a drop of sticky sap. Next you find an ant crawling amid the leaf litter and glue the thread to its abdomen with the sap. As the ant wriggles, you lower it over the hole in the stone. It takes several attempts, but finally the ant crawls into the tiny hole. The Elf King glowers inscrutably as you hold up the stone and wait. Knowing that the ant is unable to turn around, it is only a matter of time before it emerges from the other end of the hole. You detach the ant and hand the stone back to the Elf King -- once more with the silk neatly threaded through it.\n\nHe casts it aside. \"Another task -\" He begins.\n\n\"Now it is my turn to set a task,\" you protest. \"You have just set one.\"\n\n\"That was by way of being an example of what was needed. Now we begin the contest proper.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree to attempt another task that he sets you", 187));
        Choices.push_back(Choice::Base("Accept a more conventional duel because you think you might fail a second try", 18));

        Controls = Story::Controls::STANDARD;
    }
};

class Story059 : public Story::Base
{
public:
    Story059()
    {
        ID = 59;

        Text = "The dragon pins you to the ground beneath a huge claw. You look up from the massive green scaled claw to the beast's smouldering red eyes some thirty feet above. Clearly it wasn't as sleepy as you thought and your actions have made it think you were trying to kill it. The dragon opens its jaws wide and its stomach convulses. A second later a gout of poisonous gas and acid hits you like a suffocating and burning wave. There is no surviving the breath of an ancient green dragon.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story060 : public Story::Base
{
public:
    Story060()
    {
        ID = 60;

        Text = "The hairs on the nape of your neck begin to bristle as you step quietly between the Greenbark trees. You sense you are being watched.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hide", 80));
        Choices.push_back(Choice::Base("Stop and look about you", 90));
        Choices.push_back(Choice::Base("Call out that you are Elanor's friend come in search of the immortal elves", 109));

        Controls = Story::Controls::STANDARD;
    }
};

class Story061 : public Story::Base
{
public:
    Story061()
    {
        ID = 61;

        Text = "You grab two flailing tentacles, haul yourself towards the creature's cone-shaped head and smash your fist repeatedly between its murky grey eyes. Its coils loosen and fall away, and you break the surface gasping for air. Swimming to the far bank, you scramble out before the Embracer can recover.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 13; }
};

class Story062 : public Story::Base
{
public:
    Story062()
    {
        ID = 62;

        Text = "The innkeeper's daughter is overjoyed to see her father returned. The innkeeper is as good as his word and he kills a fattened pig to give you a banquet fit for a king.\n\nAll too soon, however, you have to leave their pleasant hospitality behind and return to your quest. Yet you are already too late. As you journey back towards the Sirion river the Westermen have found the Tree of Life and cut it down. The forest is doomed and so, in the end, is all mankind. You have failed: the long winter is beginning.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story063 : public Story::Base
{
public:
    Story063()
    {
        ID = 63;

        Image = "images/gathkeri.png";

        Text = "Deciding your best chance of success in the duel is to use unarmed combat, you inform the King of the Elves of your choice. He scowls at you, then looks about him for a champion.\n\nOne of the few young elves walks forward. He is the only elf you have ever seen who you could describe as reasonably well built. His muscles are long and well defined. You have noticed how swift and deft the other elves are, and noted their surprising wiry strength. The young elf could prove to be a difficult adversary.\n\nHe walks forward, rocking up onto the balls of his feet, like a spring-heeled Jack, looks towards the king and asks, \"Do we fight to the death, Lord? Have no fear for me.\"\n\n\"You will duel until one of you submits or is killed,\" answers the king. \"If you survive we have two of the Lady of the Forest's potions to revive those who are wounded.\"\n\nGathkeri walks to one side of the grassy circle and waits confidently with his arms folded in front of him. He appears to be concentrating hard and mumbling.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take up your position opposite Gathkeri", 201));
        Choices.push_back(Choice::Base("Try to get out of the duel by protesting to the king that you should be measured against your foes, the Westermen, not against the elves you have come to help", 92));

        Controls = Story::Controls::STANDARD;
    }
};

class Story064 : public Story::Base
{
public:
    Story064()
    {
        ID = 64;

        Text = "Speaking the word you clench your fist, imagining you are twisting and crushing the entrails of the Infernal Statue. The machine does not buckle or hold its stomach, as must a man affected by this puissant spell. Instead it lurches past the Tree of Life, then circles and lurches forward again, towards the deep blue pool.\n\nThe cries of the Westermen die to silence. In the resulting quiet you can hear muffled groans coming from somewhere inside the Infernal State. It totters on the brink of the pool and then begins to turn slowly back towards the Tree of Life. It seems to be recovering and will not be harmed by the spell again.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Bafflement", 372));
        Choices.push_back(Choice::Base("Cast Tower of Will", 207));

        Controls = Story::Controls::STANDARD;
    }
};

class Story065 : public Story::Base
{
public:
    Story065()
    {
        ID = 65;

        Text = "Your sudden rush takes him by surprise as he was preparing a spell. Just before you reach him he calls out the word \"Sanctuary\" in a ringing voice and claps his hands together. There is a second clap and he is gone. He has disappeared completely. You go to the door of the inn but there is no sign of him in the rain-lashed cobbled street.\n\nOnly the old woman in grey remains in the common room. She nods at you approvingly.";

        Choices.clear();
        Choices.push_back(Choice::Base("Sit at her table and talk to her", 181));
        Choices.push_back(Choice::Base("Take a room in the inn for the night", 333));

        Controls = Story::Controls::STANDARD;
    }
};

class Story066 : public Story::Base
{
public:
    Story066()
    {
        ID = 66;

        Text = "You have taken a few more steps when the ground starts to shake. It feels like an earthquake and you fall down. Then the very ground beneath you hurtles skyward. There is a sudden hissing and a cloud of noisome vapours suddenly spurs from the other end of the hillock, giving the game away. You are lying on a dragon.\n\nThe dragon rolls over, away from the ledge it has been slumbering against, and as it does so you clamber up its back -- an experience that is like scrambling up the side of a gigantic rolling barrel -- and manage to grab hold of the bottle-green row of scales that runs in a crest down the creature's back.\n\nMoving slowly as it wakes from its lengthy slumber, the dragon turns its necks like a corkscrew and points its cart-sized face at you. Its smouldering red eyes are like the gateways to hell.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leap at its head to attack the dragon before it becomes fully awake", 74));
        Choices.push_back(Choice::Base("Smile at the dragon in the hope that it doesn't eat you", 36));

        Controls = Story::Controls::STANDARD;
    }
};

class Story067 : public Story::Base
{
public:
    Story067()
    {
        ID = 67;

        Text = "\"The Westermen hate spiders. They say the spiders are ugly, poisonous and unnatural. To them spiders are the evil creatures of the Demoness. It does no harm to the forest to kill a spider. Are they right, these Westermen?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Say there is no harm in killing spiders", 51));
        Choices.push_back(Choice::Base("Say it is bad to kill spiders", 106));
        Choices.push_back(Choice::Base("Use [WILDERNESS LORE]", 136, Skill::Type::WILDERNESS_LORE));

        Controls = Story::Controls::STANDARD;
    }
};

class Story068 : public Story::Base
{
public:
    Story068()
    {
        ID = 68;

        Text = "Pushing through the ferns you come to a desolate area of worn rock. The breeze carries the acrid smell of sulphurous gases. The few plants growing here are wizened and brown, struggling on the edge of survival. The strange gurgling sound starts again, further away. The smoke rises out of the ground ahead of you followed by a watery burp.";

        Choices.clear();
        Choices.push_back(Choice::Base("Run away", 32));
        Choices.push_back(Choice::Base("Otherwise", 88));

        Controls = Story::Controls::STANDARD;
    }
};

class Story069 : public Story::Base
{
public:
    Story069()
    {
        ID = 69;

        Image = "images/filler2.png";

        Text = "The Elf King raises his open hand in front of your face, palm upwards. It looks empty, but when he blows across it a flurry of fine ochre pollen flies into your eyes. Stumbling back, you wipe the pollen out of your eyes. It stings, causing tears to run down your face, and by the time your vision clears the elves have melted away into the forest depths. You are alone in the clearing.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 78; }
};

class Story070 : public Story::Base
{
public:
    Story070()
    {
        ID = 70;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS_ALL(player, {Codeword::Type::WATERBEARER, Codeword::Type::BULLHORN}))
        {
            return 256;
        }
        else if (Character::VERIFY_CODEWORD(player, Codeword::Type::WATERBEARER))
        {
            return 42;
        }
        else
        {
            return 60;
        }
    }
};

class Story071 : public Story::Base
{
public:
    Story071()
    {
        ID = 71;

        Text = "Your will invades the mind of the King of the Elves while he is still reeling from the effects of your Bafflement spell. As his senses return to him, you realize that his mind has been toughened beyond comprehension by the centuries of leading all elvendom, and the responsibility and judgment such a position requires. Quickly you grasp the moment to force him to speak the words of submission. You have won the duel.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 263; }
};

class Story072 : public Story::Base
{
public:
    Story072()
    {
        ID = 72;

        Text = "You tell them of your quest to find the Tree of Knowledge in the Forest of Arden. The tallest of the two men introduces himself as Renard the Guide.\n\n\"If you seek the Tree of Knowledge, you will need a guide. The forest hold many snares, and its ways are treacherous. If you enter there alone you'll surely perish. That or you'll be hopelessly lost, never to see the lands of men again.\"\n\n\"Ha!\" snorts the short man. \"Renard doesn't know the whereabouts of the tree you seek, I'll warrant.\"\n\nThe hunter turns away, quietly saying as his parting shot, \"About as much as you, Renard, and that's nothing at all.\" He walks over to the kitchen door to talk to the young woman who pours him a jug of beer.\n\nRenard sits down at the table, pulls up a second chair, and gestures you to join him.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask him about the Tree of Knowledge", 130));
        Choices.push_back(Choice::Base("Learn about the other travellers in the inn", 145));

        Controls = Story::Controls::STANDARD;
    }
};

class Story073 : public Story::Base
{
public:
    Story073()
    {
        ID = 73;

        Text = "You stand up sharply when a thorn suddenly grows out of the branch on which you are sitting and pricks your bottom.\n\nThe appearance of the Lady in Grey changes. she is old again, as she appeared in the inn. She looks weary and downcast but resolute. \"If you do not quit the forest quickly the birds and the beasts will see to it that you never return to the lands of men.\"\n\nYou wander in the forest for many days. One day, you come across the bodies of hundreds of elves lying among the trees. It looks as though someone had just switched off their life force all at once -- some even died in the middle of eating their supper. The forest is doomed and so are you.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story074 : public Story::Base
{
public:
    std::string PreText = "";

    Story074()
    {
        ID = 74;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "It is a difficult leap, made harder by the dragon slowly rearing up onto its legs.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            PreText += "\n\nYou leap into the air but the dragon twitches its head away and you miss the target. With nothing to land on, you plummet twenty feet to the ground, landing almost underneath one of the creature's massive claws.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 86;
        }
        else
        {
            return 59;
        }
    }
};

class Story075 : public Story::Base
{
public:
    Story075()
    {
        ID = 75;

        Text = "\"The Westermen hate spiders. They say the spiders are ugly, poisonous and unnatural. To them spiders are the evil creatures of the Demoness. It does no harm to the forest to kill a spider. Are they right, these Westermen?";

        Choices.clear();
        Choices.push_back(Choice::Base("There is no harm in killing spiders", 51));
        Choices.push_back(Choice::Base("It is bad to kill spiders", 89));

        Controls = Story::Controls::STANDARD;
    }
};

class Story076 : public Story::Base
{
public:
    std::string PreText = "";

    Story076()
    {
        ID = 76;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::WINDFACE))
        {
            PreText = "You take up position in the circle on the east side, where the ground is uneven and the wind is in your face.";
        }
        else
        {
            PreText = "You take up position in the circle on the west side, where the ground is flattest and the wind is at your back.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 110; }
};

class Story077 : public Story::Base
{
public:
    Story077()
    {
        ID = 77;

        Text = "Nothing in your life so far has prepared you for the first sight of the great Sirion river. The furthest bank -- or perhaps it is just a large island in midstream -- seems to be three miles away. Its roiling waters carry a multitude of dead tree branches towards the sea, like a vein carrying detritus out of a body.\n\nAcross the river the treeline is unbroken. You are deep in the rainforest now. The gigantic trees spread their branches more than a hundred feet from the ground here. At the river's edge mangroves reach far out into the water; bloated river buffalo shelter beneath their arching roots. It is hard going here. At every other step you sink into oozing mud.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 44; }
};

class Story078 : public Story::Base
{
public:
    Story078()
    {
        ID = 78;

        Text = "You trudge on, singling out and mentally marking individual trees as far away as you can see with the object of keeping them in sight so you don't walk in circles. Each time you reach your target tree you look back and try to identify the one you left behind so that you can choose another tree to make for in the same general direction. It is tiring work, and it exhausts you in body and mind.\n\nAs you walk on you eventually see gaunty grey crags jump out of the forest. It is a relief to find clear landmarks at last. The forest is broken here, as only grass can grow on where the soil is thin above the grey rock.\n\nYou walk out of the gloom into bright sunlight that hurts your eyes. There are countless paths leading back into the forest in all directions. As you stand contemplating which way to choose, a voice above and behind you says, \"Lost, are you?\"\n\nYou turn round and look up. All you can see is a silver-feathered owl perched on top of an outcrop.\n\n\"Lost, are you?\" the voice says again. It sounded as if the voice came from the owl but its beak didn't move.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!(Character::VERIFY_ITEMS(player, {Item::Type::EMERALD_RING_ELANOR}) && Character::VERIFY_CODEWORD(player, Codeword::Type::CRABCLAW)) && !(Character::VERIFY_ITEMS(player, {Item::Type::EMERALD_RING_ELANOR}) && Character::VERIFY_CODEWORD(player, Codeword::Type::TWINHEAD)))
        {
            Choices.push_back(Choice::Base("Admit you are lost", 258));
            Choices.push_back(Choice::Base("Ignore the voice and walk on, picking one of the many ways at random", 277));
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::EMERALD_RING_ELANOR}) && Character::VERIFY_CODEWORD(player, Codeword::Type::CRABCLAW))
        {
            return 440;
        }
        else
        {
            return 459;
        }
    }
};

class Story079 : public Story::Base
{
public:
    Story079()
    {
        ID = 79;

        Text = "The dragon seems to read your mind. The monster flicks its tails and licks its lips.\n\n\"Walk into the cavern and behold my hoard which has been garnered from palaces across the whole world. Many of my treasures are old, so very old, that they have a tale to tell.\"\n\nThe dragon bats you with a mighty claw, bowling you over so you fall to the ground. Once you have gotten back on your feet, the ancient creature ushers you forward into the dark cavern. Entering, you stop for a moment to adjust to the dim light. Blinking in astonishment, your jaw goes slack at the sight before you. You stare in awe at the veritable mountain of golden coins, goblets, candelabra and jewellery that comprise the dragon's treasure trove.\n\n\"All the gold and jewels you can carry I give to you,\" says the dragon.\n\nAt the creature's words, some of the coins fly up into the air and push themselves against you. Soon you are covered in a golden crust which has gathered like barnacles do on the hull of a ship. Although your arms and legs are left free, you are terribly weighed down by the fortune that is now stuck to you. You try to prise the coins away but they are stuck fast by the magic of the dragon.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 19; }
};

class Story080 : public Story::Base
{
public:
    Story080()
    {
        ID = 80;

        Text = "You hide underneath a clump of bushes for what seems an age. Here in the deepest part of the forest you can only guess that it is still daytime. When you are certain that you can hear and see nothing, you emerge from your hiding place and decide to journey on.\n\nYou have walked but half a mile further when the feeling of being watched returns.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hide again", 129));
        Choices.push_back(Choice::Base("Stop and look around you", 90));
        Choices.push_back(Choice::Base("Walk on seemingly unaware", 150));
        Choices.push_back(Choice::Base("Try calling out that you are Elanor's friend come in search of the immortal elves", 109));

        Controls = Story::Controls::STANDARD;
    }
};

class Story081 : public Story::Base
{
public:
    Story081()
    {
        ID = 81;

        Text = "As the Embracer prepares to wrap you up in its tentacles, the smell of rot and marsh gas almost makes you gag. The tips of the fibrous tentacles wave in the air as if trying to sniff you out.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to climb the great mass of vegetation and drive your sword between its eyes", 287));
        Choices.push_back(Choice::Base("Slash at the other tentacles as it is preparing to coil around you", 48));

        Controls = Story::Controls::STANDARD;
    }
};

class Story082 : public Story::Base
{
public:
    Story082()
    {
        ID = 82;

        Text = "You speak the word and a magical silver shield appears to protect you from magic. But there is no one here using magic against you. You are wasting precious time. Now is your last chance to save the Tree of Life.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Choking Fog", 346));
        Choices.push_back(Choice::Base("Cast Bafflement", 113));
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 64));
        Choices.push_back(Choice::Base("Cast Tower of Will", 186));

        Controls = Story::Controls::STANDARD;
    }
};

class Story083 : public Story::Base
{
public:
    Story083()
    {
        ID = 83;

        Text = "\"Great Garoshtar, aid me now. Listen to and respect your friend's wishes -- the forest needs your help.\"\n\nGaroshtar's great head rises slowly above you and his red eyes bore into yours.\n\n\"I need your help now, Garoshtar. The Westermen are marching to uproot the Tree of Life.\"\n\nThe dragon is ready to bear you and to frighten the Westermen into the bargain. You ask him to attack the head of the Westermen columns as they advance, to give time for the King of the Elves to muster all his available forces. You climb onto Garoshtar's back and sit just in front of the great taut wings that beat the air like mainsails close-rigged in a storm.";

        Choices.clear();
        Choices.push_back(Choice::Base("Remain astride Garoshtar's back while he attacks the Westermen", 228));
        Choices.push_back(Choice::Base("Get him to deliver you to Elvenhame before making his attack", 247));

        Controls = Story::Controls::STANDARD;
    }
};

class Story084 : public Story::Base
{
public:
    Story084()
    {
        ID = 84;

        Text = "As the Westermen close in on you with swords and maces, you defend yourself as best as you can while the Infernal Statue hews great lumps of green stained wood from the trunk of the Tree of Life. You fight like a hero, but for every foe you kill two more take his place. At the last your feet are knocked out from under you and your body is pierced by countless sword thrusts. You have failed the forest: it will be destroyed by the Westermen.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story085 : public Story::Base
{
public:
    Story085()
    {
        ID = 85;

        Text = "She will not listen as you ask her to stop and she moves so lightly you have a hard time keeping up.\n\n\"What have I done to upset you?\" you ask. \"I can't help it if I don't know the ways of the forest as you do. I've had a hard life on the streets of Godorno. I didn't know what I would find here in the forest. Don't leave me here...\"\n\nYour pleas are useless: you cannot change her mind.\n\nShe flits between a curtain of creepers and down a secret tunnel, leaving you with an inexplicably strong feeling of loss. You try to find the concealed opening, but after hours of fruitless searching you reluctantly admit you have no choice but to follow your own destiny.\n\nYou wander in the forest for many days, until you come across the bodies of hundreds of elves lying among the trees. They are like figures of clay, cold and limp without the spark of life. You realize that the most terrible of fates have come to pass: the Westermen have succeeded in destroying the heart of the forest. You slump to your knees in despair as you hear their engines of destruction cutting through the trees towards you. Soon you will share the doom of the elves.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story086 : public Story::Base
{
public:
    Story086()
    {
        ID = 86;

        Text = "Your agile leap carries you into the monster's face, where you clutch at the beast's long thick whiskers to stop yourself falling off. You are right next to the dragon's mouth and your eyes are looking straight into its cavernous nostrils. But how will you take advantage of your precarious position?";

        Choices.clear();
        Choices.push_back(Choice::Base("Scramble up on top of the ancient creature's head", 116));
        Choices.push_back(Choice::Base("Pat the dragon gently on the end of its great scaly nose", 125));

        Controls = Story::Controls::STANDARD;
    }
};

class Story087 : public Story::Base
{
public:
    Story087()
    {
        ID = 87;

        Text = "A silver noose magically appears in the air before you and drops over your head. You try to drag the noose up and over your head, but the silvery cord tightens slowly until it flattens your windpipe. You grow purple owing to the lack of oxygen and the great effort you are putting into staying alive.\n\nIt is a futile struggle. Gurgling horribly, unable even to speak, you subside into the floor and black out, never to regain consciousness.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story088 : public Story::Base
{
public:
    Story088()
    {
        ID = 88;

        Text = "For a long while nothing happens. Nervously you begin to edge closer to the source of the strange sounds. There is a ledge ahead and you can't see what lies beyond.\n\nThere is a sudden dire hissing, as if a hundred vipers were baring their venomous fangs or perhaps it is an ancient dragon drawing breath. Then another whoosh followed by an eruption of hot water that fountains into the air gives you the solution to the mystery. There is no dragon here and you are indeed, nowhere near the Bonehill. Walking to the edge you see a cluster of large bubbling pools. All you have found is an area of hot springs. Every now and then a geyser erupts; gurgling that follows is the escape of foul-smelling gases. There is nothing of interest here so you go on your way.";

        Choices.clear();
        Choices.push_back(Choice::Base("Turn and head west from here", 43));
        Choices.push_back(Choice::Base("Continue north in your original direction if you prefer", 127));

        Controls = Story::Controls::STANDARD;
    }
};

class Story089 : public Story::Base
{
public:
    Story089()
    {
        ID = 89;

        Text = "\"Why is it bad to kill spiders?\" she asks.";

        Choices.clear();
        Choices.push_back(Choice::Base("Say it is because all evil things as well as good things must be tolerated in the forest", 104));
        Choices.push_back(Choice::Base("Say you believe it is because the birds would die without spiders to eat, and without birds to eat berries there would be no young trees ", 128));

        Controls = Story::Controls::STANDARD;
    }
};

class Story090 : public Story::Base
{
public:
    Story090()
    {
        ID = 90;

        Text = "You stop still in your tracks and start to stare about, thinking to catch an elf slyly peeking at you from behind a tree.\n\nThere is the rushing whine of an arrow and a stabbing pain between your shoulder-blades. The force of the shot spins you round enabling you to see your assailant.\n\nIt is a tall, proud elf, who stands between two Greenbark trees, his legs apart. He lets his bow fall to his side as your legs buckle under you. Your nameless attacker is a fine shot: his arrow has pierced your lung. Slowly you begin to drown in your own blood.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story091 : public Story::Base
{
public:
    Story091()
    {
        ID = 91;

        Text = "You marshal your thoughts and unleash the magic that begins a struggle of wills. Seconds after your eyes have glazed with the effort you realize your mistake. The centuries of being the one on whom all elvenkind has depended for leadership have hardened the king's will. He quickly exerts his power over your feeble mind. Your body trembles with the effort of trying to resist, but none the less you find yourself walking forward step by step until you are in front of the king. He compels you to kneel before him. Powerless to resist, you speak the words of submission. You have lost the duel.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 163; }
};

class Story092 : public Story::Base
{
public:
    Story092()
    {
        ID = 92;

        Text = "\"You would have us risk our lives in battle with a hundred thousand Westermen, yet you will not dare face one elf in a duel? You are no better than the other humans.\" The king's voice is loaded with contempt. \"We will have no dealings with you. Slay the coward.\"\n\nYou begin to expostulate, but they are already drawing back on the bowstrings.\n\n\"Alright, I'll fight the duel,\" you cry. \"It won't prove anything, aahhh!\" The first arrow pierces your windpipe -- it is followed by many more. You die spurned by all elvendom.\"";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story093 : public Story::Base
{
public:
    Story093()
    {
        ID = 93;

        Text = "You call out the dragon's name and its great head rears slowly above you and its eyes bore into yours. Its nostrils dilate as it sucks in a deep breath. Too late you realize you lied to yourself about knowing the dragon's real name as it breathes acid and gas down on you. The intense burning and blistering that follows wracks your body with pain. Yet the torment is mercifully brief, as you quickly lapse into unconsciousness and then the permanent sleep of death.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story094 : public Story::Base
{
public:
    Story094()
    {
        ID = 94;

        Text = "Ignoring you, the two men continue their conversation about hunting in the forest. The shorter of the two becomes insulting when the taller claims to know the forest better than he.\n\n\"There are things in the forest which you wouldn't dare look upon, yet which I have seen with my own eyes.\"\n\n\"What things?\"\n\n\"Terrible things, green ghosts that walk through trees, phantasms and, in the darkest depths beyond Sirion, a huge monster as big as a hill.\"\n\n\"You've been too long alone in the forest. All your pent-up thoughts turn to babble.\"\n\n\"I saw it, it blinked its great eye at me. An eye like a salver big enough to carry a boar's head.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell them of your quest to the forest now", 162));
        Choices.push_back(Choice::Base("As your eyes become accustomed to the light and you can see the other travellers in the inn; look them over before before choosing a table", 176));

        Controls = Story::Controls::STANDARD;
    }
};

class Story095 : public Story::Base
{
public:
    Story095()
    {
        ID = 95;

        Text = "You jump nimbly and quickly over a stack of books and slink out between the chief's advisers. The guards at the porch don't notice you bass between them and you are soon safe back in the forest. The awful sights and sounds of the Westermen camp are soon far behind.";

        Choices = Story::FourDirections();

        Controls = Story::Controls::STANDARD;
    }
};

class Story096 : public Story::Base
{
public:
    Story096()
    {
        ID = 96;

        Text = "Nothing in your life so far has prepared you for the first sight of the great Sirion river. The furthest bank -- or perhaps it is just a large island in midstream -- seems three miles away. Its roiling waters carry a multitude of dead tree branches towards the sea, like a vein carrying detritus out of a body.\n\nAcross the river the treeline is unbroken. You are deep in the rainforest now. The gigantic trees spread their branches more than a hundred feet from the ground here. At the river's edge mangroves reach far out into the water; bloated river buffalo shelter beneath their arching roots. It is hard going here. At every other step you sink into oozing mud. Twice you nearly lose your life in the oozing mud: once when a vine you were clinging to snaps, and again when a huge river buffalo erupts out of the water between the mangrove and rushes you. It storms through the water margin and crashes into the trees in hot pursuit. Soon the trees are too thick for it to follow and you trudge on, abandoning the river bank. Quite lost by now, you hope you can find a landmark to guide you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 131; }
};

class Story097 : public Story::Base
{
public:
    Story097()
    {
        ID = 97;

        Image = "images/filler4.png";

        Text = "The chief shakes his head. \"My new realm will never be safe until I have destroyed every last tree in the forest. Valerian tells me so and his counsel has always been good in the past.\"\n\n\"But the whole world needs the forest,\" you argue. \"Without the forest there would be no air to breathe. We will all die.\"\n\n\"Valerian doesn't want to die any more than either you or I, I'll warrant. What nonsense is this you talk?\" He narrows his eyes, suddenly suspicious. \"Where was it we met? Was it the Reaver's Inn in Bessaraban? Remind me.\" He screws up his eyes in the effort of remembering a meeting that you know never took place.";

        Choices.clear();
        Choices.push_back(Choice::Base("Pretend that you met in the Reaver's Inn in the far off city of Bessaraban", 204));
        Choices.push_back(Choice::Base("Make up an excuse and leave", 305));

        Controls = Story::Controls::STANDARD;
    }
};

class Story098 : public Story::Base
{
public:
    Story098()
    {
        ID = 98;

        Text = "The Lady of the Forest watches your departure sadly, but she does nothing to prevent you leaving. How can she be grieving at your loss when she hardly knows you? She must be mad. Nevertheless you quit her beautiful garden with regret and continue your quest for the Tree of Knowledge.\n\nIt will soon be Midsummer's day. Where will you search for the tree next?";

        Choices.clear();
        Choices.push_back(Choice::Base("Head west", 43));
        Choices.push_back(Choice::Base("Head east", 427));
        Choices.push_back(Choice::Base("Head south-west", 70));

        Controls = Story::Controls::STANDARD;
    }
};

class Story099 : public Story::Base
{
public:
    Story099()
    {
        ID = 99;

        Text = "You pass several of the great Umbellifer bushes, so called because of their bell shape. You walk on between them, where only grass that has been cropped by deer grows, until you come to an archway that has been cut through the thorns to provide a way into the shadowy recesses of the immense bush.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go inside the bush", 119));
        Choices.push_back(Choice::Base("Hurry past with not so much as a backward glance", 127));

        Controls = Story::Controls::STANDARD;
    }
};

class Story100 : public Story::Base
{
public:
    Story100()
    {
        ID = 100;

        Text = "As you walk towards the guards you are horrified to see them spearing the animals that are fleeing the burning brush. The men throw the unfortunate beasts onto the fire beneath the great cauldron. The others laugh merrily as if they could think of no better sport than to wantonly slaughter helpless beasts.\n\nYou call a greeting above the hissing of the steam bellows that is rising and falling, driven by the metal machine. The guards stand up and fan out as if to surround you, without a word of command.\n\n\"Search the southerner for weapons,\" shouts their captain.";

        Choices.clear();
        Choices.push_back(Choice::Base("Surrender and let them search you", 151));
        Choices.push_back(Choice::Base("Fight your way out", 202));

        Controls = Story::Controls::STANDARD;
    }
};

class Story101 : public Story::Base
{
public:
    Story101()
    {
        ID = 101;

        Text = "Your spell of Bafflement crosses unseen the space that separates you and the King of the Elves, silently invading his mind. His eyes look at you, blankly uncomprehending, and the two false images that his magic created just flicker and die away. The king is powerless; he is far too confused to attempt a spell or even move from the spot. Unfortunately he is also too baffled to realize the time has come for him to submit to you and acknowledge you the winner of the duel.\n\nUnder the rules of a duel you can only use magic to subdue him so you let the Bafflement fade and prepare another spell.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 111));
        Choices.push_back(Choice::Base("Cast Tower of will", 71));

        Controls = Story::Controls::STANDARD;
    }
};

class Story102 : public Story::Base
{
public:
    Story102()
    {
        ID = 102;

        Text = "You call out the dragon's name. Its great head rears slowly above you and his glittering eyes bore into yours. His nostrils dilate as he sucks in a deep breath. Too late, you realize you were wrong about knowing the dragon's name. There is a terrible whooshing sound as the dragon's breath of acid and gas roars towards you. The torrent of gas and air rolls you across the ground and you are lucky to bang your head on a rock and spare yourself a more painful death.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story103 : public Story::Base
{
public:
    Story103()
    {
        ID = 103;

        Text = "It was a mistake to enter the forest without a guide. There is no time to do anything as the Embracer sucks you down into the murky depths. You struggle desperately hard but, unable to breathe, your strength soon fails you and you drown in the clutches of this hideous creature.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story104 : public Story::Base
{
public:
    Story104()
    {
        ID = 104;

        Image = "images/filler2.png";

        Text = "\"The men who have come to the forest say that when the trees have been felled the undergrowth should be burned to clear it for humans to live in. They say burning returns all the goodness in the plants to the soil so that crops can flourish. Do you agree with them?\" asks Elanor.";

        Choices.clear();
        Choices.push_back(Choice::Base("Admit that you have no reason to disbelieve them", 51));
        Choices.push_back(Choice::Base("Say instead that the forest should be kept as it is for it makes the air that man breathes", 147));

        Controls = Story::Controls::STANDARD;
    }
};

class Story105 : public Story::Base
{
public:
    Story105()
    {
        ID = 105;

        Text = "\"So,\" hisses your mirror image, \"you would rather shatter your promise...\"\n\n\"You witless sprite,\" you retort sharply, \"If I break the mirror right away, the enchantress will wake up. Be patient; I'll get around to it.\"\n\n\"No!\" wails the voice from the glass. \"You're lying. You intend to use me just as she has -- but I'll foil that scheme. Wake, mistress, wake! A mortal prowls within your boudoir!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 499; }
};

class Story106 : public Story::Base
{
public:
    Story106()
    {
        ID = 106;

        Text = "\"Why is it bad to kill spiders?\" she asks.";

        Choices.clear();
        Choices.push_back(Choice::Base("Say it is because all evil things as well as good things must be tolerated in the forest", 51));
        Choices.push_back(Choice::Base("Reason that without spiders to eat the birds would die, and without birds to eat berries there would be no young trees", 128));

        Controls = Story::Controls::STANDARD;
    }
};

class Story107 : public Story::Base
{
public:
    Story107()
    {
        ID = 107;

        Text = "\"I have watched you coming here in the mirror I keep in my secret bower. I think you have the makings of a hero,\" she says.\n\n\"Did it amuse you to watch me struggle to find my way in the forest?\"\n\n\"Not at all. I was hoping you would survive at least this far.\"\n\n\"That doesn't sound very encouraging.\"\n\n\"Only you can shape your own destiny. I think perhaps you have greatness within you.\"\n\n\"If you have plans for me why didn't you bring me straight here from the inn in Burg?\"\n\n\"The ways of the forest cannot all be taught. They must be experienced. And besides, I needed to know your mettle.\"\n\nShe smiles a smile that could mean anything from cruel amusement to genuine welcome; you are too confused by what she has said to judge the difference.\n\nIt feels slightly shaming to think that this woman has watched your most intimate moments in the forest. Still, you have done nothing to be ashamed of.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go along with her", 9));
        Choices.push_back(Choice::Base("Leave: You are convinced she is mad", 98));

        Controls = Story::Controls::STANDARD;
    }
};

class Story108 : public Story::Base
{
public:
    Story108()
    {
        ID = 108;

        Text = "You stride to the fireside and turn so that the light of the flaming logs plays across your face. All eyes are on you, but you can't see well in the gloom. The two men who had been rubbing their hands at the fire sit down at the other end of the old hall.\n\n\"We don't take kindly to strangers here. What brings you to Burg, southerner?\"\n\nIt seems to be the sinister man clocked in black who is talking.";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell him the truth that you journey to the great Forest of Arden to seek the Tree of Knowledge", 124));
        Choices.push_back(Choice::Base("Say that you are a scout sent out from your city to explore far-off lands and bring news back to your masters", 155));
        Choices.push_back(Choice::Base("Use [STREETWISE]", 188, Skill::Type::STREETWISE));

        Controls = Story::Controls::STANDARD;
    }
};

class Story109 : public Story::Base
{
public:
    Story109()
    {
        ID = 109;

        Text = "You call out loudly. \"I am a friend of Elanor, the Lady of the Forest. I come in search of the immortal elves.\"\n\nYou feel rather unheroic, calling out like this when you don't know whether anyone can hear you. But there is also the nasty feeling that you might be struck by an arrow at any moment.\n\nYou call out a second time and this time, to your relief, you are answered.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 120; }
};

class Story110 : public Story::Base
{
public:
    Story110()
    {
        ID = 110;

        Text = "You review the spells you can cast against the King of the Elves in the duel.\n\nVANISH allows you to disappear and move unseen. CHOKING FOG brings a cloud of poisonous gas. VISCERAL DISRUPTION causes crippling stomach cramps. SHIELD OF DEFENSE protects against manifest magical attacks. BAFFLEMENT makes your foe unable to understand what is happening. VISIONS creates two false illusions of yourself. TOWER OF WILL subdues your enemy and makes him do your will.\n\nThe elven bard announces the beginning of the duel. You are shocked at the swiftness of elven king's magic. Before you have even fully contemplated which spell to use, he cries a single word of power and vanishes. A moment later he reappears along with two exact copies of himself. You can't tell which is which because all three appear motionless. You must quickly decide which spell to use first.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Vanish", 122));
        Choices.push_back(Choice::Base("Cast Choking Fog", 143));
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 347));
        Choices.push_back(Choice::Base("Cast Shield of Defense", 326));
        Choices.push_back(Choice::Base("Cast Bafflement", 347));
        Choices.push_back(Choice::Base("Cast Visions", 249));
        Choices.push_back(Choice::Base("Cast Tower of Will", 174));

        Controls = Story::Controls::STANDARD;
    }
};

class Story111 : public Story::Base
{
public:
    Story111()
    {
        ID = 111;

        Text = "You mouth the strange words that set off Visceral Disruption. A spasm wracks the King of the Elves and he tries to stop himself clutching his stomach as the spell twists his guts.\n\nYou have never known anyone who could remain standing under the effects of this agonizing spell, but it is taking all of the Elf King's will. He cannot cast another spell.\n\n\"Cancel the spell, mortal. I concede victory to your sorcery,\" the King of the Elves says from between clenched teeth.\n\nKnowing how unpleasant the spell can be and out of compassion for the king, you quickly comply. You have won the duel.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 263; }
};

class Story112 : public Story::Base
{
public:
    Story112()
    {
        ID = 112;

        Text = "\"Do you think that the knowledge of the Tree of Life should be passed on to man so mankind can benefit from the tree's wisdom? Or are men too greedy and selfish to be trusted with this great wisdom?\" she asks.";

        Choices.clear();
        Choices.push_back(Choice::Base("Reply that wise men rule well and that you hope to take the wisdom of the Tree of Life back", 104));
        Choices.push_back(Choice::Base("Say that the knowledge must be guarded as a secret treasure and not given to men at large because man cannot be trusted", 140));

        Controls = Story::Controls::STANDARD;
    }
};

class Story113 : public Story::Base
{
public:
    Story113()
    {
        ID = 113;

        Text = "For a moment your Bafflement spell seems to have had little effect: the statue's sword arm rises and falls like a mindless piston. Soon, however, the sword starts to miss its mark, flailing pointlessly through the air. There are cries of alarm from the Westermen, who then begin to fall silent as the Infernal Statue lurches a few steps away from the tree and teeters near the edge of the deep blue pool.\n\nIt lapses into inaction -- it would seem truly baffled. How will you followup with your success?";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 362));
        Choices.push_back(Choice::Base("Cast Choking Fog", 31));
        Choices.push_back(Choice::Base("Cast Tower of Will", 207));

        Controls = Story::Controls::STANDARD;
    }
};

class Story114 : public Story::Base
{
public:
    Story114()
    {
        ID = 114;

        Text = "Your confident announcement fails to enthral the Elf King as you had hoped. Instead he only shakes his head slowly, the look in his eyes reflecting some inner emotion unknown to mortal men. Just as you open your mouth to try another guess, he comes striding rapidly forward to throw his cloak up in front of your eyes. There is no time to react before your vision is blotted out in a rustle of soft green fabric. A scent wafts to you, reminiscent of meadows and leafy lanes in summer.\n\nReaching up to pull aside the folds of the cloak, your fingers close only on a handful of fresh green leaves. You look around. The elves have vanished. You have no choice but to turn and trudge through the trees, calling out for them to return. But your pleas are unanswered except by the song of the birds and the murmuring of a distant brook.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 78; }
};

class Story115 : public Story::Base
{
public:
    Story115()
    {
        ID = 115;

        Image = "images/filler3.png";

        Text = "While you wait, quite still behind the chief's chair, you hear a visitor being announced. \"It is Valerian the Moon Druid, sire, he has important news. Shall we let him come in?\"\n\n\"Aye, let him.\" The speech of the Westermen is guttural and uncouth-sounding but you can understand their dialect.\n\nIt is the man you first saw in the inn at Burg. He is still dressed in a black travelling cloak but the hood is thrown back to reveal his hatchet-like face and pointed black goatee beard. He bows before the chief, then wrinkles his nose and stares at thin air in your general direction.\n\n\"I have driven off the tree bears, you will have no more trouble from them,\" he tells the chief. He sniffs again and moves his head from side to side while fixing his gaze just above your head, giving him a most comical air.\n\nThe chief spreads out the map of the forest and his advisers gather round, almost blocking your exit.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to get away now", 29));
        Choices.push_back(Choice::Base("Wait to see what they may plan", 4));

        Controls = Story::Controls::STANDARD;
    }
};

class Story116 : public Story::Base
{
public:
    Story116()
    {
        ID = 116;

        Text = "You nimbly climb up on top of the dragon's head perching behind its glittering eyes. The monster reaches a claw up over its shoulder to flick you off onto the ground.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to kill the dragon", 135));
        Choices.push_back(Choice::Base("Talk to it", 178));
        Choices.push_back(Choice::Base("Try to dodge the claw", 133));

        Controls = Story::Controls::STANDARD;
    }
};

class Story117 : public Story::Base
{
public:
    Story117()
    {
        ID = 117;

        Image = "images/filler1.png";

        Text = "It is a cold and blustery night. You look for another inn but there is none. The houses are shuttered and the doors are barred. You try knocking but all your attempts at seeking entry are ignored. The inhabitants really don't like strangers here.\n\nA woman shouts from a top window, \"You'd best get outside the gates before they turn the dogs loose in the streets.\"\n\nAs she speaks you hear the baying of a pack of dogs from near the gate. You walk quickly through. The dog handlers seem to be sizing you up as quarry as they shut the gate behind you.\n\nYou pass a cold, damp night outside the town, awakening stiff and soaked through in the morning. You are only too glad to leave Burg behind you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 210; }
};

class Story118 : public Story::Base
{
public:
    std::string PreText = "";

    Story118()
    {
        ID = 118;

        Choices.clear();
        Choices.push_back(Choice::Base("Break the mirror", 418));
        Choices.push_back(Choice::Base("Otherwise", 105));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "There is a tingling pins-and-needles feeling as the sprite's magic takes effect.\n\n\"Now do as you promised,\" urges the sprite in the mirror. \"Free me.\"";

        if (player.Life == player.MAX_LIFE_LIMIT)
        {
            PreText += "\n\nYou GAIN a PERMANENT +1 Life Point.";

            player.MAX_LIFE_LIMIT += 1;

            Character::GAIN_LIFE(player, 1);
        }
        else
        {
            PreText += "\n\nYour Life Points are RESTORED.";

            player.Life = player.MAX_LIFE_LIMIT;
        }

        Text = PreText.c_str();
    }
};

class Story119 : public Story::Base
{
public:
    Story119()
    {
        ID = 119;

        Image = "images/imp.png";

        Text = "The archway leads into a tunnel that has been cut through the thick branches and thorns of the bell-shaped bush. You walk on towards the great open space that surrounds the trunk of the bush.\n\nLooking back, however, you cannot make out the archway at all, even though it should be directly behind you. You press on anyway until you hear a chirruping little voice say, \"Welcome, sirrah, 'tis a pretty place to spend the rest of your days, is it not?\"\n\nA strange little man the size of a small capuchin monkey sits cross-legged on a giant toadstool. Even in the dim light you can see the fungus is liver-spotted and looks poisonous.\n\n\"Come, share my provender,\" invites the little man as he breaks off a piece of the toadstool on which he is sitting. He offers it to you. \"Share my provender, there is nothing more helpful to a hero than the flesh of the Blood of Iron toadstool.\" The little imp proffers it to you with an elaborate bow.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take and eat the flesh", 138));
        Choices.push_back(Choice::Base("Kill the little man", 148));
        Choices.push_back(Choice::Base("Ask him to help you in your quest", 158));

        Controls = Story::Controls::STANDARD;
    }
};

class Story120 : public Story::Base
{
public:
    Story120()
    {
        ID = 120;

        Image = "images/elves.png";

        Text = "You are surrounded by a circle of elves, all of whom seem to have appeared as if by magic. They look solemn but not hostile. Their faces have the perfect beauty of unsullied youth but their green almond-shaped eyes are like windows onto the wisdom of the centuries. Their skin is flawless pale green with a silvery bloom like grape bloom. Their long straight hair is the colour of rich red wine. They seem not in the least surprised to see you.\n\nYou wait for them to say something but they seem in no hurry, so you tell men you are a friend of the forest and an enemy of the burners.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 180; }
};

class Story121 : public Story::Base
{
public:
    Story121()
    {
        ID = 121;

        Text = "Seeing your eyes measuring the left of the three images, the one you are looking at smiles imperturbably, but something tells you, you have guessed correctly.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Bafflement", 101));
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 111));
        Choices.push_back(Choice::Base("Cast Tower of Will", 91));

        Controls = Story::Controls::STANDARD;
    }
};

class Story122 : public Story::Base
{
public:
    Story122()
    {
        ID = 122;

        Text = "You cry a single word of power and vanish, then move slowly and silently in a circle to your right while you prepare another spell.\n\nAs you creep silently along, you notice to your dismay the faces of all the elves turned towards you. Several are grinning. The King of the Elves is looking straight at you as he mouths another incantation.\n\nYour legs feel as if they have turned to jelly and you cannot stop yourself collapsing to the ground.\n\n\"Submit, mortal, I have defeated you,\" cries the King of the Elves.";

        Choices.clear();
        Choices.push_back(Choice::Base("Do as he requests", 255));
        Choices.push_back(Choice::Base("Fight on", 272));

        Controls = Story::Controls::STANDARD;
    }
};

class Story123 : public Story::Base
{
public:
    Story123()
    {
        ID = 123;

        Text = "The King of the Elves draws a green silk veil from his waist, holds it up and lets it fall from in front of his eyes.\n\n\"See your peril, mortal, and despair.\"\n\nHis words ring out as though your skull was a vast hollow chamber and the elf was exhorting you from within it, his words rolling through your senses like ocean waves. As the veil falls it is as if scales had dropped from your eyes. You see the forest for what it is, a hostile place, inimical to man. Everything around you is united against your intrusion. The plants will snare you and tear you limb from limb, with the slow strength of growth. The ants will eat you alive. Stinging insects will plague you and bears will maul you. You do indeed despair at the awful nature of your plight. Losing reason you flee in fear. As the veil falls lightly to the ground, so the terror passes and you stop.\n\n\"You have stepped outside the circle, mortal, and forfeited the duel. I am the victor,\" says the king.\n\nHis magic made you break the rules and lose.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 163; }
};

class Story124 : public Story::Base
{
public:
    Story124()
    {
        ID = 124;

        Text = "\"It is my intention to search for the Tree of Knowledge in the Forest of Arden,\" you announce in a firm clear voice.\n\nAs your eyes become accustomed to the gloom you can begin to make out details of those in the room. The black-cowled man merely stares inscrutably. A woman, old and weather-beaten, in a grey robe, looks up at you with interest. The two who were at the fire stand up and walk over to you. The shorter one has a face that reminds you of a bull-mastiff. \"Why would you seek the Tree of Knowledge?\" he asks. \"What use it is to you, a southerner?\"\n\n\"Fool, don't speak to him of the tree,\" interrupts the man in black. \"All must be left as it is, nothing changed. The knowledge of the tree is lost to men and it is better that way.\"\n\nThe woman speaks with a clear voice that sounds too young for her age. \"You would have it that way. You are not at one with the forest. Because the tree sees your evil heart, you seek to keep its knowledge and pervert it.\"\n\n\"You dare to say I am no friend of the forest?\" The black cowled man surges to his feet and the cowl slips back to reveal a bald head, a hatchet-thin face with a long black goatee beard and eyes of flint.\n\n\"You lost your way in the forest many years ago.\"\n\n\"I didn't need you to find me, old woman. You only dare challenge me now because you think these simple folk of Burg can offer you protection.\"\n\n\"You know full well I am at my strongest in the forest, Valerian,\" says the woman. \"The beasts follow me. They sense your evil.\"\n\n\"There is a new power astir in the forest,\" he retorts. \"It will sweep you and all your bestial followers aside like chaff in the wind.\"\n\n\"There is no cause to fill the hearts of good people of Burg with dismay. I know of what you speak...\"\n\nHe sneers. \"Much good may the knowledge do you, old one. Haven't you heard the song of the wind? The time of man has come to the forest. All must change -- or pass away.\"\n\nValerian speaks the last words in such dire tones that three townsfolk at the nearby table hastily leave the inn. Valerian himself twitches his cloak around him and follows them out, pausing to give you a last look as though committing your face to memory.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take a room at the inn for the night", 333));
        Choices.push_back(Choice::Base("Talk to the hunter and the guide who are by the fire", 297));
        Choices.push_back(Choice::Base("Talk to the woman in grey", 181));

        Controls = Story::Controls::STANDARD;
    }
};

class Story125 : public Story::Base
{
public:
    Story125()
    {
        ID = 125;

        Text = "Your parting makes the dragon wrinkle up its nose and there is a roar as it starts to sneeze. Its breath is a mixture of acid and poisonous gas. It hits you like a wave of blistering, burning pain. There is no surviving the breath of an ancient dragon.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story126 : public Story::Base
{
public:
    Story126()
    {
        ID = 126;

        Text = "You shake your head. \"Better that I retain it for now. If we are to be allies, what better token that I fight for the elves than that their king has entrusted me with his royal symbol?\"\n\nHe knows you have guessed him aright. If you had returned the ring, the elves would no doubt have found some way to back out of their bargain. Now they are bound to fight beside you, and your carefully chosen words allow the king to accede to this without losing his dignity. His eyes show a flicker of grudging admiration as he says, \"Well spoken, mortal. Now let us feast and discuss our plans.\"\n\nYou RECEIVED an EMERALD RING.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::EMERALD_RING});
    }

    int Continue(Character::Base &player) { return 232; }
};

class Story127 : public Story::Base
{
public:
    Story127()
    {
        ID = 127;

        Text = "A chameleon on a tree changes colour to pale yellow as you walk past it. A beautiful silken-winged butterfly, black and scarlet, settles on your shoulder and spreads its wings in the sun. You are beginning to feel harmony with the forest at last. You journey on, hopeful and determined.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 277; }
};

class Story128 : public Story::Base
{
public:
    Story128()
    {
        ID = 128;

        Text = "\"Abide with me for a while.\" Elanor requests. \"I can teach you something about the forest and its ways. And I can put you to the test again, to see if you are worthy of being hailed the saviour of the forest.\"\n\nYou spend three days in the tree-house and the meadow-garden talking with Elanor about the forest she loves. You had never realized how much all living things are linked, each depending on the others for survival.\n\nThe forest, you learn is teeming with an abundant wealth of life. All things are tolerated in the forest, which is neither a good nor an evil region, as long as they do not threaten the balance of nature. After you have partaken of a delicious repast of mushrooms and loganberries on the third day, Elanor starts to question you again, to see if you have learned anything.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 112; }
};

class Story129 : public Story::Base
{
public:
    Story129()
    {
        ID = 129;

        Text = "This time you hide beneath the roots of a fallen pine tree. You try to stay calm to still the pounding of your heart that makes the blood rush loudly in your ears. This time you think you may have heard cruel sounding laughter, now off to one side, now behind you, and now off to another side. You see nothing so at last you decide to journey on.\n\nYou have walked but half a mile further when you stumble against a branch. The deep green of the forest by day is giving way to the blackest dark of the forest by night. You will never find the elves on Midsummer's Day now. You will have to find a place to rest and hope the elves will still receive you cordially at a later date.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 139; }
};

class Story130 : public Story::Base
{
public:
    Story130()
    {
        ID = 130;

        Image = "images/filler3.png";

        Text = "\"The Tree of Knowledge grows alone out of a blue pool in the very centre of the forest. It is an ancient Greenbark tree with gold and silver leaves which are said never to fall.\"\n\n\"Have you seen it?\" you ask Renard.\n\n\"Once from a long way off. But I didn't dare talk to it.\"\n\n\"It can talk? Is there anyone here in Burg who has spoken with the tree?\" you ask, glancing at the other travellers in the inn.\n\n\"No, no. The folk here are simple enough. Ask them about the tree and they'll likely make something up just to satisfy your asking. Now look, why don't you put up for the night at my house and we can set out at first light?\"\n\nRenard seems keen to take you away from the inn. Looking around you notice the old woman in grey seems to be taking an interest in you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go with Renard to his house", 224));
        Choices.push_back(Choice::Base("Stay and talk to the other travellers in the inn a while longer", 176));

        Controls = Story::Controls::STANDARD;
    }
};

class Story131 : public Story::Base
{
public:
    Story131()
    {
        ID = 131;

        Text = "The path twists and turns, winding down through dense undergrowth overhung by barrel-like Gwelph trees that are festooned with lianas. You try to fix the shape of each tree in your mind so you will know if you have passed one before. The thin crooked branches that sprout from the top of the barrel-like boles remind you of terrified old men with their hair standing on end. To your dismay the path ends in a little clearing chocked with dead leaves with two paths leading off in different directions. Each is lined with thorn bushes that have grown to the height of a man and are covered in inch-long purple barbs which ooze an orange fluid. The thorns would break off in your flesh if you brushed against them.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take the left-hand path", 196));
        Choices.push_back(Choice::Base("Take the right-hand path", 211));
        Choices.push_back(Choice::Base("Despair of ever finding a way out of the forest", 156));
        Choices.push_back(Choice::Base("Mark one of the great Gwelph trees by scraping away a patch of bark", 177));

        Controls = Story::Controls::STANDARD;
    }
};

class Story132 : public Story::Base
{
public:
    Story132()
    {
        ID = 132;

        Text = "You have directed your spell against one of the king's images, not against the king himself. The image you have assailed disappears with a startling pop, but the elf has used the time he has gained to prepare another spell.\n\nThe King of the Elves draws a green silk veil from his waist and lets it fall from in front of his eyes.\n\n\"See your peril, mortal, and despair.\"\n\nHis words ring out as though your skull was a vast hollow chamber and the elf was exhorting you from within it, his words echoing through your senses. As the veil falls it is as if scales had dropped from your eyes. You see the forest for what it is, a hostile place, inimical to man. Everything around you is united against your intrusion. The plants will snare you and tear you limb from limb with the slow strength of their growth. The ants will eat you alive. Stinging insects will plague you and bears will maul you. You do indeed despair at the awful nature of your plight.\n\nLosing reason you flee in fear. As the veil falls lightly to the ground, so the terror passes and you stop.\n\n\"You have stepped outside the circle, mortal, and forfeited the duel. I am the victor,\" says the king.\n\nHis magic made you break the rules and lose.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 163; }
};

class Story133 : public Story::Base
{
public:
    Story133()
    {
        ID = 133;

        Text = "The great claw sweeps you clean off the monster's head. The only way to dodge would have been to jump to your death in any case. You fall stunned on the ground and the dragon pins you to the earth beneath a massive claw. You look from the green scaled claw to the smouldering red eyes thirty feet above. It thinks you were trying to kill it. The dragon opens its jaws wide and its stomach convulses. A second later a gout of poisonous gas and acid hits you like a wave. There is no surviving the breath of an ancient green dragon.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story134 : public Story::Base
{
public:
    Story134()
    {
        ID = 134;

        Text = "Watching from the edge of the trees you see a man who bears an uncanny resemblance to the girl in the inn at Burg. He must be her father.";

        Choices.clear();
        Choices.push_back(Choice::Base("Free him from the clutches of the Westermen", 264));
        Choices.push_back(Choice::Base("Be content and abandon him to their tender mercies", 279));

        Controls = Story::Controls::STANDARD;
    }
};

class Story135 : public Story::Base
{
public:
    Story135()
    {
        ID = 135;

        Text = "You are too slow. The great claw sweeps you clean off the monster's head. You fall stunned to the ground; the dragon pins you beneath the other massive claw. You look from the huge green scaled claw to the smouldering red eyes thirty feet above. The dragon opens its jaws wide and its stomach convulses. A second later a gout of poisonous gas and acid hit you like a wave. There is no surviving the breath of an ancient green dragon.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story136 : public Story::Base
{
public:
    Story136()
    {
        ID = 136;

        Text = "Your knowledge of the wilderness and the complicated web of links between all the living things in the forest makes this an easy question to answer.\n\n\"Without spiders to eat, the birds would die and without birds to eat berries and spread seeds there would be no young trees,\" you say confidently. \"Without young trees to replace the old fallen hulks there would be no forests.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 128; }
};

class Story137 : public Story::Base
{
public:
    Story137()
    {
        ID = 137;

        Text = "Decide how you will prove your cause to the elves.";

        Choices.clear();
        Choices.push_back(Choice::Base("[CUNNING] Challenge the Elf King to a battle of wits", 58, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("[ARCHERY] Propose a contest to prove the better bowman", 159, Skill::Type::ARCHERY));
        Choices.push_back(Choice::Base("Hesitate and let the elves themselves choose the terms of the duel", 18));

        Controls = Story::Controls::STANDARD;
    }
};

class Story138 : public Story::Base
{
public:
    Story138()
    {
        ID = 138;

        Text = "The toadstool is a dull red colour, spotted with purple. Underneath the soft gills are mauve. You ask nervously whether it is poisonous.\n\n\"No, no, never, not poisonous, my dear, Oh no! The Kwerrel eats it every day.\"\n\nIt tastes surprisingly good; it almost melts in your mouth.\n\nQuite soon, however, you begin to feel sleepy. You walk a few steps further then sit down with your back to the central trunk of the giant bush. Feeling warm, snug and content you fall into a deep sleep.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 189; }
};

class Story139 : public Story::Base
{
public:
    Story139()
    {
        ID = 139;

        Text = "The next day you awake feeling uneasy and begin your journey once more. The feeling of being watched soon returns. There seems to be no point in hiding; there might not be anything there. You call out that you have come to search for the immortal elves.\n\nA soft high voice, but a cold voice none the less, speaks with a total lack of emotion. \"It is not the day to seek a meeting with the elves.\"\n\nYou spin round to find the source of the words. There is the rushing whine of an arrow and a stabbing pain between your shoulder-blades.\n\nThe force of the shot spins you round and you see your killer: a tall, proud elf, standing braced with feet apart between two great Greenbark trees. He lets his bow fall to his side in a gesture of merciless contempt.\n\nThe arrow has pierced your lung and you begin to drown in your own blood. The elf looks on without pity as you die.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story140 : public Story::Base
{
public:
    Story140()
    {
        ID = 140;

        Text = "\"You pass the test. I know you to be true of heart. You care about living things. You are the saviour of the forest. I will do all in my power to aid you, but you will need the elves on your side. They are the real masters of the forest.\"\n\nElanor fills two horn cups of elderflower nectar and offers you one. Taking the drink, you raise the cup in thanks before putting it to your lips. The nectar is marvellously refreshing, sweet but not cloying to the taste.\n\n\"The Westermen have cut great swathes through the forest. They are settling the land, but without the trees the soil will be carried away by the wind and this region will become a terrible desert. These men don't know what they are doing, and they care nothing for life. You must stop them.\"\n\n\"How am I to stop them?\" you ask. \"How strong are they?\"\n\n\"Tens of thousands. They came from the western plains like columns of ants and devoured everything in their path.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 152; }
};

class Story141 : public Story::Base
{
public:
    Story141()
    {
        ID = 141;

        Text = "The red liquid tastes vile, but unlike medicine it doesn't seem to to anything to you. You start to run as the swarm of bees settles around your head, but you have left it too late. Death from a hundred bee stings is not a pleasant way to leave the world. Your neck swells until your windpipe closes right up, and slowly but surely you choke to death. You bitterly rue your folly in upsetting Elanor, the Lady of the Forest, and you have paid the price.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story142 : public Story::Base
{
public:
    Story142()
    {
        ID = 142;

        Image = "images/filler4.png";

        Text = "This time your rush makes Gathkeri stumble back over a hummock and your lunge catches him. You start to wrestle, trying to throw him to the ground.";

        Choices.clear();
        Choices.push_back(Choice::Base("Throttle your opponent for your next manoeuvre", 435));
        Choices.push_back(Choice::Base("Throw him into the ground so that you land on top of him", 425));

        Controls = Story::Controls::STANDARD;
    }
};

class Story143 : public Story::Base
{
public:
    Story143()
    {
        ID = 143;

        Text = "Throwing your arms wide to embrace the wind and blowing mightily as if playing a trumpet you cast the mighty spell Choking Fog. There is a hiss and puff of green smoke that appears in front of appears in front of the three images of your foe, one of which you know to be real.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::WINDFACE))
        {
            return 294;
        }
        else
        {
            return 285;
        }
    }
};

class Story144 : public Story::Base
{
public:
    Story144()
    {
        ID = 144;

        Text = "You back off and reach a rock behind which you can take cover.\n\nThe Infernal Statue recovers its equilibrium and hacks into the trunk of the Tree of Life once more. The sword bites deep and one of the tree's great branches cracks and falls to the ground, killing and maiming more than twenty of its assailants. At the next sword blow another branch cracks and falls, and those not dead or trapped fall back as the machine completes its job of destruction.\n\nYou screw up your courage and rush once more against the machine but you are too late. One last great blow splits the trunk in the middle and the tree is dead. The destruction of the Tree of Life shatters your hopes. Utterly dejected you do not resist as the Westermen take you prisoner. The only certainty about the future is that you will be a slave of the forces that you should have defeated.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story145 : public Story::Base
{
public:
    Story145()
    {
        ID = 145;

        Text = "\"There's Marek the Hunter there.\" He points to the stocky man with a face like a bull-mastiff, drinking beer by the kitchen door. \"He's a good enough man if it's simple hunting you're after.\" Renard looks at you as if you must be after something more.\n\n\"Then there's old Oakmother there, lives in the forest. She says she comes to Burg just to remind herself once in a while that she is a human being. She's a strange old cove.\" He points to a weather-beaten old woman in a grey robe. \"She won't eat meat. Says her friends the animals will desert her if she does. Says they'll smell it on her skin.\" Renard shakes his head pityingly.\n\n\"And who is the man in black?\" you whisper.\n\n\"I am Valerian and I have the ears of a bat, the eyes of an owl and the sting of a viper.\" The main in black gets to his feet and approaches.\n\nRenard slinks away to join Marek the Hunter.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 252; }
};

class Story146 : public Story::Base
{
public:
    Story146()
    {
        ID = 146;

        Text = "The chief looks at you as though scales have fallen from his eyes. \"Miserable trickster... Hmm, you look strong and fit, a fine log-puller you'll make.\"\n\nValerian takes away your wand, and the guards strip you of your possessions. Without even asking who you are or where you have come from they chain you to a yoke beside another slave.\n\nYou begin a life of back-breaking work, pulling tree trunks from the fellers to the sawyers for week after week, year after year. Your pitiful existence is dominated by thoughts of how you might make a desperate escape before the toil kills you.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story147 : public Story::Base
{
public:
    Story147()
    {
        ID = 147;

        Text = "\"Hunters come to the forest from Burg, Dale and the few villages near the forest's edge. They come to kill and then to eat and to find furs to wear. Should I stop hem coming to the forest? It lies within my power.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Reply that the hunters should be stopped", 51));
        Choices.push_back(Choice::Base("Reply that hunters are so few that it cannot harm the forest", 140));

        Controls = Story::Controls::STANDARD;
    }
};

class Story148 : public Story::Base
{
public:
    Story148()
    {
        ID = 148;

        Image = "images/filler2.png";

        Text = "As soon as the idea of killing the impish little man forms in your head, he bounds down from the toadstool.\n\n\"It's mischief you're planning, is it? May your bones rot to feed the Umbellifer bush. I leave you its prisoner.\"\n\nWith that he rushes to the central trunk of the giant bush and scrambles up just as if he was a monkey, writhing sinuously past the wicked barbed thorns. You could never follow such a difficult route. The little imp is soon lost to sight and you start to look for a way out of the bush.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 432; }
};

class Story149 : public Story::Base
{
public:
    Story149()
    {
        ID = 149;

        Text = "You have directed your spell against one of the king's images, not against the king himself. The image you have assailed disappears with a startling pop but the elf has used this time to prepare another spell.\n\nThe King of the Elves draws a green silk veil from his waist and lets it fall from in front of his eyes.\n\n\"See your peril, mortal, and despair.\"\n\nHis words ring out as though your skull was a vast hollow chamber and the elf was exhorting you from within it, his words echoing through your senses. As the veil falls it is as if scales had dropped from your eyes. You see the forest for what it is, a hostile place, inimical to man. Everything around you is united against your intrusion. The plants will snare you and tear you limb from limb with the slow strength of their growth. The ants will eat you alive. Stinging insects will plague you and bears will maul you. You do indeed despair at the awful nature of your plight.\n\nLosing reason you flee in fear. As the veil falls lightly to the ground, so the terror passes and you stop.\n\n\"You have stepped outside the circle, mortal, and forfeited the duel. I am the victor,\" declares the king.\n\nHis magic has made you break the rules. You have lost.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 163; }
};

class Story150 : public Story::Base
{
public:
    Story150()
    {
        ID = 150;

        Image = "images/little-animal.png";

        Text = "You feign nonchalance as you walk on between the beautiful Greenbark trees, which every now and then let a golden leaf fall on your brow. Though you have been hit by several leaves you never see one falling. It is as if the gargantuan trees, with their trunks as wide as towers, have been shaken slightly by your footsteps.\n\nA little way ahead there is a clearing from which you can hear the crackle of fire and see the orange flickering of flame. The sun must have set fire to the dried grass. Advancing closer, you see a chipmunk chittering in panic inside the closing ring of flames. A solid wall of fire surrounds the desperate little animal, a fire so strong that it would undoubtedly burn you horribly.";

        Choices.clear();
        Choices.push_back(Choice::Base("Brave the flames to save the chipmunk", 160));
        Choices.push_back(Choice::Base("Keep out of the clearing on the grounds that you will make an easy target there", 170));

        Controls = Story::Controls::STANDARD;
    }
};

class Story151 : public Story::Base
{
public:
    std::string PreText = "";

    Story151()
    {
        ID = 151;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "You surrender yourself up to the Westermen guards and are taken before a man who is clearly their chief.\n\nThe Chief of the Westermen is a balding corpulent man whose eyes seem to gleam with greed. He appraises your worth in a quick glance. \"Hmm, you look -- strong and fit -- doubtless you'll make a find log-puller.\"\n\nWithout even asking who you are or where you have come from, the Westermen chain you to a yoke beside a man who reminds you of the girl in the inn at Burg. It must be her father.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::SPELLS))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nYou begin a life of back-breaking work, pulling tree trunks from the fellers to the sawyers for week after week, year after year. Your pitiful existence is dominated by thoughts of how you might make a desperate escape before the toil kills you. There is no escape. You live only to see the utter destruction of the Forest of Arden.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 229; }
};

class Story152 : public Story::Base
{
public:
    Story152()
    {
        ID = 152;

        Text = "\"How am I to stop them? I am a stranger here in the forest.\"\n\n\"Make the elves fight them. Kill the Westermen's leader. Wake the mighty dragon and send him forth to destroy them. If the forest perishes the whole world will die.\"\n\n\"Which of these three should I do?\" you ask. \"Or it is not as simple as that, and I must do two or even all three of these things?\"\n\n\"I do not know.\"\n\n\"Can't you talk to the elves?\"\n\n\"The elves will talk to men only on Midsummer's Day. On that day, you must find them and convince them to help you save the forest. I can never talk with elvenkind except on Midsummer's Day.\"\n\nThere are so many questions you would like to ask Elanor, but the elderflower nectar seems to be going to your head and you feel too drowsy to continue.\n\n\"Sleep now, and awake a hero.\"\n\nAs Elanor says the word sleep, your eyes shut and you sink in deep slumber.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 166; }
};

class Story153 : public Story::Base
{
public:
    Story153()
    {
        ID = 153;

        Image = "images/filler2.png";

        Text = "Renard thanks you for the six pieces of gold. \"It's not that I'm a coward, you understand. It's just that nobody in their right mind would brave the Bonehill.\"\n\nYou awake at dawn in time to glimpse Renard's disappearing back. It seems he doesn't want to stay a moment longer than he has to. You slept soundly and feel invigorated and confident as you begin to climb the slop away from the Sirion river.\n\nYou RECOVER 2 Life Points.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, -6);

        Character::GAIN_LIFE(player, 2);
    }

    int Continue(Character::Base &player) { return 237; }
};

class Story154 : public Story::Base
{
public:
    Story154()
    {
        ID = 154;

        Text = "\"Then tell your masters that Burg is a broken-down little hamlet soon to be swamped by the forest. Go and tell them there is nothing for them here.\"\n\nThe man in black steps forward. You can see a hatchet-shaped face inside the cowl of his robe and a pointed black goatee beard. He is flanked by the two who were by the fire.\n\n\"We don't take to foreigners. You better leave Burg before we set the dogs on you.\"\n\nIt seems they think you are a spy sent out to find rich towns to pillage and despoil. You decide to leave while you can still walk.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 117; }
};

class Story155 : public Story::Base
{
public:
    Story155()
    {
        ID = 155;

        Text = "You grab the phial and gulp down the cloudy blue fluid. The owl, perched on a tree, watches as unblinking as ever.\n\n\"You have just drunk the mulch of the fire lizard's gizzard. You have not long to live.\"\n\nThe owl is right. Your throat goes into spasm as the poison starts to work and soon you cannot breathe. You fall to the ground writhing in agony, but it is not long before unconsciousness brings merciful release from the pain of the poison.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story156 : public Story::Base
{
public:
    Story156()
    {
        ID = 156;

        Text = "Crushed by despair you realize you will never find your way out of the forest. There is nothing you can eat here -- everything tastes of poison, even the dead leaves. You try eating some of the earwigs in the leaf litter but their blood burns your mouth like acid.\n\nBeyond caring, you push your way into the undergrowth, heedless of the purple thorns that rip your flesh. The bushes are not as thick as you believed. You crash through into a dark avenue between tall slender trees growing so close together you cannot force your way between their trunks. Resigned to your fate you walk on down the avenue for what seems an age.\n\nYou start to pass bodies lying where they have fallen, one at a time, and then a forlorn-looking group, huddled together. Exhausted and starving like the others before, you give up hope and lie down to die.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return 251;
        }
        else
        {
            return -1;
        }
    }
};

class Story157 : public Story::Base
{
public:
    Story157()
    {
        ID = 157;

        Text = "Squirming quickly round to the statue's back you work at the screws. Two come free and the head starts to tilt. With one great forearm smash you knock it off and the Infernal Statue lurches back from the Tree of Life. Inside the machine is a small man who cannot defend himself. You rain blows down on his head and he slumps forward, knocking the strange levers inside the machine and sending it striding towards the deep blue pool.\n\nIt totters on the brink of the pool and you leap clear just as it keels over into the water. There is a rush of steam like a geyser, followed by an explosion underwater as the machine tears itself apart. The Westermen cry out in alarm and begin to retreat, harried by the arrows of the elves.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 500; }
};

class Story158 : public Story::Base
{
public:
    Story158()
    {
        ID = 158;

        Text = "\"You want my help, what is in it fore me then? How will you pay your side of the bargain?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Offer the little imp some gold (10 gold pieces)", 214, Choice::Type::MONEY, 10));
        Choices.push_back(Choice::Base("Beg him to help you for the sake of the forest and all who dwell there", 225));
        Choices.push_back(Choice::Base("Offer him the Lady of the Forest's EMERALD RING if you have it", 236, {Item::EMERALD_RING_ELANOR}));
        Choices.push_back(Choice::Base("Offer him a magic potion if you are carrying one", 160, Choice::Type::ANY_ITEM, {Item::POTION_CLOUDY_BLUE, Item::JAR_WHITE_JELLY, Item::POTION_RED_LIQUID}));

        Controls = Story::Controls::STANDARD;
    }
};

class Story159 : public Story::Base
{
public:
    Story159()
    {
        ID = 159;

        Text = "A slender elf with moon-coloured hair steps forward to answer his monarch's summons. He carries a bow of silver-chased ivory, and the fletching of the arrows in his quiver is purest white. \"Your opponent will be Huldranas,\" the Elf King tells you. He points to a tall tree. \"That branch will be the target.\"\n\nYou look where he is pointing, then glance back at him. \"Which branch?\"\n\n\"The one where the orchid grows.\"\n\nYou look back. You had not noticed before the flower blazing like a pale jewel against the black bark of the tree. Huldranas gestures for you to take the first shot. You nock on an arrow and send it sailing up towards the branch. It strikes wide of the orchid, but it was only intended as a ranging shot. At least now you have a good sense of the allowance you need to make for height and wind speed.\n\nHuldranas' arrow flashes from his bow. It impales one of the petals of the orchid. He turns to you with a casual look that betrays neither arrogance not tension. Again without a word, he gestures for you to shoot.\n\nAs you sight along your arrow, you consider what to do.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go for a cautious shot, since Huldranas' first arrow might have been lucky", 320));
        Choices.push_back(Choice::Base("Attempt a shot slightly better than his, perhaps striking the orchid in its centre", 469));
        Choices.push_back(Choice::Base("Try an extremely difficult but impressive shot, such as shooting through the thin twig at the end of the branch", 276));

        Controls = Story::Controls::STANDARD;
    }
};

class Story160 : public Story::Base
{
public:
    Story160()
    {
        ID = 160;

        Text = "As soon as you make the jump to clear the ring of flame, the fire vanishes without even a trace of smoke. The chipmunk too has vanished. Instead you are surrounded by a circle of elves who have appeared as if by magic.\n\nThe elves look solemn but not hostile. Their faces have the perfect beauty of unsullied youth, but their green almond eyes are like windows that open to the wisdom of the centuries. Their skin is flawless pale green with a silvery dusting like grape bloom. Their long straight hair is the colour of rich red wine.\n\nThey seem not in the least surprised to see you. You wait for them to say something but they seem in no hurry, so you tell them you are a friend of the forest and an enemy of the burners.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 180; }
};

class Story161 : public Story::Base
{
public:
    Story161()
    {
        ID = 161;

        Text = "Gathkeri closes in, still circling but moving ever closer, until he suddenly launches into a flurry of kicks aimed at your head. You parry them with your arms up high and step into the right, watching his movements, learning so that you can anticipate what he will do. Now that you have assessed his fighting style you can see that he uses kicks better than punches, and deduce that he might not be able to fight so well at close quarters. Armed with this knowledge you can probably beat him.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to grapple him", 183));
        Choices.push_back(Choice::Base("Attack him with your fists and feet", 172));

        Controls = Story::Controls::STANDARD;
    }
};

class Story162 : public Story::Base
{
public:
    Story162()
    {
        ID = 162;

        Text = "You tell them of your quest to find the Tree of Knowledge in the Forest of Arden, after which the taller of the two introduces himself as Renard the Guide.\n\n\"You will need a guide in the forest, or you'll be lost, never to see the lands of men again.\"\n\n\"Renard doesn't know the whereabouts of this tree you seek, I'll warrant,\" comments Marek.\n\n\"What would a hunter know of the Tree of Knowledge?\"\n\nThe hunter turns away; his parting shot is: \"About as much as you, Renard, and that is nothing at all.\" He walks over to the kitchen door to talk to the young woman, who pours him jug of beer.\n\nRenard sits down at a table, draws up a second chair and gestures for you to join him.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask him about the Tree of Knowledge", 130));
        Choices.push_back(Choice::Base("Learn more about the other travellers", 145));
        Choices.push_back(Choice::Base("Ask the hunter about he monster he has seen", 281));

        Controls = Story::Controls::STANDARD;
    }
};

class Story163 : public Story::Base
{
public:
    Story163()
    {
        ID = 163;

        Text = "To your shame you have lost the duel and failed the elven test. The elves vanish back into the forest, warning you to return straight to Burg or you will suffer a death of a thousand bites and stings here in the forest.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 384; }
};

class Story164 : public Story::Base
{
public:
    Story164()
    {
        ID = 164;

        Text = "The ants inject poison with every bite. You take more than a hundred bites as you toil uphill, at last abandoning flight and stripping off your gear in a final effort to scrape the ants from your skin.\n\nIt is too late: the venom weakens your muscles and you sink helpless to the forest floor, mercifully losing consciousness before the ants consume you. Within minutes they strip your flesh to the bone. It does not do to have the whole forest against you.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story165 : public Story::Base
{
public:
    Story165()
    {
        ID = 165;

        Text = "Turning your back on a dragon is never wise. The ancient creature pins you to the ground beneath a huge claw. You look up from the massive green scaled claw to the smouldering red eyes thirty feet above. It wasn't as sleepy as you thought and now it thinks you were trying to kill it. The dragon opens its jaws wide and its stomach convulses. A second later a gout of poisonous gas and acid hit you like a wave. There is no surviving the breath of an ancient green dragon.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story166 : public Story::Base
{
public:
    Story166()
    {
        ID = 166;

        Text = "When you awake you are wonderfully restored to healthy vitality.\n\nElanor is nowhere to be seen. On the third finger of your right hand, however is an EMERALD RING with the stone set in a furled silver leaf. It fits perfectly. You get up, stretch your limbs, and deep in thought, rub the gem.\n\nYou feel in your bones that it is your destiny to save the forest and that you will risk your life to do so. You suffer a moment's unease as you worry about the dangers ahead, an unease that turns to deep-rooted fear. Once more you look at the ring. Is it magical? Is it the ring causing you to feel the reckless courage of a hero? Or did the blood of a hero always run in your veins?";

        Choices.clear();
        Choices.push_back(Choice::Base("Take off the ring", 179));
        Choices.push_back(Choice::Base("Leave the ring on if you trust Elanor", 35));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::EMERALD_RING_ELANOR});
    }
};

class Story167 : public Story::Base
{
public:
    Story167()
    {
        ID = 167;

        Text = "Renard surlily agrees to take you up the Bonehill on the morrow, and you settle down to sleep, exhausted after days of hard travelling.\n\nAt dawn, when you awake, Renard is nowhere to be seen and neither is your money pouch. He must have stolen it while you slept before slinking away into the forest. You will never find him. He has left you penniless but at least he didn't slit your throat.\n\nYou slept soundly enough but the loss of your money has upset you, even though you can foresee no need for money here in the forest.\n\nCursing Renard, you begin to climb the slope away from the Sirion River.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Money = 0;
    }

    int Continue(Character::Base &player) { return 237; }
};

class Story168 : public Story::Base
{
public:
    Story168()
    {
        ID = 168;

        Text = "The black tarty goo smells of putrefaction and does not deter the bees at all. You start to run as the swarm of bees settles around your head, but you have left it too late. Death from a hundred bee stings is not pleasant. Your neck swells until your windpipe is closed tight up and you choke to death. You rue bitterly your folly in upsetting Elanor, the Lady of the Forest, and you have paid the price.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story169 : public Story::Base
{
public:
    Story169()
    {
        ID = 169;

        Text = "You cast your best attack spell for this situation: a magical javelin that should always find its mark. It appears in your right hand just as a silver noose materializes in the air before you. You hurl the javelin which leaves a trail of golden sparks in the air, as the silver noose rises above you and drops towards your head.\n\nBefore the noose can tighten around your neck and as the javelin flies towards him, Valerian speaks a word of negation: both his spell and yours are cancelled. The golden javelin and the silver noose disappear.\n\n\"Had I known you were a sorcerer I should not have been so short with you. A sorcerer is by nature secretive. We need not prolong our quarrel here.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack him with another spell", 206));
        Choices.push_back(Choice::Base("Talk to the woman in grey, who seems unmoved by the violence she has seen", 181));

        Controls = Story::Controls::STANDARD;
    }
};

class Story170 : public Story::Base
{
public:
    Story170()
    {
        ID = 170;

        Text = "You turn your back on the chittering chipmunk, leaving it to a fiery death. But you have taken no more than three steps before you hear the rushing whine of an arrow as it heads towards you.\n\nYou attempt to dodge the unseen attack, but your action is in vain. There is a terrible stabbing pain in the middle of your back and you are knocked to your knees by the force of the shot. Looking down, you see the sharp head of a deadly elven arrow protruding from your belly; your stomach convulses and you begin to cough up blood.\n\nOut of the corner of one eye you can see your assailant: a tall, proud elf, who is standing between two great Greenbark trees. An arrow is already nocked ready for a second shot, but it proves unnecessary as the first has done its work. As your lifeblood spills onto the ground, the silent elf looks on without pity.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story171 : public Story::Base
{
public:
    Story171()
    {
        ID = 171;

        Text = "Your knowledge of the wilderness and the ways of even its smallest creatures makes this an easy question to answer. You know full well that without ants to clear away the debris of wood and leaves the forest would drown in a blanket of rot in but a few years.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 67; }
};

class Story172 : public Story::Base
{
public:
    Story172()
    {
        ID = 172;

        Text = "You close with Gathkeri and unleash a combination of kicks and punches. The elf, however, is quicker than you. At the end of the exchange of blows his foot smashes into your chest at the bottom of your ribcage, causing you to double up in pain. Gathkeri has smashed some of your ribs.\n\nThe elf gives you no time to recover. He darts in to the attack again, his feet a blur as they shoot out at your head and body.\n\nYou LOSE 5 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try the same tactic again", 422));
        Choices.push_back(Choice::Base("Try to grapple him", 142));
        Choices.push_back(Choice::Base("Fallback before his attack", 381));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -5);
    }
};

class Story173 : public Story::Base
{
public:
    Story173()
    {
        ID = 173;

        Text = "The new way you have taken plunges you deep into a dark emerald gloom, where the moisture of rotting bark seems to deaden all sound. You feel as if you are walking away from the lands of men into another time, a time of desolation and loneliness.\n\nAs you walk you begin to feel an unpleasant itching which turns to pain and, looking down, you see a horde of brown ants swarming up your legs.\n\nThere are thousands of them converging on you out of fallen trees and cracks in the earth. You run for it, brushing frantically at your body to dislodge the insects as you go.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head uphill", 164));
        Choices.push_back(Choice::Base("Go downhill", 199));

        Controls = Story::Controls::STANDARD;
    }
};

class Story174 : public Story::Base
{
public:
    Story174()
    {
        ID = 174;

        Text = "The magic bindings of the Tower of Will spell leave your mind and cross to the mind of the King of the Elves. You reach out and touch an alien mind, an old green-blooded mind that is at home here in the forest and unable to comprehend much of your thoughts.\n\nUnfortunately it is as hard for you to get a grip on the king's thoughts. His will, tempered by leadership over the millennia, is at least the match of yours, and your mind, not yet fatigued by spellcasting, retreats in confusion. In a desperate flurry of thought, you cast the Shield of Defense spell to protect yourself from his magic.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 52; }
};

class Story175 : public Story::Base
{
public:
    Story175()
    {
        ID = 175;

        Text = "You cut a length of creeper from a nearby tree to bind the elf, who does not stop you tying him to a branch. \"At least now you can stop looking at me, mortal.\"\n\nAs your gaze is obviously making the poor elf feel very uncomfortable you decide to spend a little time checking the area for any of his friends. You find none, though at any moment you expect to feel an arrow piercing your flesh.\n\nWhen you return to the branch to check on the elf, he has vanished. So has the creeper with which you tied him. All that remains is a spattering of ash on the forest floor. In the short time you were away he couldn't have gotten far so you search for him, but his woodcraft is superior to yours and you cannot find him.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 380; }
};

class Story176 : public Story::Base
{
public:
    Story176()
    {
        ID = 176;

        Text = "Apart from the hunter and the guide there are five other people in the room. Three sit together -- they look like ordinary townsfolk, suspicious but not dangerous.\n\nOf the two others, one is a woman dressed in a grey travelling robe. The cowl is thrown back to reveal grey hair and a weather-beaten face. The remaining person is a sinister-looking man in a black cloak whose face is hidden in the shadows of his cowl.";

        Choices.clear();
        Choices.push_back(Choice::Base("Sit at the nearest table to the fire and talk to the hunter and guide", 297));
        Choices.push_back(Choice::Base("Join the woman dressed in grey", 181));
        Choices.push_back(Choice::Base("Have dealings with the sinister main in black", 324));

        Controls = Story::Controls::STANDARD;
    }
};

class Story177 : public Story::Base
{
public:
    std::string PreText = "";

    Story177()
    {
        ID = 177;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "You choose a suitable tree. As you prepare to slash into its bark, you glance upwards at its branches. The knots on the bole remind you of the face of a wizened old man, or perhaps of the eyes of an owl.\n\nWhen you cut the bark a great flake comes off with your blade, and the pale wood beneath seems to shrink from the dim light like the stomach of an old man coughing. There is a far-away call that sounds like a howl of rage and terror lost in the wind.\n\nThe bole of the tree convulses suddenly and there is a ripping sound as its roots grow suddenly out of the ground, pinioning you.";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::MAPLE_FLUTE}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nThere is nothing you can do to save yourself as the tree, creaking and juddering, begins to sink into the ground, burying you along with it.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 222; }
};

class Story178 : public Story::Base
{
public:
    Story178()
    {
        ID = 178;

        Text = "The dragon's nostrils smoulder as it looks down its long nose at you.\n\n\"You are brave, O impudent man,\" it booms. Its voice has the timbre of thunder in a summer storm.\n\n\"Aye, when I have to be,\" you reply, recoiling at the beast's terrifying voice. All thoughts of brave action and heroism desert you.\n\n\"What is it you want with me? Do you hanker to call yourself dragon-slayer and have your name bruited about the land? Have you perhaps heard that dragons sleep on vast hoards of treasure? Or perhaps you want me to teach you magic?";

        Choices.clear();
        Choices.push_back(Choice::Base("Say you wish to be taught the wonders of magic", 185));
        Choices.push_back(Choice::Base("Say that you would like a tenth part of the dragon's hoard", 194));
        Choices.push_back(Choice::Base("Say you want the dragon's help", 205));
        Choices.push_back(Choice::Base("Say you don't want anything from the dragon", 10));

        Controls = Story::Controls::STANDARD;
    }
};

class Story179 : public Story::Base
{
public:
    Story179()
    {
        ID = 179;

        Text = "As you start to pull the EMERALD RING off your finger you notice the owl perched on top of the ladder looking on with its unblinking eyes.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take off the ring and throw it into the pool", 195));
        Choices.push_back(Choice::Base("Take off the ring and keep it", 208));
        Choices.push_back(Choice::Base("Change your mind and leave the ring on", 220));

        Controls = Story::Controls::STANDARD;
    }
};

class Story180 : public Story::Base
{
public:
    Story180()
    {
        ID = 180;

        Text = "Your words seem to make no difference: the elves just stare at you. Their childlike faces belie the threat they present. A few of them carry slender longbows but these are slung over their shoulders. The elves are not trying to frighten you but the eeriness of those young old faces, silent and quizzical, is unnerving. For all you know each one of them was born before man came into existence.\n\nYou repeat that you are no friend of the Westermen and that you want to save the forest. Your words are met by stony silence. Rattled by this lack of communication, you end up by saying that not all men are evil. You then decide to keep your mouth shut.\n\n\"I have met many men,\" says a voice. \"Seven this very millennium have found me here in the greenwood. On the whole, taken for what they were, summing the sinews of their spirit and the canopy of their souls, they were bad; not evil, just bad. We came here to avoid the prattling of men. It is hard for us to be near those we must pity.\"\n\nAt the mention of the word pity, many of the elves turn their faces away for a moment, as if to spare you. You will have to win their respect.";

        Choices.clear();
        Choices.push_back(Choice::Base("Apologize for making them feel uncomfortable by disturbing them in the greenwood", 209));
        Choices.push_back(Choice::Base("Tell them it is they who are to be pitied, for the Westermen are destroying their forest as surely as night follows day", 219));

        Controls = Story::Controls::STANDARD;
    }
};

class Story181 : public Story::Base
{
public:
    Story181()
    {
        ID = 181;

        Image = "images/filler3.png";

        Text = "The woman looks wise. \"My name is Elanor, I am a priestess of the All Mother, from whom springs all life, eternally.\" Her weather-beaten face comes to life as she speaks and you sense her love of life.\n\nShe tells you Valerian, the man in the black robe, is a Moon Druid who vies with her for control of the forest and the beasts dwelling there. \"But they sense his evil and flock to me. His envy of me consumes his heart and turns it as black as his cloak. Valerian has thrown in his lot with the Westermen, the hewers and burners. They have come to destroy the great forest.\"\n\nShe seems very grave.";

        Choices.clear();
        Choices.push_back(Choice::Base("Say that it would be a terrible thing to destroy the great forest", 14));
        Choices.push_back(Choice::Base("Ask her why it would be such a bad thing to destroy the forest", 2));

        Controls = Story::Controls::STANDARD;
    }
};

class Story182 : public Story::Base
{
public:
    Story182()
    {
        ID = 182;

        Text = "You cast the spell of the Shield of Defense just as a silver noose appears in the air before you. The noose drops over your head magically, avoiding the shield by dancing above it. You try to drag it from your neck but the silver cord tightens slowly until it flattens your windpipe. You grow purple with effort and lack of oxygen. Gurgling horribly, unable to speak, you subside to the floor and black out, never to regain consciousness. It is doubtful that these unfriendly people of Burg will even give you a decent burial: your remains will probably be thrown on a spoil heap.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story183 : public Story::Base
{
public:
    Story183()
    {
        ID = 183;

        Image = "images/filler1.png";

        Text = "As Gathkeri circles you, you try to cut him off by making a sudden rush to back him up against the edge of the circle. You lunge to grapple him, but he is too quick for you this time. He skips nimbly past and falls back onto a patch of uneven ground inside the circle. He looks down when he treads on a root and you close in again.";

        Choices.clear();
        Choices.push_back(Choice::Base("Repeat the same tactic", 142));
        Choices.push_back(Choice::Base("Attack him with your fists and feet", 172));
        Choices.push_back(Choice::Base("Wait for him to attack you", 161));

        Controls = Story::Controls::STANDARD;
    }
};

class Story184 : public Story::Base
{
public:
    Story184()
    {
        ID = 184;

        Text = "As soon as you take the stopper out of the round bottle the bees veer away. You smear a little of the white jelly across your forehead and smile. The jelly has a pungent smell which seems to be driving the insects away. Even the beetles on the forest floor are scurrying away from you.\n\nSaved from the insects by the white balm, you ponder where to search for the Tree of Knowledge next. You know it will soon be Midsummer's Day.";

        Choices.clear();
        Choices.push_back(Choice::Base("Continue your search by heading west", 43));
        Choices.push_back(Choice::Base("Head east", 427));
        Choices.push_back(Choice::Base("Go south-west", 70));

        Controls = Story::Controls::STANDARD;
    }
};

class Story185 : public Story::Base
{
public:
    Story185()
    {
        ID = 185;

        Text = "The dragon tells you that because you have disturbed it from its slumbers it seems appropriate to begin by teaching you the spell of sleep. It starts to recite the words of the spell, but chooses to demonstrate on you to show what the effect is like. Unfortunately it is a dragon sleep-spell and will keep a puny mortal like you asleep for a hundred years. By the time you awake the forest will be no more. Your selfish thirst for knowledge has sealed the destruction of the forest and all the things that live in it.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story186 : public Story::Base
{
public:
    Story186()
    {
        ID = 186;

        Text = "You summon all your willpower and try to grapple with the machine in a battle of minds, your resolve weakened by the nagging fear that the machine doesn't have a will of its own.\n\nTo your surprise your magic tells you there is a mind within the machine -- one that belongs to the man who is controlling it. He is too busy working the machine to notice your attack, and when your psychic assault hits him, the machine grinds to a halt.\n\nYou sense his shift in attention from the machine to you. Although you hold the machine motionless for many moments, you fail to overpower the will of the man inside it, and at last he manages to throw the lever that sets the steam-hammer of a sword arm into motion again.\n\nOne last great blow splits the trunk in the middle and the Tree of Life is dead. Your hopes of saving the forest are destroyed; dejected you are taken prisoner and enslaved.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story187 : public Story::Base
{
public:
    Story187()
    {
        ID = 187;

        Text = "The Elf King crosses to a juniper bush and shakes it branches. \"Attend to my word,\" he says to the bush. \"Awaken -- speak. Tell me of a secret.\"\n\nThe bush speaks in a voice like sighing: \"Under my roots, a mole with a scarred forepaw, has just devoured an earthworm. No other know this secret until now.\"\n\nThe Elf King turns to you triumphantly. \"Well, mortal? Can you make the very plants themselves speak? If not, you forfeit the contest.\"\n\nYou go over to a tree and snap off a twig. \"I shall make this single twig tell a secret,\" you declare. \"And moreover, it will not be by magic, but in a manner that any man might use.\" So saying, you strike up a small fire among some dead leaves and char the end of the twig. Then, removing your shirt, you use the charred tip of the twig like a pencil. The elves gather round to watch as you write: \"The Elf King's true name is --\"\n\n\"Enough!\" The Elf King snatches the twig out of your hand. He casts it aside, an unsettled look clouding his silver-grey eyes. \"This is mere trickery. My next task will not be so easy to circumvent.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Insist that it is your turn to set him a task", 221));
        Choices.push_back(Choice::Base("Let him set a third task", 20));

        Controls = Story::Controls::STANDARD;
    }
};

class Story188 : public Story::Base
{
public:
    Story188()
    {
        ID = 188;

        Image = "images/man-in-black-cowl.png";

        Text = "These people look very wary of strangers. Whatever you say mustn't alarm them. They could easily be untrustworthy so you had better not mention the Tree of Knowledge. You loudly announce that you are searching for a rare kind of bird that you hope to find in the forest, the violet tanager. \"Can anyone guide me to the nest of such a bird?\" you ask, fingering your money-pouch significantly.\n\n\"I know of no such bird in the forest. Indeed, I have never heard tell of a tanager that was violet.\" The voice of the woman in grey carries absolute certainty; she must be steeped in wilderness lore.\n\nYou explain it is a very rare bird mentioned in ancient manuscripts and ask about the birds she has seen in the forest.\n\nShe gestures you to join her table; she seems happy to talk to you all night about the forest. The man in black cowl stares at you all the while; his eyes look like glittering flints within his cowl. The other two have returned to the fire.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 181; }
};

class Story189 : public Story::Base
{
public:
    Story189()
    {
        ID = 189;

        Image = "images/filler2.png";

        Text = "When you awake the Kwerrel is nowhere to be seen, although the archway back out to the forest has reappeared. You make good your escape, knowing that the Kwerrel could have killed you if it had wanted to.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 406; }
};

class Story190 : public Story::Base
{
public:
    Story190()
    {
        ID = 190;

        Text = "\"No,\" you say loudly. \"The contest is over. I have won.\"\n\nHuldranas was already in the act of notching another arrow to his bow. He assumed that you, like any elf, would immediately accede to the king's commands. Now he lowers the bow and looks around uncertainly.\n\n\"Do you value pride above the truth?\" you demand of the assembled elves. \"Is this what has become of the legendary elves -- cloistered from the sight of other peoples, you turn your vision inwards and forget the values of honour, courtesy and courage?\"\n\nHundreds of faces stare back inscrutably from the gloom between the trees. The Elf King sweeps back his cloak in an extravagant gesture which reminds you of a sleek cat grooming itself. \"Very well, mortal,\" he says in a languid voice. \"You have won the contest. Now let us talk.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 232; }
};

class Story191 : public Story::Base
{
public:
    Story191()
    {
        ID = 191;

        Text = "You whip an arrow to your bow and let fly. It splinters your opponent's shaft in mid air before it reaches its target. You breathe a sigh, knowing that it was a one in a hundred fluke that you did not miss your target and end up humiliated.\n\nThe effect on Huldranas is deeply mysterious and utterly elfin. For a long moment he remains gazing along the arrow's flight, his bow half lowered, arm still poised in the moment of release. Then it is as if he wakes from a trance. Turning to you, he performs an elegant courtly salute, then snaps his bow across his knee and casts it aside along with his quiver. \"Henceforth I eschew the bow,\" he declares to the assembled elves. \"Huldranas will take his prey with spear or not at all. This is my geas.\"\n\nHe turns and stalks away. You regret the loss archery such a fine exponent of the art, but at least your daring risk has secured you victory. Now the elves will respect your words.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 232; }
};

class Story192 : public Story::Base
{
public:
    Story192()
    {
        ID = 192;

        Text = "The chance is gone. You had the opportunity not only to reach the vulnerable hose but also to jump away from your attackers. They close in from both sides and though you evade two sword cuts, a sudden thrust from behind finishes you off.\n\nYour allies, the elves, are already melting back into the forest. You have lost your chance to save the great Forest of Arden.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story193 : public Story::Base
{
public:
    Story193()
    {
        ID = 193;

        Text = "You beg the owl's pardon and implore it to wait, but it has taken to the wing again and is swiftly lost in the gloom of the forest. As you walk away from the crags three small tree warblers drive-bomb you, pecking your ears. They are too small to be of any danger, although you have never seen small birds act in this way.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 173; }
};

class Story194 : public Story::Base
{
public:
    Story194()
    {
        ID = 194;

        Text = "The dragon flicks its tail and licks its lips. \"Walk into the cavern and behold my hoard. It has been garnered from the palaces of the whole world. Many of my pieces are old, so very old, that they have a tale to tell.\"\n\nThe dragon rolls over so you fall to the ground on your feet. With a sweep of its massive claw, it ushers you forward into the dark cavern.\n\n\"All the gold and jewels you can carry I give to you.\"\n\nAs you stare in awe at a pile of coins, goblets, candelabra and jewellery, some of the coins fly up into the air and push themselves against you. Soon they are covering you in a crust, like barnacles on the hull of a ship. They leave your arms and legs free but you are terribly weighed down by the gold that has stuck to you. You try to prise the coins away but they are stuck fast by the magic of the dragon.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 19; }
};

class Story195 : public Story::Base
{
public:
    Story195()
    {
        ID = 195;

        Text = "The RING slips of easily off your finger, but as you take it off you feel a sense of loss -- a loss of purpose and of strength. But the certainty that the RING is magical and has been influencing you strengthens your resolve. You send it spinning through the air to land in a pool with a plop.\n\nThe owl shuts its eyes and says, \"What a waste. And that was my lady's RING, not for you to hurl away.\"\n\nThere is still no sign of Elanor.";

        Choices.clear();
        Choices.push_back(Choice::Base("Steal potions and leave", 235));
        Choices.push_back(Choice::Base("Ask the owl where Elanor is", 244));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::EMERALD_RING_ELANOR});
    }
};

class Story196 : public Story::Base
{
public:
    Story196()
    {
        ID = 196;

        Text = "The path twists and turns, winding through dense undergrowth overhung by barrel-like Gwelph trees that are festooned with lianas. You try to fix the shape of each tree in your mind so you will know if you have passed by one before.\n\nTo your dismay the path ends in a little clearing choked with dead leaves, but from which two paths lead off in different directions. Each path is lined with thorn bushes that have grown to the height of a man and are covered in inch-long purple barbs oozing an orange fluid. The thorns would break off in your flesh if you brushed against them.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head left", 131));
        Choices.push_back(Choice::Base("Head right", 211));
        Choices.push_back(Choice::Base("Despair of ever finding your way out of the forest", 156));
        Choices.push_back(Choice::Base("Mark one of the great Gwelph trees by scoring it with your dagger", 177));

        Controls = Story::Controls::STANDARD;
    }
};

class Story197 : public Story::Base
{
public:
    Story197()
    {
        ID = 197;

        Text = "The bees fly faster than you can run. They settle around your head so you cannot see to run. Blindly, you stagger about the forest, continually stung by the bees. Death from so many bee stings is not pleasant. Your neck swells until your windpipe is closed up and you choke to death. You rue bitterly your folly in upsetting Elanor, the Lady of the Forest, and you have paid the price.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story198 : public Story::Base
{
public:
    Story198()
    {
        ID = 198;

        Text = "Your heartfelt plea for the Chief of the Westermen to reconsider his actions falls upon deaf ears. He simply cannot believe you are being so foolish to question him. \"How can cutting down trees destroy the whole world? You are talking nonsense! Who are you, and who sent you to interfere in our plans?\"\n\n\"Listen to me or we are all doomed,\" you tell him. But now you see that you can never hope to persuade him. You have simply put yourself in danger by attempting to end the Westermen's onslaught peaceably.\n\nThe chief has had enough. \"Silence this wittering fool. Bring chains -- we'll add another slave to the work gangs.\"\n\nValerian is watching you. His hard stare suggests he is calling a spell to mind.";

        Choices.clear();
        Choices.push_back(Choice::Base("Surrender and be enslaved", 146));
        Choices.push_back(Choice::Base("Make a run for it", 451));
        Choices.push_back(Choice::Base("[SPELLS] Use magic", 450, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story199 : public Story::Base
{
public:
    std::string PreText = "";

    Story199()
    {
        ID = 199;

        Choices.clear();
        Choices.push_back(Choice::Base("Fight the serpent", 218));
        Choices.push_back(Choice::Base("Cry out in despair to the owl in case it is still nearby and prepared to forgive and help you", 227));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The ants' bites are poisonous. You have already suffered dozens of wounds by the time you reach a large pond in a dark hollow. You LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nThrowing caution to the winds and driven by the tormenting pain of the bites, you plunge into the water and immerse yourself where you tear off your clothes.\n\nThe torment ceases as the ants drown and float to the surface, and although the venom makes you feel drowsy you manage to drag yourself towards the pond's edge.\n\nJust as you are about to hand yourself out of the water, you feel a huge water snake coiling around your legs.";
        }

        Text = PreText.c_str();
    }
};

class Story200 : public Story::Base
{
public:
    Story200()
    {
        ID = 200;

        Image = "images/filler2.png";

        Text = "Renard leads you out of the town through the waterside gate to the bank of the Burgstream. You walk north along a path next to the bank. The river valley has quite steep sides, making it difficult for you to see very much of the surrounding land. Ahead, however, you can see the vast top of a leafy canopy that stretches to the far horizon like a green sea fading to blue in the distance. The air is good here -- fresh and clean, laden only with the perfumes of wild flowers.\n\nA lone figure in grey walks ahead. You suggest trying to catch up but Renard just shakes his head.\"We will never find her in the forest unless she wishes it. A man might as well try to fly.\"\n\n\"If we run we can catch up before she reaches the forest,\" you suggest.\n\n\"She moves as fast as a deer at need. We'd only tire ourselves to no end.\"\n\nIf it is the same old woman from the inn last night, she looked too old even to break into a trot. You ponder Renard's strange claims until you can see the trunks of the trees at the edge of the Forest of Arden.\n\nAs you enter the forest you are surprised by how much colour there is. Blossoming trees, fungus mounds in bright hues, flowering creepers and giant butterflies are lit by the dappled sunshine that pours through gaps in the leafy canopy. It is noisy too -- the forest is alive with insects, birds and small mammals. Renard leads you along short cuts where the Burgstream bends tortuously until at last you hear the roar of the great Sirion river as it rushes through the forest ahead. He brings you to a ford over the Burgstream.\n\n\"We must cross here and then walk west beside the Sirion.\" You follow across the ford and on through the thick forest.\n\nNothing in your life has prepared you for the moment when you first catch sight of the Sirion river. The furthest bank is just a line of shimmering heat-hazed greenery at least six miles away. The roiling waters carry a multitude of dead tree branches towards the sea, like a vein carrying detritus out of a living body. Across the river the treeline is unbroken. You are deep in the rainforest now. The gigantic trees spread their branches more than a hundred feet above the ground. At the river's edge mangroves reach far out into the water. Bloated river buffalo bask beneath their arching roots.\n\n\"The going will be difficult for a while until we reach higher ground,\" says Renard. He presses on, hacking at the undergrowth, until you reach a tributary of the river. It blocks your progress, and is spanned by only a narrow rope bridge. The bridge show signs of regular repair: bushes have been hacked back from the stanchions between which it hangs. Renard tells you that the elves maintain this bridge as a link between different parts of their domain. He leads the way across and you follow.\n\nHe is halfway across when a waterspout surges up from the river. Out of it rears a mass of vegetation ringed with fibrous tentacles. It is a dreaded Embracer, and in seconds it has plucked Renard from the bridge. As he is pulled under the water, he manages to cry out to you: \"You must go on, then climb. Then you may find what you seek --\"\n\nThe tentacles drag him under. You watch the muddied water swirl beneath the bridge, but there is no sign of poor Renard.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to save him", 316));
        Choices.push_back(Choice::Base("Cross the bridge quickly while the Embracer is otherwise occupied", 343));

        Controls = Story::Controls::STANDARD;
    }
};

class Story201 : public Story::Base
{
public:
    Story201()
    {
        ID = 201;

        Text = "The Elf King gives the order to begin. Gathkeri circles you warily. He is very light-footed and the look in his eyes is murderous.";

        Choices.clear();
        Choices.push_back(Choice::Base("Grapple with him", 183));
        Choices.push_back(Choice::Base("Attack him with your fists and feet", 172));
        Choices.push_back(Choice::Base("Wait for him to attack you", 161));

        Controls = Story::Controls::STANDARD;
    }
};

class Story202 : public Story::Base
{
public:
    Story202()
    {
        ID = 202;

        Text = "These men look well armed and well fed. They are probably veterans of many campaigns but their jowls and their paunches have grown a little flabby from lack of exercise here in the forest. The chief hired them to protect the camp against the elves, but so far, the fey sylvan elves have done nothing to hinder the Westermen and the guards have led an indolent life with nothing more to do than keep the slaves in check. Still, there are eight of them and all are armed with swords and protected by corslets of mail.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [SWORDPLAY]", 461, Skill::Type::SWORDPLAY));
        Choices.push_back(Choice::Base("Use [CHARMS]", 471, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Use [STREETWISE]", 481, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("Use [SPELLS]", 442, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("You have none of these skills", 491));

        Controls = Story::Controls::STANDARD;
    }
};

class Story203 : public Story::Base
{
public:
    Story203()
    {
        ID = 203;

        Text = "You rush to attack, and several of the Westermen turn to meet your onslaught. As individuals and taken one at a time they would certainly be no match for you. The men you are facing, however are seasoned campaigners and no fools. You are quickly surrounded.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to kill one, leap over his fallen body and then retreat to safer ground nearby", 376));
        Choices.push_back(Choice::Base("Fight it out until you or all your opponents are slain", 84));

        Controls = Story::Controls::STANDARD;
    }
};

class Story204 : public Story::Base
{
public:
    Story204()
    {
        ID = 204;

        Text = "\"Yes, that was it,\" you reply. \"The Reaver's Inn, Bessaraban. What a place, eh?\"\n\n\"Remember the one-legged serving wench who used to take her leg off and poke the fire with it?\" asks the chief.";

        Choices.clear();
        Choices.push_back(Choice::Base("Say yes, you remember her, but can't think of her name", 358));
        Choices.push_back(Choice::Base("Admit that you don't remember her", 367));

        Controls = Story::Controls::STANDARD;
    }
};

class Story205 : public Story::Base
{
public:
    Story205()
    {
        ID = 205;

        Text = "You explain your quest to save the forest from the Westermen. The dragon has been asleep all the time the men have been hacking and burning the forest, but he seems to believe your tale of woe. He tells you his name is Garoshtar and says he is surprised and impressed that a human could want so little of him when he has great power and riches to give.\n\nHe tells you to come for him at your hour of greatest need and he will help you against the Westermen. Remember you have the promise of Garoshtar's help.\n\nYou gained the codeword SCORPION.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::SCORPION});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::WATERBEARER))
        {
            return 49;
        }
        else
        {
            return 21;
        }
    }
};

class Story206 : public Story::Base
{
public:
    Story206()
    {
        ID = 206;

        Text = "As he sees you about to cast another spell, Valerian utters a single word, \"Sanctuary,\" in a ringing voice and claps his hands together. There is a second clap and he is gone. He has disappeared completely. You go to the door of the inn but there is no sign of him in the rain-lashed cobbled street.\n\nOnly the old woman in grey remains in the common room.";

        Choices.clear();
        Choices.push_back(Choice::Base("Sit at her table and talk with her", 181));
        Choices.push_back(Choice::Base("Take a room at the inn for the night", 333));

        Controls = Story::Controls::STANDARD;
    }
};

class Story207 : public Story::Base
{
public:
    Story207()
    {
        ID = 207;

        Text = "You summon all your willpower and try to grapple with the machine in a battle of minds, even though your resolve is weakened by the nagging fear that the machine doesn't have a will of its own.\n\nTo your surprise your magic tells you there is a mind within the machine -- it belongs to the man who is controlling it. He is busy working the machine, and the machine grinds to a halt as he is hit by your psychic assault.\n\nThe operator switches his attention to you and focuses his mental powers. You hold the machine motionless for long moments without managing to overpower the will of the man inside it.\n\nHow will you follow up your success?";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Choking Fog", 395));
        Choices.push_back(Choice::Base("Use Bafflement", 372));
        Choices.push_back(Choice::Base("Cast Visceral Disruption", 64));

        Controls = Story::Controls::STANDARD;
    }
};

class Story208 : public Story::Base
{
public:
    Story208()
    {
        ID = 208;

        Text = "What if, you reason, the EMERALD RING is taking over control of your mind with every passing moment? As the RING slips easily off your finger you feel a sense of loss -- loss of purpose and of strength. The RING must be magical. You decide to keep it safe but not to wear it for now. You need your wits about you.\n\nThe owl has been watching you all the time.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 244; }
};

class Story209 : public Story::Base
{
public:
    Story209()
    {
        ID = 209;

        Image = "images/filler3.png";

        Text = "\"It is a mistake soon remedied by returning to the lands of men.\"\n\n\"But, but...\" you stammer as the elves turn away and slip out of sight. As they go, you look from one to another, and as you do so, each one freezes under your gaze. Perhaps they act so strangely because they are too polite to disappear while you look at them, for at the edges of your vision you see them move behind trees and leaf curtains. They vanish swiftly and silently, moving through the dense forest like rainbow trout in a murky river. They are not wasting magic, you cannot keep up with them.\n\nAt last only one elf is left.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 230; }
};

class Story210 : public Story::Base
{
public:
    Story210()
    {
        ID = 210;

        Text = "After leaving Burg by the waterside gate you walk north along a path next to the bank of the Burgstream. The river valley has quite steep sides and you can see little of the land that surrounds you. Ahead you see the vast leafy canopy that stretches to the far horizon like a green sea fading to blue in the distance. The air is good here, fresh and clean, laden only with the perfume of wild flowers.\n\nA lone figure in grey walks ahead. You increase your pace to catch up. After half an hour's hard walking you seem to be no nearer the figure. You break into a jog but even this seems to bring you no closer to the slender woman dressed in grey. You ponder the strange fact that even though she seems only to be walking you cannot seem to come any closer to her. At last you reach the crest of a rise to find she has vanished, but now you can see the trunks of the trees at the edge of the Forest of Arden.\n\nAs you enter the forest you are surprised by how much colour there is. Blossoming trees, fungus mounds in bright hues, flowering creepers and giant butterflies are lit up by the dappled sunshine that trickles through gaps in the leafy canopy. It is noisy, too -- the forest is alive with insects, birds and small mammals.\n\nThe path stays close to the river, almost doubling back on itself where the Burgstream bends tortuously until at last you hear the roar of the great Sirion river as it washes through the forest ahead. Pressing on, you come to a ford over the Burgstream.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cross the ford and follow the bank of the Sirion river to the west", 77));
        Choices.push_back(Choice::Base("Remain on this side of the Burgstream and turn east when you meet the Sirion", 96));

        Controls = Story::Controls::STANDARD;
    }
};

class Story211 : public Story::Base
{
public:
    Story211()
    {
        ID = 211;

        Image = "images/path-twists.png";

        Text = "The path twists and turns, winding through dense undergrowth overhung by barrel-like Gwelph trees that are festooned with lianas. You try to fix the shape of each tree in your mind so you will know if you have passed one before. To your dismay the path ends in a little clearing choked with dead leaves. Two paths lead off in different directions, and each is lined with thorn bushes that are at least the height of a man and which are covered in inch-long purple barbs that ooze an orange fluid. The thorns would break off in your flesh if you brushed against them.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head left", 196));
        Choices.push_back(Choice::Base("Head right", 131));
        Choices.push_back(Choice::Base("Despair of ever finding your way out of the forest", 156));
        Choices.push_back(Choice::Base("Orient yourself by marking one of the great Gwelph trees by scoring it with your dagger", 177));

        Controls = Story::Controls::STANDARD;
    }
};

class Story212 : public Story::Base
{
public:
    Story212()
    {
        ID = 212;

        Text = "There is something very strange about the grass on that hillock. It seems almost reflective, as if the stems of grass were coated in shiny wax. White egrets like the one on the hillock eat insects -- they catch mites and parasites on the hides of large animals. You've never known one probe the ground for worms.";

        Choices.clear();
        Choices.push_back(Choice::Base("Walk to the top of the hillock, anyway, to see what you can see", 47));
        Choices.push_back(Choice::Base("Leave the valley and skirt around it to the east, if you prefer", 408));

        Controls = Story::Controls::STANDARD;
    }
};

class Story213 : public Story::Base
{
public:
    Story213()
    {
        ID = 213;

        Text = "You tackle her before she can leap through the hatch and, pinioning her arms behind her back, tie her to a vine that is growing in and out of the walls of the tree house.\n\n\"What do you hope to gain by this?\" she asks.\n\n\"The potions, what do they do?\" you ask urgently.\n\nThere are five potions on the shelf behind her. There is a clear cherry-red liquid in a wax-stoppered phial, a small round bottle of something like runny tar, a jar of white jelly, a cloud sea-blue fluid in a phial and a glass pot that contains layers of coloured earth.\n\nElanor starts to explain what each does. \"The blue fluid, if quaffed in sunlight, will heal all save the most serious of hurts.\" As she says the word \"hurts\" the back of your wrist is stung by a bee. Elanor seems not to notice and goes on talking about the potions.\n\n\"This black tarry goo is mulch of fire lizard's gizzard, a deadly poison.\"\n\nYou are stung twice more, on the leg and the neck. More bees fly into the tree-house, buzzing angrily. You can't stand being stung like this for much longer. The bees' stings feel like those of hornets.";

        Choices.clear();
        Choices.push_back(Choice::Base("Quickly ask about the red liquid", 313));
        Choices.push_back(Choice::Base("Ask about the white jelly", 304));
        Choices.push_back(Choice::Base("Ask about the bands of coloured earth in the hope that one of them will protect against the insects", 296));
        Choices.push_back(Choice::Base("Grab the phial of blue fluid and drink it", 292));

        Controls = Story::Controls::STANDARD;
    }
};

class Story214 : public Story::Base
{
public:
    Story214()
    {
        ID = 214;

        Text = "\"These golden disks look pretty,\" says the Kwerrel. \"Give me ten and I will help you\".";

        Choices.clear();
        Choices.push_back(Choice::Base("Hand them over (10 gold pieces)", 8, Choice::Type::LOSE_MONEY, 10));
        Choices.push_back(Choice::Base("You don't have enough or won't pay that much", 158));

        Controls = Story::Controls::STANDARD;
    }
};

class Story215 : public Story::Base
{
public:
    Story215()
    {
        ID = 215;

        Image = "images/filler2.png";

        Text = "You recall a snippet of doggerel that used to be sung by the old gypsy women who came to town selling their handicrafts:\n\nThe name of the elfin king\nIs a terribly powerful thing:\nIf you speak it to him, or even sing,\nYou can make him give you his signet ring.\nThe Elf King's name is --\nAh! but that would be telling!\n\nSuch songs always fascinated you, since their simple folk rhythm seems to conceal a core of hoary secret truth. The hard part is to strip away the mystery so that you are left with that truth. You also know that you must tread carefully. The elves are proud and pitiless, and often behave like spiteful children in spite of their immemorial wisdom. You must not show weakness or hesitation which they could exploit to their advantage, but neither must you offend them.";

        Choices.clear();
        Choices.push_back(Choice::Base("Guess the Elf King's name", 309));
        Choices.push_back(Choice::Base("You would prefer to accept a duel", 137));

        Controls = Story::Controls::STANDARD;
    }
};

class Story216 : public Story::Base
{
public:
    Story216()
    {
        ID = 216;

        Text = "You cast a Thunderclap spell in an effort to stun the owl. The spell works and the owl, stunned, dashes its head against the branch of a tree and falls to the ground.\n\nIt lies still for a while, then raises its head to look at you.\n\n\"The curse of the Grey Touch be upon you, traveller, for striking the Grey Lady's servant,\" it calls.\n\nThe owl flaps its wings and takes off, swooping past you back to the forest.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 193; }
};

class Story217 : public Story::Base
{
public:
    Story217()
    {
        ID = 217;

        Image = "images/filler3.png";

        Text = "You wait, concealed in the trees, for nightfall. You have not been waiting and watching long when Valerian the Moon Druid, who you saw at the inn at Burg, pays a visit to the black and scarlet pavilion. He is still wearing the all-enveloping black robe but the hood is back to reveal the hatchet-like features and black goatee beard.\n\nHe leaves an hour later, looking smugly satisfied. Other men come and go with reports or to suit for some privilege or to settle disputes. The day fades into a dark and moonless night, ideal for what you have in mind.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Use magic to enter the pavilion", 452, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Rely on natural stealth", 462));

        Controls = Story::Controls::STANDARD;
    }
};

class Story218 : public Story::Base
{
public:
    Story218()
    {
        ID = 218;

        Text = "The serpent is heavy and horribly powerful. You are in its element and are powerless to resist as it crushes the life out of you. The last thing you hear is the sound of your own ribcage shattering.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story219 : public Story::Base
{
public:
    Story219()
    {
        ID = 219;

        Text = "There is no mistaking the expression in the elves' eyes this time. You have angered them.\n\n\"We are older than the forest. We were alive before the forest grew and we will live on after it is gone.\"\n\n\"But it has been your home for so long. Does it not anger you to see the burners destroying its beauty?\" you ask. \"And where will you live? Where will you find a place where there are no men to be pitied?\"\n\n\"Have you come here to taunt us? It is the coming of the time of men. All things must pass and we with them.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Taunt them to goad them into action", 426));
        Choices.push_back(Choice::Base("Humble yourself and beg them to let you see the wonders of their homes in the greenwood before it is lost for ever", 436));

        Controls = Story::Controls::STANDARD;
    }
};

auto prologue = Prologue();
auto story001 = Story001();
auto story002 = Story002();
auto story003 = Story003();
auto story004 = Story004();
auto story005 = Story005();
auto story006 = Story006();
auto story007 = Story007();
auto story008 = Story008();
auto story009 = Story009();
auto story010 = Story010();
auto story011 = Story011();
auto story012 = Story012();
auto story013 = Story013();
auto story014 = Story014();
auto story015 = Story015();
auto story016 = Story016();
auto story017 = Story017();
auto story018 = Story018();
auto story019 = Story019();
auto story020 = Story020();
auto story021 = Story021();
auto story022 = Story022();
auto story023 = Story023();
auto story024 = Story024();
auto story025 = Story025();
auto story026 = Story026();
auto story027 = Story027();
auto story028 = Story028();
auto story029 = Story029();
auto story030 = Story030();
auto story031 = Story031();
auto story032 = Story032();
auto story033 = Story033();
auto event033 = Event033();
auto story034 = Story034();
auto story035 = Story035();
auto story036 = Story036();
auto story037 = Story037();
auto story038 = Story038();
auto story039 = Story039();
auto story040 = Story040();
auto story041 = Story041();
auto story042 = Story042();
auto story043 = Story043();
auto story044 = Story044();
auto story045 = Story045();
auto story046 = Story046();
auto story047 = Story047();
auto story048 = Story048();
auto story049 = Story049();
auto story050 = Story050();
auto story051 = Story051();
auto story052 = Story052();
auto story053 = Story053();
auto story054 = Story054();
auto story055 = Story055();
auto story056 = Story056();
auto story057 = Story057();
auto story058 = Story058();
auto story059 = Story059();
auto story060 = Story060();
auto story061 = Story061();
auto story062 = Story062();
auto story063 = Story063();
auto story064 = Story064();
auto story065 = Story065();
auto story066 = Story066();
auto story067 = Story067();
auto story068 = Story068();
auto story069 = Story069();
auto story070 = Story070();
auto story071 = Story071();
auto story072 = Story072();
auto story073 = Story073();
auto story074 = Story074();
auto story075 = Story075();
auto story076 = Story076();
auto story077 = Story077();
auto story078 = Story078();
auto story079 = Story079();
auto story080 = Story080();
auto story081 = Story081();
auto story082 = Story082();
auto story083 = Story083();
auto story084 = Story084();
auto story085 = Story085();
auto story086 = Story086();
auto story087 = Story087();
auto story088 = Story088();
auto story089 = Story089();
auto story090 = Story090();
auto story091 = Story091();
auto story092 = Story092();
auto story093 = Story093();
auto story094 = Story094();
auto story095 = Story095();
auto story096 = Story096();
auto story097 = Story097();
auto story098 = Story098();
auto story099 = Story099();
auto story100 = Story100();
auto story101 = Story101();
auto story102 = Story102();
auto story103 = Story103();
auto story104 = Story104();
auto story105 = Story105();
auto story106 = Story106();
auto story107 = Story107();
auto story108 = Story108();
auto story109 = Story109();
auto story110 = Story110();
auto story111 = Story111();
auto story112 = Story112();
auto story113 = Story113();
auto story114 = Story114();
auto story115 = Story115();
auto story116 = Story116();
auto story117 = Story117();
auto story118 = Story118();
auto story119 = Story119();
auto story120 = Story120();
auto story121 = Story121();
auto story122 = Story122();
auto story123 = Story123();
auto story124 = Story124();
auto story125 = Story125();
auto story126 = Story126();
auto story127 = Story127();
auto story128 = Story128();
auto story129 = Story129();
auto story130 = Story130();
auto story131 = Story131();
auto story132 = Story132();
auto story133 = Story133();
auto story134 = Story134();
auto story135 = Story135();
auto story136 = Story136();
auto story137 = Story137();
auto story138 = Story138();
auto story139 = Story139();
auto story140 = Story140();
auto story141 = Story141();
auto story142 = Story142();
auto story143 = Story143();
auto story144 = Story144();
auto story145 = Story145();
auto story146 = Story146();
auto story147 = Story147();
auto story148 = Story148();
auto story149 = Story149();
auto story150 = Story150();
auto story151 = Story151();
auto story152 = Story152();
auto story153 = Story153();
auto story154 = Story154();
auto story155 = Story155();
auto story156 = Story156();
auto story157 = Story157();
auto story158 = Story158();
auto story159 = Story159();
auto story160 = Story160();
auto story161 = Story161();
auto story162 = Story162();
auto story163 = Story163();
auto story164 = Story164();
auto story165 = Story165();
auto story166 = Story166();
auto story167 = Story167();
auto story168 = Story168();
auto story169 = Story169();
auto story170 = Story170();
auto story171 = Story171();
auto story172 = Story172();
auto story173 = Story173();
auto story174 = Story174();
auto story175 = Story175();
auto story176 = Story176();
auto story177 = Story177();
auto story178 = Story178();
auto story179 = Story179();
auto story180 = Story180();
auto story181 = Story181();
auto story182 = Story182();
auto story183 = Story183();
auto story184 = Story184();
auto story185 = Story185();
auto story186 = Story186();
auto story187 = Story187();
auto story188 = Story188();
auto story189 = Story189();
auto story190 = Story190();
auto story191 = Story191();
auto story192 = Story192();
auto story193 = Story193();
auto story194 = Story194();
auto story195 = Story195();
auto story196 = Story196();
auto story197 = Story197();
auto story198 = Story198();
auto story199 = Story199();
auto story200 = Story200();
auto story201 = Story201();
auto story202 = Story202();
auto story203 = Story203();
auto story204 = Story204();
auto story205 = Story205();
auto story206 = Story206();
auto story207 = Story207();
auto story208 = Story208();
auto story209 = Story209();
auto story210 = Story210();
auto story211 = Story211();
auto story212 = Story212();
auto story213 = Story213();
auto story214 = Story214();
auto story215 = Story215();
auto story216 = Story216();
auto story217 = Story217();
auto story218 = Story218();
auto story219 = Story219();

void InitializeStories()
{
    Stories = {
        &event033,
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019,
        &story020, &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029,
        &story030, &story031, &story032, &story033, &story034, &story035, &story036, &story037, &story038, &story039,
        &story040, &story041, &story042, &story043, &story044, &story045, &story046, &story047, &story048, &story049,
        &story050, &story051, &story052, &story053, &story054, &story055, &story056, &story057, &story058, &story059,
        &story060, &story061, &story062, &story063, &story064, &story065, &story066, &story067, &story068, &story069,
        &story070, &story071, &story072, &story073, &story074, &story075, &story076, &story077, &story078, &story079,
        &story080, &story081, &story082, &story083, &story084, &story085, &story086, &story087, &story088, &story089,
        &story090, &story091, &story092, &story093, &story094, &story095, &story096, &story097, &story098, &story099,
        &story100, &story101, &story102, &story103, &story104, &story105, &story106, &story107, &story108, &story109,
        &story110, &story111, &story112, &story113, &story114, &story115, &story116, &story117, &story118, &story119,
        &story120, &story121, &story122, &story123, &story124, &story125, &story126, &story127, &story128, &story129,
        &story130, &story131, &story132, &story133, &story134, &story135, &story136, &story137, &story138, &story139,
        &story140, &story141, &story142, &story143, &story144, &story145, &story146, &story147, &story148, &story149,
        &story150, &story151, &story152, &story153, &story154, &story155, &story156, &story157, &story158, &story159,
        &story160, &story161, &story162, &story163, &story164, &story165, &story166, &story167, &story168, &story169,
        &story170, &story171, &story172, &story173, &story174, &story175, &story176, &story177, &story178, &story179,
        &story180, &story181, &story182, &story183, &story184, &story185, &story186, &story187, &story188, &story189,
        &story190, &story191, &story192, &story193, &story194, &story195, &story196, &story197, &story198, &story199,
        &story200, &story201, &story202, &story203, &story204, &story205, &story206, &story207, &story208, &story209,
        &story210, &story211, &story212, &story213, &story214, &story215, &story216, &story217, &story218, &story219};
}

#endif