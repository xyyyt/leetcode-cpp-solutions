#include <algorithm>
#include <limits>
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
    int maxPathSum(TreeNode *root)
    {
        constexpr int MIN_VALUE = std::numeric_limits<int>::min();

        if (!root)
        {
            return MIN_VALUE;
        }

        int bestPathSum = MIN_VALUE;

        maxPathSum(root, bestPathSum);

        return bestPathSum;
    }

private :
    int maxPathSum(TreeNode *node, int& bestPathSum) const noexcept
    {
        if (!node)
        {
            return 0;
        }

        int leftBestPathSum = maxPathSum(node->left, bestPathSum);
        int rightBestPathSum = maxPathSum(node->right, bestPathSum);
        int bestPathSum2 = std::max({
            node->val,
            node->val + leftBestPathSum,
            node->val + rightBestPathSum,
            node->val + leftBestPathSum + rightBestPathSum});

        bestPathSum = std::max(bestPathSum, bestPathSum2);

        return bestPathSum2;
    }
};

int main()
{
    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);

        std::cout << Solution().maxPathSum(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(-10);

        root->left = new TreeNode(9);
        root->right = new TreeNode(20);
        root->right->left = new TreeNode(15);
        root->right->right = new TreeNode(7);

        std::cout << Solution().maxPathSum(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(10);

        root->left = new TreeNode(2);
        root->right = new TreeNode(10);
        root->left->left = new TreeNode(20);
        root->left->right = new TreeNode(1);
        root->right->right = new TreeNode(-25);
        root->right->right->left = new TreeNode(3);
        root->right->right->right = new TreeNode(4);

        std::cout << Solution().maxPathSum(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(-17);

        root->left = new TreeNode(11);
        root->right = new TreeNode(4);
        root->left->left = new TreeNode(20);
        root->left->right = new TreeNode(-2);
        root->right->left = new TreeNode(10);

        std::cout << Solution().maxPathSum(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(25);

        root->right = new TreeNode(37);
        root->right->left = new TreeNode(62);
        root->right->left->left = new TreeNode(7);
        root->right->left->right = new TreeNode(-32);
        root->right->left->right->left = new TreeNode(345);

        std::cout << Solution().maxPathSum(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(32);

        root->left = new TreeNode(-54);
        root->left->right = new TreeNode(-1);
        root->left->right->left = new TreeNode(85);

        std::cout << Solution().maxPathSum(root) << '\n';
    }

    {
        std::cout << Solution().maxPathSum(new TreeNode(18)) << '\n';
    }

    return 0;
}
