#include "AVL/AVL.h"

AVL::AVL() : root(nullptr), curNode(nullptr) {}

AVL::~AVL(){
    clearTree();
}

void AVL::createTree(std::string text){
    clearTree();
    std::string value;
    std::stringstream ss(text);
    while(std::getline(ss,value,',')){
        insertNode(std::stoi(value));
    }
}

void AVL::insertNode(int value){
    if(!root){
        root = new AVLNode();
        root->setValue(value);
        calculateHeight();
        root->setPosition({(float)GetScreenWidth()/2,150});
        root->setTargetPosition({(float)GetScreenWidth()/2,150});
        return;
    }
    AVLNode* cur = root;
    while(true){
        if(value<cur->getValue()){
            if(!cur->left){
                cur->left = new AVLNode();
                cur->left->setValue(value);
                cur->left->parent = cur;
                calculateHeight();
                cur->left->setPosition({cur->getOrigin().x-(cur->left->getHeight()*(AVLLeafSpace+AVLNodeSize.x)/2.0f),cur->getOrigin().y+AVLLevelSpace});
                cur->left->setTargetPosition({cur->getOrigin().x-(cur->left->getHeight()*(AVLLeafSpace+AVLNodeSize.x)/2.0f),cur->getOrigin().y+AVLLevelSpace});
                break;
            }
            cur = cur->left;
        }
        else{
            if(!cur->right){
                cur->right = new AVLNode();
                cur->right->setValue(value);
                cur->right->parent = cur;
                calculateHeight();
                cur->right->setPosition({cur->getOrigin().x+(cur->right->getHeight()*(AVLLeafSpace+AVLNodeSize.x)/2.0f),cur->getOrigin().y+AVLLevelSpace});
                cur->right->setTargetPosition({cur->getOrigin().x+(cur->right->getHeight()*(AVLLeafSpace+AVLNodeSize.x)/2.0f),cur->getOrigin().y+AVLLevelSpace});
                break;
            }
            cur = cur->right;
        }
    }
    calculateDepth();
    balanceTree();
}

void AVL::updateInsertAnimation(int value){
    if(!root){
        root = new AVLNode();
        root->setValue(value);
        calculateHeight();
        root->setPosition({(float)GetScreenWidth()/2,150});
        root->setTargetPosition({(float)GetScreenWidth()/2,150});
        return;
    }
}

void AVL::balanceTree(){
    balanceTree(root);
}

void AVL::balanceTree(AVLNode*& root){
    if(!root) return;
    balanceTree(root->left);
    balanceTree(root->right);
    if(root->left && root->right){
        if(root->left->getHeight()-root->right->getHeight()>1){
            if((!root->left->right)||(root->left->left&&root->left->right&&root->left->left->getHeight()>root->left->right->getHeight())) rotateRight(root);
            else rotateLeftRight(root);
        }
        else if(root->right->getHeight()-root->left->getHeight()>1){
            if((!root->right->left)||(root->right->right&&root->right->left&&root->right->right->getHeight()>root->right->left->getHeight())) rotateLeft(root);
            else rotateRightLeft(root);
        }
    }
    else if(root->left && root->left->getHeight()>1){
        if((!root->left->right)||(root->left->left&&root->left->right&&root->left->left->getHeight()>root->left->right->getHeight())) rotateRight(root);
        else rotateLeftRight(root);
    }
    else if(root->right && root->right->getHeight()>1){
        if((!root->right->left)||(root->right->right&&root->right->left&&root->right->right->getHeight()>root->right->left->getHeight())) rotateLeft(root);
        else rotateRightLeft(root);
    }
    updatePosition();
    calculateDepth();
}

void AVL::rotateRight(AVLNode*& root) {  
    if (!root || !root->left) return; 
    AVLNode* newRoot = root->left;
    root->left = newRoot->right;
    if (newRoot->right) newRoot->right->parent = root;
    newRoot->right = root;
    newRoot->parent = root->parent;
    root->parent = newRoot;

    if (!newRoot->parent) this->root = newRoot;  
    else if (newRoot->parent->left == root) newRoot->parent->left = newRoot;
    else newRoot->parent->right = newRoot;

    root = newRoot;  
    calculateHeight();
}

void AVL::rotateLeft(AVLNode*& root){
    AVLNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    newRoot->parent = root->parent;
    root->parent = newRoot;
    if(root->right) root->right->parent = root;
    if(newRoot->parent){
        if(newRoot->parent->left==root) newRoot->parent->left = newRoot;
        else newRoot->parent->right = newRoot;
    }
    else root = newRoot;
    calculateHeight();
}

