#include <cassert>

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
        if (!root && !subRoot)
        {
            return true;
        }
        else if (!root || !subRoot)
        {
            return false;
        }
        else if (root->val == subRoot->val
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
    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(4);
        root->right = new TreeNode(5);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(2);

        TreeNode *subRoot = new TreeNode(4);

        subRoot->left = new TreeNode(1);
        subRoot->right = new TreeNode(2);

        assert(Solution().isSubtree(root, subRoot));
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

        assert(!Solution().isSubtree(root, subRoot));
    }

    {
        TreeNode *root = new TreeNode(8);

        root->left = new TreeNode(3);
        root->right = new TreeNode(10);
        root->left->left = new TreeNode(1);
        root->left->right = new TreeNode(6);
        root->left->right->left = new TreeNode(4);
        root->left->right->right = new TreeNode(7);

        TreeNode *subRoot = new TreeNode(6);

        subRoot->left = new TreeNode(4);
        subRoot->right = new TreeNode(7);

        assert(Solution().isSubtree(root, subRoot));
    }

    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(4);
        root->right = new TreeNode(8);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(9);

        TreeNode *subRoot = new TreeNode(8);

        subRoot->left = new TreeNode(6);
        subRoot->right = new TreeNode(10);

        assert(!Solution().isSubtree(root, subRoot));
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(1);

        TreeNode *subRoot = new TreeNode(1);

        assert(Solution().isSubtree(root, subRoot));
    }

    {
        TreeNode *root = new TreeNode(7);

        root->left = new TreeNode(3);
        root->right = new TreeNode(9);

        TreeNode *subRoot = new TreeNode(3);

        subRoot->left = new TreeNode(1);

        assert(!Solution().isSubtree(root, subRoot));
    }

    {
        assert(Solution().isSubtree(nullptr, nullptr));
    }

    return 0;
}
