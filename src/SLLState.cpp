#include "SLL/SLLState.h"

SLLState::SLLState(): createBox(120,700,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,SLLBoxColor, SLLBoxTextColor), indexBox(120,700,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,SLLBoxColor, SLLBoxTextColor), valueBox(120,825,SLLBoxSize.x, SLLBoxSize.y,SLLBoxFontSize,SLLBoxColor, SLLBoxTextColor){
    this->Random.setText("Random",SLLButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,760});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",SLLButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,760});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Front.setText("Front",SLLButtonFontSize);
    this->Front.setSize({120, 30});
    this->Front.setPosition({180,760});
    this->Front.setColor(panelNormal,panelHovered,panelPressed);
    this->Front.setRectangle();

    this->End.setText("Back",SLLButtonFontSize);
    this->End.setSize({120, 30});
    this->End.setPosition({320,760});
    this->End.setColor(panelNormal,panelHovered,panelPressed);
    this->End.setRectangle();

    this->Apply.setText("Apply",SLLButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,800});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();

    createBox.setNameBox("Input Elements");
    indexBox.setNameBox("Index");
    valueBox.setNameBox("Value");
}

void SLLState::update(){
    if (panel.isPlayPressed()) {
        if(currentStep==stateList.size()-1){
            restart();
        }
        else if(currentStep==0){
            play();
        }
        else if(isPlaying&&!isPaused){
            pause();
        }
        else if(isPlaying&&isPaused){
            resume();
        }
    }
    else if (panel.isNextPressed()) {
        nextStep();
    }
    else if (panel.isPrevPressed()) {
        prevStep();
    }
    else if (panel.isEndPressed()) {
        moveEnd();
    }
    else if (panel.isStartPressed()) {
        moveStart();
    }
    SLL.update();
    panel.update();
    code.update();
    switch (animationState) {
        case SLLAnimationMode::INSERT_FRONT:
            if (!isStateSaved) {
                saveInsertFrontState(std::stoi(indexText), std::stoi(valueText));
                isStateSaved = true;
            }
            animateInsertFront(std::stoi(indexText), std::stoi(valueText));
            break;
        case SLLAnimationMode::INSERT_MID:
            if (!isStateSaved) {
                saveInsertMidState(std::stoi(indexText), std::stoi(valueText));
                isStateSaved = true; 
            }
            animateInsertMid(std::stoi(indexText), std::stoi(valueText));
            break;
        case SLLAnimationMode::REMOVE_FRONT:
            if (!isStateSaved) {
                saveRemoveFrontState(std::stoi(indexText));
                isStateSaved = true; 
            }
            animateRemoveFront(std::stoi(indexText));
            break;
        case SLLAnimationMode::REMOVE_MID:
            if (!isStateSaved) {
                saveRemoveMidState(std::stoi(indexText));
                isStateSaved = true; 
            }
            animateRemoveMid(std::stoi(indexText));
            break;
        case SLLAnimationMode::SEARCH:
            if (!isStateSaved) {
                saveSearchState(std::stoi(valueText));
                isStateSaved = true;
            }
            animateSearch(std::stoi(valueText));
            break;
        case SLLAnimationMode::UPDATE:
            if (!isStateSaved) {
                saveUpdateState(std::stoi(indexBox.GetText()), std::stoi(valueBox.GetText()));
                isStateSaved = true;
            }
            animateUpdate(std::stoi(indexBox.GetText()), std::stoi(valueBox.GetText()));
            break;
        case SLLAnimationMode::IDLE:
            if (isStateSaved) {
                isStateSaved = false; 
            }
            break;
        default:
            break;
    }
    if(panel.isCreateUsed()){
        valueBox.setPosition({120,825});
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Front.deActive();
        End.deActive();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()){
        if(panel.isAddUsed())
            valueBox.setPosition({120,825});
        else
            valueBox.setPosition({120,700});
        Front.setActive();
        End.setActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    else if(panel.isUpdateUsed()){
        valueBox.setPosition({120,825});
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    else if(panel.isSearchUsed()){
        valueBox.setPosition({120,700});
        Front.deActive();
        End.deActive();
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
    }
    if(Random.isPressed()){
        createBox.setText(getRandomInput());
    }
    else if(Front.isPressed()){
        indexBox.setText("0");
    }
    else if(End.isPressed()){
        if(panel.isAddUsed())
            indexBox.setText(std::to_string(SLL.getListSize()));
        else if(panel.isRemoveUsed()){
            indexBox.setText(std::to_string(SLL.getListSize()-1));
        }
    }
    else if(LoadFile.isPressed()){
        
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        isStateSaved=false;
        isPlaying=true;
        isPaused=false;
        indexText=indexBox.GetText();
        valueText=valueBox.GetText();
        createText=createBox.GetText();
        resetBox();
        if(panel.isCreateUsed()&&createText!=""){
            SLL.createList(createText);
        }
        else if(panel.isAddUsed()&&indexText!=""&&valueText!=""){
            if(std::stoi(indexText)==0){
                animationState=SLLAnimationMode::INSERT_FRONT;
            }
            else{
                animationState=SLLAnimationMode::INSERT_MID;
            }
            //SLL.insertNode(std::stoi(indexBox.GetText()),std::stoi(valueBox.GetText()));
        }
        else if(panel.isRemoveUsed()&&indexText!=""){
            if(std::stoi(indexText)==0){
                animationState=SLLAnimationMode::REMOVE_FRONT;
            }
            else{
                animationState=SLLAnimationMode::REMOVE_MID;
            }
            //SLL.removeNode(std::stoi(indexBox.GetText()));
        }
        else if(panel.isUpdateUsed()&&valueText!=""){
            animationState=SLLAnimationMode::UPDATE;
            //SLL.updateNode(std::stoi(indexBox.GetText()),std::stoi(valueBox.GetText()));
        }
        else if(panel.isSearchUsed()&&valueText!=""){
            animationState=SLLAnimationMode::SEARCH;
            //SLL.searchNode(std::stoi(valueBox.GetText()));
        }
    }
    else if(panel.isBackPressed()){
        SLL.clearList();
        resetBox();
    }
    else if(panel.isAnyButtonPressed()){
        SLL.resetHighlight();
        resetBox();
    }
    if(panel.isCreateUsed()){
        createBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isUpdateUsed()){
        this->Front.update();
        this->End.update();
        indexBox.Update();
        if(!panel.isRemoveUsed())
            valueBox.Update();
    }
    else if(panel.isSearchUsed()){
        valueBox.Update();
    }
}

void SLLState::draw(){
    code.draw();
    SLL.draw();
    panel.draw();
    DrawText("Singly Linked List",GetScreenWidth()/2.0f-MeasureText("Singly Linked List",dataTitleFontSize)/2.0f,40-dataTitleFontSize/2.0f,dataTitleFontSize, dataTitleTextColor);
    if(panel.isCreateUsed()){
        createBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->Random.drawText(panelSubButtonTextColor);
        this->LoadFile.drawRectangleRounded(100);
        this->LoadFile.drawText(panelSubButtonTextColor);
        this->Apply.drawRectangleRounded(100);
        this->Apply.drawText(panelSubButtonTextColor);
    }
    else if(panel.isAddUsed()||panel.isRemoveUsed()||panel.isUpdateUsed()){
        if(!panel.isUpdateUsed()){
            this->Front.drawRectangleRounded(100);
            this->Front.drawText(panelSubButtonTextColor);
            this->End.drawRectangleRounded(100);
            this->End.drawText(panelSubButtonTextColor);
        }
        indexBox.Draw();
        if(!panel.isRemoveUsed())
            valueBox.Draw();
    }
    else if(panel.isSearchUsed()){
        valueBox.Draw();
    }
}

void SLLState::saveInsertFrontState(int index, int value){
    clearState();
    if(SLL.indexStep>=index) return;
    saveState();
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        SLL.newNode=new SLLNode();
        SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.newNode->setNull();
        SLL.newNode->setValue(value);
        SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.myNode->setLabel("myNode");
        SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
        SLL.myNode->setDestination(SLL.newNode->getStartPos());
        SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
        saveState();
        if(!SLL.list.empty()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+50), SLLposition.y});
            }
            for(int i=index;i<SLL.list.size()-1;i++){
                SLL.list[i]->setDestination(SLL.list[i+1]->getStartPos());
            }
            SLL.list[SLL.list.size()-1]->setDestination({SLL.list[SLL.list.size()-1]->getEndPos().x+ArrowLength,SLLposition.y});
            SLL.head->setDestination(SLL.list[0]->getStartPos());
            SLL.animationStep++;
            saveState();
        }
        else{
            SLL.animationStep+=2;
            SLL.list.insert(SLL.list.begin(),SLL.newNode);
        }
    }
    if(SLL.animationStep==1){
        SLL.newNode->setDestination(SLL.list[index]->getStartPos());
        SLL.animationStep++;
        SLL.list.insert(SLL.list.begin(),SLL.newNode);
        saveState();
    }
    if(SLL.animationStep==2){
        SLL.head->setDestination(SLL.newNode->getStartPos());
        SLL.animationStep++;
        SLL.isNewNode=false;
        saveState();
    }
    if(SLL.animationStep==3){
        SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50), SLLposition.y});
        SLL.indexStep=-1;
        SLL.animationStep=0;
        SLL.newNode=nullptr;
        delete SLL.myNode;
        SLL.myNode=nullptr;
        animationState=SLLAnimationMode::IDLE;
        saveState();
    }
    applyState();
}

