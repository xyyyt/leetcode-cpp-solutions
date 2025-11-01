#include <algorithm>
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
    int maxDepth(TreeNode *root)
    {
        return (root) ?
            1 + std::max(maxDepth(root->left), maxDepth(root->right)) : 0;
    }
};

int main()
{
    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(9);
        root->right = new TreeNode(20);
        root->right->left = new TreeNode(15);
        root->right->right = new TreeNode(7);

        assert(Solution().maxDepth(root) == 3);
    }

    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);

        assert(Solution().maxDepth(root) == 2);
    }

    {
        TreeNode *root = new TreeNode(10);

        root->left = new TreeNode(5);
        root->right = new TreeNode(15);
        root->left->left = new TreeNode(3);

        assert(Solution().maxDepth(root) == 3);
    }

    {
        TreeNode *root = new TreeNode(7);

        root->left = new TreeNode(4);

        assert(Solution().maxDepth(root) == 2);
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->left->left = new TreeNode(3);
        root->left->left->left = new TreeNode(4);

        assert(Solution().maxDepth(root) == 4);
    }

    {
        TreeNode *root = new TreeNode(8);

        assert(Solution().maxDepth(root) == 1);
    }

    {
        assert(Solution().maxDepth(nullptr) == 0);
    }

    return 0;
}
