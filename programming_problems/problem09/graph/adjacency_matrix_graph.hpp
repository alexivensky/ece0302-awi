#ifndef _ADJACENCY_MATRIX_GRAPH_H_
#define _ADJACENCY_MATRIX_GRAPH_H_

#include "abstract_graph.hpp"
#include <set>
#include <map>
#include <algorithm>

template <typename LabelType>
class AdjacencyMatrixGraph: public AbstractGraph<LabelType>
{
    public:

        AdjacencyMatrixGraph();

        int getNumVertices() const;
        
        int getNumEdges() const;

        bool add(LabelType start, LabelType end);

        bool remove(LabelType start, LabelType end);

        void depthFirstTraversal(LabelType start, void visit(LabelType&));

        void breadthFirstTraversal(LabelType start, void visit(LabelType&));

    private:

        std::vector<std::vector<bool> > adjMatrix;
        std::vector<LabelType> vertices;
        int numEdges;        
  
};

#include "adjacency_matrix_graph.tpp"

#endif 
