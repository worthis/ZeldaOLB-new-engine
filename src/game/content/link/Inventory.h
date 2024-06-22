/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "../../../engine/common/Common.h"
#include "../../../engine/resources/WImage.h"

#include "../../Save.h"

class Inventory {
    public :
        Inventory(Save* save);
        ~Inventory();

        void saveData(Save* save);

        void draw(Equipment e, int x, int y);

        void setObject(Equipment e, int value = 1);

        bool hasObject(Equipment e);

        bool hasObject();

        Equipment getCurrent();

        void setCurrent(Equipment e);

        bool hasQuartCoeur(int i);

        void setQuartCoeur(int i, int value = 1);

        int nbQuartCoeur();

        int totalQuartCoeur();

        bool hasCoeur(int i);

        void setCoeur(int i, int value = 1);

        void setGraal(int i, int value = 1);

        bool hasGraal(int i);

        int nbGraals();

        int getFlacon(int i);

        void setFlacon(int i, int value);

        int getCurrentFlacon();

        void setCurrentFlacon(int value);

    private :

        void loadFromSave(Save* save);

        void drawFlacon(int x, int y, int value);

        int equipment[NB_EQPMT];

        Equipment current;

        WImage* inventaire;

        int quartCoeur[NB_QUART_COEUR];

        int coeur[NB_COEUR];

        int graals[NB_GRAALS];

        int flacons[NB_FLACON];
};

#endif  // Inventory.h
