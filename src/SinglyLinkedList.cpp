#include "SLL/SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList() : head(new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f})), cur(new SLLArrow({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f+50})),newNode(nullptr), myNode(nullptr) {
    head->setTargetDestination({head->getPosition().x+ArrowLength,head->getPosition().y});
    head->setPosition({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f});
    head->setLabel("head");
    head->setNull();
    cur->setLabel("cur");
    cur->setNull();
    cur->setDestination({SLLposition.x+ArrowLength,SLLposition.y+SLLNodeSize.y/2.0f+50});
}

SinglyLinkedList::~SinglyLinkedList() {
    clearList();
    if(head) delete head;
    if(cur) delete cur;
    if(myNode) delete myNode;
    if(newNode) delete newNode;
    head = nullptr;
    cur = nullptr;
    myNode = nullptr;
    newNode = nullptr;
}

void SinglyLinkedList::createList(std::string text){
    clearList();
    head->setDestination({SLLposition.x,SLLposition.y+SLLNodeSize.y/2.0f});
    isCreated=true;
    std::string value;
    std::stringstream ss(text);
    int index=0;
    while (std::getline(ss, value, ',')) {
        int val=stoi(value);
        SLLNode* newNode = new SLLNode();
        newNode->setValue(val);
        list.insert(list.begin()+index++,newNode);
        for (int i=0;i<list.size();i++){
            list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
            list[i]->setTargetPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
        }
    }
    if(list.empty()){
        head->setTargetDestination({head->getPosition().x+ArrowLength,head->getPosition().y});
        head->setNull();
    }
    head->update();
    if (!list.empty()) {
        head->setTargetDestination(list[0]->getStartPos());
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->setTargetDestination(list[index + 1]->getStartPos());
            list[index]->updateCur();
        }
        list[list.size()-1]->setTargetDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->updateCur();
        list[list.size() - 1]->setNull();
    }
}

void SinglyLinkedList::clear(){
    clearList();
    if(head) delete head;
    if(cur) delete cur;
    if(myNode) delete myNode;
    if(newNode) delete newNode;
    head = nullptr;
    cur = nullptr;
    myNode = nullptr;
    newNode = nullptr;
}

// void SinglyLinkedList::insertNode(const int& index, int value) {
//     if(!isCreated) isCreated=true;
//     newNode = new SLLNode();
//     newNode->setValue(value);
//     list.insert(list.begin()+index,newNode);
//     for (int i=index;i<list.size();i++){
//         list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
//         list[i]->setTargetPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
//     }
//     for (int i = index; i < list.size() - 1; i++) {
//         list[i]->setDestination(list[i + 1]->getStartPos());
//         list[i]->updateCur();
//     }
//     list[list.size()-1]->setDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
//     list[list.size() - 1]->updateCur();
//     list[list.size() - 1]->setNull();
//     newNode=nullptr;
//     update();
// }

// void SinglyLinkedList::removeNode(const int& index) {
//     if (index < 0 || index >= list.size()) return;
//     delete list[index];
//     list.erase(list.begin() + index);
//     for (int i=index;i<list.size();i++){
//         list[i]->setPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
//         list[i]->setTargetPosition({head->getPosition().x+ArrowLength + (i) * (SLLNodeSize.x+50), SLLposition.y});
//     }
//     if(list.empty()) return;
//     for (int i = index; i < list.size() - 1; i++) {
//         list[i]->setDestination(list[i + 1]->getStartPos());
//         list[i]->updateCur();
//     }
//     list[list.size()-1]->setDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
//     list[list.size() - 1]->updateCur();
//     list[list.size() - 1]->setNull();
//     update();
// }

// void SinglyLinkedList::updateNode(const int &index,int value){
//     list[index]->setValue(value);
// }

// void SinglyLinkedList::searchNode(int value){
//     resetHighlight();
//     for (int i=0;i<list.size();i++){
//         if(list[i]->getValue()==value){
//             list[i]->setHighlight();
//             return;
//         }
//     }
// }

void SinglyLinkedList::clearList(){
    for (auto node : list) {
        delete node;
        node=nullptr;
    }
    list.clear();
    isCreated=false;
}

void SinglyLinkedList::resetHighlight(){
    for (auto node : list){
        node->deHighlight();
    }
}

int SinglyLinkedList::getListSize(){
    return list.size();
}

SinglyLinkedList* SinglyLinkedList::clone() const {
    SinglyLinkedList* cloneSLL = new SinglyLinkedList();
    delete cloneSLL->head;
    delete cloneSLL->cur;  
    cloneSLL->head=nullptr;
    cloneSLL->cur=nullptr;
    for (auto node : this->list) {
        cloneSLL->list.push_back(node->clone()); 
    }
    cloneSLL->head = (head)? new SLLArrow(*this->head) : nullptr;  
    cloneSLL->cur = (cur)? new SLLArrow(*this->cur) : nullptr;    
    cloneSLL->myNode = (myNode)? new SLLArrow(*this->myNode) : nullptr;
    cloneSLL->newNode = (newNode)? newNode->clone() : nullptr;
    cloneSLL->isNewNode=this->isNewNode;
    cloneSLL->isCur=this->isCur;
    cloneSLL->indexStep=this->indexStep;
    cloneSLL->animationStep=this->animationStep;
    cloneSLL->isCreated=this->isCreated;
    return cloneSLL;
}

void SinglyLinkedList::update(){
    if(isCur)
        cur->update();
    if(isNewNode){
        if(myNode){
            myNode->update();
            myNode->setDestination(newNode->getStartPos());
        }
        if(newNode){
            newNode->updateCur();
        }
    }
    if(list.empty()){
        head->setTargetDestination({head->getPosition().x+ArrowLength,head->getPosition().y});
        head->setNull();
    }
    if (!list.empty()) {
        head->setTargetDestination({list[0]->getStartPos()});
        for (int index = 0; index < list.size() - 1; index++) {
            list[index]->setTargetDestination(list[index + 1]->getStartPos());
            list[index]->updateCur();
        }
        list[list.size()-1]->setTargetDestination({list[list.size() - 1]->getEndPos().x + ArrowLength, list[list.size() - 1]->getEndPos().y});
        list[list.size() - 1]->updateCur();
        list[list.size() - 1]->setNull();
    }
    head->update();
}

void SinglyLinkedList::draw(){
    if(isNewNode){
        if(myNode)
            myNode->draw();
        if(newNode)
            newNode->drawCur();
    }
    if(isCur)
        cur->draw();
    if(isCreated)
        head->draw();
    for (auto node : list) {
        if (!node) continue;
        node->drawCur();
    }
}