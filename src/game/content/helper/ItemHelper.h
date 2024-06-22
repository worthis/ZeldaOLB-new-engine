/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ITEMHELPER_H__
#define __ITEMHELPER_H__

#include "../types/Item.h"

class ItemHelper
{
public:
    static ItemHelper *getInstance();

    Item *createItem(TypeItem type, int x, int y, int id = -1, bool withAnim = true);

    void drawItem(TypeItem type, int x, int y);

    void close();

private:
    ItemHelper();
    ~ItemHelper();
    static ItemHelper instance;

    WImage *image;
};

#endif // ItemHelper.h
