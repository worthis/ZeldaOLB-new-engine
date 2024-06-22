/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WRESOURCE_H__
#define __WRESOURCE_H__

#include "../common/Common.h"

class WResource
{
public:
    WResource();
    virtual ~WResource() = 0;
    string getName();
    void load();
    int unload();

private:
    int count;

protected:
    string name;
};

#endif // WResource.h
