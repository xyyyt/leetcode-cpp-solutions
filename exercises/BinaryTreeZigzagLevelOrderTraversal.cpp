#include <iostream>
#include <queue>
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

enum class ZigzagOrder : uint8_t { LEFT_TO_RIGHT, RIGHT_TO_LEFT };

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
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& levels) noexcept
{
    if (levels.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& level : levels)
    {
        if (level.empty())
        {
            continue;
        }

        auto begin = level.cbegin();
        auto end = level.cend();

        os << '[' << *begin;
        ++begin;

        while (begin != end)
        {
            os << ", " << *begin;
            ++begin;
        }

        os << ']';
    }

    return os;
}

int main()
{
    TreeNode *root = new TreeNode(3);

    root->left = new TreeNode(9);
    root->right = new TreeNode(20);

    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    std::cout << Solution().zigzagLevelOrder(root) << '\n';

    return 0;
}