void SLLState::saveInsertMidState(int index, int value){
    clearState();
    if(SLL.indexStep>index) return;
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
    }
    saveState();
    while(SLL.indexStep<index-1){
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-50,SLL.list[SLL.indexStep+1]->getStartPos().y+50});
        SLL.indexStep++;
        saveState();
    }
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        SLL.newNode=new SLLNode();
        SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.newNode->setNull();
        SLL.newNode->setValue(value);
        SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.myNode->setLabel("myNode");
        SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
        SLL.myNode->setDestination(SLL.newNode->getStartPos());
        SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
        saveState();
        if(SLL.indexStep+1!=SLL.list.size()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+50), SLLposition.y});
            }
            for (int i=index-1;i<SLL.list.size()-1;i++){
                SLL.list[i]->setDestination(SLL.list[i+1]->getStartPos());
            }
            SLL.list[SLL.list.size()-1]->setDestination({SLL.list[SLL.list.size()-1]->getEndPos().x+ArrowLength,SLLposition.y});
            SLL.animationStep++;
            saveState();
        }
        else{
            SLL.animationStep+=2;
            SLL.list.insert(SLL.list.begin()+index,SLL.newNode);
        }
    }
    if(SLL.animationStep==1){
        SLL.newNode->setDestination(SLL.list[index]->getStartPos());
        SLL.animationStep++;
        SLL.list.insert(SLL.list.begin()+index,SLL.newNode);
        saveState();
    }
    if(SLL.animationStep==2){
        SLL.list[index-1]->setDestination(SLL.newNode->getStartPos());
        SLL.animationStep++;
        SLL.isNewNode=false;
        saveState();
    }
    if(SLL.animationStep==3){
        SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50), SLLposition.y});
        SLL.indexStep=-1;
        SLL.animationStep=0;
        SLL.newNode=nullptr;
        if(SLL.myNode);
            delete SLL.myNode;
        SLL.myNode=nullptr;
        SLL.isCur=false;
        resetCursorPosition();
        animationState=SLLAnimationMode::IDLE;
        saveState();
    }
    applyState();
}

