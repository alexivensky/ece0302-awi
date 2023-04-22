#ifndef _ADJACENCY_LIST_GRAPH_H_
#define _ADJACENCY_LIST_GRAPH_H_

#include "abstract_graph.hpp"
#include <map>
#include <set>
#include <vector>

template <typename LabelType>
class AdjacencyListGraph: public AbstractGraph<LabelType>
{
    public:

        AdjacencyListGraph();
        
        int getNumVertices() const;
        
        int getNumEdges() const;

        bool add(LabelType start, LabelType end);

        bool remove(LabelType start, LabelType end);

        void depthFirstTraversal(LabelType start, void visit(LabelType&));

        void breadthFirstTraversal(LabelType start, void visit(LabelType&));

    private:
        std::map< LabelType, std::set<LabelType> > adjList;
        int numEdges, numVertices;
        std::vector<LabelType> vertices;

  
};

#include "adjacency_list_graph.tpp"

#endif 
