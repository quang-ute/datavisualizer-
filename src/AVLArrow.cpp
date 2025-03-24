#include "AVL/AVLArrow.h"

AVLArrow::AVLArrow(Vector2 pos): Arrow(pos){}

void AVLArrow::update(){
    if (destination.x == targetDestination.x&&destination.y == targetDestination.y) return;
    float deltaTime=GetFrameTime();
    float disX=targetDestination.x-destination.x, disY=targetDestination.y-destination.y;
    float dis=sqrt(disX*disX+disY*disY);
    float deltaX=disX/dis*speed*deltaTime;
    float deltaY=disY/dis*speed*deltaTime;
    if(fabs(deltaX)>=fabs(disX)&&fabs(deltaY)>=fabs(disY)){
        destination=targetDestination;
    }
    else{
        destination.x+=deltaX;
        destination.y+=deltaY;
    }
}

void AVLArrow::draw(){
    DrawLineEx(this->position,this->destination,2,color);
}