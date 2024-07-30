//Yael Gabay
//322653411
//yael4231@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstddef>  // Include this header for size_t
#include <queue>
#include <climits> // For INT_MAX

using namespace std;

namespace ariel {
    bool Graph::isSymmetric(const std::vector<std::vector<int>> &matrix) const {
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix) {
        if (matrix.empty() || matrix.size() != matrix[0].size()) {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        this->isDirected = !isSymmetric(matrix);

        this->isWeighted = false;
        for (const auto &row : matrix) {
            for (int weight : row) {
                if (weight != 0 && weight != 1) {
                    this->isWeighted = true;
                    break;
                }
            }
            if (this->isWeighted) {
                break;
            }
        }

        this->adjacencyMatrix = matrix;
        this->vertices = matrix.size();
        this->numberOfEdges = 0;

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                if (this->adjacencyMatrix[i][j] != 0) {
                    this->numberOfEdges++;
                }
            }
        }

        if (!this->isDirected) {
            this->numberOfEdges /= 2;
        }
    }

    void Graph::printGraph() const {
        cout << "The graph is "
             << (this->isDirected ? "directed" : "undirected") << ", "
             << (this->isWeighted ? "weighted" : "unweighted") << ", "
             << "with " << this->vertices << " vertices and "
             << this->numberOfEdges << " edges." << endl;

        for (const auto &row : adjacencyMatrix) {
            for (const auto &element : row) {
                cout << element << ' ';
            }
            cout << '\n';
        }
    }

    bool Graph::getIsDirected() const {
        return this->isDirected;
    }

    bool Graph::getIsWeighted() const {
        return this->isWeighted;
    }

    size_t Graph::getNumberOfVertices() const {
        return this->vertices;
    }

    std::vector<int> Graph::getNeighbors(int vertex) const {
        std::vector<int> neighbors;
        if (vertex >= 0 && static_cast<size_t>(vertex) < this->vertices) {
            for (size_t i = 0; i < this->adjacencyMatrix[static_cast<size_t>(vertex)].size(); ++i) {
                if (this->adjacencyMatrix[static_cast<size_t>(vertex)][i] != 0) {
                    neighbors.push_back(static_cast<int>(i));
                }
            }
        }
        return neighbors;
    }

    int Graph::getEdgeWeight(int from, int to) const {
        if (from >= 0 && static_cast<size_t>(from) < this->vertices &&
            to >= 0 && static_cast<size_t>(to) < this->vertices) {
            return this->adjacencyMatrix[static_cast<size_t>(from)][static_cast<size_t>(to)];
        }
        return -1; // Invalid edge
    }
}
