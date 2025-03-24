#include "AVL/AVLState.h"

AVLState::AVLState(): createBox(120,700,AVLBoxSize.x, AVLBoxSize.y,AVLBoxFontSize,AVLBoxColor, AVLBoxTextColor), valueBox(120,700,AVLBoxSize.x, AVLBoxSize.y,AVLBoxFontSize,AVLBoxColor, AVLBoxTextColor){
    this->Random.setText("Random",AVLButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,760});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",AVLButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,760});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Apply.setText("Apply",AVLButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,800});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();

    createBox.setNameBox("Input Elements");
    valueBox.setNameBox("Value");
}

void AVLState::update(){
    AVL.update();
    panel.update();
    if(panel.isCreateUsed()){
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    if(Random.isPressed()){
        createBox.setText(getRandomInput());
    }
    else if(LoadFile.isPressed()){
        
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        if(panel.isCreateUsed()&&createBox.GetText()!=""){
            AVL.createTree(createBox.GetText());
        }
        else if(panel.isAddUsed()&&valueBox.GetText()!=""){
            AVL.insertNode(std::stoi(valueBox.GetText()));
        }
        else if(panel.isRemoveUsed()&&valueBox.GetText()!=""){
            AVL.removeNode(std::stoi(valueBox.GetText()));
        }
        else if(panel.isSearchUsed()&&valueBox.GetText()!=""){
            AVL.searchNode(std::stoi(valueBox.GetText()));
        } 
        resetBox();
    }
    else if(panel.isBackPressed()){
        AVL.clearTree();
        resetBox();
    }
    else if(panel.isAnyButtonPressed()){
        resetBox();
    }
    if(panel.isCreateUsed()){
        createBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        valueBox.Update();
    }
}

void AVLState::draw(){
    AVL.draw();
    panel.draw();
    DrawText("AVL Tree",GetScreenWidth()/2.0f-MeasureText("AVL Tree",dataTitleFontSize)/2.0f,40-dataTitleFontSize/2.0f,dataTitleFontSize, dataTitleTextColor);
    AVLCode.draw();
    if(panel.isCreateUsed()){
        createBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->Random.drawText(panelSubButtonTextColor);
        this->LoadFile.drawRectangleRounded(100);
        this->LoadFile.drawText(panelSubButtonTextColor);
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText(panelSubButtonTextColor);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isSearchUsed()){
        valueBox.Draw();
    }
}

void AVLState::resetBox(){
    createBox.resetBox();
    valueBox.resetBox();
}

std::string AVLState::getRandomInput(){
    int numElement=rand()%30;
    std::string elements="";
    for (int i=0;i<=numElement;i++){
        if(i==numElement){
            elements+=std::to_string(rand()%100);
            continue;
        }
        elements+= std::to_string(rand()%100) +",";
    }
    return elements;
}

bool AVLState::isBackPressed(){
    return panel.isBackPressed();
}