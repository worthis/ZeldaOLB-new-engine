#include "Coffre.h"

#include "../../../engine/resources/ResourceManager.h"
#include "../../../engine/window/WindowManager.h"
#include "../../../engine/audio/AudioManager.h"

#include "../../MainController.h"

Coffre::Coffre(int i, int j, int t, bool op, TypeItem obj, int id) : type(t), opened(op), object(obj), objId(id), displayContent(0)
{
    x = i;
    y = j;

    image = ResourceManager::getInstance()->loadImage("data/images/objects/coffres.png", true);

    // for quadtree operations:
    if (type == 0)
    {
        width = 16;
        height = 16;
    }
    else
    {
        width = 32;
        height = 24;
    }

    box.setX(x);
    box.setY(y);
    box.setW(width);
    box.setH(height);
}

Coffre::~Coffre()
{
    ResourceManager::getInstance()->free(image);
}

void Coffre::draw(int offsetX, int offsetY)
{

    int srcX = (type == 0 && opened) ? 16 : 0;
    int srcY = type == 0 ? 0 : opened ? 40
                                      : 16;

    WindowManager::getInstance()->draw(image, srcX, srcY, width, height, x - offsetX, y - offsetY);

    if (displayContent)
    {
        ItemHelper::getInstance()->drawItem(object, x - offsetX + 8, y - offsetY);
        displayContent--;
    }
}

bool Coffre::action(Direction dir)
{
    if (dir == N && !opened)
    {
        AudioManager::getInstance()->playSound(TS_COFFRE);
        if (object != TI_NO_ITEM)
        {
            MainController::getInstance()->getGameController()->getSceneController()->getScene()->getLink()->trouveObjet(object, objId);
        }
        else
        {
            AudioManager::getInstance()->playSound(TS_ERROR);
        }
        opened = true;
        // for map 47 : open all chests
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->openChests(x, y);
        MainController::getInstance()->getGameController()->getSceneController()->getScene()->getMap()->testAnimRoom();
        return true;
    }
    return false;
}

bool Coffre::isOpened()
{
    return opened;
}

void Coffre::open(bool showContent)
{
    if (showContent && object != TI_NO_ITEM && !opened)
    {
        displayContent = 32;
    }
    opened = true;
}

void Coffre::close(TypeItem obj, int id)
{
    objId = id;
    opened = false;
    object = obj;
}

int Coffre::getDown() { return y - 240; }
