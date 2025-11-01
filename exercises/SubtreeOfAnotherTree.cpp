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
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if (!root || !subRoot)
        {
            return false;
        }

        if (root->val == subRoot->val
            && compareTree(root, subRoot))
        {
            return true;
        }

        return isSubtree(root->left, subRoot)
            || isSubtree(root->right, subRoot);
    }

private :
    [[nodiscard]]
    bool compareTree(
        TreeNode *root, TreeNode *subRoot) const noexcept
    {
        if (!root && !subRoot)
        {
            return true;
        }
        else if ((!root || !subRoot)
                 || (root->val != subRoot->val))
        {
            return false;
        }

        return compareTree(root->left, subRoot->left)
            && compareTree(root->right, subRoot->right);
    }
};

int main()
{
    std::cout << std::boolalpha;

    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(4);
        root->right = new TreeNode(5);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(2);

        TreeNode *subRoot = new TreeNode(4);

        subRoot->left = new TreeNode(1);
        subRoot->right = new TreeNode(2);

        std::cout << Solution().isSubtree(root, subRoot) << '\n';
    }

    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(4);
        root->right = new TreeNode(5);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(2);
        root->left->right->left = new TreeNode(0);

        TreeNode *subRoot = new TreeNode(4);

        subRoot->left = new TreeNode(1);
        subRoot->right = new TreeNode(2);

        std::cout << Solution().isSubtree(root, subRoot) << '\n';
    }

    return 0;
}
