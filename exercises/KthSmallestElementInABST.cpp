#include <queue>
#include <iostream>

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) { }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }

    TreeNode(int x, TreeNode *left, TreeNode *right) :
        val(x), left(left), right(right)
    { }
};

class Solution
{
public:
    int kthSmallest(TreeNode *root, int k)
    {
        if (!root)
        {
            return -1;
        }

        PQueue_t pQueue;

        kthSmallest(root, pQueue);

        if (pQueue.size() < k)
        {
            return -1;
        }

        int smallest = 0;

        for (int n = 0; n < k && !pQueue.empty(); ++n)
        {
            smallest = pQueue.top();
            pQueue.pop();
        }

        return smallest;
    }

private :
    using PQueue_t = std::priority_queue<
        int, std::vector<int>, std::greater<int>>;

    void kthSmallest(
        const TreeNode *node, PQueue_t& pQueue) const
    {
        if (!node)
        {
            return;
        }

        kthSmallest(node->left, pQueue);
        pQueue.emplace(node->val);
        kthSmallest(node->right, pQueue);
    }
};

int main()
{
    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(1);
        root->right = new TreeNode(4);
        root->left->right = new TreeNode(2);

        std::cout << Solution().kthSmallest(root, 1) << '\n';
    }

    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(3);
        root->right = new TreeNode(6);
        root->left->left = new TreeNode(2);
        root->left->right = new TreeNode(4);
        root->left->left->left = new TreeNode(1);

        std::cout << Solution().kthSmallest(root, 3) << '\n';
    }

    return 0;
}
