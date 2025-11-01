#include <cassert>

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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        return hasPathSum(root, targetSum, 0);
    }

private :
    [[nodiscard]]
    bool hasPathSum(
        TreeNode *root, int targetSum, int currentSum) const noexcept
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

        assert(Solution().hasPathSum(root, 22));
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);

        assert(!Solution().hasPathSum(root, 5));
    }

    {
        TreeNode *root = new TreeNode(10);

        root->left = new TreeNode(5);
        root->right = new TreeNode(12);

        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(7);

        assert(Solution().hasPathSum(root, 22));
    }

    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(1);
        root->right = new TreeNode(2);

        assert(!Solution().hasPathSum(root, 6));
    }

    {
        TreeNode *root = new TreeNode(8);

        root->left = new TreeNode(3);
        root->left->left = new TreeNode(1);

        assert(Solution().hasPathSum(root, 12));
    }

    {
        TreeNode *root = new TreeNode(4);

        root->right = new TreeNode(9);
        root->right->right = new TreeNode(11);

        assert(!Solution().hasPathSum(root, 10));
    }

    {
        assert(!Solution().hasPathSum(nullptr, 0));
    }

    return 0;
}
