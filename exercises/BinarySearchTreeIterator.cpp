#include <stack>
#include <limits>
#include <cassert>

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

class BSTIterator
{
public:
    BSTIterator(TreeNode *root) { pushLeft(root); }

    int next()
    {
        assert(!_stack.empty());

        const auto node = _stack.top();

        _stack.pop();

        if (node->right)
        {
            pushLeft(node->right);
        }

        return node->val;
    }

    bool hasNext() const { return !_stack.empty(); }

private :
    std::stack<const TreeNode *> _stack;

    void pushLeft(const TreeNode *node)
    {
        while (node)
        {
            _stack.emplace(node);
            node = node->left;
        }
    }
};

int main()
{
    {
        TreeNode *root = new TreeNode(42);
        BSTIterator bstIterator(root);

        assert(bstIterator.next() == 42);
        assert(!bstIterator.hasNext());
    }

    {
        TreeNode *root = new TreeNode(12);

        root->right = new TreeNode(33);

        BSTIterator bstIterator(root);

        assert(bstIterator.next() == 12);
        assert(bstIterator.hasNext());
        assert(bstIterator.next() == 33);
        assert(!bstIterator.hasNext());
    }

    {
        TreeNode *root = new TreeNode(54);

        root->left = new TreeNode(37);
        root->left->right = new TreeNode(46);

        BSTIterator bstIterator(root);

        assert(bstIterator.next() == 37);
        assert(bstIterator.hasNext());
        assert(bstIterator.next() == 46);
        assert(bstIterator.hasNext());
        assert(bstIterator.next() == 54);
        assert(!bstIterator.hasNext());
    }

    {
        TreeNode *root = new TreeNode(7);

        root->left = new TreeNode(3);
        root->right = new TreeNode(15);
        root->right->left = new TreeNode(9);
        root->right->right = new TreeNode(20);

        BSTIterator bstIterator(root);

        assert(bstIterator.next() == 3);
        assert(bstIterator.next() == 7);
        assert(bstIterator.hasNext());
        assert(bstIterator.next() == 9);
        assert(bstIterator.hasNext());
        assert(bstIterator.next() == 15);
        assert(bstIterator.hasNext());
        assert(bstIterator.next() == 20);
        assert(!bstIterator.hasNext());
    }

    return 0;
}
