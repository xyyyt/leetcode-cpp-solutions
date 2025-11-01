#include <iostream>
#include <vector>

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
    TreeNode *mergeTrees(TreeNode *root, TreeNode *root2)
    {
        if (!root && !root2)
        {
            return nullptr;
        }

        int nodesSum = 0;

        if (root)
        {
            nodesSum += root->value;
        }

        if (root2)
        {
            nodesSum += root2->value;
        }

        TreeNode *root3 = new TreeNode(nodesSum);

        root3->left = mergeTrees(
            (root) ? root->left : nullptr,
            (root2) ? root2->left : nullptr);
        root3->right = mergeTrees(
            (root) ? root->right : nullptr,
            (root2) ? root2->right : nullptr);

        return root3;
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

            std::cout << ", " << node->value;
            (*this)(node->left);
            (*this)(node->right);
        }
    } traverseTree{os};

    std::cout << root->value;
    traverseTree(root->left);
    traverseTree(root->right);

    return os;
}

int main()
{
    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(3);
        root->right = new TreeNode(2);

        root->left->left = new TreeNode(5);

        TreeNode *root2 = new TreeNode(2);

        root2->left = new TreeNode(1);
        root2->right = new TreeNode(3);

        root2->left->right = new TreeNode(4);

        root2->right->right = new TreeNode(7);

        std::cout << Solution().mergeTrees(root, root2) << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);
        TreeNode *root2 = new TreeNode(1);

        root2->left = new TreeNode(2);

        std::cout << Solution().mergeTrees(root, root2) << '\n';
    }

    return 0;
}
