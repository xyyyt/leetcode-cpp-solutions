#include <queue>
#include <vector>
#include <cstdint>
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
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        if (!root)
        {
            return {};
        }

        std::vector<std::vector<int>> levels;
        std::queue<TreeNode *> queue;
        ZigzagOrder zigZagOrder = ZigzagOrder::RIGHT_TO_LEFT;

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

                if (zigZagOrder == ZigzagOrder::LEFT_TO_RIGHT)
                {
                    if (node->left)
                    {
                        queue.emplace(node->left);
                    }

                    if (node->right)
                    {
                        queue.emplace(node->right);
                    }
                }
                else
                {
                    if (node->right)
                    {
                        queue.emplace(node->right);
                    }

                    if (node->left)
                    {
                        queue.emplace(node->left);
                    }
                }
            }

            zigZagOrder = (zigZagOrder == ZigzagOrder::LEFT_TO_RIGHT) ?
                ZigzagOrder::RIGHT_TO_LEFT : ZigzagOrder::LEFT_TO_RIGHT;
            levels.emplace_back(std::move(valuesOfTheLevel));
        }

        return levels;
    }

private :
    enum class ZigzagOrder : uint8_t { LEFT_TO_RIGHT, RIGHT_TO_LEFT };
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

        check(Solution().zigzagLevelOrder(root), {{3}, {20, 9}, {15, 7}});
    }

    {
        check(Solution().zigzagLevelOrder(nullptr), {});
    }

    {
        TreeNode *root = new TreeNode(7);

        root->left = new TreeNode(4);
        root->left->left = new TreeNode(2);

        check(Solution().zigzagLevelOrder(root), {{7}, {4}, {2}});
    }

    {
        TreeNode *root = new TreeNode(8);

        root->right = new TreeNode(12);
        root->right->left = new TreeNode(10);

        check(Solution().zigzagLevelOrder(root), {{8}, {12}, {10}});
    }

    return 0;
}
