#include <queue>
#include <cassert>

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

        assert(Solution().kthSmallest(root, 1) == 1);
    }

    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(3);
        root->right = new TreeNode(6);
        root->left->left = new TreeNode(2);
        root->left->right = new TreeNode(4);
        root->left->left->left = new TreeNode(1);

        assert(Solution().kthSmallest(root, 3) == 3);
    }

    {
        TreeNode *root = new TreeNode(8);

        root->left = new TreeNode(3);
        root->right = new TreeNode(10);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(6);
        root->left->right->left = new TreeNode(4);
        root->left->right->right = new TreeNode(7);

        assert(Solution().kthSmallest(root, 4) == 6);
    }

    {
        TreeNode *root = new TreeNode(15);

        root->left = new TreeNode(5);
        root->right = new TreeNode(20);
        root->left->left = new TreeNode(3);
        root->left->right = new TreeNode(7);
        root->left->right->left = new TreeNode(6);

        assert(Solution().kthSmallest(root, 2) == 5);
    }

    {
        TreeNode *root = new TreeNode(4);

        root->left = new TreeNode(2);
        root->right = new TreeNode(6);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(3);

        assert(Solution().kthSmallest(root, 5) == 6);
    }

    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);

        assert(Solution().kthSmallest(root, 3) == 3);
    }


    return 0;
}
