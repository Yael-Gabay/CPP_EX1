//Yael Gabay
//322653411
//yael4231@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel {
    class Algorithms {
    public:
        static int isConnected(const Graph& g);
        static std::string shortestPath(const Graph& g, size_t start, size_t end);
        static int isContainsCycle(const Graph& g);
        static std::string isBipartite(const Graph& g);
        static void negativeCycle(const Graph& g);
    };
}

#endif // ALGORITHMS_HPP
