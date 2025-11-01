#include <vector>
#include <unordered_map>
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

class Solution
{
public :
    TreeNode *buildTree(
        std::vector<int> preorder, std::vector<int> inorder)
    {
        if (preorder.empty()
            || inorder.empty()
            || preorder.size() != inorder.size())
        {
            return nullptr;
        }

        std::unordered_map<int, int> indexesOfValuesFromInorder;

        indexesOfValuesFromInorder.reserve(preorder.size());

        for (int n = 0; n < preorder.size(); ++n)
        {
            indexesOfValuesFromInorder.emplace(preorder[n], n);
        }

        int currentIndexOfPreorder = 0;

        return buildTree(preorder,
                         inorder,
                         indexesOfValuesFromInorder,
                         currentIndexOfPreorder,
                         0,
                         inorder.size() - 1);
    }

private :
    [[nodiscard]]
    TreeNode *buildTree(
        const std::vector<int>& preorder,
        const std::vector<int>& inorder,
        const std::unordered_map<int, int>& indexesOfValuesFromInorder,
        int& currentIndexOfPreorder,
        int startIndexOfInorder,
        int endIndexOfInorder) const
    {
        if (startIndexOfInorder > endIndexOfInorder)
        {
            return nullptr;
        }

        TreeNode *root = new TreeNode(preorder[currentIndexOfPreorder]);
        int index = indexesOfValuesFromInorder.at(preorder[currentIndexOfPreorder]);

        ++currentIndexOfPreorder;
        root->left = buildTree(
            preorder,
            inorder,
            indexesOfValuesFromInorder,
            currentIndexOfPreorder,
            startIndexOfInorder,
            index - 1);
        root->right = buildTree(
            preorder,
            inorder,
            indexesOfValuesFromInorder,
            currentIndexOfPreorder,
            index + 1,
            endIndexOfInorder);

        return root;
    }
};

void check(const TreeNode *root, std::vector<int> expected)
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

    inner(root, expected, n);
    assert(n == expected.size());
}

int main()
{
    check(Solution().buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}),
          {3, 9, 20, 15, 7});
    check(Solution().buildTree({-1}, {-1}),
          {-1});
    check(Solution().buildTree({1, 2, 3, 4}, {4, 3, 2, 1}),
          {1, 2, 3, 4});
    check(Solution().buildTree({1, 2, 3, 4}, {1, 2, 3, 4}),
          {1, 2, 3, 4});
    check(Solution().buildTree({1, 2, 3}, {1, 2, 3}),
          {1, 2, 3});
    check(Solution().buildTree({1, 2, 3}, {3, 2, 1}),
          {1, 2, 3});

    return 0;
}
