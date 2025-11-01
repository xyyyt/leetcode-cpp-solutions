#include <stack>
#include <limits>
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

class BSTIterator
{
public:
    BSTIterator(TreeNode* root) noexcept : _node(root) { }

    int next()
    {
        if (!_node)
        {
            return std::numeric_limits<int>::min();
        }

        while (!_fromStack && _node->left)
        {
            _stack.emplace(_node);
            _node = _node->left;
        }

        TreeNode *node = _node;

        if (_node->right)
        {
            _node = _node->right;
            _fromStack = false;
        }
        else if (!_stack.empty())
        {
            _node = _stack.top();
            _stack.pop();
            _fromStack = true;
        }
        else
        {
            _node = nullptr;
            _fromStack = false;
        }

        return node->val;
    }

    bool hasNext() const { return !(_node == nullptr && _stack.empty()); }

private :
    std::stack<TreeNode *> _stack;
    TreeNode *_node;
    bool _fromStack = false;
};

int main()
{
    std::cout << std::boolalpha;

    {
        TreeNode *root = new TreeNode(42);
        BSTIterator bstIterator(root);

        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
    }

    std::cout << '\n';

    {
        TreeNode *root = new TreeNode(12);

        root->right = new TreeNode(33);

        BSTIterator bstIterator(root);

        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
    }

    std::cout << '\n';

    {
        TreeNode *root = new TreeNode(54);

        root->left = new TreeNode(37);
        root->left->right = new TreeNode(46);

        BSTIterator bstIterator(root);

        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
    }

    std::cout << '\n';

    {
        TreeNode *root = new TreeNode(7);

        root->left = new TreeNode(3);
        root->right = new TreeNode(15);
        root->right->left = new TreeNode(9);
        root->right->right = new TreeNode(20);

        BSTIterator bstIterator(root);

        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
        std::cout << bstIterator.next() << '\n';
        std::cout << bstIterator.hasNext() << '\n';
    }

    return 0;
}
