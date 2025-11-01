#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

// Definition for a Node.
class Node
{
public:
    int val;
    std::vector<Node *> neighbors;

    Node()
    {
        val = 0;
        neighbors = std::vector<Node *>();
    }

    Node(int _val)
    {
        val = _val;
        neighbors = std::vector<Node *>();
    }

    Node(int _val, std::vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public :
    Node *cloneGraph(Node *node)
    {
        if (!node)
        {
            return nullptr;
        }

        std::unordered_set<const Node *> visitedNodes;
        std::unordered_map<int, Node *> visitedNodesCopy;
        Node *copy = new Node(node->val);

        cloneGraph(visitedNodes, visitedNodesCopy, node, copy);

        return copy;
    }

private :
    void cloneGraph(
        std::unordered_set<const Node *>& visitedNodes,
        std::unordered_map<int, Node *>& visitedNodesCopy,
        const Node *node,
        Node *copy) const
    {
        if (visitedNodes.find(node) != visitedNodes.cend())
        {
            return;
        }

        visitedNodes.emplace(node);
        visitedNodesCopy.emplace(copy->val, copy);

        if (node->neighbors.empty())
        {
            return;
        }

        for (const auto *neighbor : node->neighbors)
        {
            Node *neighborCopy = nullptr;

            if (auto it = visitedNodesCopy.find(neighbor->val);
                it != visitedNodesCopy.cend())
            {
                neighborCopy = it->second;
            }
            else
            {
                neighborCopy = new Node(neighbor->val);
            }

            copy->neighbors.emplace_back(neighborCopy);
            cloneGraph(
                visitedNodes, visitedNodesCopy, neighbor, neighborCopy);
        }
    }
};

void check(
    const Node *node, std::vector<std::vector<int>> expected)
{
    struct
    {
        void operator()(
            std::unordered_set<const Node *>& visitedNodes,
            const Node *node,
            const std::vector<std::vector<int>>& expected,
            int& n) const
        {
            if (visitedNodes.find(node) != visitedNodes.cend())
            {
                return;
            }

            visitedNodes.emplace(node);

            if (node->neighbors.empty())
            {
                return;
            }

            assert(n < expected.size());

            int n2 = 0;

            for (const auto neighbor : node->neighbors)
            {
                assert(n2 < expected[n].size());
                assert(neighbor->val == expected[n][n2++]);
            }

            assert(n2 == expected[n++].size());

            for (const auto neighbor : node->neighbors)
            {
                (*this)(visitedNodes, neighbor, expected, n);
            }
        }
    } inner;

    std::unordered_set<const Node *> visitedNodes;
    int n = 0;

    inner(visitedNodes, node, expected, n);
    assert(n == expected.size());
}

int main()
{
    {
        Node *node = new Node(1);
        Node *node2 = new Node(2);
        Node *node3 = new Node(3);
        Node *node4 = new Node(4);

        node->neighbors.emplace_back(node2);
        node->neighbors.emplace_back(node4);

        node2->neighbors.emplace_back(node);
        node2->neighbors.emplace_back(node3);

        node3->neighbors.emplace_back(node2);
        node3->neighbors.emplace_back(node4);

        node4->neighbors.emplace_back(node);
        node4->neighbors.emplace_back(node3);

        check(Solution().cloneGraph(node),
              {{2, 4}, {1, 3}, {2, 4}, {1, 3}});

    }

    {
        check(Solution().cloneGraph(new Node(1)), {});
    }

    return 0;
}
