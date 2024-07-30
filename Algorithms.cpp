//Yael Gabay
//322653411
//yael4231@gmail.com
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <functional>

using namespace std;

namespace ariel {

    int Algorithms::isConnected(const Graph& g) {
        vector<bool> visited(g.getNumberOfVertices(), false);
        size_t count = 0;
        
        function<void(size_t)> dfs = [&](size_t v) {
            visited[v] = true;
            ++count;
            for (int neighbor : g.getNeighbors(v)) { // Treat as int and cast if needed
                size_t neighbor_size = static_cast<size_t>(neighbor); // Explicit conversion
                if (!visited[neighbor_size]) {
                    dfs(neighbor_size);
                }
            }
        };

        dfs(0); // start DFS from node 0
        
        return count == g.getNumberOfVertices() ? 1 : 0;
    }

    std::string Algorithms::shortestPath(const Graph& g, size_t start, size_t end) {
        if (start == end) return std::to_string(start);

        vector<size_t> dist(g.getNumberOfVertices(), numeric_limits<size_t>::max());
        vector<size_t> prev(g.getNumberOfVertices(), numeric_limits<size_t>::max());
        queue<size_t> q;
        
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            size_t u = q.front();
            q.pop();

            for (int v : g.getNeighbors(u)) { // Treat as int and cast if needed
                size_t v_size = static_cast<size_t>(v); // Explicit conversion
                if (dist[v_size] == numeric_limits<size_t>::max()) {
                    dist[v_size] = dist[u] + 1;
                    prev[v_size] = u;
                    q.push(v_size);
                }
            }
        }

        if (dist[end] == numeric_limits<size_t>::max()) return "-1";

        std::string path;
        for (size_t at = end; at != numeric_limits<size_t>::max(); at = prev[at]) {
            path = std::to_string(at) + (path.empty() ? "" : "->") + path;
        }
        return path;
    }

    int Algorithms::isContainsCycle(const Graph& g) {
        vector<bool> visited(g.getNumberOfVertices(), false);
        
        function<bool(size_t, size_t)> dfs = [&](size_t v, size_t parent) {
            visited[v] = true;
            for (int neighbor : g.getNeighbors(v)) { // Treat as int and cast if needed
                size_t neighbor_size = static_cast<size_t>(neighbor); // Explicit conversion
                if (!visited[neighbor_size]) {
                    if (dfs(neighbor_size, v)) {
                        return true;
                    }
                } else if (neighbor_size != parent) {
                    return true;
                }
            }
            return false;
        };

        for (size_t i = 0; i < g.getNumberOfVertices(); ++i) {
            if (!visited[i] && dfs(i, numeric_limits<size_t>::max())) {
                return 1; // Cycle detected
            }
        }
        return 0; // No cycle detected
    }

    std::string Algorithms::isBipartite(const Graph& g) {
        vector<int> color(g.getNumberOfVertices(), -1);

        function<bool(size_t)> bfs = [&](size_t start) {
            queue<size_t> q;
            color[start] = 0;
            q.push(start);
            
            while (!q.empty()) {
                size_t u = q.front();
                q.pop();
                for (int v : g.getNeighbors(u)) { // Treat as int and cast if needed
                    size_t v_size = static_cast<size_t>(v); // Explicit conversion
                    if (color[v_size] == -1) {
                        color[v_size] = 1 - color[u];
                        q.push(v_size);
                    } else if (color[v_size] == color[u]) {
                        return false;
                    }
                }
            }
            return true;
        };

        for (size_t i = 0; i < g.getNumberOfVertices(); ++i) {
            if (color[i] == -1 && !bfs(i)) {
                return "0";
            }
        }

        vector<size_t> setA, setB;
        for (size_t i = 0; i < g.getNumberOfVertices(); ++i) {
            if (color[i] == 0) {
                setA.push_back(i);
            } else {
                setB.push_back(i);
            }
        }

        std::string result = "The graph is bipartite: A={";
        for (size_t i : setA) result += std::to_string(i) + ", ";
        if (!setA.empty()) result.pop_back(), result.pop_back(); // Remove last comma and space
        result += "}, B={";
        for (size_t i : setB) result += std::to_string(i) + ", ";
        if (!setB.empty()) result.pop_back(), result.pop_back(); // Remove last comma and space
        result += "}";

        return result;
    }

    void Algorithms::negativeCycle(const Graph& g) {
        size_t V = g.getNumberOfVertices();
        vector<int> dist(V, numeric_limits<int>::max());

        // Bellman-Ford algorithm
        dist[0] = 0;

        // Relax all edges |V| - 1 times
        for (size_t i = 1; i <= V - 1; ++i) {
            for (size_t u = 0; u < V; ++u) {
                for (int v : g.getNeighbors(u)) {
                    size_t v_size = static_cast<size_t>(v); // Explicit conversion
                    if (dist[u] != numeric_limits<int>::max() && dist[u] + 1 < dist[v_size]) {
                        dist[v_size] = dist[u] + 1;
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (size_t u = 0; u < V; ++u) {
            for (int v : g.getNeighbors(u)) {
                size_t v_size = static_cast<size_t>(v); // Explicit conversion
                if (dist[u] != numeric_limits<int>::max() && dist[u] + 1 < dist[v_size]) {
                    cout << "Graph contains a negative-weight cycle." << endl;
                    return;
                }
            }
        }

        cout << "No negative cycle detected." << endl;
    }

}