void SLLState::saveRemoveFrontState(int index){
    clearState();
    if(SLL.indexStep>index) return;
    saveState();
    if(SLL.animationStep==0){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        saveState();
        SLL.animationStep++;
        SLL.newNode=SLL.list[index];
        SLL.list.erase(SLL.list.begin()+index);
        SLL.isCur=false;
        resetCursorPosition();
        delete SLL.newNode;
        SLL.newNode=nullptr;
        saveState();
    }
    if(SLL.list.empty()){
        SLL.head->setDestination({SLLposition.x+ArrowLength,SLLposition.y});
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        saveState();
        applyState();
        return;
    }
    if(SLL.animationStep==1){
        SLL.head->setDestination(SLL.list[index]->getStartPos());
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==2){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+50), SLLposition.y});
        }
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        saveState();
    }
    applyState();
}

void SLLState::saveRemoveMidState(int index){
    clearState();
    if(SLL.indexStep>index) return;
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
        saveState();
    }
    for (int i=0;i<=index;i++){
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-50,SLL.list[SLL.indexStep+1]->getStartPos().y+50});
        SLL.indexStep++;
        if(i==index){
            SLL.animationStep++;
        }
        saveState();
    }
    if(SLL.animationStep==1){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
        saveState();
        SLL.animationStep++;
        SLL.newNode=SLL.list[index];
        SLL.list.erase(SLL.list.begin()+index);
        SLL.isCur=false;
        resetCursorPosition();
        delete SLL.newNode;
        SLL.newNode=nullptr;
        saveState();
    }
    if(SLL.animationStep==2&&index==SLL.list.size()){
        SLL.list[index-1]->setDestination({SLL.list[index-1]->getEndPos().x+ArrowLength,SLLposition.y});
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        saveState();
        applyState();
        return;
    }
    else if(SLL.animationStep==2){
        SLL.list[index-1]->setDestination(SLL.list[index]->getStartPos());
        SLL.animationStep++;
        saveState();
    }
    if(SLL.animationStep==3){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+50), SLLposition.y});
        }
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        saveState();
    }
    applyState();
}

