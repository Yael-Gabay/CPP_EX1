//Yael Gabay
//322653411
//yael4231@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        bool isDirected;
        bool isWeighted;
        size_t vertices;
        size_t numberOfEdges;

        bool isSymmetric(const std::vector<std::vector<int>> &matrix) const;

    public:
        void loadGraph(const std::vector<std::vector<int>> &matrix);
        void printGraph() const;
        bool getIsDirected() const;
        bool getIsWeighted() const;
        size_t getNumberOfVertices() const;
        std::vector<int> getNeighbors(int vertex) const;
        int getEdgeWeight(int from, int to) const;
    };
}

#endif // GRAPH_HPP
