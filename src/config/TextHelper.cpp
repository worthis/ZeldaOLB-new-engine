#include "TextHelper.h"

#include "../engine/resources/ResourceManager.h"

#include "../game/MainController.h"
#include "../game/keys/KeyBinder.h"

TextHelper::TextHelper()
{
    setWSpace(6);
    setWSize(8);
    setHSize(16);
    image = ResourceManager::getInstance()->loadImage("data/images/texts/font.png", true);
    setImage(image);
}

TextHelper::~TextHelper()
{
    ResourceManager::getInstance()->free(image);
}

void TextHelper::setLanguage(int i)
{
    switch (i)
    {
    case 0:
        setTextfile("data/texts/french.txt");
        break;
    case 1:
        setTextfile("data/texts/english.txt");
        break;
    case 2:
        setTextfile("data/texts/spanish.txt");
        break;
    case 3:
        setTextfile("data/texts/russian.txt");
        break;
    default:
        setTextfile("data/texts/english.txt");
        break;
    }
}

string TextHelper::getVariableValue(int textId, int varId)
{
    ostringstream os;
    int tmp;

    Scene *scene = MainController::getInstance()->getGameController()->getSceneController()->getScene();
    Link *link = scene->getLink();
    Inventory *inventory = link->getInventory();
    Status *status = link->getStatus();

    switch (textId)
    {
    case 97:
        tmp = 4 - inventory->nbQuartCoeur();
        os << tmp;
        return os.str();
    case 434:
        tmp = scene->getMonstersSolde();
        os << tmp;
        return os.str();
    case 539:
    case 540:
        tmp = status->getNbDeaths();
        os << tmp;
        return os.str();
    case 541:
        tmp = inventory->totalQuartCoeur();
        os << tmp;
        return os.str();
    case 542:
        tmp = 10; // graals + sword
        for (int i = 0; i < NB_EQPMT; i++)
            if (inventory->hasObject((Equipment)i))
                tmp++;                 // 24 -> 34
        tmp += link->getBouclier();    // 3 -> 37
        tmp += link->getTunique() - 1; // 2 -> 39
        if (status->getMaxMagic() == 64)
            tmp++; // 1 -> 40
        for (int i = 1; i < NB_COFFRES; i++)
            for (int j = 0; j < 3; j++)
                if (scene->getCoffre(i, j))
                    tmp++; // 42 -> 82
        os << tmp;
        return os.str();
    case 543:
        tmp = 0;
        for (int i = 0; i < NB_MONSTERS; i++)
        {
            if (scene->getMonsters(i))
                tmp++;
        }
        os << tmp;
        return os.str();
    case 544:
        tmp = MainController::getInstance()->getGameController()->getSave()->getCompletion();
        os << tmp;
        return os.str();
    }
    return "";
}

string TextHelper::getCommonValue(string tag)
{
    if (tag == "EPEE")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_EPEE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "CARTE")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_CARTE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "ACTION")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_ACTION);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "MONSTERS")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_MONSTERS);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "COURSE")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_COURSE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "INVENTAIRE")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_INVENTAIRE);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "OBJECT")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_OBJET);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "TELEPORT")
    {
        Text *tmp = KeyBinder::getInstance()->getTextForType(BT_TELEPORT);
        string result = tmp->getText();
        delete tmp;
        return result;
    }
    if (tag == "center")
    {
        return "[center]";
    }
    else if (tag == "/center")
    {
        return "[/center]";
    }
    else if (tag == "br")
    {
        return "[br]";
    }
    return "";
}
