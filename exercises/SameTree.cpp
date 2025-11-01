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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (!p && !q)
        {
            return true;
        }
        else if (!p || !q || p->val != q->val)
        {
            return false;
        }

        return isSameTree(p->left, q->left)
            && isSameTree(p->right, q->right);
    }
};

int main()
{
    {
        TreeNode *p = new TreeNode(1);

        p->left = new TreeNode(2);
        p->right = new TreeNode(3);

        TreeNode *q = new TreeNode(1);

        q->left = new TreeNode(2);
        q->right = new TreeNode(3);

        assert(Solution().isSameTree(p, q));
    }

    {
        TreeNode *p = new TreeNode(1);

        p->left = new TreeNode(2);

        TreeNode *q = new TreeNode(1);

        q->right = new TreeNode(2);

        assert(!Solution().isSameTree(p, q));
    }

    {
        TreeNode *p = new TreeNode(1);

        p->left = new TreeNode(2);
        p->right = new TreeNode(1);

        TreeNode *q = new TreeNode(1);

        q->left = new TreeNode(1);
        q->right = new TreeNode(2);

        assert(!Solution().isSameTree(p, q));
    }

    {
        TreeNode *p = new TreeNode(4);

        p->left = new TreeNode(2);
        p->right = new TreeNode(6);

        TreeNode *q = new TreeNode(4);

        q->left = new TreeNode(2);
        q->right = new TreeNode(6);

        assert(Solution().isSameTree(p, q));
    }

    {
        TreeNode *p = new TreeNode(3);

        p->left = new TreeNode(1);
        p->right = new TreeNode(5);

        TreeNode *q = new TreeNode(3);

        q->left = new TreeNode(1);
        q->right = new TreeNode(4);

        assert(!Solution().isSameTree(p, q));
    }

    {
        TreeNode *p = new TreeNode(7);

        p->left = new TreeNode(3);

        TreeNode *q = new TreeNode(7);

        q->left = new TreeNode(3);
        q->right = new TreeNode(9);

        assert(!Solution().isSameTree(p, q));
    }

    {
        assert(Solution().isSameTree(new TreeNode(2),
                                     new TreeNode(2)));
    }

    {

        assert(Solution().isSameTree(nullptr, nullptr));
    }

    return 0;
}
