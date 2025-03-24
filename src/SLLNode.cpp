#include "SLL/SLLNode.h"

SLLNode::SLLNode() : Pointer(nullptr) {}

SLLNode::~SLLNode(){
    delete Pointer;
    Pointer=nullptr;
}

void SLLNode::setNull(){
    if (Pointer) {
        Pointer->setNull();
    }
}

void SLLNode::setValue(int value){
    this->value=value;
}

void SLLNode::setPosition(Vector2 position){
    this->position = position;
    this->targetPosition=position;
    this->node = {position.x, position.y, SLLNodeSize.x, SLLNodeSize.y};

    if (Pointer) delete Pointer;
    Pointer = new SLLArrow(getEndPos());
}

void SLLNode::setTargetDestination(Vector2 targetDes){
    if(Pointer)
    Pointer->setTargetDestination(targetDes);
}

void SLLNode::setTargetPosition(Vector2 targetPos){
    this->targetPosition=targetPos;
}

void SLLNode::setDestination(Vector2 destination){
    Pointer->setDestination(destination);
}

void SLLNode::setHighlight(){
    isHighlight=true;
}

void SLLNode::deHighlight(){
    isHighlight=false;
}

Vector2 SLLNode::getStartPos(){
    return {position.x, position.y+node.height/2.0f};
}

Vector2 SLLNode::getEndPos(){
    return {position.x+node.width,position.y+node.height/2.0f};
}

Vector2 SLLNode::getPosition(){
    return position;
}


int SLLNode::getValue(){
    return value;
}

Vector2 SLLNode::getDestination(){
    return Pointer->getDestination();
}

void SLLNode::updateNode(){
    if (position.x == targetPosition.x&&position.y == targetPosition.y) return;
    float deltaTime=GetFrameTime();
    float disX=targetPosition.x-position.x, disY=targetPosition.y-position.y;
    float dis=sqrt(disX*disX+disY*disY);
    float deltaX=disX/dis*speed*deltaTime;
    float deltaY=disY/dis*speed*deltaTime;
    if(fabs(deltaX)>=fabs(disX)&&fabs(deltaY)>=fabs(disY)){
        position=targetPosition;
    }
    else{
        position.x+=deltaX;
        position.y+=deltaY;
    }
}

void SLLNode::updateCur(){
    updateNode();
    node={position.x, position.y, SLLNodeSize.x, SLLNodeSize.y};
    if (Pointer) {
        Pointer->setPosition(getEndPos());
        Pointer->setTargetPosition(getEndPos());
        Pointer->update();
    }
}

void SLLNode::drawCur(){
    DrawRectangleRounded(node, 50, 100, (isHighlight)? highlight : nodeColor);
    DrawText(std::to_string(this->value).c_str(),position.x+SLLNodeSize.x/2.0f-MeasureText(std::to_string(this->value).c_str(),SLLNodeFontSize)/2.0f,position.y+SLLNodeSize.y/2.0f-SLLNodeFontSize/2.0f,SLLNodeFontSize,(isHighlight)? textHighlight : textColor);
    if (Pointer) {
        Pointer->draw();
    }
}

SLLNode* SLLNode::clone() const{
    SLLNode* newNode = new SLLNode(); 
    newNode->node=this->node;
    newNode->value = this->value;
    newNode->position = this->position;
    newNode->targetPosition = this->targetPosition;
    newNode->nodeColor = this->nodeColor;
    newNode->textColor = this->textColor;
    newNode->highlight = this->highlight;
    newNode->textHighlight = this->textHighlight;
    newNode->isHighlight = this->isHighlight;
    newNode->Pointer = (this->Pointer) ? new SLLArrow(*this->Pointer) : nullptr;

    return newNode;
}