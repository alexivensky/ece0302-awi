#include "adjacency_list_graph.hpp"
#include <algorithm>

template <typename LabelType>
AdjacencyListGraph<LabelType>::AdjacencyListGraph() { 
    numEdges = 0;
    numVertices = 0;
}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumVertices() const {
    return vertices.size();
}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumEdges() const {
    return numEdges;
}
        
template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::add(LabelType start, LabelType end) {
 //if unconnected, do not allow add
    if (adjList.size() != 0 && adjList.find(start) == adjList.end() && adjList.find(end) == adjList.end()) {
        return false;
    }

    //check if start vertex exists
    if (adjList.find(start) == adjList.end()) {
        std::set<LabelType> newSet;
        adjList.insert({start, newSet});
    }
    //check if end vertex exists
    if (adjList.find(end) == adjList.end()) {
        std::set<LabelType> newSet;
        adjList.insert({end, newSet});
    }

    //if start / end combo already exists, return false
    if (adjList[start].find(end) != adjList[start].end() || adjList[end].find(start) != adjList[end].end()) {
        return false;
    }

    //add combo
    adjList[start].insert(end);
    adjList[end].insert(start);
    if (!std::count(vertices.begin(), vertices.end(), start)) {
        vertices.push_back(start);
    }
    if (!std::count(vertices.begin(), vertices.end(), end)) {
        vertices.push_back(end);
    }
    
    numEdges++;

    return true;
}   

template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::remove(LabelType start, LabelType end) {
   

    //if start doesnt exist, return false
    if (adjList.find(start) == adjList.end()) {
        return false;
    }
    //if end doesn't exist in start, return false
    if (adjList[start].find(end) == adjList[start].end()) {
        return false;
    }
    //now it is confirmed that start / end combo exists, and it is safe to assume that both directions are accounted for,
    //so we will not check.

    adjList[start].erase(end);
    adjList[end].erase(start);
    numEdges--;

    if (adjList[start].size() == 0) {
        adjList.erase(start);
        vertices.erase(std::find(vertices.begin(), vertices.end(), start));
    }
    if (adjList[end].size() == 0) {
        adjList.erase(end);
        vertices.erase(std::find(vertices.begin(), vertices.end(), end));
    }

    return true;
}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}