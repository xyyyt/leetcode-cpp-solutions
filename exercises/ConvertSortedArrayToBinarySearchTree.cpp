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
    TreeNode *sortedArrayToBST(const std::vector<int>& nums)
    {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }

private :
    [[nodiscard]]
    TreeNode *sortedArrayToBST(
        const std::vector<int>& nums, int startIndex, int endIndex) const
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
    check(Solution().sortedArrayToBST({-10, -3, 0, 5, 9}),
          {0, -10, -3, 5, 9});
    check(Solution().sortedArrayToBST({1, 3}),
          {1, 3});
    check(Solution().sortedArrayToBST({}),
          {});
    check(Solution().sortedArrayToBST({1}),
          {1});
    check(Solution().sortedArrayToBST({1, 2}),
          {1, 2});

    return 0;
}
