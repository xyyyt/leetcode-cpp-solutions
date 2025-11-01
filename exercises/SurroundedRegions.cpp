#include <vector>
#include <unordered_set>
#include <type_traits>
#include <iostream>

namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        [[nodiscard]]
        size_t operator()(const std::pair<int, int>& pair) const noexcept
        {
            return std::hash<int>()(pair.first)
                ^ std::hash<int>()(pair.second);
        }
    };
}

class Solution
{
public :
    void solve(std::vector<std::vector<char>>& board)
    {
        if (board.empty())
        {
            return;
        }

        VCSet_t O_regionVCSet;

        for (int m = 0; m < board.size(); ++m)
        {
            for (int n = 0; n < board[m].size(); ++n)
            {
                if (board[m][n] == to(BoardItem::O)
                    && (m != 0 && m != board.size() - 1)
                    && (n != 0 && n != board[m].size() - 1)
                    && O_regionVCSet.find({m, n}) == O_regionVCSet.cend())
                {
                    findRegion(
                        board, O_regionVCSet, Direction::UNKNOWN, m, n);
                }
            }
        }

        for (auto [m, n] : O_regionVCSet)
        {
            board[m][n] = to(BoardItem::X);
        }
    }

private :
    enum class BoardItem : char { X = 'X', O = 'O' };
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN, UNKNOWN };

    using BoardItemUnderlying_t = typename std::underlying_type<BoardItem>::type;

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    [[nodiscard]]
    inline static constexpr BoardItemUnderlying_t to(BoardItem item) noexcept
    {
        return static_cast<BoardItemUnderlying_t>(item);
    }

    void findRegion(
        const std::vector<std::vector<char>>& board,
        VCSet_t& O_regionVCSet,
        Direction fromDirection,
        int m,
        int n) const
    {
        if (board[m][n] == to(BoardItem::X)
            || O_regionVCSet.find({m, n}) != O_regionVCSet.cend())
        {
            return;
        }

        O_regionVCSet.emplace(m, n);

        if (fromDirection != Direction::LEFT
            && n - 1 >= 0)
        {
            findRegion(
                board, O_regionVCSet, Direction::RIGHT, m, n - 1);
        }

        if (fromDirection != Direction::RIGHT
            && n + 1 < board[m].size())
        {
            findRegion(
                board, O_regionVCSet, Direction::LEFT, m, n + 1);
        }

        if (fromDirection != Direction::UP
            && m - 1 >= 0)
        {
            findRegion(
                board, O_regionVCSet, Direction::DOWN, m - 1, n);
        }

        if (fromDirection != Direction::DOWN
            && m + 1 < board.size())
        {
            findRegion(
                board, O_regionVCSet, Direction::UP, m + 1, n);
        }
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::vector<char>>& board) noexcept
{
    if (board.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& range : board)
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

        os << "]";
    }

    return os;
}

int main()
{
    {
        std::vector<std::vector<char>> board{
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'}};

        Solution().solve(board);
        std::cout << board << '\n';
    }

    {
        std::vector<std::vector<char>> board{
            {'X'}};

        Solution().solve(board);
        std::cout << board << '\n';
    }

    return 0;
}
