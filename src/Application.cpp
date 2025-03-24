#include "Application.h"

Application::Application(){}

void Application::run(){
    InitWindow(1600, 900, "Data Structure Visualization");
    SetTargetFPS(60);
    srand(time(NULL));
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (menuState.currentSelection){
        case MenuSelection::NONE:
            this->menuState.update();
            this->menuState.draw();
            break;

        case MenuSelection::SLL:
            this->SLL.update();
            this->SLL.draw();
            if(SLL.isBackPressed()){
                menuState.currentSelection=MenuSelection::NONE;
            }
            break;

        case MenuSelection::LINEAR_HT:
            
            if(AVL.isBackPressed()){
                menuState.currentSelection=MenuSelection::NONE;
            }
            break;

        case MenuSelection::TREE_234:
            
            if(AVL.isBackPressed()){
                menuState.currentSelection=MenuSelection::NONE;
            }
            break;

        case MenuSelection::AVL_TREE:
            this->AVL.update();
            this->AVL.draw();
            if(AVL.isBackPressed()){
                menuState.currentSelection=MenuSelection::NONE;
            }
            break;

        case MenuSelection::MIN_SPANNING_TREE:

            if(AVL.isBackPressed()){
                menuState.currentSelection=MenuSelection::NONE;
            }
            break;

        case MenuSelection::SHORTEST_PATH:
            this->ST.update();
            this->ST.draw();
            if(ST.isBackPressed()){
                menuState.currentSelection=MenuSelection::NONE;
            }
            break;
        default:
            break;
        }
        EndDrawing();
    }
    CloseWindow();
}