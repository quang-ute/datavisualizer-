#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "ShortestPath/ShortestPathNode.h"

class ShortestPath{
    public:
        ShortestPath();
        ~ShortestPath();

        void createGraph(int numNodes, int edges);
        void addEdge(int node1, int node2);
        void removeEdge(int node1, int node2);
        void searchPath(int startNode, int endNode);
        void clearGraph();
        void resetGraph();
        void setWeighted();
        void deWeighted();
        void setDirected();
        void deDirected();
        
        void update();
        void draw();
        
        void Dijkstra(int startNode);
        void FruchtermanReingold();
        Vector2 ComputeRepulsiveForce(ShortestPathNode* &v, ShortestPathNode* &u);    
        Vector2 ComputeAttractiveForce(ShortestPathNode* &v, ShortestPathNode* &u);
        
    private:
        std::vector<ShortestPathNode*> graph;
        float k;
        bool isWeighted;
        bool isDirected;
};

#endif