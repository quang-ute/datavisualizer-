#ifndef AVLNODE_H
#define AVLNODE_H

#include <algorithm>

#include "GUI/Resources.h"
#include "AVL/AVLArrow.h"

class AVLNode{
    public:
        AVLNode();
        ~AVLNode();

        void setValue(int value);
        void setPosition(Vector2 position);
        void setTargetPosition(Vector2 targetPos);
        void setHeight(int value);
        void setDepth(int value);
        void setHighlight();
        void deHighlight();

        Vector2 getOrigin();
        int getValue();
        int getHeight();
        int getDepth();
        bool isLeaf();

        void updateHeight();

        void updateNode();
        void updateCur();
        void drawCur();

        void setDestinationLeft(Vector2 targetDes);
        void setDestinationRight(Vector2 targetDes);
        void setTargetDestinationLeft(Vector2 targetDes);
        void setTargetDestinationRight(Vector2 targetDes);
    public:
        AVLNode* left;
        AVLNode* right;
        AVLNode* parent;
    private:
        Rectangle node;

        Color nodeColor=LIGHTGRAY;
        Color textColor=BLACK;
        Color highlight = GREEN;
        Color textHighlight = WHITE;

        AVLArrow* leftPointer;
        AVLArrow* rightPointer;

        Vector2 position;
        Vector2 targetPosition; 
        int value;
        int height=0;
        int depth=0;

        bool isHighlight=false;
};

#endif