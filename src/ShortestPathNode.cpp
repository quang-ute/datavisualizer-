#include "ShortestPath/ShortestPathNode.h"

ShortestPathNode::ShortestPathNode(Vector2 pos) {
    id = 0;
    cost = -1;
    isKnown = false;
    visited = false;
    position=pos;
}

ShortestPathNode::ShortestPathNode(int id) {
    this->id = id;
    cost = 0;
    isKnown = false;
    visited = false;
}

ShortestPathNode::~ShortestPathNode() {
    for(auto node : adj){
        node=nullptr;
    }
    adj.clear();
}

void ShortestPathNode::setID(int id) {
    this->id = id;
}

int ShortestPathNode::getID() {
    return id;
}

void ShortestPathNode::setCost(int cost) {
    this->cost = cost;
}

int ShortestPathNode::getCost() {
    return cost;
}

void ShortestPathNode::setVisited() {
    this->visited = true;
}

void ShortestPathNode::deVisited() {
    this->visited = false;
}

bool ShortestPathNode::getVisited() {
    return visited;
}

void ShortestPathNode::setKnown() {
    this->isKnown = true;
}

void ShortestPathNode::deKnown() {
    this->isKnown = false;
}

bool ShortestPathNode::getKnown() {
    return isKnown;
}

Vector2 ShortestPathNode::getPosition() {
    return position;
}

void ShortestPathNode::setPosition(Vector2 position) {
    this->position = position;
    node = {position.x-STNodeSize.x/2.0f,position.y-STNodeSize.y/2.0f, STNodeSize.x, STNodeSize.y};
    for(auto a : arrow){
        a->setPosition(position);
    }
}

Vector2 ShortestPathNode::getForce(){
    return force;
}

void ShortestPathNode::setForce(Vector2 force){
    this->force=force;
}

void ShortestPathNode::addEdge(ShortestPathNode* node) {
    STArrow* a = new STArrow(position,node->getID());
    a->setFrom(id);
    a->setTo(node->getID());
    a->setTargetDestination(node->getPosition());
    arrow.push_back(a);
}

void ShortestPathNode::removeEdge(ShortestPathNode* node) {
    for (auto it = arrow.begin(); it != arrow.end(); ++it) {
        if ((*it)->getTo() == node->getID()) {
            delete *it;  
            arrow.erase(it);  
            break;
        }
    }
}

void ShortestPathNode::clearEdges() {
    for(auto a : arrow){
        delete a;
    }
    arrow.clear();
}

void ShortestPathNode::update() {
    node={position.x-STNodeSize.x/2.0f,position.y-STNodeSize.y/2.0f,STNodeSize.x,STNodeSize.y};
    for(auto ar : arrow){
        for(auto node : adj){
            if(ar&&ar->getTo()==node->getID()){
                ar->setTargetDestination(node->getPosition());
                ar->update();
            }
        }
    }
}

void ShortestPathNode::draw(bool isWeighted, bool isDirected) {
    for(auto ar : arrow){
        if(ar)
            ar->draw(isWeighted, isDirected);
    }
}

void ShortestPathNode::drawNode(){
    DrawRectangleRounded(node, 100, 0, visited ? RED : LIGHTGRAY);
    if(cost==-1){
        DrawText("INF", position.x+STNodeSize.x/2.0f, position.y-STNodeSize.y/2.0f, STNodeIDFontSize, STNodeIDColor);
    }
    else{
        DrawText(std::to_string(cost).c_str(), position.x+STNodeSize.x/2.0f, position.y-STNodeSize.y/2.0f, STNodeIDFontSize, STNodeIDColor);
    }
    DrawText(std::to_string(id).c_str(), position.x-MeasureText(std::to_string(id).c_str(),STNodeCostFontSize)/2.0f,position.y-STNodeCostFontSize/2.0f,STNodeCostFontSize,STNodeCostColor);
}