void SLLState::saveSearchState(int value){
    clearState();
    SLL.resetHighlight();
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
        saveState();
    }
    static int index=0;
    while(true){
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
        if(SLL.list[index]->getValue()!=value){
            saveState();
            index++;
        }
        else{
            SLL.list[index]->setHighlight();
            SLL.isCur=false;
            resetCursorPosition();
            index=0;
            animationState=SLLAnimationMode::IDLE;
            saveState();
            applyState();
            return;
        }
    }
    applyState();
}

void SLLState::saveUpdateState(int index, int value){
    clearState();
    if(SLL.indexStep>index) return;
    saveState();
    if(!SLL.isCur){
        SLL.isCur=true;
        resetCursorPosition();
        saveState();
    }
    while (SLL.indexStep<index){
        SLL.cur->setDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-50,SLL.list[SLL.indexStep+1]->getStartPos().y+50});
        SLL.indexStep++;
        if(SLL.indexStep==index-1){
            SLL.animationStep++;
        }
        saveState();
    }
    if(SLL.animationStep==1){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
        saveState();
        SLL.animationStep++;
        SLL.list[index]->setValue(value);
        saveState();
    }
    if(SLL.animationStep==2){
        SLL.list[index]->setPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50), SLLposition.y});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
        saveState();
        SLL.indexStep=-1;
        SLL.animationStep=0;
        SLL.isCur=false;
        resetCursorPosition();
        animationState=SLLAnimationMode::IDLE;
        saveState();
    }
    applyState();
}

void SLLState::animateInsertFront(int index, int value){
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>=index) return;
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        if(!SLL.newNode){
            SLL.newNode=new SLLNode();
            SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
            SLL.newNode->setNull();
            SLL.newNode->setValue(value);
            SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        }
        if(!SLL.myNode){
            SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+50), SLLposition.y+100});
            SLL.myNode->setLabel("myNode");
            SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
            SLL.myNode->setDestination(SLL.newNode->getStartPos());
            SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
            currentStep++;
        }
        if(!SLL.list.empty()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+50), SLLposition.y});
            }
            if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index+1) * (SLLNodeSize.x+50)){
                SLL.animationStep++;
                currentStep++;
            }
        }
        else{
            SLL.animationStep+=2;
            SLL.list.insert(SLL.list.begin(),SLL.newNode);
        }
    }
    else if(SLL.animationStep==1){
        SLL.newNode->setTargetDestination(SLL.list[index]->getStartPos());
        if(SLL.newNode->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.newNode->getDestination().y==SLL.list[index]->getStartPos().y){
            SLL.animationStep++;
            SLL.list.insert(SLL.list.begin(),SLL.newNode);
            currentStep++;
        }
    }
    else if(SLL.animationStep==2){
        if(SLL.head->getDestination().x==SLL.newNode->getStartPos().x&&SLL.head->getDestination().y==SLL.newNode->getStartPos().y){
            SLL.animationStep++;
            SLL.isNewNode=false;
            currentStep++;
        }
    }
    else if(SLL.animationStep==3){
        SLL.newNode->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50), SLLposition.y});
        if(SLL.newNode->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50)&&SLL.newNode->getPosition().y==SLLposition.y){
            SLL.indexStep=-1;
            SLL.animationStep=0;
            SLL.newNode=nullptr;
            delete SLL.myNode;
            SLL.myNode=nullptr;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
            isPlaying=false;
            isPaused=true;
        }
    }
}

