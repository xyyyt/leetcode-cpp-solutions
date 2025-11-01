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
    int countBattleships(std::vector<std::vector<char>> board)
    {
        if (board.empty())
        {
            return 0;
        }

        VCSet_t battleshipVCSet;
        int battleshipCounter = 0;

        for (int m = 0; m < board.size(); ++m)
        {
            for (int n = 0; n < board[m].size(); ++n)
            {
                if (board[m][n] == to(BoardItem::BATTLESHIP)
                    && battleshipVCSet.find({m, n}) == battleshipVCSet.cend())
                {
                    VCSet_t battleshipVCSet2;

                    findBiggerBattleships(
                        board,
                        battleshipVCSet,
                        battleshipVCSet2,
                        Direction::RIGHT,
                        m, n);

                    if (battleshipVCSet2.size() < 2)
                    {
                        findBiggerBattleships(
                            board,
                            battleshipVCSet,
                            battleshipVCSet2,
                            Direction::DOWN,
                            m,
                            n);
                    }

                    battleshipVCSet.merge(battleshipVCSet2);
                    ++battleshipCounter;
                }
            }
        }

        return battleshipCounter;
    }

private :
    enum class BoardItem : char { BATTLESHIP = 'X', EMPTY = '.' };
    enum class Direction : uint8_t { RIGHT, DOWN };

    using BoardItemUnderlying_t = typename std::underlying_type<BoardItem>::type;

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;

    [[nodiscard]]
    inline static constexpr BoardItemUnderlying_t to(BoardItem item) noexcept
    {
        return static_cast<BoardItemUnderlying_t>(item);
    }

    void findBiggerBattleships(
        const std::vector<std::vector<char>>& board,
        const VCSet_t& battleshipVCSet,
        VCSet_t& battleshipVCSet2,
        Direction directionWhereToGo,
        int m,
        int n) const
    {
        if (board[m][n] == to(BoardItem::EMPTY)
            || battleshipVCSet.find({m, n}) != battleshipVCSet.cend())
        {
            return;
        }

        battleshipVCSet2.emplace(m, n);

        if (directionWhereToGo == Direction::RIGHT
            && n + 1 < board[m].size())
        {
            findBiggerBattleships(
                board,
                battleshipVCSet,
                battleshipVCSet2,
                Direction::RIGHT,
                m,
                n + 1);
        }
        else if (directionWhereToGo == Direction::DOWN
            && m + 1 < board.size())
        {
            findBiggerBattleships(
                board,
                battleshipVCSet,
                battleshipVCSet2,
                Direction::DOWN,
                m + 1,
                n);
        }
    }
};

int main()
{
    std::cout << Solution().countBattleships({
        {'X', '.', '.', 'X'},
        {'.', '.', '.', 'X'},
        {'.', '.', '.', 'X'}})
              << '\n';
    std::cout << Solution().countBattleships({
        {'.'}})
              << '\n';

    return 0;
}
