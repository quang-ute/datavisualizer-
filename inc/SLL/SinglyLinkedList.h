#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <vector>
#include <sstream>

#include "SLL/SLLNode.h"

class SinglyLinkedList {
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        void createList(std::string text);
        // void insertNode(const int& index, int value);
        // void removeNode(const int& index);
        // void updateNode(const int& index, int value);
        // void searchNode(int value);
        void clearList();
        void resetHighlight();
        void clear();

        int getListSize();

        SinglyLinkedList* clone() const;
        
        void update();
        void draw();

    public:
        std::vector<SLLNode*> list;

        SLLArrow* head;
        SLLArrow* cur;

        SLLArrow* myNode;
        SLLNode* newNode;

        bool isNewNode=false;
        bool isCur=false;

        int indexStep=-1;
        int animationStep = 0;
    private:
        bool isCreated = false;        
};

#endif