#include "adjacency_matrix_graph.hpp"


template <typename LabelType>
AdjacencyMatrixGraph<LabelType>::AdjacencyMatrixGraph() {
    numEdges = 0;
}

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumVertices() const { return vertices.size(); }

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumEdges() const { return numEdges; }
        
template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::add(LabelType start, LabelType end) {
    if (vertices.size()!=0 && !std::count(vertices.begin(), vertices.end(), start) && !std::count(vertices.begin(), vertices.end(), end)) {
        return false;
    }
    //resizing matrix
    if (!std::count(vertices.begin(), vertices.end(), start)) {
        vertices.push_back(start);
        for (int i = 0; i < adjMatrix.size(); i++) {
            adjMatrix[i].push_back(0);
        }
        std::vector<bool> newRow;
        newRow.resize(vertices.size(), 0);
        adjMatrix.push_back(newRow);
    }
    if (!std::count(vertices.begin(), vertices.end(), end)) {
        vertices.push_back(end);
        for (int i = 0; i < adjMatrix.size(); i++) {
            adjMatrix[i].push_back(0);
        }
        std::vector<bool> newRow;
        newRow.resize(vertices.size(), 0);
        adjMatrix.push_back(newRow); 
    }
    int startIdx, endIdx;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == start) {
            startIdx = i;
        }
        if (vertices[i] == end) {
            endIdx = i;
        }
    }
    if (adjMatrix[startIdx][endIdx] || adjMatrix[endIdx][startIdx]) {
        return false;
    }
    adjMatrix[startIdx][endIdx] = 1;
    adjMatrix[endIdx][startIdx] = 1;
    numEdges++;
    return true;
}   

template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::remove(LabelType start, LabelType end) {
    //if start or end don't exist, return false
    if (!std::count(vertices.begin(), vertices.end(), start) || !std::count(vertices.begin(), vertices.end(), end)) {
        return false;
    }
    int startIdx, endIdx;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == start) {
            startIdx = i;
        }
        if (vertices[i] == end) {
            endIdx = i;
        }
    }
    if (!adjMatrix[startIdx][endIdx] || !adjMatrix[endIdx][startIdx]) {
        return false;
    }
    adjMatrix[startIdx][endIdx] = 0;
    adjMatrix[endIdx][startIdx] = 0;
    numEdges--;

    //check to see if start has no connections
    bool empty = 1;
    for (int i = 0; i < adjMatrix[startIdx].size(); i++) {
        if (adjMatrix[startIdx][i]) {
            empty = 0;
        }
    }
    if (empty) {
        for (int i = 0; i < adjMatrix.size(); i++) {
            adjMatrix[i].erase(adjMatrix[i].begin() + startIdx);
        }
        adjMatrix.erase(adjMatrix.begin() + startIdx);
        vertices.erase(std::find(vertices.begin(), vertices.end(), start));
    }
    //same for end
    empty = 1;
    for (int i = 0; i < adjMatrix[endIdx].size(); i++) {
        if (adjMatrix[endIdx][i]) {
            empty = 0;
        }
    }
    if (empty) {
        for (int i = 0; i < adjMatrix.size(); i++) {
            adjMatrix[i].erase(adjMatrix[i].begin() + endIdx);
        }
        adjMatrix.erase(adjMatrix.begin() + endIdx-1);
        vertices.erase(std::find(vertices.begin(), vertices.end(), end));
    }

    return true;
}

template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}