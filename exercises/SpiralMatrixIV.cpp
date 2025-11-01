#include <vector>
#include <unordered_set>
#include <cstdint>
#include <cassert>

namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        [[nodiscard]]
        size_t operator()(const std::pair<int, int>& pair) const noexcept
        {
            size_t h1 = std::hash<int>{}(pair.first);
            size_t h2 = std::hash<int>{}(pair.second);

            // boost::hash_combine formula
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
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

        auto matrix = buildMatrix(m, n);
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

        for (int i = 0; i < m; ++i)
        {
            matrix[i].resize(n);
        }

        return matrix;
    }

    void fillMatrix(
        const ListNode *head,
        std::vector<std::vector<int>>& matrix,
        VCSet_t& vcSet,
        Direction direction,
        int y,
        int x) const
    {
        matrix[y][x] = (head) ? head->val : -1;
        vcSet.emplace(y, x);

        const ListNode *next = (head) ? head->next : nullptr;

        if (direction == Direction::RIGHT)
        {
            if (x < matrix[y].size() - 1
                && vcSet.find({y, x + 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    y,
                    x + 1);
            }
            else if (y < matrix.size() - 1
                     && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    y + 1,
                    x);
            }
        }
        else if (direction == Direction::DOWN)
        {
            if (y < matrix.size() - 1
                && vcSet.find({y + 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::DOWN,
                    y + 1,
                    x);
            }
            else if (x > 0
                     && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    y,
                    x - 1);
            }
        }
        else if (direction == Direction::LEFT)
        {
            if (x > 0
                && vcSet.find({y, x - 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::LEFT,
                    y,
                    x - 1);
            }
            else if (y > 0
                     && vcSet.find({y - 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::UP,
                    y - 1,
                    x);
            }
        }
        else if (direction == Direction::UP)
        {
            if (y > 0
                && vcSet.find({y - 1, x}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::UP,
                    y - 1,
                    x);
            }
            else if (x < matrix[y].size() - 1
                     && vcSet.find({y, x + 1}) == vcSet.cend())
            {
                fillMatrix(
                    next,
                    matrix,
                    vcSet,
                    Direction::RIGHT,
                    y,
                    x + 1);
            }
        }
    }
};

inline void check(
    const std::vector<std::vector<int>>& matrix,
    std::vector<std::vector<int>> expected)
{
    assert(matrix == expected);
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

        check(Solution().spiralMatrix(3, 5, root),
              {{3, 0, 2, 6, 8},
               {5, 0, -1, -1, 1},
               {5, 2, 4, 9, 7}});
    }

    {
        ListNode *root = new ListNode(0);

        root
            ->next = new ListNode(1);
        root
            ->next->next = new ListNode(2);

        check(Solution().spiralMatrix(1, 4, root),
              {{0, 1, 2, -1}});
    }

    {
        ListNode *root = new ListNode(5);

        root
            ->next = new ListNode(6);
        root
            ->next->next = new ListNode(7);
        root
            ->next->next->next = new ListNode(8);

        check(Solution().spiralMatrix(2, 3, root),
              {{5, 6, 7},
               { -1, -1, 8}});
    }

    {
        ListNode *root = new ListNode(9);

        root
            ->next = new ListNode(10);
        root
            ->next->next = new ListNode(11);
        root
            ->next->next->next = new ListNode(12);
        root
            ->next->next->next->next = new ListNode(13);

        check(Solution().spiralMatrix(3, 3, root),
              {{9, 10, 11},
               { -1, -1, 12},
               { -1, -1, 13}});
    }

    {
        ListNode *root = new ListNode(4);

        root
            ->next = new ListNode(3);
        root
            ->next->next = new ListNode(2);
        root
            ->next->next->next = new ListNode(1);

        check(Solution().spiralMatrix(2, 2, root),
              {{4, 3},
               {1, 2}});
    }

    {
        ListNode *root = new ListNode(7);

        check(Solution().spiralMatrix(1, 1, root),
              {{7}});
    }

    {
        ListNode *root = new ListNode(0);

        root
            ->next = new ListNode(1);
        root
            ->next->next = new ListNode(2);
        root
            ->next->next->next = new ListNode(3);
        root
            ->next->next->next->next = new ListNode(4);
        root
            ->next->next->next->next->next = new ListNode(5);

        check(Solution().spiralMatrix(3, 4, root),
              {{0, 1, 2, 3},
               { -1, -1, -1, 4},
               { -1, -1, -1, 5}});
    }

    return 0;
}
