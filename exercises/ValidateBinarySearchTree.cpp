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
    bool isValidBST(TreeNode *root) noexcept
    {
        if (!root)
        {
            return true;
        }

        if ((root->left && root->left->value >= root->value)
            || (root->right && root->right->value <= root->value))
        {
            return false;
        }

        return isValidBST(root->left) && isValidBST(root->right);
    }
};

int main()
{
    std::cout << std::boolalpha;

    {
        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);
        root->right = new TreeNode(3);

        std::cout << Solution().isValidBST(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(1);
        root->right = new TreeNode(4);

        root->right->left = new TreeNode(3);
        root->right->right = new TreeNode(6);

        std::cout << Solution().isValidBST(root) << '\n';
    }

    return 0;
}
