#include <iostream>

struct TreeNode
{
    int value = 0;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    TreeNode() = default;
    TreeNode(int valuee) noexcept : value(valuee) { }

    TreeNode(int valuee, TreeNode *leftt, TreeNode *rightt) noexcept :
        value(valuee), left(leftt), right(rightt)
    { }
};

class Solution
{
public :
    bool hasPathSum(TreeNode *root, int targetSum) noexcept
    {
        return hasPathSum(root, targetSum, 0);
    }

private :
    [[nodiscard]]
    bool hasPathSum(TreeNode *root, int targetSum, int currentSum) noexcept
    {
        if (!root)
        {
            return false;
        }

        int sum = currentSum + root->value;

        if (sum == targetSum)
        {
            return true;
        }

        return hasPathSum(root->left, targetSum, sum)
            || hasPathSum(root->right, targetSum, sum);
    }
};

int main()
{
    std::cout << std::boolalpha;

    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(4);
        root->right = new TreeNode(8);

        root->left->left = new TreeNode(11);

        root->right->left = new TreeNode(13);
        root->right->right = new TreeNode(4);

        root->left->left->left = new TreeNode(7);
        root->left->left->right = new TreeNode(2);

        root->right->right->right = new TreeNode(1);

        std::cout << Solution().hasPathSum(root, 22) << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);

        std::cout << Solution().hasPathSum(root, 5) << '\n';
    }

    {
        std::cout << Solution().hasPathSum(nullptr, 0) << '\n';
    }

    return 0;
}
