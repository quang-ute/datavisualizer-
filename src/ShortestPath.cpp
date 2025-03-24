#include "ShortestPath/ShortestPath.h"

ShortestPath::ShortestPath() {
    isWeighted = false;
    isDirected = false;
    k = 0.0f;
}

ShortestPath::~ShortestPath() {
   clearGraph();
}

void ShortestPath::createGraph(int numNodes, int edges){
    clearGraph();
    k=800*450/numNodes;
    for(int i = 0; i < numNodes; i++){
        float posX = centerX + (rand() % (int)rangeX - rangeX / 2);
        float posY = centerY + (rand() % (int)rangeY - rangeY / 2);
        ShortestPathNode* n = new ShortestPathNode({posX,posY});
        n->setID(i);
        graph.push_back(n);
    }
    for(int i=0;i<edges;){
        int from = rand() % numNodes;
        int to = rand() % numNodes;
        if (from != to) {
            bool exists = false;
            for (const auto &e : graph[from]->arrow) {
                if (e->getTo() == to) {
                    exists = true;
                    break;
                }
            }
            for (const auto &e : graph[to]->arrow) {
                if (e->getTo() == from) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                graph[from]->adj.push_back(graph[to]);
                STArrow* edge=new STArrow(graph[from]->getPosition(), to);
                edge->setFrom(from);
                edge->setWeight(rand()%100+1);
                graph[from]->arrow.push_back(edge);
                i++;
            }
        }
    }
}

void ShortestPath::addEdge(int node1, int node2){
    if(node1 < graph.size() && node2 < graph.size()){
        graph[node1]->addEdge(graph[node2]);
        if(!isDirected){
            graph[node2]->addEdge(graph[node1]);
        }
    }
}

void ShortestPath::removeEdge(int node1, int node2){
    if(node1 < graph.size() && node2 < graph.size()){
        graph[node1]->removeEdge(graph[node2]);
        if(!isDirected){
            graph[node2]->removeEdge(graph[node1]);
        }
    }
}

void ShortestPath::searchPath(int startNode, int endNode){}

void ShortestPath::clearGraph(){
    for (auto n : graph) {
        if (n) {
            n->clearEdges();
            delete n;
        }
    }
    graph.clear();
}

void ShortestPath::resetGraph(){
    for(auto n : graph){
        n->deVisited();
        n->deKnown();
    }
}

void ShortestPath::setWeighted(){
    isWeighted = true;
}

void ShortestPath::deWeighted(){
    isWeighted = false;
}

void ShortestPath::setDirected(){
    isDirected = true;
}

void ShortestPath::deDirected(){
    isDirected = false;
}

void ShortestPath::update(){
    for(auto n : graph){
        if(n)
            n->update();
    }
}

void ShortestPath::draw(){
    for(auto n : graph){
        if(n)
            n->draw(isWeighted, isDirected);
    }
    for (auto n: graph){
        if(n)
            n->drawNode();
    }
}

void ShortestPath::FruchtermanReingold(){
    float X_min = centerX - rangeX / 2.0f, X_max = centerX + rangeX / 2.0f;
    float Y_min = centerY - rangeY / 2.0f, Y_max = centerY + rangeY / 2.0f;
    float deltaTime = 0.0016f;
    for (int loops = 0; loops < 8000; loops++) {
        for (auto &node : graph) {
            node->setForce({0, 0});
        }
        for (size_t i = 0; i < graph.size(); i++) {
            if (!graph[i]) continue;
            for (size_t j = i + 1; j < graph.size(); j++) {
                if (!graph[j]) continue;
                Vector2 force = ComputeRepulsiveForce(graph[i], graph[j]);
                graph[i]->setForce({graph[i]->getForce().x + force.x, graph[i]->getForce().y + force.y});
                graph[j]->setForce({graph[j]->getForce().x - force.x, graph[j]->getForce().y - force.y});
            }
            for (auto &edge : graph[i]->arrow) {
                int from = edge->getFrom();
                int to = edge->getTo();
                Vector2 force = ComputeAttractiveForce(graph[from], graph[to]);
                graph[from]->setForce({graph[from]->getForce().x - force.x, graph[from]->getForce().y - force.y});
                graph[to]->setForce({graph[to]->getForce().x + force.x, graph[to]->getForce().y + force.y});
            }
        }
        float temperature = 10.0f;
        for (auto &node : graph) {
            float newX = node->getPosition().x + node->getForce().x * temperature * deltaTime;
            float newY = node->getPosition().y + node->getForce().y * temperature * deltaTime;
            newX = std::max(X_min, std::min(newX, X_max));
            newY = std::max(Y_min, std::min(newY, Y_max));

            node->setPosition({newX, newY});
        }
        update();
        draw();
    }
}

void ShortestPath::Dijkstra(int startNode) {
    resetGraph();
    graph[startNode]->setCost(0);
    graph[startNode]->setKnown();
    int i = startNode;
    while (true) {
        int findSmall = -1;  
        int minCost = INT_MAX;
        for (auto edge : graph[i]->arrow) {
            int edgeWeight = edge->getWeight();
            int newCost = graph[i]->getCost() + edgeWeight;
            if (newCost < graph[i]->adj[edge->getTo()]->getCost()) {
                graph[i]->adj[edge->getTo()]->setCost(newCost);
            }
            if (!graph[i]->adj[edge->getTo()]->getKnown() && graph[i]->adj[edge->getTo()]->getCost() < minCost) {
                minCost = graph[i]->adj[edge->getTo()]->getCost();
                findSmall = graph[i]->adj[edge->getTo()]->getID();
            }
        }
        if (findSmall != -1) {
            i = findSmall;
            graph[i]->setKnown();
        } 
        else {
            findSmall = -1;
            minCost = INT_MAX;
            for (auto n : graph) {
                if (!n->getKnown() && n->getCost() < minCost) {
                    minCost = n->getCost();
                    findSmall = n->getID();
                }
            }
            if (findSmall == -1) break; 
            i = findSmall;
            graph[i]->setKnown();
        }
    }
}

Vector2 ShortestPath::ComputeRepulsiveForce(ShortestPathNode* &v, ShortestPathNode* &u) {
    Vector2 posU = u->getPosition(), posV = v->getPosition();
    Vector2 delta = { posV.x - posU.x, posV.y - posU.y };
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y) + 0.01f;
    float force = (k * k) / distance;
    return { (delta.x / distance) * force, (delta.y / distance) * force };
}

Vector2 ShortestPath::ComputeAttractiveForce(ShortestPathNode* &v, ShortestPathNode* &u) {
    Vector2 posU = u->getPosition(), posV = v->getPosition();
    Vector2 delta = { posV.x - posU.x, posV.y - posU.y };  
    float distance = sqrt(delta.x * delta.x + delta.y * delta.y) + 0.01f;
    float force = (distance * distance) / k;
    return { (delta.x / distance) * force, (delta.y / distance) * force };
}