#include "ShortestPath/STPanel.h"

STPanel::STPanel(){
    this->Create.setText("Create",panelButtonFontSize);
    this->Create.setSize(panelButtonSize);
    this->Create.setPosition({Create.getSize().x/2.0f+(Create.getSize().y/2.0f-Create.getfontSize()/2.0f), 650+(Create.getSize().y/2.0f-Create.getfontSize()/2.0f)});
    this->Create.setColor(panelNormal,panelHovered,panelPressed);
    this->Create.setRectangle();

    this->Dijkstra.setText("Dijkstra",panelButtonFontSize);
    this->Dijkstra.setSize(panelButtonSize);
    this->Dijkstra.setPosition({Dijkstra.getSize().x/2.0f+(Dijkstra.getSize().y/2.0f-Dijkstra.getfontSize()/2.0f), 700+(Dijkstra.getSize().y/2.0f-Dijkstra.getfontSize()/2.0f)});
    this->Dijkstra.setColor(panelNormal,panelHovered,panelPressed);
    this->Dijkstra.setRectangle();

    this->Setting.setText("Setting",panelButtonFontSize);
    this->Setting.setSize(panelButtonSize);
    this->Setting.setPosition({Setting.getSize().x/2.0f+(Setting.getSize().y/2.0f-Setting.getfontSize()/2.0f), 750+(Setting.getSize().y/2.0f-Setting.getfontSize()/2.0f)});
    this->Setting.setColor(panelNormal,panelHovered,panelPressed);
    this->Setting.setRectangle();
}

bool STPanel::isAnyButtonPressed(){
    return Create.isPressed()||Dijkstra.isPressed()||Setting.isPressed();
}

void STPanel::draw(){
    drawController();
    this->Back.drawRectangleRounded(100);
    this->Create.drawRectangleRounded(100);
    this->Create.drawText(panelButtonTextColor);
    this->Dijkstra.drawRectangleRounded(100);
    this->Dijkstra.drawText(panelButtonTextColor);
    this->Setting.drawRectangleRounded(100);
    this->Setting.drawText(panelButtonTextColor);
}

void STPanel::update(){
    updateController();
    if(this->Create.isPressed()){
        this->Create.Selected();
        if(isUsing&&isUsing!=&Create) this->isUsing->deSelected();
        this->isUsing = &this->Create;
    }
    else if(this->Dijkstra.isPressed()){
        this->Dijkstra.Selected();
        if(isUsing&&isUsing!=&Dijkstra) this->isUsing->deSelected();
        this->isUsing = &this->Dijkstra;
    }
    else if(this->Setting.isPressed()){
        this->Setting.Selected();
        if(isUsing&&isUsing!=&Setting) this->isUsing->deSelected();
        this->isUsing = &this->Setting;
    }
    if(isBackPressed()){
        if(isUsing) this->isUsing->deSelected();
        isUsing=nullptr;
    }
    this->Back.update();
    this->Create.update();
    this->Dijkstra.update(); 
    this->Setting.update();
}

bool STPanel::isCreateUsed(){
    return (isUsing == &Create);
}

bool STPanel::isDijkstraUsed(){
    return (isUsing == &Dijkstra);
}

bool STPanel::isSettingUsed(){
    return (isUsing == &Setting);
}