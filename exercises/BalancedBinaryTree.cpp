#include <iostream>

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
public :
    bool isBalanced(TreeNode *root)
    {
        if (!root)
        {
            return true;
        }

        int balanceFactor = maxHeight(root->left) - maxHeight(root->right);

        return !(balanceFactor < -1 || balanceFactor > 1);
    }

private :
    [[nodiscard]]
    int maxHeight(TreeNode *node) const noexcept
    {
        return (node) ?
            1 + std::max(maxHeight(node->left), maxHeight(node->right)) : 0;
    }
};

int main()
{
    std::cout << std::boolalpha;

    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(9);
        root->right = new TreeNode(20);
        root->right->left = new TreeNode(15);
        root->right->right = new TreeNode(7);

        std::cout << Solution().isBalanced(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(2);
        root->left->left = new TreeNode(3);
        root->left->right = new TreeNode(3);
        root->left->left->left = new TreeNode(4);
        root->left->left->right = new TreeNode(4);

        std::cout << Solution().isBalanced(root) << '\n';
    }

    {
        std::cout << Solution().isBalanced(nullptr) << '\n';
    }

    return 0;
}
