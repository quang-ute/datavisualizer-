#include "GUI/Button.h"

Button::Button(){}

void Button::setTexture(const char* path){
    this->texture = LoadTexture(path);
}

void Button::setPosition(Vector2 position){
    this->position=position;
}

void Button::setSize(Vector2 size){
    this->size=size;
}

void Button::setText(const char* text, int fontSize){
    this->text = text;
    this->fontSize=fontSize;
}

void Button::setRectangle(){
    rectangle = {position.x - size.x/2,position.y-(size.y/2-fontSize/2),size.x,size.y};
}

void Button::setColor(Color normal, Color hovered, Color pressed){
    this->normal=normal;
    this->hovered=hovered;
    this->pressed=pressed;
}

void Button::update(){
    if(this->isSelected){
        color=pressed;
    }
    else if(this->isHovered()){
        if(this->isPressed()){
            color=pressed;
        }else{
            color=hovered;
        }
    }
    else{
        color=normal;
    }
}

void Button::drawRectangle(Vector2 recSize){
    DrawRectangle(this->position.x, this->position.y, recSize.x, recSize.y, this->color);
}

void Button::drawRectangleRounded(int roundness){
    DrawRectangleRounded(this->rectangle, roundness, 100, this->color);
}

void Button::drawRectangleRoundedLinesEx(int roundness, int segments, int lineThick, Color color){
    DrawRectangleRoundedLinesEx(this->rectangle, roundness, segments, lineThick,color);
}

void Button::drawTexture(Vector2 position){
    DrawTexture(this->texture, position.x, position.y, WHITE);
}

void Button::drawText(Color color){
    DrawText(this->text, position.x - MeasureText(text, fontSize)/2 ,position.y, this->fontSize, color);
}

Vector2 Button::getSize(){
    return this->size;
}

Vector2 Button::getPosition(){
    return this->position;
}

int Button::getfontSize(){
    return this->fontSize;
}

bool Button::isPressed(){
    return isActive&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
}

bool Button::isHovered(){
    return isActive&&CheckCollisionPointRec(GetMousePosition(), {this->position.x-this->size.x/2, this->position.y-(this->size.y/2-this->fontSize/2), this->size.x, this->size.y});
}

void Button::Selected(){
    this->isSelected = true;
}

void Button::deSelected(){
    this->isSelected = false;
}

void Button::setActive(){
    isActive=true;
}

void Button::deActive(){
    isActive=false;
}