#include <vector>
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

void check(
    const TreeNode *root, std::vector<int> expected)
{
    struct
    {
        void operator()(
            const TreeNode *node,
            const std::vector<int>& expected,
            int& n) const
        {
            if (!node)
            {
                return;
            }

            assert(n < expected.size());
            assert(node->value == expected[n++]);
            (*this)(node->left, expected, n);
            (*this)(node->right, expected, n);
        }
    } inner;
    int n = 0;

    inner(root, expected, n);
    assert(n == expected.size());
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

        check(Solution().mergeTrees(root, root2),
              {3, 4, 5, 4, 5, 7});
    }

    {
        TreeNode *root = new TreeNode(1);
        TreeNode *root2 = new TreeNode(1);

        root2->left = new TreeNode(2);

        check(Solution().mergeTrees(root, root2),
              {2, 2});
    }

    {
        TreeNode *root = new TreeNode(10);

        root->right = new TreeNode(20);

        TreeNode *root2 = new TreeNode(5);

        root2->left = new TreeNode(3);
        root2->right = new TreeNode(7);

        check(Solution().mergeTrees(root, root2),
              {15, 3, 27});
    }

    {
        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);

        TreeNode *root2 = new TreeNode(3);

        root2->right = new TreeNode(4);

        check(Solution().mergeTrees(root, root2),
              {5, 1, 4});
    }

    {
        TreeNode *root = new TreeNode(6);

        root->left = new TreeNode(4);
        root->right = new TreeNode(9);

        TreeNode *root2 = new TreeNode(1);

        check(Solution().mergeTrees(root, root2),
              {7, 4, 9});
    }

    {
        TreeNode *root = nullptr;
        TreeNode *root2 = new TreeNode(8);

        root2->left = new TreeNode(3);

        check(Solution().mergeTrees(root, root2),
              {8, 3});
    }

    return 0;
}