void AVL::rotateRightLeft(AVLNode*& root){
    rotateRight(root->right);
    rotateLeft(root);
}

void AVL::rotateLeftRight(AVLNode*& root){
    rotateLeft(root->left);
    rotateRight(root);
}

void AVL::removeNode(int value){
    if(!root) return;
    AVLNode* cur = root;
    while(cur){
        if(value<cur->getValue()) cur = cur->left;
        else if(value>cur->getValue()) cur = cur->right;
        else break;
    }
    if(!cur) return;
    if(cur->isLeaf()){
        if(cur->parent){
            if(cur->parent->left==cur) cur->parent->left = nullptr;
            else cur->parent->right = nullptr;
        }
        else root=nullptr;
        delete cur;
    }
    else if(cur->left && cur->right){
        AVLNode* temp = cur->left;
        while (temp->right) temp = temp->right;
        cur->setValue(temp->getValue());
        if (temp->left) {
            if (temp->parent->right == temp) temp->parent->right = temp->left;
            else temp->parent->left = temp->left;
            temp->left->parent = temp->parent;
            temp->left = nullptr;
        }
        else {
            if (temp->parent->right == temp) temp->parent->right = nullptr;
            else temp->parent->left = nullptr;
        }
        delete temp;
    }
    else if(cur->left){
        if(cur->parent){
            if(cur->parent->left==cur) cur->parent->left = cur->left;
            else cur->parent->right = cur->left;
        }
        else{
            root=cur->left;
        }
        cur->left->parent = cur->parent;
        cur->left = nullptr;
        delete cur;
    }
    else if(cur->right){
        if(cur->parent){
            if(cur->parent->left==cur) cur->parent->left = cur->right;
            else cur->parent->right = cur->right;
        }
        else{
            root=cur->right;
        }
        cur->right->parent = cur->parent;
        cur->right = nullptr;
        delete cur;
    }
    calculateHeight();
    calculateDepth();
    balanceTree();
    update();
}

void AVL::searchNode(int value){}

void AVL::clearTree(){
    clearTree(root);
}

void AVL::clearTree(AVLNode*& root){
    if(!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root=nullptr;
}

void AVL::calculateHeight(){
    calculateHeight(this->root);
}

void AVL::calculateHeight(AVLNode* root){
    if(!root) return;
    calculateHeight(root->left);
    calculateHeight(root->right);
    if(!root->left && !root->right) root->setHeight(1);
    else if(!root->left) root->setHeight(1+root->right->getHeight());
    else if(!root->right) root->setHeight(1+root->left->getHeight());
    else root->setHeight(1+std::max(root->left->getHeight(), root->right->getHeight()));
}

void AVL::calculateDepth(){
    calculateDepth(root);
}

void AVL::calculateDepth(AVLNode* root){
    if(!root) return;
    if(!root->parent) {
        root->setDepth(0);
    }
    else{
        root->setDepth(1+root->parent->getDepth());
    }
    calculateDepth(root->left);
    calculateDepth(root->right);
}

void AVL::updatePosition(){
    root->setPosition({(float)GetScreenWidth()/2,150});
    root->setTargetPosition({(float)GetScreenWidth()/2,150});
    updatePosition(root);
}

void AVL::updatePosition(AVLNode* root){
    if(!root) return;
    if(root->left){
        root->left->setPosition({(float)(root->getOrigin().x-(pow(2,root->left->getHeight()-1)*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getOrigin().y+AVLLevelSpace});
        root->left->setTargetPosition({(float)(root->getOrigin().x-(pow(2,root->left->getHeight()-1)*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getOrigin().y+AVLLevelSpace});
    }
    if(root->right){
        root->right->setPosition({(float)(root->getOrigin().x+(pow(2,root->right->getHeight()-1)*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getOrigin().y+AVLLevelSpace});
        root->right->setTargetPosition({(float)(root->getOrigin().x+(pow(2,root->right->getHeight()-1)*(AVLLeafSpace+AVLNodeSize.x)/2.0f)),root->getOrigin().y+AVLLevelSpace});
    }
    updatePosition(root->left);
    updatePosition(root->right);
}

void AVL::update(){
    update(root);
}

void AVL::update(AVLNode* root){
    if(!root) return;
    root->updateCur();
    update(root->left);
    update(root->right);
}

void AVL::draw(){
    draw(root);
}

void AVL::draw(AVLNode* root){
    if(!root) return;
    root->drawCur();
    draw(root->left);
    draw(root->right);
}