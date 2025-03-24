#ifndef SHORTESTPATHSTATE_H
#define SHORTESTPATHSTATE_H

#include <random>

#include "ShortestPath/ShortestPath.h"
#include "ShortestPath/STPanel.h"
#include "GUI/CodeBlock.h"

class ShortestPathState{
    public:
        ShortestPathState();
        void update();
        void draw();

        void resetBox();
        bool isBackPressed();

    private:
        ShortestPath ST;
        CodeBlock STCode;
        STPanel panel;

        InputBox NodesBox;
        InputBox EdgesBox;
        InputBox StartNodesBox;

        Button Random;
        Button LoadFile;
        Button Apply;
        
        Button Weighted;
        Button Directed;
        Button Unweighted;
        Button Undirected;
};

#endif