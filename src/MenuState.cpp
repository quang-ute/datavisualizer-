#include "MenuState.h"

MenuState::MenuState(){
    this->background = LoadTexture("button.png");
    this->title = "Data Structure Visualization";

    this->exit.setText("Exit",menuButtonFontSize);
    this->exit.setSize({70,50});
    this->exit.setPosition({1500,800});
    this->exit.setColor(menuNormal,menuHovered,menuPressed);
    this->exit.setRectangle();

    this->SLL.setText("Singly Linked List",menuButtonFontSize);
    this->SLL.setSize(menuButtonSize);
    this->SLL.setPosition({400,550});
    this->SLL.setColor(menuNormal,menuHovered,menuPressed);
    this->SLL.setRectangle();
    
    this->LinearHT.setText("Linear Hashing Table",menuButtonFontSize);
    this->LinearHT.setSize(menuButtonSize);
    this->LinearHT.setPosition({800 ,550});
    this->LinearHT.setColor(menuNormal,menuHovered,menuPressed);
    this->LinearHT.setRectangle();

    this->Tree234.setText("2-3-4 Tree",menuButtonFontSize);
    this->Tree234.setSize(menuButtonSize);
    this->Tree234.setPosition({1200 ,550});
    this->Tree234.setColor(menuNormal,menuHovered,menuPressed);
    this->Tree234.setRectangle();

    this->AVLTree.setText("AVL Tree",menuButtonFontSize);
    this->AVLTree.setSize(menuButtonSize);
    this->AVLTree.setPosition({400 ,700});
    this->AVLTree.setColor(menuNormal,menuHovered,menuPressed);
    this->AVLTree.setRectangle();

    this->MinSpanningTree.setText("Minimum Spanning Tree",menuButtonFontSize);
    this->MinSpanningTree.setSize(menuButtonSize);
    this->MinSpanningTree.setPosition({800, 700});
    this->MinSpanningTree.setColor(menuNormal,menuHovered,menuPressed);
    this->MinSpanningTree.setRectangle();

    this->ShortestPath.setText("Shortest Path",menuButtonFontSize);
    this->ShortestPath.setSize(menuButtonSize);
    this->ShortestPath.setPosition({1200 ,700});
    this->ShortestPath.setColor(menuNormal,menuHovered,menuPressed);
    this->ShortestPath.setRectangle();
}

void MenuState::draw(){
    DrawTexture(this->background, 0, 0, WHITE);
    DrawText(this->title, GetScreenWidth()/2.0f - MeasureText(this->title, appTitleFontSize)/2.0f, 350, 40, appTitleColor);

    this->exit.drawRectangleRounded(70);
    this->SLL.drawRectangleRounded(70);
    this->LinearHT.drawRectangleRounded(70);
    this->Tree234.drawRectangleRounded(70);
    this->AVLTree.drawRectangleRounded(70);
    this->MinSpanningTree.drawRectangleRounded(70);
    this->ShortestPath.drawRectangleRounded(70);

    this->exit.drawText(menuButtonTextColor);
    this->SLL.drawText(menuButtonTextColor);
    this->LinearHT.drawText(menuButtonTextColor);
    this->Tree234.drawText(menuButtonTextColor);
    this->AVLTree.drawText(menuButtonTextColor);
    this->MinSpanningTree.drawText(menuButtonTextColor);
    this->ShortestPath.drawText(menuButtonTextColor);
}

void MenuState::update(){
    if(this->exit.isPressed()){
        CloseWindow();
    }
    if(this->SLL.isPressed()){
        currentSelection=MenuSelection::SLL;
    }
    else if(this->LinearHT.isPressed()){
        currentSelection=MenuSelection::LINEAR_HT;
    }
    else if(this->Tree234.isPressed()){
        currentSelection=MenuSelection::TREE_234;
    }
    else if(this->AVLTree.isPressed()){
        currentSelection=MenuSelection::AVL_TREE;
    }
    else if(this->MinSpanningTree.isPressed()){
        currentSelection=MenuSelection::MIN_SPANNING_TREE;
    }
    else if(this->ShortestPath.isPressed()){
        currentSelection=MenuSelection::SHORTEST_PATH;
    }
    this->exit.update();
    this->SLL.update();
    this->LinearHT.update();
    this->Tree234.update();
    this->AVLTree.update();
    this->MinSpanningTree.update();
    this->ShortestPath.update();
}