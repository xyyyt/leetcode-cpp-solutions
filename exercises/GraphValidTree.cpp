#include <vector>
#include <unordered_set>
#include <iostream>

class Solution
{
public :
    bool validTree(int n, std::vector<std::vector<int>> edges)
    {
        if (edges.empty())
        {
            return false;
        }

        for (int n = 0; n < edges.size(); ++n)
        {
            if (!validTree(edges, {}, edges[n][0], edges[n][1], n))
            {
                return false;
            }
        }

        return true;
    }

private :
    [[nodiscard]]
    bool validTree(
        const std::vector<std::vector<int>>& edges,
        const std::unordered_set<int>& visitedNodes,
        int currentNode,
        int neighborNode,
        int n) const
    {
        if (visitedNodes.find(currentNode) != visitedNodes.cend())
        {
            return false;
        }

        for (int n2 = 0; n2 < edges.size(); ++n2)
        {
            if (n2 == n)
            {
                continue;
            }

            for (int n3 = 0; n3 < edges[n2].size(); ++n3)
            {
                if (edges[n2][n3] == neighborNode)
                {
                    std::unordered_set<int> visitedNodes2(
                        visitedNodes.cbegin(), visitedNodes.cend());
                    int currentNode2 = edges[n2][n3];
                    int neighborNodes2 = edges[n2][(n3 == 0) ? 1 : 0];

                    visitedNodes2.emplace(currentNode);

                    if (!validTree(
                        edges,
                        visitedNodes2,
                        currentNode2,
                        neighborNodes2,
                        n2))
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().validTree(
        5, {{0, 1}, {0, 2}, {0, 3}, {1, 4}})
              << '\n';
    std::cout << Solution().validTree(
        5, {{0, 1}, {1, 2}, {2, 3}, {1, 3}, {1, 4}})
              << '\n';

    return 0;
}