void SLLState::animateInsertMid(int index, int value){
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>=index) return;
    static float checkTimer = 0.0f;
    if(SLL.indexStep+1<index&&(SLL.cur->getDestination().x!=SLL.list[SLL.indexStep+1]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[SLL.indexStep+1]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-50,SLL.list[SLL.indexStep+1]->getStartPos().y+50});
    }
    else if(SLL.indexStep+1<index){
        checkTimer+=GetFrameTime();
        if(checkTimer>=0.5f){
            checkTimer=0;
            SLL.indexStep++;
            currentStep++;
        }
    }
    if(SLL.indexStep+1==index&&SLL.animationStep==0){
        SLL.isNewNode=true;
        if(!SLL.newNode){
            SLL.newNode=new SLLNode();
            SLL.newNode->setPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
            SLL.newNode->setNull();
            SLL.newNode->setValue(value);
            SLL.newNode->setDestination({SLL.newNode->getEndPos().x+ArrowLength,SLL.newNode->getEndPos().y});
        }
        if(!SLL.myNode){
            SLL.myNode=new SLLArrow({SLL.head->getPosition().x + index * (SLLNodeSize.x+50), SLLposition.y+100});
            SLL.myNode->setLabel("myNode");
            SLL.myNode->setPosition({SLL.newNode->getStartPos().x-ArrowLength,SLL.newNode->getStartPos().y});
            SLL.myNode->setDestination(SLL.newNode->getStartPos());
            SLL.myNode->setTargetDestination(SLL.newNode->getStartPos());
            currentStep++;
        }
        if(SLL.indexStep+1!=SLL.list.size()){
            for (int i=index;i<SLL.list.size();i++){
                SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (i+1) * (SLLNodeSize.x+50), SLLposition.y});
            }
            if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index+1) * (SLLNodeSize.x+50)){
                SLL.animationStep++;
                currentStep++;
            }
        }
        else{
            SLL.animationStep+=2;
            SLL.list.insert(SLL.list.begin()+index,SLL.newNode);
        }
    }
    else if(SLL.animationStep==1){
        SLL.newNode->setTargetDestination(SLL.list[index]->getStartPos());
        if(SLL.newNode->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.newNode->getDestination().y==SLL.list[index]->getStartPos().y){
            SLL.animationStep++;
            SLL.list.insert(SLL.list.begin()+index,SLL.newNode);
            currentStep++;
        }
    }
    else if(SLL.animationStep==2){
        if(SLL.list[index-1]->getDestination().x==SLL.newNode->getStartPos().x&&SLL.list[index-1]->getDestination().y==SLL.newNode->getStartPos().y){
            SLL.animationStep++;
            SLL.isNewNode=false;
            currentStep++;
        }
    }
    else if(SLL.animationStep==3){
        SLL.newNode->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50), SLLposition.y});
        if(SLL.newNode->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50)&&SLL.newNode->getPosition().y==SLLposition.y){
            SLL.indexStep=-1;
            SLL.animationStep=0;
            SLL.newNode=nullptr;
            delete SLL.myNode;
            SLL.myNode=nullptr;
            SLL.isCur=false;
            resetCursorPosition();
            animationState=SLLAnimationMode::IDLE;
            isStateSaved=false;
            currentStep++;
        }
    }
}

