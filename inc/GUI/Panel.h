#ifndef PANEL_H
#define PANEL_H

#include "GUI/Button.h"
#include "GUI/inputBox.h"

class Panel{
    public:
        Panel();
        virtual void draw()=0;
        virtual void update()=0;
        bool isBackPressed();
        virtual bool isAnyButtonPressed()=0;
        bool isPlayPressed();
        bool isNextPressed();
        bool isPrevPressed();
        bool isEndPressed();
        bool isStartPressed();
        void updateController();
        void drawController();
    protected:
        Rectangle dataTitle;
        Button Back;

        Rectangle Controller;
        Button Play;
        Button Next;
        Button Prev;
        Button End;
        Button Start;

        Rectangle panelHolder;
};

#endif