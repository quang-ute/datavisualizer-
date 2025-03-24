#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GUI/Button.h"

enum class MenuSelection {
    NONE,
    SLL,
    LINEAR_HT,
    TREE_234,
    AVL_TREE,
    MIN_SPANNING_TREE,
    SHORTEST_PATH
};

class MenuState {
    public:
        MenuState();
        void draw();
        void update();
    public:
        MenuSelection currentSelection = MenuSelection::NONE;
    private:
        Texture2D background;
        const char* title;
        Button exit;
        Button SLL;
        Button LinearHT;
        Button Tree234;
        Button AVLTree;
        Button MinSpanningTree;
        Button ShortestPath;
};

#endif