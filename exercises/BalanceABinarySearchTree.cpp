#include <vector>
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

// // Classic solution
// class Solution
// {
// public :
//     TreeNode *balanceBST(TreeNode *root)
//     {
//         if (!root)
//         {
//             return nullptr;
//         }

//         std::vector<int> array;

//         fillArray(root, array);

//         return buildBalancedBST(array, 0, array.size() - 1);
//     }

// private :
//     void fillArray(
//         const TreeNode *node, std::vector<int>& array) const
//     {
//         if (!node)
//         {
//             return;
//         }

//         fillArray(node->left, array);
//         array.emplace_back(node->val);
//         fillArray(node->right, array);
//     }

//     [[nodiscard]]
//     TreeNode *buildBalancedBST(
//         const std::vector<int>& array,
//         int start,
//         int end) const
//     {
//         if (start > end)
//         {
//             return nullptr;
//         }

//         int mid = (start + end) / 2;
//         TreeNode *node = new TreeNode(array[mid]);

//         node->left = buildBalancedBST(array, start, mid - 1);
//         node->right = buildBalancedBST(array, mid + 1, end);

//         return node;
//     }
// };

// Optimized solution for locals unbalanced subtrees (i.e : rotations)
class Solution
{
public :
    TreeNode *balanceBST(TreeNode *root) { return _balanceBST(root); }

private :
    [[nodiscard]]
    int maxHeight(TreeNode *node) const noexcept
    {
        return (node) ?
            1 + std::max(maxHeight(node->left), maxHeight(node->right)) : 0;
    }

    [[nodiscard]]
    TreeNode *leftRotation(TreeNode *node) const noexcept
    {
        TreeNode *pivot = node->right;
        TreeNode *leftPivot = pivot->left;

        pivot->left = node;
        node->right = leftPivot;

        return pivot;
    }

    [[nodiscard]]
    TreeNode *rightRotation(TreeNode *node) const noexcept
    {
        TreeNode *pivot = node->left;
        TreeNode *rightPivot = pivot->right;

        pivot->right = node;
        node->left = rightPivot;

        return pivot;
    }

    [[nodiscard]]
    TreeNode *_balanceBST(TreeNode *node) const noexcept
    {
        if (!node)
        {
            return nullptr;
        }

        node->left = _balanceBST(node->left);
        node->right = _balanceBST(node->right);

        int balanceFactor = maxHeight(node->left) - maxHeight(node->right);

        if (balanceFactor > 1)
        {
            if (!node->left->left && node->left->right)
            {
                node->left = leftRotation(node->left);
            }

            return rightRotation(node);
        }
        else if (balanceFactor < -1)
        {
            if (!node->right->right && node->right->left)
            {
                node->right = rightRotation(node->right);
            }

            return leftRotation(node);
        }

        return node;
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
    // // [Tests for classic solution]

    // {
    //     TreeNode *root = new TreeNode(1);

    //     root->right = new TreeNode(2);
    //     root->right->right = new TreeNode(3);
    //     root->right->right->right = new TreeNode(4);
    //     check(Solution().balanceBST(root), {2, 1, 3, 4});
    // }

    // {
    //     TreeNode *root = new TreeNode(1);

    //     root->left = new TreeNode(2);
    //     root->left->left = new TreeNode(3);
    //     root->left->left->left = new TreeNode(4);
    //     check(Solution().balanceBST(root), {3, 4, 2, 1});
    // }

    // {
    //     TreeNode *root = new TreeNode(5);

    //     root->left = new TreeNode(3);
    //     root->left->right = new TreeNode(4);
    //     check(Solution().balanceBST(root), {4, 3, 5});
    // }

    // {
    //     TreeNode *root = new TreeNode(3);

    //     root->right = new TreeNode(5);
    //     root->right->left = new TreeNode(4);
    //     check(Solution().balanceBST(root), {4, 3, 5});
    // }

    // {
    //     TreeNode *root = new TreeNode(2);

    //     root->left = new TreeNode(1);
    //     root->right = new TreeNode(3);
    //     check(Solution().balanceBST(root), {2, 1, 3});
    // }


    // [Tests for optimized solution]

    // Right Right Case (Left Rotation) + Right Right Case (Left Rotation)
    {
        TreeNode *root = new TreeNode(1);

        root->right = new TreeNode(2);
        root->right->right = new TreeNode(3);
        root->right->right->right = new TreeNode(4);
        check(Solution().balanceBST(root), {3, 1, 2, 4});
    }

    // Left Left Case (Right Rotation) + Left Left Case (Right Rotation)
    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->left->left = new TreeNode(3);
        root->left->left->left = new TreeNode(4);
        check(Solution().balanceBST(root), {3, 4, 1, 2});
    }

    // Left Right Case (Left rotation + Right rotation)
    {
        TreeNode *root = new TreeNode(5);

        root->left = new TreeNode(3);
        root->left->right = new TreeNode(4);
        check(Solution().balanceBST(root), {4, 3, 5});
    }

    // Right Left Case (Right rotation + Left rotation)
    {
        TreeNode *root = new TreeNode(3);

        root->right = new TreeNode(5);
        root->right->left = new TreeNode(4);
        check(Solution().balanceBST(root), {4, 3, 5});
    }

    // No Case (No rotations)
    {
        TreeNode *root = new TreeNode(2);

        root->left = new TreeNode(1);
        root->right = new TreeNode(3);
        check(Solution().balanceBST(root), {2, 1, 3});
    }

    return 0;
}
