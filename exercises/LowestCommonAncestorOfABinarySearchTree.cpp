#include <iostream>

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

class Solution
{
public :
    TreeNode *lowestCommonAncestor(
        TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root)
        {
            return nullptr;
        }

        const TreeNode *lca = nullptr;

        lowestCommonAncestor(root, p, q, &lca);

        return const_cast<TreeNode *>(lca);
    }

private :
    bool lowestCommonAncestor(
        const TreeNode *node,
        const TreeNode *p,
        const TreeNode *q,
        const TreeNode **lca) const noexcept
    {
        if (!node)
        {
            return false;
        }
        else if (node == p || node == q)
        {
            if ((node->left
                 && (node->left == p || node->left == q))
                || (node->right
                    && (node->right == p || node->right == q)))
            {
                *lca = node;
            }

            return true;
        }

        bool descendantFound = lowestCommonAncestor(
             node->left, p, q, lca);
        bool descendantFound2 = lowestCommonAncestor(
             node->right, p, q, lca);

        if (descendantFound && descendantFound2)
        {
            *lca = node;
        }

        return descendantFound || descendantFound2;
    }
};

int main()
{
    {
        TreeNode *root = new TreeNode(6);

        root->left = new TreeNode(2);
        root->left->left = new TreeNode(0);
        root->left->right = new TreeNode(4);
        root->left->right->left = new TreeNode(3);
        root->left->right->right = new TreeNode(5);
        root->right = new TreeNode(8);
        root->right->left = new TreeNode(7);
        root->right->right = new TreeNode(9);

        TreeNode *node = Solution().lowestCommonAncestor(
            root,
            root->left,
            root->right);

        std::cout << node->val << '\n';
    }

    {
        TreeNode *root = new TreeNode(6);

        root->left = new TreeNode(2);
        root->right = new TreeNode(8);
        root->left->left = new TreeNode(0);
        root->left->right = new TreeNode(4);
        root->right->left = new TreeNode(7);
        root->right->right = new TreeNode(9);
        root->left->right->left = new TreeNode(3);
        root->left->right->right = new TreeNode(5);

        TreeNode *node = Solution().lowestCommonAncestor(
            root,
            root->left,
            root->left->right);

        std::cout << node->val << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(7);

        TreeNode *node = Solution().lowestCommonAncestor(
            root,
            root->left->right,
            root->right->left);

        std::cout << node->val << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(7);
        root->left->right->left = new TreeNode(8);
        root->left->right->right = new TreeNode(9);

        TreeNode *node = Solution().lowestCommonAncestor(
            root,
            root->left->left,
            root->left->right->right);

        std::cout << node->val << '\n';
    }

    {
        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);

        TreeNode *node = Solution().lowestCommonAncestor(
            root,
            root,
            root->left);

        std::cout << node->val << '\n';
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->left->left = new TreeNode(3);
        root->left->left->left = new TreeNode(4);

        if (TreeNode *node = Solution().lowestCommonAncestor(
            root,
            root->left,
            root->left->left->left);
            node)
        {
            std::cout << node->val << '\n';
        }
        else
        {
            std::cout << nullptr << '\n';
        }
    }

    return 0;
}
