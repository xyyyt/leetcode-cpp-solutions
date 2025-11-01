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

    std::cout << Solution().levelOrder(root) << '\n';

    return 0;
}
