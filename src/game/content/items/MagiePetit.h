/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MAGIEPETIT_H__
#define __MAGIEPETIT_H__

#include "../types/Item.h"

class MagiePetit : public Item {
    public :
        MagiePetit(int x, int y);
        ~MagiePetit();

        void loop();
        void draw(int offsetX, int offsetY);

        void action();

};

#endif  // MagiePetit.h
