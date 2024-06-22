/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TEXT_H__
#define __TEXT_H__

#include "../common/Common.h"

class Text {
    public :
        Text(string txt);
        ~Text();

        void display(int x, int y, int l = -1);     // display on a line
        void displayBox(int x, int y, int l = -1);  // display on a box

        void setBox(int w, int h);
        bool hasNext();
        void next();

        int getWBox();
        int getHBox();
        int getLength();
        int getLengthInBox();
        string getText();
        char charAtInBox(int i);

        int getSize();

    private :
        void computeLength();
        void cutBox(); // cut text to inBox and outBox
        int wordSize(string txt, unsigned int i); // return size of a word from i
        int sizeToCenter(string txt, unsigned int i); // return size of words to center from i

        void displayInternal(int x, int y, int l);     // display on a line

        int wBox;
        int hBox;
        int length;
        int lengthInBox;
        string text;
        string inBox;
        string outBox;

};

#endif  // Text.h
