/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __WFILE_H__
#define __WFILE_H__

#include "../common/Common.h"
#include "WResource.h"

class WFile : public WResource
{
public:
    WFile(string filename);
    ~WFile();
    char *getBuffer();
    long getSize();

private:
    char *buffer;
    long size;
};

#endif // WFile.h
