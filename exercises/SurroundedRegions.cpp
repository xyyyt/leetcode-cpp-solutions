#include <vector>
#include <unordered_set>
#include <type_traits>
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
        Direction from,
        int m,
        int n) const
    {
        if (board[m][n] == to(BoardItem::X)
            || O_regionVCSet.find({m, n}) != O_regionVCSet.cend())
        {
            return;
        }

        O_regionVCSet.emplace(m, n);

        if (from != Direction::LEFT
            && n - 1 >= 0)
        {
            findRegion(
                board, O_regionVCSet, Direction::RIGHT, m, n - 1);
        }

        if (from != Direction::RIGHT
            && n + 1 < board[m].size())
        {
            findRegion(
                board, O_regionVCSet, Direction::LEFT, m, n + 1);
        }

        if (from != Direction::UP
            && m - 1 >= 0)
        {
            findRegion(
                board, O_regionVCSet, Direction::DOWN, m - 1, n);
        }

        if (from != Direction::DOWN
            && m + 1 < board.size())
        {
            findRegion(
                board, O_regionVCSet, Direction::UP, m + 1, n);
        }
    }
};

inline void check(
    const std::vector<std::vector<char>>& board,
    std::vector<std::vector<char>> expected)
{
    assert(board == expected);
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
        check(board,
              {{'X', 'X', 'X', 'X'},
               {'X', 'X', 'X', 'X'},
               {'X', 'X', 'X', 'X'},
               {'X', 'O', 'X', 'X'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'X'}};

        Solution().solve(board);
        check(board,
              {{'X'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'O'}};

        Solution().solve(board);
        check(board,
              {{'O'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'X'}};

        Solution().solve(board);
        check(board,
              {{'X'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'O', 'O'},
            {'O', 'O'}};

        Solution().solve(board);
        check(board,
              {{'O', 'O'},
               {'O', 'O'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'X', 'O'},
            {'O', 'X'}};

        Solution().solve(board);
        check(board,
              {{'X', 'O'},
               {'O', 'X'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'X', 'X', 'X'},
            {'X', 'O', 'X'},
            {'X', 'X', 'X'}};

        Solution().solve(board);
        check(board,
              {{'X', 'X', 'X'},
               {'X', 'X', 'X'},
               {'X', 'X', 'X'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'O', 'X', 'X'},
            {'X', 'O', 'X'},
            {'X', 'X', 'O'}};

        Solution().solve(board);
        check(board,
              {{'O', 'X', 'X'},
               {'X', 'X', 'X'},
               {'X', 'X', 'O'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'X', 'X', 'X', 'X', 'X'},
            {'X', 'O', 'X', 'O', 'X'},
            {'X', 'X', 'O', 'X', 'X'},
            {'X', 'O', 'X', 'O', 'X'},
            {'X', 'X', 'X', 'X', 'X'}};

        Solution().solve(board);
        check(board,
              {{'X', 'X', 'X', 'X', 'X'},
               {'X', 'X', 'X', 'X', 'X'},
               {'X', 'X', 'X', 'X', 'X'},
               {'X', 'X', 'X', 'X', 'X'},
               {'X', 'X', 'X', 'X', 'X'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'O', 'O', 'O', 'O'},
            {'O', 'X', 'X', 'O'},
            {'O', 'X', 'X', 'O'},
            {'O', 'O', 'O', 'O'}};

        Solution().solve(board);
        check(board,
              {{'O', 'O', 'O', 'O'},
               {'O', 'X', 'X', 'O'},
               {'O', 'X', 'X', 'O'},
               {'O', 'O', 'O', 'O'}});
    }

    {
        std::vector<std::vector<char>> board{
            {'X', 'O', 'X', 'O', 'X'},
            {'O', 'X', 'O', 'X', 'O'},
            {'X', 'O', 'O', 'O', 'X'},
            {'O', 'X', 'O', 'X', 'O'},
            {'X', 'O', 'X', 'O', 'X'}};

        Solution().solve(board);
        check(board,
              {{'X', 'O', 'X', 'O', 'X'},
               {'O', 'X', 'X', 'X', 'O'},
               {'X', 'X', 'X', 'X', 'X'},
               {'O', 'X', 'X', 'X', 'O'},
               {'X', 'O', 'X', 'O', 'X'}});
    }

    return 0;
}
