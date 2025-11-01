#include <vector>
#include <unordered_set>
#include <iostream>

namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        [[nodiscard]]
        size_t operator()(const std::pair<int, int>& cell) const noexcept
        {
            return std::hash<int>()(cell.first)
                ^ std::hash<int>()(cell.second);
        }
    };
}

struct ListNode
{
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) { }
    ListNode(int x) : val(x), next(nullptr) { }
    ListNode(int x, ListNode *next) : val(x), next(next) { }
};

class Solution
{
public:
    std::vector<std::vector<int>> spiralMatrix(
        int m, int n, ListNode *head)
    {
        if (m <= 0 || n <= 0)
        {
            return {};
        }

        std::vector<std::vector<int>> matrix = buildMatrix(m, n);
        VCSet_t vcSet;

        fillMatrix(head, matrix, vcSet, Direction::RIGHT, 0, 0);

        return matrix;
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN };

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    [[nodiscard]]
    inline std::vector<std::vector<int>> buildMatrix(
        int m, int n) const
    {
        std::vector<std::vector<int>> matrix(m);

        for (int n2 = 0; n2 < m; ++n2)
        {
            matrix[n2].resize(n);
        }

        return matrix;
    }

    void fillMatrix(
        const ListNode *head,
        std::vector<std::vector<int>>& matrix,
        VCSet_t& vcSet,
        Direction directionWhereToGo,
        int posY,
        int posX) const
    {
        matrix[posY][posX] = (head) ? head->val : -1;
        vcSet.emplace(posY, posX);

        const ListNode *next = (head) ? head->next : nullptr;

        if (directionWhereToGo == Direction::RIGHT)
        {
            if (posX < matrix[posY].size() - 1
                && vcSet.find({posY, posX + 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    posY,
                    posX + 1);
            }
            else if (posY < matrix.size() - 1
                     && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    posY + 1,
                    posX);
            }
        }
        else if (directionWhereToGo == Direction::DOWN)
        {
            if (posY < matrix.size() - 1
                && vcSet.find({posY + 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    posY + 1,
                    posX);
            }
            else if (posX > 0
                     && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    posY,
                    posX - 1);
            }
        }
        else if (directionWhereToGo == Direction::LEFT)
        {
            if (posX > 0
                && vcSet.find({posY, posX - 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    posY,
                    posX - 1);
            }
            else if (posY > 0
                     && vcSet.find({posY - 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::UP,
                    posY - 1,
                    posX);
            }
        }
        else if (directionWhereToGo == Direction::UP)
        {
            if (posY > 0
                && vcSet.find({posY - 1, posX}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::UP,
                    posY - 1,
                    posX);
            }
            else if (posX < matrix[posY].size() - 1
                     && vcSet.find({posY, posX + 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    posY,
                    posX + 1);
            }
        }
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<int>>& matrix) noexcept
{
    if (matrix.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& range : matrix)
    {
        if (range.empty())
        {
            continue;
        }

        auto begin = range.cbegin();
        auto end = range.cend();

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
    {
        ListNode *root = new ListNode(3);

        root
            ->next = new ListNode(0);
        root
            ->next->next = new ListNode(2);
        root
            ->next->next->next = new ListNode(6);
        root
            ->next->next->next->next = new ListNode(8);
        root
            ->next->next->next->next->next = new ListNode(1);
        root
            ->next->next->next->next->next->next = new ListNode(7);
        root
            ->next->next->next->next->next->next->next = new ListNode(9);
        root
            ->next->next->next->next->next->next->next
            ->next = new ListNode(4);
        root
            ->next->next->next->next->next->next->next
            ->next->next = new ListNode(2);
        root
            ->next->next->next->next->next->next->next
            ->next->next->next = new ListNode(5);
        root
            ->next->next->next->next->next->next->next
            ->next->next->next->next = new ListNode(5);
        root
            ->next->next->next->next->next->next->next
            ->next->next->next->next->next = new ListNode(0);

        std::cout << Solution().spiralMatrix(3, 5, root) << '\n';
    }

    {
        ListNode *root = new ListNode(0);

        root
            ->next = new ListNode(1);
        root
            ->next->next = new ListNode(2);

        std::cout << Solution().spiralMatrix(1, 4, root) << '\n';
    }

    return 0;
}