void SLLState::animateRemoveFront(int index){
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>index) return;
    if(SLL.animationStep==0){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50)&&SLL.list[index]->getPosition().y==SLLposition.y+100){
            currentStep++;
            SLL.animationStep++;
            SLL.newNode=SLL.list[index];
            SLL.list.erase(SLL.list.begin()+index);
            resetCursorPosition();
            delete SLL.newNode;
            SLL.newNode=nullptr;
            currentStep++;
        }
    }
    if(SLL.list.empty()){
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        currentStep++;
    }
    else if(SLL.animationStep==1){
        if(SLL.head->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.head->getDestination().y==SLL.list[index]->getStartPos().y){
            SLL.animationStep++;
            currentStep++;
        }
    }
    else if(SLL.animationStep==2){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+50), SLLposition.y});
        }
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50)){
            SLL.animationStep=0;
            SLL.indexStep=-1;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
        }
    }
}

void SLLState::animateRemoveMid(int index){
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>index) return;
    static float checkTimer = 0.0f;
    if(SLL.animationStep==0&&SLL.indexStep<index&&(SLL.cur->getDestination().x!=SLL.list[SLL.indexStep+1]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[SLL.indexStep+1]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-50,SLL.list[SLL.indexStep+1]->getStartPos().y+50});
    }
    else if(SLL.animationStep==0&&SLL.indexStep<index){
        checkTimer+=GetFrameTime();
        if(checkTimer>=0.5f){
            checkTimer=0;
            SLL.indexStep++;
            if(SLL.indexStep==index){
                SLL.animationStep++;
            }
            currentStep++;
        }
    }
    else if(SLL.animationStep==1){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50)&&SLL.list[index]->getPosition().y==SLLposition.y+100){
            currentStep++;
            SLL.animationStep++;
            SLL.newNode=SLL.list[index];
            SLL.list.erase(SLL.list.begin()+index);
            SLL.isCur=false;
            resetCursorPosition();
            delete SLL.newNode;
            SLL.newNode=nullptr;
            currentStep++;
        }
    }
    if(SLL.animationStep==2&&index==SLL.list.size()){
        SLL.animationStep=0;
        SLL.indexStep=-1;
        animationState=SLLAnimationMode::IDLE;
        currentStep++;
    }
    else if(SLL.animationStep==2){
        if(SLL.list[index-1]->getDestination().x==SLL.list[index]->getStartPos().x&&SLL.list[index-1]->getDestination().y==SLL.list[index]->getStartPos().y){
            SLL.animationStep++;
            currentStep++;
        }
    }
    else if(SLL.animationStep==3){
        for (int i=index;i<SLL.list.size();i++){
            SLL.list[i]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + i * (SLLNodeSize.x+50), SLLposition.y});
        }
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50)){
            SLL.animationStep=0;
            SLL.indexStep=-1;
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
        }
    }
}

void SLLState::animateSearch(int value){
    if(!isPlaying||isPaused) return;
    SLL.resetHighlight();
    static int index=0;
    static float checkTimer = 0.0f;
    if((SLL.cur->getDestination().x!=SLL.list[index]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[index]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        SLL.cur->setTargetDestination(SLL.list[index]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
    }
    else {
        checkTimer+=GetFrameTime();
        if(checkTimer>=0.5f){
            if(SLL.list[index]->getValue()==value){
                SLL.list[index]->setHighlight();
                SLL.isCur=false;
                SLL.cur->setPosition({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f+50});
                SLL.cur->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f+50});
                index=0;
                animationState=SLLAnimationMode::IDLE;
                currentStep++;
                return;
            }
            currentStep++;
            index++;
            checkTimer=0;
        }
    }
}

