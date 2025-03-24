#include "SLL/SLLArrow.h"

SLLArrow::SLLArrow(Vector2 pos) : Arrow(pos), isNull(true), label(""){}

void SLLArrow::setLabel(const std::string &text){
    label=text;
}

void SLLArrow::setNull(){
    isNull=true;
}

bool SLLArrow::checkNull(){
    return isNull;
}

void SLLArrow::setTargetDestination(Vector2 targetDes){
    targetDestination=targetDes;
    isNull=false;
}

void SLLArrow::moveNode(Vector2 targetPos, Vector2 targetDes){
    targetPosition = targetPos;
    targetDestination = targetDes;
}

void SLLArrow::draw(){
    drawArrow(position, destination);
    if(isNull){
        DrawText("null", destination.x + 10, destination.y-8, 16, color);
    }
    if (!label.empty()){
        DrawText(label.c_str(),position.x-MeasureText(label.c_str(),16)-5,position.y-8,16,color);
    }
}