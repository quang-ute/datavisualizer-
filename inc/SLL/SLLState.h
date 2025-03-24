#ifndef SLLSTATE_H
#define SLLSTATE_H

#include <sstream>
#include <vector>
#include <random>

#include "SLL/SLLCode.h"
#include "SLL/SinglyLinkedList.h"
#include "SLL/SLLPanel.h"
#include "GUI/CodeBlock.h"
#include "GUI/inputBox.h"
#include "GUI/Button.h"

enum class SLLAnimationMode {
    IDLE, INSERT_FRONT, INSERT_MID, REMOVE_FRONT, REMOVE_MID, SEARCH, UPDATE
};

class SLLState{
    public:
        SLLState();
        void update();
        void draw();

        void saveInsertFrontState(int index, int value);
        void saveInsertMidState(int index, int value);
        void saveRemoveFrontState(int index);
        void saveRemoveMidState(int index);
        void saveSearchState(int value);
        void saveUpdateState(int index, int value);

        void animateInsertFront(int index, int value);
        void animateInsertMid(int index, int value);
        void animateRemoveFront(int index);
        void animateRemoveMid(int index);
        void animateSearch(int value);
        void animateUpdate(int index, int value);
        
        void resetCursorPosition();
        void resetBox();
        std::string getRandomInput();
        bool isBackPressed();

        void play();
        void pause();
        void resume();
        void nextStep();
        void prevStep();
        void restart();
        void moveEnd();
        void moveStart();
        void saveState();
        void applyState();
        void clearState();

    private:
        SinglyLinkedList SLL;
        SLLPanel panel;

        InputBox createBox;
        InputBox indexBox;
        InputBox valueBox;

        Button Random;
        Button LoadFile;
        Button Apply;
        Button Front;
        Button End;

        CodeBlock code;

        SLLAnimationMode animationState=SLLAnimationMode::IDLE;

        bool isPlaying = false;
        bool isPaused = false;
        int currentStep = 0;
        bool isStateSaved=false;

        struct AnimationStep{
            SinglyLinkedList* SLL;
            SLLAnimationMode animationState;
        };

        std::vector<AnimationStep*> stateList;

        std::string indexText;
        std::string valueText;
        std::string createText;
};

#endif