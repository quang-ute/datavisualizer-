#ifndef RESOURCES_H
#define RESOURCES_H

#include "raylib.h"

const int speed = 200;

//Menu
const int appTitleFontSize(40);
const Color appTitleColor({BLACK});
const Color menuPressed({26,67,128,255});
const Color menuHovered({38,98,186,255});
const Color menuNormal({50,130,246,255});
const Vector2 menuButtonSize({300,50});
const int menuButtonFontSize(20);
const Color menuButtonTextColor({BLACK});

//Panel
const Color dataTitleColor({185,185,185,255});
const Color dataTitleTextColor({BLACK});
const int dataTitleFontSize = 24;
const Vector2 dataTitleSize({400,50});
const Vector2 dataTitlePosition({800,15+dataTitleSize.y/2.0f});

const Vector2 panelButtonSize({80, 40});//Create, Add, Remove ...
const int panelButtonFontSize(15);
const Color panelButtonTextColor({BLACK});
const Color panelNormal({161,161,161,255});
const Color panelHovered({133,133,133,255});
const Color panelPressed({110,110,110,255});

const Color panelSubButtonTextColor({BLACK});

const Color highlightColor({255,253,85,255});

const Vector2 backSize({50,50});

//InputBox
const int inputBoxFontSize(20);
const int inputBoxNameFontSize(20);

//SLL
const Vector2 SLLNodeSize({80,60});
const Vector2 SLLposition({150,250});
const int SLLNodeFontSize(24);

const Vector2 SLLBoxSize({260,40});
const int SLLBoxFontSize(20);
const Color SLLBoxColor({LIGHTGRAY});
const Color SLLBoxTextColor({BLACK});
const int SLLButtonFontSize(15);

//AVL
const Vector2 AVLNodeSize({40,40});
const int AVLLeafSpace = 5;
const int AVLNodeFontSize(24);
const Color AVLNodeTextColor({BLACK});
const int AVLLevelSpace = 60;

const Vector2 AVLBoxSize({260,40});
const int AVLBoxFontSize(20);
const Color AVLBoxColor({LIGHTGRAY});
const Color AVLBoxTextColor({BLACK});
const int AVLButtonFontSize(15);

//Shortest Path
const float centerX=800, centerY=325;
const float rangeX=1200,rangeY=430;

const Vector2 STNodeSize({40,40});
const int STNodeCostFontSize(24);
const int STNodeIDFontSize(12);
const Color STNodeCostColor({BLACK});
const Color STNodeIDColor({BLACK});

const Vector2 STBoxSize({260,40});
const int STBoxFontSize(20);
const Color STBoxColor({LIGHTGRAY});
const Color STBoxTextColor({BLACK});
const int STButtonFontSize(15);

//Arrow
const int ArrowLength = 50;

//Controller
const Vector2 controllerButtonSize({50,50});
const Vector2 controllerPosition({800,860});
const Vector2 controllerSize({400,2*(900-controllerPosition.y)});

#endif