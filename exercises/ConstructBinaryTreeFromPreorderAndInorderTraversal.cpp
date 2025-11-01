#include <vector>
#include <unordered_map>
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
        int endIndexOfInorder)
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
    std::cout << Solution().buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}) << '\n';
    std::cout << Solution().buildTree({-1}, {-1}) << '\n';

    return 0;
}
