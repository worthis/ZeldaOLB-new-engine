#include "JoystickBinder.h"

#include "../../engine/texts/TextManager.h"

#include "../MainController.h"

JoystickBinder JoystickBinder::instance = JoystickBinder();

JoystickBinder::JoystickBinder() : rush(false), haveToSave(false)
{
    restoreDefault();
}

JoystickBinder::~JoystickBinder()
{
}

JoystickBinder *JoystickBinder::getInstance()
{
    return &instance;
}

void JoystickBinder::restoreDefault()
{
    // default values
    for (int i = 0; i < BT_UP; i++)
    {
        map[i] = getDefaultKey((BindableType)i);
    }
}

Keys JoystickBinder::getDefaultKey(BindableType type)
{
    switch (type)
    {
    case BT_OPTIONS:
        return jStart;
    case BT_CARTE:
        return jRB;
    case BT_MONSTERS:
        return jLB;
    case BT_INVENTAIRE:
        return jY;
    case BT_ACTION:
        return jB;
    case BT_EPEE:
        return jA;
    case BT_OBJET:
        return jX;
    case BT_COURSE:
        return jSelect;
    case BT_TELEPORT:
        return jRS;
    default:
        return jStart;
    }
}

void JoystickBinder::init(string filename)
{
    file = filename;
    rush = false;
    haveToSave = false;

    ifstream f(file.c_str(), ios::in | ios::binary);
    if (f.is_open())
    {
        f.read((char *)&map[BT_OPTIONS], sizeof(int));
        f.read((char *)&map[BT_CARTE], sizeof(int));
        f.read((char *)&map[BT_MONSTERS], sizeof(int));
        f.read((char *)&map[BT_INVENTAIRE], sizeof(int));
        f.read((char *)&map[BT_ACTION], sizeof(int));
        f.read((char *)&map[BT_EPEE], sizeof(int));
        f.read((char *)&map[BT_OBJET], sizeof(int));
        f.read((char *)&map[BT_COURSE], sizeof(int));
        f.read((char *)&map[BT_TELEPORT], sizeof(int));
        f.close();
    }
}

void JoystickBinder::save()
{
    if (!haveToSave)
    {
        return;
    }
    ofstream f(file.c_str(), ios::out | ios::binary);
    f.write((char *)&map[BT_OPTIONS], sizeof(int));
    f.write((char *)&map[BT_CARTE], sizeof(int));
    f.write((char *)&map[BT_MONSTERS], sizeof(int));
    f.write((char *)&map[BT_INVENTAIRE], sizeof(int));
    f.write((char *)&map[BT_ACTION], sizeof(int));
    f.write((char *)&map[BT_EPEE], sizeof(int));
    f.write((char *)&map[BT_OBJET], sizeof(int));
    f.write((char *)&map[BT_COURSE], sizeof(int));
    f.write((char *)&map[BT_TELEPORT], sizeof(int));
    f.close();
    haveToSave = false;
}

void JoystickBinder::addMenuEventsForJoystick(Event *event)
{
    // return
    if (event->isPushed(jStart) || event->isPushed(jA) || event->isPushed(jB))
    {
        event->setEvent(kReturn, true);
    }

    // arrows
    if (event->isDown(jLUp) || event->isDown(jUp))
    {
        event->setEvent(kUp, true);
    }
    if (event->isDown(jLDown) || event->isDown(jDown))
    {
        event->setEvent(kDown, true);
    }
    if (event->isDown(jLLeft) || event->isDown(jLeft))
    {
        event->setEvent(kLeft, true);
    }
    if (event->isDown(jLRight) || event->isDown(jRight))
    {
        event->setEvent(kRight, true);
    }
}

