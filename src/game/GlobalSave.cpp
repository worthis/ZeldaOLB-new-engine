#include "GlobalSave.h"

GlobalSave GlobalSave::instance = GlobalSave();

GlobalSave *GlobalSave::getInstance()
{
    return &instance;
}
GlobalSave::GlobalSave()
{
    init();
    load();
}

GlobalSave::~GlobalSave()
{
}

void GlobalSave::init()
{
    fullROTH = false;
    ultimeROTH = false;
    rushROTH = false;
    fullOLB = false;
    ultimeOLB = false;
    rushOLB = false;
    bestTime = -1;
}

void GlobalSave::load()
{
    // ROTH
    ifstream fROTH("../Zelda Return of the Hylian/saves/records.dat", ios::in | ios::binary);
    if (fROTH.is_open())
    {
        fROTH.read((char *)&fullROTH, sizeof(bool));
        fROTH.read((char *)&ultimeROTH, sizeof(bool));
        fROTH.read((char *)&rushROTH, sizeof(bool));
        fROTH.close();
    }

    ifstream fOLB("saves/records.dat", ios::in | ios::binary);
    if (!fOLB.is_open())
    {
        return;
    }
    fOLB.read((char *)&fullOLB, sizeof(bool));
    fOLB.read((char *)&ultimeOLB, sizeof(bool));
    fOLB.read((char *)&rushOLB, sizeof(bool));
    fOLB.read((char *)&bestTime, sizeof(int));

    fOLB.close();
}

void GlobalSave::save()
{
    ofstream f("saves/records.dat", ios::out | ios::binary);
    f.write((char *)&fullOLB, sizeof(bool));
    f.write((char *)&ultimeOLB, sizeof(bool));
    f.write((char *)&rushOLB, sizeof(bool));
    f.write((char *)&bestTime, sizeof(int));
    f.close();
}

void GlobalSave::erase()
{
    remove("saves/records.dat");
    fullOLB = false;
    ultimeOLB = false;
    rushOLB = false;
    bestTime = -1;
}

void GlobalSave::update(Save *sv, bool endGame)
{
    bool needToSave = false;

    if (endGame)
    {
        if (!fullOLB && sv->getCompletion() == 100)
        {
            fullOLB = true;
            needToSave = true;
        }
        if (!ultimeOLB && !sv->getDeaths() && sv->getMaxLife() <= 30 && sv->getMaxMagic() <= 32 && !sv->getFlacons(0) && !sv->getFlacons(1) && !sv->getFlacons(2) && sv->getTunique() == 1 && !sv->getBouclier())
        {
            ultimeOLB = true;
            needToSave = true;
        }
        if (sv->getTime() < bestTime || bestTime == -1)
        {
            bestTime = sv->getTime();
            if (!rushOLB && bestTime < 14400)
            {
                rushOLB = true;
            }
            needToSave = true;
        }
    }

    if (needToSave)
    {
        save();
    }
}

bool GlobalSave::isFullROTH()
{
    return fullROTH;
}

bool GlobalSave::isUltimeROTH()
{
    return ultimeROTH;
}

bool GlobalSave::isRushROTH()
{
    return rushROTH;
}

bool GlobalSave::isFullOLB()
{
    return fullOLB;
}

bool GlobalSave::isUltimeOLB()
{
    return ultimeOLB;
}

bool GlobalSave::isRushOLB()
{
    return rushOLB;
}

int GlobalSave::getBestTime()
{
    return bestTime;
}
