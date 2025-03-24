#include "AVL/AVLNode.h"

AVLNode::AVLNode() : parent(nullptr), left(nullptr), right(nullptr), leftPointer(nullptr), rightPointer(nullptr) {}

AVLNode::~AVLNode(){
    delete left;
    delete right;
    delete leftPointer;
    delete rightPointer;
}

void AVLNode::setValue(int value){
    this->value=value;
}

void AVLNode::setPosition(Vector2 position){
    this->position=position;
    this->node = {position.x-AVLNodeSize.x/2.0f,position.y-AVLNodeSize.y/2.0f, AVLNodeSize.x, AVLNodeSize.y};
    if(leftPointer) delete leftPointer;
    leftPointer = new AVLArrow({position.x,position.y});
    if(rightPointer) delete rightPointer;
    rightPointer = new AVLArrow({position.x,position.y});
}

void AVLNode::setTargetPosition(Vector2 targetPos){
    this->targetPosition=targetPos;
}

void AVLNode::setHeight(int value){
    height=value;
}

void AVLNode::setDepth(int value){
    depth=value;
}

void AVLNode::setHighlight(){
    isHighlight=true;
}

void AVLNode::deHighlight(){
    isHighlight=false;
}

Vector2 AVLNode::getOrigin(){
    return position;
}

int AVLNode::getValue(){
    return value;
}

int AVLNode::getDepth(){
    return depth;
}

int AVLNode::getHeight(){
    return height;
}

bool AVLNode::isLeaf(){
    return (!left&&!right);
}

void AVLNode::updateHeight(){
    if(!left&&!right) height=1;
    else if(!left) height=1+right->getHeight();
    else if(!right) height=1+left->getHeight();
    else height=1+std::max(left->getHeight(),right->getHeight());
}

void AVLNode::updateNode(){
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

void AVLNode::updateCur(){
    updateNode();
    node={position.x-AVLNodeSize.x/2.0f,position.y-AVLNodeSize.y/2.0f, AVLNodeSize.x, AVLNodeSize.y};
    if(left&&leftPointer){
        leftPointer->setTargetDestination(left->getOrigin());
        leftPointer->update();
    }
    if(right&&rightPointer){
        rightPointer->setTargetDestination(right->getOrigin());
        rightPointer->update();
    }
}

void AVLNode::drawCur(){
    if(left&&leftPointer){
        leftPointer->draw();
    }
    if(right&&rightPointer){
        rightPointer->draw();
    }
    DrawRectangleRounded(node,100,0,(isHighlight)? highlightColor : nodeColor);
    DrawText(std::to_string(this->value).c_str(),position.x-MeasureText(std::to_string(this->value).c_str(),AVLNodeFontSize)/2.0f,position.y-AVLNodeFontSize/2.0f,AVLNodeFontSize,(isHighlight)? textHighlight:textColor);
}

void AVLNode::setDestinationLeft(Vector2 targetDes){
    if(leftPointer){
        leftPointer->setDestination(targetDes);
    }
}

void AVLNode::setDestinationRight(Vector2 targetDes){
    if(rightPointer){
        rightPointer->setDestination(targetDes);
    }
}

void AVLNode::setTargetDestinationLeft(Vector2 targetDes){
    if(leftPointer){
        leftPointer->setTargetDestination(targetDes);
    }
}

void AVLNode::setTargetDestinationRight(Vector2 targetDes){
    if(rightPointer){
        rightPointer->setTargetDestination(targetDes);
    }
}