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
    TreeNode *balanceBST(TreeNode *root) { return _balanceBST(root); }

private :
    [[nodiscard]]
    TreeNode *_balanceBST(TreeNode *node) const noexcept
    {
        if (!node)
        {
            return nullptr;
        }

        node->left = _balanceBST(node->left);
        node->right = _balanceBST(node->right);

        int balanceFactor = maxHeight(node->left) - maxHeight(node->right);

        if (balanceFactor > 1)
        {
            if (!node->left->left && node->left->right)
            {
                node->left = leftRotation(node->left);
            }

            return rightRotation(node);
        }
        else if (balanceFactor < -1)
        {
            if (!node->right->right && node->right->left)
            {
                node->right = rightRotation(node->right);
            }

            return leftRotation(node);
        }
        else
        {
            return node;
        }
    }

    [[nodiscard]]
    int maxHeight(TreeNode *node) const noexcept
    {
        return (node) ?
            1 + std::max(maxHeight(node->left), maxHeight(node->right)) : 0;
    }

    [[nodiscard]]
    TreeNode *leftRotation(TreeNode *node) const noexcept
    {
        TreeNode *pivot = node->right;
        TreeNode *leftPivot = pivot->left;

        pivot->left = node;
        node->right = leftPivot;

        return pivot;
    }

    [[nodiscard]]
    TreeNode *rightRotation(TreeNode *node) const noexcept
    {
        TreeNode *pivot = node->left;
        TreeNode *rightPivot = pivot->right;

        pivot->right = node;
        node->left = rightPivot;

        return pivot;
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
    // Right Right Case (Left Rotation) + Right Right Case (Left Rotation)
    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);
        root->right->right->right = new TreeNode(4);
        std::cout << Solution().balanceBST(root) << '\n';
    }

    // Left Left Case (Right Rotation) + Left Left Case (Right Rotation)
    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->left->left = new TreeNode(3);
        root->left->left->left = new TreeNode(4);
        std::cout << Solution().balanceBST(root) << '\n';
    }

    // Left Right Case (Left rotation + Right rotation)
    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(3);
        root->left->right = new TreeNode(4);
        std::cout << Solution().balanceBST(root) << '\n';
    }

    // Right Left Case (Right rotation + Left rotation)
    {
        TreeNode *root = new TreeNode(3);

        root->right = new TreeNode(5);
        root->right->left = new TreeNode(4);
        std::cout << Solution().balanceBST(root) << '\n';
    }

    // No Case
    {
        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);
        root->right = new TreeNode(3);
        std::cout << Solution().balanceBST(root) << '\n';
    }

    return 0;
}
