/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2016  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TRANSITIONROOMSCONTROLLER_H__
#define __TRANSITIONROOMSCONTROLLER_H__

#include "../../../engine/common/Common.h"

#include "TransitionRooms.h"

class TransitionRoomsController {
    public :
        TransitionRoomsController();
        ~TransitionRoomsController();

        void launch();

        void loop();

    private :

        TransitionRooms transitionRooms;
};

#endif  // TransitionRoomsController.h