void JoystickBinder::addGameEventsForJoystick(Event *event)
{
    KeyBinder *kb = KeyBinder::getInstance();

    // rush
    if (event->isPushed(map[BT_COURSE]))
    {
        rush = !rush;
    }
    if (rush)
    {
        event->setEvent(kb->getKey(BT_COURSE), true);
    }

    // arrows
    if (event->isDown(jLUp) || event->isDown(jUp))
    {
        event->setEvent(kb->getKey(BT_UP), true);
    }
    if (event->isDown(jLDown) || event->isDown(jDown))
    {
        event->setEvent(kb->getKey(BT_DOWN), true);
    }
    if (event->isDown(jLLeft) || event->isDown(jLeft))
    {
        event->setEvent(kb->getKey(BT_LEFT), true);
    }
    if (event->isDown(jLRight) || event->isDown(jRight))
    {
        event->setEvent(kb->getKey(BT_RIGHT), true);
    }

    // camera
    if (event->isDown(jRUp))
    {
        event->setEvent(kb->getKey(BT_CAMERA), true);
        event->setEvent(kb->getKey(BT_UP), true);
    }
    if (event->isDown(jRDown))
    {
        event->setEvent(kb->getKey(BT_CAMERA), true);
        event->setEvent(kb->getKey(BT_DOWN), true);
    }
    if (event->isDown(jRLeft))
    {
        event->setEvent(kb->getKey(BT_CAMERA), true);
        event->setEvent(kb->getKey(BT_LEFT), true);
    }
    if (event->isDown(jRRight))
    {
        event->setEvent(kb->getKey(BT_CAMERA), true);
        event->setEvent(kb->getKey(BT_RIGHT), true);
    }

    // buttons
    if (event->isDown(map[BT_OPTIONS]))
    {
        event->setEvent(kb->getKey(BT_OPTIONS), true);
    }
    if (event->isDown(map[BT_INVENTAIRE]))
    {
        event->setEvent(kb->getKey(BT_INVENTAIRE), true);
    }
    if (event->isDown(map[BT_CARTE]))
    {
        event->setEvent(kb->getKey(BT_CARTE), true);
    }
    if (event->isDown(map[BT_MONSTERS]))
    {
        event->setEvent(kb->getKey(BT_MONSTERS), true);
    }
    if (event->isDown(map[BT_ACTION]))
    {
        event->setEvent(kb->getKey(BT_ACTION), true);
    }
    if (event->isDown(map[BT_EPEE]))
    {
        event->setEvent(kb->getKey(BT_EPEE), true);
    }
    if (event->isDown(map[BT_OBJET]))
    {
        event->setEvent(kb->getKey(BT_OBJET), true);
    }
    if (event->isDown(map[BT_TELEPORT]))
    {
        event->setEvent(kb->getKey(BT_TELEPORT), true);
    }
}

bool JoystickBinder::isJoystickInUsage(Event *event)
{
    return event->isPushed(map[BT_COURSE]) ||
           event->isDown(jLUp) ||
           event->isDown(jLDown) ||
           event->isDown(jLLeft) ||
           event->isDown(jLRight) ||
           event->isDown(jRUp) ||
           event->isDown(jRDown) ||
           event->isDown(jRLeft) ||
           event->isDown(jRRight) ||
           event->isDown(jUp) ||
           event->isDown(jDown) ||
           event->isDown(jLeft) ||
           event->isDown(jRight) ||
           event->isDown(map[BT_OPTIONS]) ||
           event->isDown(map[BT_INVENTAIRE]) ||
           event->isDown(map[BT_CARTE]) ||
           event->isDown(map[BT_MONSTERS]) ||
           event->isDown(map[BT_ACTION]) ||
           event->isDown(map[BT_EPEE]) ||
           event->isDown(map[BT_OBJET]) ||
           event->isDown(map[BT_TELEPORT]);
}

Keys JoystickBinder::getKey(BindableType type)
{
    return map[type];
}

void JoystickBinder::setKey(BindableType type, Keys key)
{
    if (map[type] != key)
    {
        haveToSave = true;
        map[type] = key;
    }
}

Text *JoystickBinder::getTextForType(BindableType type, int color)
{
    return getTextForKey(map[type], color);
}

Text *JoystickBinder::getTextForKey(Keys key, int color)
{
    ostringstream os;
    if (color > 0)
    {
        os << "[c=" << color << "]";
    }
    switch (key)
    {
    case jA:
        os << "A";
        break;
    case jB:
        os << "B";
        break;
    case jX:
        os << "X";
        break;
    case jY:
        os << "Y";
        break;
    case jLB:
        os << "LB";
        break;
    case jLT:
        os << "LT";
        break;
    case jRB:
        os << "RB";
        break;
    case jRT:
        os << "RT";
        break;
    case jLS:
        os << "LS";
        break;
    case jRS:
        os << "RS";
        break;
    case jSelect:
        os << "Select";
        break;
    case jStart:
        os << "Start";
        break;
    default:
        os << "?";
        break;
    }
    return new Text(os.str());
}

void JoystickBinder::forceToSave()
{
    haveToSave = true;
}
