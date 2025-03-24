#include "GUI/Panel.h"

Panel::Panel(){
    this->dataTitle = {dataTitlePosition.x-dataTitleSize.x/2.0f,dataTitlePosition.y-dataTitleSize.y/2.0f,dataTitleSize.x,dataTitleSize.y};
    this->Controller = {controllerPosition.x-controllerSize.x/2.0f,controllerPosition.y-controllerSize.y/2.0f,controllerSize.x,controllerSize.y};

    this->Back.setSize(backSize);
    this->Back.setPosition({dataTitle.y+dataTitle.height/2.0f,dataTitle.y+dataTitle.height/2.0f});
    this->Back.setColor(panelNormal,panelHovered,panelPressed);
    this->Back.setRectangle();

    this->Play.setSize(controllerButtonSize);
    this->Play.setPosition(controllerPosition);
    this->Play.setColor(panelNormal,panelHovered,panelPressed);
    this->Play.setRectangle();

    this->Next.setSize(controllerButtonSize);
    this->Next.setPosition({controllerPosition.x+(controllerButtonSize.x+15),controllerPosition.y});
    this->Next.setColor(panelNormal,panelHovered,panelPressed);
    this->Next.setRectangle();

    this->Prev.setSize(controllerButtonSize);
    this->Prev.setPosition({controllerPosition.x-(controllerButtonSize.x+15),controllerPosition.y});
    this->Prev.setColor(panelNormal,panelHovered,panelPressed);
    this->Prev.setRectangle();

    this->End.setSize(controllerButtonSize);
    this->End.setPosition({controllerPosition.x+2*(controllerButtonSize.x+15),controllerPosition.y});
    this->End.setColor(panelNormal,panelHovered,panelPressed);
    this->End.setRectangle();

    this->Start.setSize(controllerButtonSize);
    this->Start.setPosition({controllerPosition.x-2*(controllerButtonSize.x+15),controllerPosition.y});
    this->Start.setColor(panelNormal,panelHovered,panelPressed);
    this->Start.setRectangle();

    this->panelHolder = {0,650-(panelButtonSize.y/2.0f-panelButtonFontSize/2.0f),400,350};
}

bool Panel::isBackPressed(){ 
    return Back.isPressed();
}

bool Panel::isPlayPressed(){
    return Play.isPressed();
}

bool Panel::isNextPressed(){
    return Next.isPressed();
}

bool Panel::isPrevPressed(){
    return Prev.isPressed();
}

bool Panel::isEndPressed(){
    return End.isPressed();
}

bool Panel::isStartPressed(){
    return Start.isPressed();
}

void Panel::updateController(){
    Play.update();
    Next.update();
    Prev.update();
    End.update();
    Start.update();
}

void Panel::drawController(){
    DrawRectangleRounded(Controller,0,100,dataTitleColor);
    DrawRectangleRounded(dataTitle,100,0,dataTitleColor);
    DrawRectangleRounded(panelHolder,0,0,panelNormal);
    Play.drawRectangleRounded(100);
    Next.drawRectangleRounded(100);
    Prev.drawRectangleRounded(100);
    End.drawRectangleRounded(100);
    Start.drawRectangleRounded(100);
}