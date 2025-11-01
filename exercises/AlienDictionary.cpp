#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <iostream>

class Solution
{
public :
    std::string foreignDictionary(std::vector<std::string> words)
    {
        if (words.empty())
        {
            return "";
        }

        AdjacencyList_t adjList;

        // build adjacency list with all dependencies
        for (int n = 0; n < words.size() - 1; ++n)
        {
            int n2 = 0;
            int n3 = 0;

            while (n2 < words[n].size()
                   && n3 < words[n + 1].size()
                   && words[n][n2] == words[n + 1][n3])
            {
                adjList.emplace(words[n][n2], Vertices_t{});
                ++n2;
                ++n3;
            }

            if (n2 >= words[n].size()
                && n3 >= words[n + 1].size())
            {
                continue;
            }

            if (n2 < words[n].size()
                && n3 < words[n + 1].size())
            {
                adjList[words[n][n2++]].emplace(words[n + 1][n3]);
                adjList.emplace(words[n + 1][n3++], Vertices_t{});
            }

            while (n2 < words[n].size())
            {
                adjList.emplace(words[n][n2++], Vertices_t{});
            }

            while (n3 < words[n + 1].size())
            {
                adjList.emplace(words[n + 1][n3++], Vertices_t{});
            }
        }

        Vertices_t visited;
        std::stack<Vertex_t> stack;

        for (const auto& [vertex, _] : adjList)
        {
            if (!dfs(adjList, vertex, visited, stack, {}))
            {
                return "";
            }
        }

        /* topologically sorted after every elements
           from stack is pushed in 'order' */
        std::string order;

        order.reserve(stack.size());

        while (!stack.empty())
        {
            order.push_back(stack.top());
            stack.pop();
        }

        return order;
    }

private :
    using Vertex_t = char;
    using Vertices_t = std::unordered_set<Vertex_t>;

    // DAG (= Directed Acyclic Graph) representation
    using AdjacencyList_t = std::unordered_map<Vertex_t, Vertices_t>;

    // cycle in graph if dfs() return false
    [[nodiscard]]
    bool dfs(const AdjacencyList_t& adjList,
             Vertex_t vertex,
             Vertices_t& visited,
             std::stack<Vertex_t>& stack,
             const Vertices_t& currentPath) const
    {
        if (visited.find(vertex) != visited.cend())
        {
            return true;
        }
        else if (currentPath.find(vertex) != visited.cend())
        {
            return false;
        }

        for (auto vertex2 : adjList.at(vertex))
        {
            Vertices_t currentPath2 = currentPath;

            currentPath2.emplace(vertex);

            if (!dfs(adjList, vertex2, visited, stack, currentPath2))
            {
                return false;
            }
        }

        visited.emplace(vertex);
        stack.emplace(vertex);

        return true;
    }
};

int main()
{
    std::cout << Solution().foreignDictionary(
        {"z", "o"})
              << '\n';
    std::cout << Solution().foreignDictionary(
        {"hrn", "hrf", "er", "enn", "rfnn"})
              << '\n';
    std::cout << Solution().foreignDictionary(
        {"baa", "abcd", "abca", "cab", "cad"})
              << '\n';
    std::cout << Solution().foreignDictionary(
        {"caa", "aaa", "aab"})
              << '\n';
    std::cout << Solution().foreignDictionary(
        {"wrt", "wrf", "er", "ett", "rftt"})
              << '\n';

    return 0;
}
