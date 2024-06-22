/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ITEMRANDOMIZER_H__
#define __ITEMRANDOMIZER_H__

#include "ItemHelper.h"
#include <vector>

struct p_node
{
    TypeItem type;
    int proba;
};

class ItemRandomizer
{
public:
    ItemRandomizer();
    ~ItemRandomizer();

    void addType(TypeItem type, int proba);

    TypeItem selectType();

private:
    TypeItem checkWithLink(TypeItem type);

    vector<p_node> nodes;
};

#endif // ItemRandomizer.h
