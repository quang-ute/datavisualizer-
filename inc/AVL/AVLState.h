#ifndef AVLSTATE_H
#define AVLSTATE_H

#include <random>

#include "AVL/AVLCode.h"
#include "AVL/AVL.h"
#include "AVL/AVLPanel.h"
#include "GUI/CodeBlock.h"

enum class AVLAnimationMode{
    IDLE, INSERTING, REMOVING, SEARCHING
};

class AVLState {   
    public: 
        AVLState();
        void update();
        void draw();

        void animateInsert(int value);
        void animateRemove(int value);
        void animateSearch(int value);

        void resetBox();
        std::string getRandomInput();
        bool isBackPressed();
        
    private:
        AVL AVL;
        CodeBlock AVLCode;
        AVLPanel panel;
        
        InputBox createBox;
        InputBox valueBox;

        Button Random;
        Button LoadFile;
        Button Apply;

        AVLAnimationMode animationState=AVLAnimationMode::IDLE;
};

#endif