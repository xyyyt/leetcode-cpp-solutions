#include <vector>
#include <unordered_set>
#include <iostream>

class Solution
{
public :
    int countComponents(std::vector<std::vector<int>> edges)
    {
        if (edges.empty())
        {
            return 0;
        }

        std::unordered_set<int> visitedEdges;
        int connectedComponentCounter = 0;

        for (int n = 0; n < edges.size(); ++n)
        {
            if (visitedEdges.find(n) == visitedEdges.cend())
            {
                visitedEdges.emplace(n);
                traverseConnectedComponent(edges, visitedEdges, n);
                ++connectedComponentCounter;
            }
        }

        return connectedComponentCounter;
    }

private :
    void traverseConnectedComponent(
        const std::vector<std::vector<int>>& edges,
        std::unordered_set<int>& visitedEdges,
        int pos) const
    {
        for (int n = 0; n < edges.size(); ++n)
        {
            if (n == pos || visitedEdges.find(n) != visitedEdges.cend())
            {
                continue;
            }

            if (edges[pos][0] == edges[n][0]
                || edges[pos][0] == edges[n][1]
                || edges[pos][1] == edges[n][0]
                || edges[pos][1] == edges[n][1])
            {
                visitedEdges.emplace(n);
                traverseConnectedComponent(edges, visitedEdges, n);
            }
        }
    }
};

int main()
{
    std::cout << Solution().countComponents(
        {{0, 1}, {0, 2}})
              << '\n';
    std::cout << Solution().countComponents(
        {{0, 1}, {1, 2}, {2, 3}, {4, 5}})
              << '\n';
    std::cout << Solution().countComponents(
        {{5, 3}, {5, 8}})
              << '\n';
    std::cout << Solution().countComponents(
        {{5, 3}, {8, 5}})
              << '\n';
    std::cout << Solution().countComponents(
        {{7, 4}, {4, 12}})
              << '\n';
    std::cout << Solution().countComponents(
        {{7, 4}, {12, 4}})
              << '\n';
    std::cout << Solution().countComponents(
        {{0, 1}, {2, 1}, {3, 4}})
              << '\n';
    std::cout << Solution().countComponents(
        {{0, 1}, {6, 0}, {2, 4}, {2, 3}, {3, 4}, {7, 5}})
              << '\n';

    return 0;
}
