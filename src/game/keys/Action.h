/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ACTION_H__
#define __ACTION_H__

enum ActionType {UP, DOWN, LEFT, RIGHT, PUSH_UP, PUSH_DOWN, PUSH_LEFT, PUSH_RIGHT, CAMERA,
                RUN, HIT, LOAD, OBJECT, ACTION, INVENTAIRE, MONSTERS, DISPLAY_MAP, TELEPORT,
                MAP_1, MAP_2, MAP_3, MAP_4, MAP_5, MAP_6, MAP_7, MAP_8, MAP_9,
                QUIT_GAME, AIDE, NB_ACTIONS};


class Action {
    public :
        Action();
        ~Action();

        void setAction(ActionType key, bool b);
        bool isAction(ActionType key);

        void reset();

    private :
        bool actions[NB_ACTIONS];
};

#endif  // Action.h

