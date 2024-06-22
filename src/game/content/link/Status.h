/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __STATUS_H__
#define __STATUS_H__

#include "../../../engine/common/Common.h"

#include "../../../engine/util/time/Chrono.h"

#include "../../Save.h"

class Status {
    public :
        Status(Save* save);
        ~Status();

        void saveData(Save* save);

        void loop();

        int getLife();
        int getMaxLife();
        int getMagic();
        int getMaxMagic();
        int getRupees();
        int getMaxRupees();
        int getArrows();
        int getMaxArrows();
        int getBombs();
        int getMaxBombs();
        bool isOniLinkable();
        bool isOniLink();
        int getValueOni();
        int getMaxOni();

        void setLife(int i);
        void setMaxLife(int i);
        void setMagic(int i);
        void setMaxMagic(int i);
        void setRupees(int i);
        void setMaxRupees(int i);
        void setArrows(int i);
        void setMaxArrows(int i);
        void setBombs(int i);
        void setMaxBombs(int i);
        void setOniLinkable(bool b);
        void setOniLink(bool b);
        void setValueOni(int i);
        void setMaxOni(int i);

        void updateLife(int i);
        void updateRupees(int i);
        void updateMagic(int i);

        int getVirtualLife();
        int getVirtualRupees();
        int getVirtualMagic();

        void setInvincible();
        bool isInvincible();

        void increaseDeaths();
        int getNbDeaths();

        int getMaxWeight();

        void updateGel(int value);
        void resetGel();
        int getGel();
        int getMaxGel();

    private :

        void loadFromSave(Save* save);

        Chrono chrono;

        int life;
        int maxLife;
        int magic;
        int maxMagic;
        int rupees;
        int maxRupees;
        int arrows;
        int maxArrows;
        int bombs;
        int maxBombs;
        bool oniLinkable;  //risque de transformation
        bool oniLink;      //transformé
        int valueOni; //jauge transformation
        int maxOni;   //capacité jauge

        int lifeToAdd;
        int magicToAdd;
        int rupeesToAdd;

        int invincible;

        int deaths;

        int gel;
        int maxGel;
};

#endif  // Status.h
