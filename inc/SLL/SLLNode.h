#ifndef SLLNODE_H
#define SLLNODE_H

#include "SLL/SLLArrow.h"
#include "GUI/Resources.h"

class SLLNode{
    public:
        SLLNode();
        ~SLLNode();

        void setNull();
        void setValue(int value);
        void setPosition(Vector2 position);
        void setTargetDestination(Vector2 targetDes);
        void setTargetPosition(Vector2 targetPos);
        void setDestination(Vector2 destination);
        void setHighlight();
        void deHighlight();

        Vector2 getStartPos();
        Vector2 getEndPos();
        Vector2 getPosition();
        int getValue();
        Vector2 getDestination();
        
        void updateNode();
        void updateCur();
        void drawCur();

        SLLNode* clone() const;
        
    private:
        Rectangle node;
        int value;
        SLLArrow* Pointer;

        Color nodeColor=LIGHTGRAY;
        Color textColor=BLACK;
        Color highlight = GREEN;
        Color textHighlight = WHITE;
        bool isHighlight=false;

        Vector2 position;
        Vector2 targetPosition;
};

#endif