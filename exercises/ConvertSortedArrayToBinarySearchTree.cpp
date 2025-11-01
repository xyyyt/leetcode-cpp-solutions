#include <iostream>
#include <vector>

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
    TreeNode *sortedArrayToBST(const std::vector<int>& nums)
    {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }

private :
    [[nodiscard]]
    TreeNode *sortedArrayToBST(
        const std::vector<int>& nums, int startIndex, int endIndex)
    {
        if (startIndex > endIndex)
        {
            return nullptr;
        }

        int midIndex = (startIndex + endIndex) / 2;
        TreeNode *root = new TreeNode(nums[midIndex]);

        root->left = sortedArrayToBST(nums, startIndex, midIndex - 1);
        root->right = sortedArrayToBST(nums, midIndex + 1, endIndex);

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

            std::cout << ", " << node->value;
            (*this)(node->left);
            (*this)(node->right);
        }
    } traverseTree{os};

    std::cout << root->value;
    traverseTree(root->left);
    traverseTree(root->right);

    return os;
}

int main()
{
    std::cout << Solution().sortedArrayToBST({-10, -3, 0, 5, 9}) << '\n';
    std::cout << Solution().sortedArrayToBST({1, 3}) << '\n';

    return 0;
}
