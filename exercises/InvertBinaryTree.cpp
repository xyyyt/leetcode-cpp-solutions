#include <vector>
#include <cassert>
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

void check(
    const TreeNode *node, std::vector<int> expected)
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
            assert(node->val == expected[n++]);
            (*this)(node->left, expected, n);
            (*this)(node->right, expected, n);
        }
    } inner;
    int n = 0;

    inner(node, expected, n);
    assert(n == expected.size());
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

        check(Solution().invertTree(root),
              {4, 7, 9, 6, 2, 3, 1});
    }

    {
        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);
        root->right = new TreeNode(3);

        check(Solution().invertTree(root),
              {2, 3, 1});
    }

    {
        TreeNode *root = new TreeNode(10);

        root->left = new TreeNode(6);
        root->right = new TreeNode(14);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(8);
        root->right->left = new TreeNode(12);
        root->right->right = new TreeNode(16);

        check(Solution().invertTree(root),
              {10, 14, 16, 12, 6, 8, 4});
    }

    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(3);
        root->left->left = new TreeNode(1);

        check(Solution().invertTree(root),
              {5, 3, 1});
    }

    {
        TreeNode *root = new TreeNode(7);

        root->right = new TreeNode(9);
        root->right->right = new TreeNode(11);

        check(Solution().invertTree(root),
              {7, 9, 11});
    }

    {
        check(Solution().invertTree(nullptr),
              {});
    }

    return 0;
}
