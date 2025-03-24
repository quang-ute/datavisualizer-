#include "ShortestPath/STArrow.h"

STArrow::STArrow(Vector2 pos,int to) : Arrow(pos){
    this->to=to;
    this->weight=0;
}

void STArrow::setTargetDestination(Vector2 targetDes){
    float disX=targetDes.x-position.x, disY=targetDes.y-position.y;
    float dis=sqrt(disX*disX+disY*disY);
    this->targetDestination={targetDes.x-STNodeSize.x/(2.0f*dis)*disX,targetDes.y-STNodeSize.y/(2.0f*dis)*disY};
}

void STArrow::update(){
    destination.x += ((targetDestination.x-destination.x));
    destination.y += ((targetDestination.y-destination.y));
}

void STArrow::draw(bool isWeighted, bool isDirected){
    if(isWeighted)
        DrawText(std::to_string(this->weight).c_str(),(this->position.x+this->destination.x)/2,(this->position.y+this->destination.y)/2,10,color);
    if(isDirected){
        drawArrow(this->position,this->destination);
    }
    else{
        DrawLineEx(this->position,this->destination,2,color);
    }
}

void STArrow::setWeight(int weight){
    this->weight=weight;
}

int STArrow::getWeight(){
    return this->weight;
}

void STArrow::setTo(int to){
    this->to=to;
}

int STArrow::getTo(){
    return this->to;
}

void STArrow::setFrom(int from){
    this->from=from;
}

int STArrow::getFrom(){
    return this->from;
}