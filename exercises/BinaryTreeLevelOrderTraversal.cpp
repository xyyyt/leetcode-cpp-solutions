#include <vector>
#include <queue>
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
    std::vector<std::vector<int>> levelOrder(TreeNode *root)
    {
        if (!root)
        {
            return {};
        }

        std::vector<std::vector<int>> levels;
        std::queue<TreeNode *> queue;

        queue.emplace(root);

        while (!queue.empty())
        {
            std::vector<int> valuesOfTheLevel;
            std::queue<TreeNode *> currentLevel = std::move(queue);

            valuesOfTheLevel.reserve(currentLevel.size());

            while (!currentLevel.empty())
            {
                auto node = currentLevel.front();

                currentLevel.pop();
                valuesOfTheLevel.emplace_back(node->value);

                if (node->left)
                {
                    queue.emplace(node->left);
                }

                if (node->right)
                {
                    queue.emplace(node->right);
                }
            }

            levels.emplace_back(std::move(valuesOfTheLevel));
        }

        return levels;
    }
};

inline void check(
    const std::vector<std::vector<int>>& levels,
    std::vector<std::vector<int>> expected)
{
    assert(levels == expected);
}

int main()
{
    {
        TreeNode *root = new TreeNode(3);

        root->left = new TreeNode(9);
        root->right = new TreeNode(20);

        root->right->left = new TreeNode(15);
        root->right->right = new TreeNode(7);

        check(Solution().levelOrder(root), {{3}, {9, 20}, {15, 7}});
    }

    {
        check(Solution().levelOrder(nullptr), {});
    }

    {
        TreeNode *root = new TreeNode(1);

        root->left = new TreeNode(2);
        root->right = new TreeNode(3);

        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);

        check(Solution().levelOrder(root), {{1}, {2, 3}, {4, 5}});
    }

    {
        TreeNode *root = new TreeNode(10);

        root->left = new TreeNode(6);
        root->right = new TreeNode(15);

        root->right->left = new TreeNode(12);
        root->right->right = new TreeNode(18);
        root->right->right->right = new TreeNode(20);

        check(Solution().levelOrder(root), {{10}, {6, 15}, {12, 18}, {20}});
    }

    {
        TreeNode *root = new TreeNode(7);

        root->left = new TreeNode(3);
        root->left->left = new TreeNode(1);

        check(Solution().levelOrder(root), {{7}, {3}, {1}});
    }

    {
        TreeNode *root = new TreeNode(5);

        root->right = new TreeNode(9);
        root->right->right = new TreeNode(11);

        check(Solution().levelOrder(root), {{5}, {9}, {11}});
    }

    return 0;
}