void SLLState::animateUpdate(int index, int value){
    if(!isPlaying||isPaused) return;
    if(SLL.indexStep>index) return;
    static float checkTimer = 0.0f;
    if(SLL.animationStep==0&&SLL.indexStep<index&&(SLL.cur->getDestination().x!=SLL.list[SLL.indexStep+1]->getStartPos().x||SLL.cur->getDestination().y!=SLL.list[SLL.indexStep+1]->getStartPos().y)){
        if(!SLL.isCur){
            SLL.isCur=true;
            resetCursorPosition();
            currentStep++;
        }
        SLL.cur->setTargetDestination(SLL.list[SLL.indexStep+1]->getStartPos());
        SLL.cur->setTargetPosition({SLL.list[SLL.indexStep+1]->getStartPos().x-50,SLL.list[SLL.indexStep+1]->getStartPos().y+50});
    }
    else if(SLL.animationStep==0&&SLL.indexStep<index){
        checkTimer+=GetFrameTime();
        if(checkTimer>=0.5f){
            checkTimer=0;
            SLL.indexStep++;
            if(SLL.indexStep==index) {
                SLL.animationStep++;
                currentStep++;
            }
        }
    }
    else if(SLL.animationStep==1){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + index * (SLLNodeSize.x+50), SLLposition.y+100});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50)&&SLL.list[index]->getPosition().y==SLLposition.y+100){
            currentStep++;
            SLL.animationStep++;
            SLL.list[index]->setValue(value);
            currentStep++;
        }
    }
    else if(SLL.animationStep==2){
        SLL.list[index]->setTargetPosition({SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50), SLLposition.y});
        SLL.cur->setDestination(SLL.list[index]->getStartPos());
        SLL.cur->setPosition({SLL.list[index]->getStartPos().x-50,SLL.list[index]->getStartPos().y+50});
        if(SLL.list[index]->getPosition().x==SLL.head->getPosition().x+ArrowLength + (index) * (SLLNodeSize.x+50)&&SLL.list[index]->getPosition().y==SLLposition.y){
            currentStep++;
            SLL.indexStep=-1;
            SLL.animationStep=0;
            SLL.isCur=false;
            resetCursorPosition();
            animationState=SLLAnimationMode::IDLE;
            currentStep++;
        }
    }
}

void SLLState::resetCursorPosition(){
    SLL.cur->setPosition({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f+50});
    SLL.cur->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f+50});
}

void SLLState::resetBox(){
    createBox.resetBox();
    indexBox.resetBox();
    valueBox.resetBox();
}

std::string SLLState::getRandomInput(){
    int numElement=rand()%10;
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

bool SLLState::isBackPressed(){
    return panel.isBackPressed();
}

void SLLState::play(){
    if (!stateList.empty()) {
        isPlaying = true;   
        isPaused = false;   
        currentStep = 0;    
        animationState = stateList[currentStep]->animationState;
    }
}

void SLLState::pause() {
    isPaused = true;  
}

void SLLState::resume() {
    isPaused = false;
}

void SLLState::nextStep(){
    isPlaying=true;
    if(currentStep<stateList.size()-1){
        currentStep++;
        if(currentStep==stateList.size()-1){
            isPlaying=false;
        }
        applyState();
    }
}

void SLLState::prevStep() {
    isPlaying=true;
    if (currentStep > 0) {
        currentStep--;
        applyState();
    }
}

void SLLState::restart(){
    isPlaying=true;
    isPaused=false;
    currentStep=0;
    applyState();
}

void SLLState::moveEnd(){
    isPlaying=false;
    currentStep=stateList.size()-1;
    applyState();
}

void SLLState::moveStart(){
    isPlaying=true;
    currentStep=0;
    applyState();
}

void SLLState::saveState(){
    SinglyLinkedList* currentState = SLL.clone();
    SLLAnimationMode currentMode = this->animationState;
    stateList.push_back(new AnimationStep{currentState, currentMode});
}

void SLLState::applyState(){
    if(stateList.empty()) return;
    if (currentStep < 0) {
        currentStep = 0; 
    }
    else  if (currentStep >= stateList.size()) {
        currentStep = stateList.size() - 1;
    }
    SLL.clear();
    SLL = *stateList[currentStep]->SLL->clone();
    animationState=stateList[currentStep]->animationState;
}

void SLLState::clearState() {
    for (auto state : stateList) {
        if (state) {
            delete state;
            state=nullptr;
        }
    }
    stateList.clear();
}