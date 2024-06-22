/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TEXTMANAGER_H__
#define __TEXTMANAGER_H__

#include "../common/Common.h"

#include "TextConfiguration.h"
#include "Text.h"

#include <vector>

class TextManager {
    public :
        static TextManager* getInstance();

        void setConfiguration(TextConfiguration* conf);

        int getWSpace();
        int getWSize();
        int getHSize();

        Text* getText(int id);
        WImage* getImage();

        void drawLetter(char c, int i, int j, int style = 0);

        void displayNumber(int n, int digits, int x, int y);

        void reloadTexts();

    private :
        TextManager();
        ~TextManager();
        static TextManager instance;

        void loadTextsFromFile(string filename);

        void drawLetterInternal(char c, int i, int j, int style);

        void displayNumberInternal(int d, int x, int y);

        TextConfiguration* config;
        vector<string> texts;
};

#endif  // TextManager.h
