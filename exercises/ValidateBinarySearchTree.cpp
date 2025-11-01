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
    bool isValidBST(TreeNode *root)
    {
        return isValidBST(root, nullptr, nullptr);
    }

private :
    [[nodiscard]]
    bool isValidBST(
        const TreeNode *node,
        const TreeNode *minNode,
        const TreeNode *maxNode) const noexcept
    {
        if (!node)
        {
            return true;
        }
        else if ((minNode && node->value < minNode->value)
                 || (maxNode && node->value > maxNode->value))
        {
            return false;
        }
        else
        {
            return isValidBST(node->left, minNode, node)
                && isValidBST(node->right, node, maxNode);
        }
    }
};

int main()
{
    {
        //   2
        //  / \
        // 1   3

        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);
        root->right = new TreeNode(3);

        assert(Solution().isValidBST(root));
    }

    {
        //   5
        //  / \
        // 1   4
        //    / \
        //   3   6

        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(1);
        root->right = new TreeNode(4);

        root->right->left = new TreeNode(3);
        root->right->right = new TreeNode(6);

        assert(!Solution().isValidBST(root));
    }

    {
        //      20
        //     /  \
        //   10    30
        //  /  \     \
        //     15     40

        TreeNode *root = new TreeNode(20);

        root->left = new TreeNode(10);
        root->right = new TreeNode(30);

        root->left->right = new TreeNode(15);

        root->right->right = new TreeNode(40);

        assert(Solution().isValidBST(root));
    }

    {
        //     5
        //    / \
        //   3   7
        //  /
        // 6

        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(3);
        root->right = new TreeNode(7);

        root->left->left = new TreeNode(6);

        assert(!Solution().isValidBST(root));
    }

    {
        //     20
        //    /
        //   10
        //  /
        // 15

        TreeNode *root = new TreeNode(20);

        root->left = new TreeNode(10);

        root->left->left = new TreeNode(15);

        assert(!Solution().isValidBST(root));
    }

    {
        //     13
        //    / \
        //   4   25
        //    \
        //     7

        TreeNode *root = new TreeNode(13);

        root->left = new TreeNode(4);
        root->right = new TreeNode(25);

        root->left->right = new TreeNode(7);

        assert(Solution().isValidBST(root));
    }

    {
        //   8
        //  / \
        // 4   10
        //    /
        //   2

        TreeNode *root = new TreeNode(8);

        root->left = new TreeNode(4);
        root->right = new TreeNode(10);

        root->right->left = new TreeNode(2);

        assert(!Solution().isValidBST(root));
    }

    {
        //   10
        //  /  \
        // 5    15
        //  \
        //   12

        TreeNode *root = new TreeNode(10);

        root->left = new TreeNode(5);
        root->right = new TreeNode(15);

        root->left->right = new TreeNode(12);

        assert(!Solution().isValidBST(root));
    }

    {
        //     20
        //     /
        //   10
        //  /  \
        // 5    15
        //  \
        //  12

        TreeNode *root = new TreeNode(20);

        root->left = new TreeNode(10);

        root->left->left = new TreeNode(5);
        root->left->right = new TreeNode(15);

        root->left->left->right = new TreeNode(12);

        assert(!Solution().isValidBST(root));
    }

    {
        //     30
        //     /
        //   10
        //  /  \
        // 5    15
        //  \
        //  42

        TreeNode *root = new TreeNode(30);

        root->left = new TreeNode(10);

        root->left->left = new TreeNode(5);
        root->left->right = new TreeNode(15);

        root->left->left->right = new TreeNode(42);

        assert(!Solution().isValidBST(root));
    }

    return 0;
}
