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
    TreeNode *invertTree(TreeNode *root)
    {
        if (!root)
        {
            return nullptr;
        }

        std::swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};

std::ostream& operator<<(
    std::ostream& os, const TreeNode *root) noexcept
{
    if (!root)
    {
        os << "EMPTY";

        return os;
    }

    struct
    {
        std::ostream& os;

        void operator()(const TreeNode *node) const noexcept
        {
            if (!node)
            {
                return;
            }

            std::cout << ", " << node->val;
            (*this)(node->left);
            (*this)(node->right);
        }
    } traverseTree{os};

    std::cout << root->val;
    traverseTree(root->left);
    traverseTree(root->right);

    return os;
}

int main()
{
    {
        TreeNode *root = new TreeNode(4);

        root->left = new TreeNode(2);
        root->right = new TreeNode(7);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(3);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(9);

        std::cout << Solution().invertTree(root) << '\n';
    }

    {
        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);
        root->right = new TreeNode(3);

        std::cout << Solution().invertTree(root) << '\n';
    }

    {
        std::cout << Solution().invertTree(nullptr) << '\n';
    }

    return 0;
}
