#include <vector>
#include <unordered_set>
#include <cstdint>
#include <type_traits>
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
    int countBattleships(std::vector<std::vector<char>> board)
    {
        if (board.empty())
        {
            return 0;
        }

        VCSet_t battleshipVCSet;
        int battleshipCounter = 0;

        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board[y].size(); ++x)
            {
                if (board[y][x] == to(BoardItem::BATTLESHIP)
                    && battleshipVCSet.find({y, x}) == battleshipVCSet.cend())
                {
                    VCSet_t battleshipVCSet2;

                    findBiggerBattleships(
                        board,
                        battleshipVCSet,
                        battleshipVCSet2,
                        Direction::RIGHT,
                        y,
                        x);

                    if (battleshipVCSet2.size() < 2)
                    {
                        findBiggerBattleships(
                            board,
                            battleshipVCSet,
                            battleshipVCSet2,
                            Direction::DOWN,
                            y,
                            x);
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
        Direction direction,
        int y,
        int x) const
    {
        if (board[y][x] == to(BoardItem::EMPTY)
            || battleshipVCSet.find({y, x}) != battleshipVCSet.cend())
        {
            return;
        }

        battleshipVCSet2.emplace(y, x);

        if (direction == Direction::RIGHT
            && x + 1 < board[y].size())
        {
            findBiggerBattleships(
                board,
                battleshipVCSet,
                battleshipVCSet2,
                Direction::RIGHT,
                y,
                x + 1);
        }
        else if (direction == Direction::DOWN
            && y + 1 < board.size())
        {
            findBiggerBattleships(
                board,
                battleshipVCSet,
                battleshipVCSet2,
                Direction::DOWN,
                y + 1,
                x);
        }
    }
};

int main()
{
    assert(Solution().countBattleships({
        {'X', '.', '.', 'X'},
        {'.', '.', '.', 'X'},
        {'.', '.', '.', 'X'}}) == 2);
    assert(Solution().countBattleships({
        {'.'}}) == 0);
    assert(Solution().countBattleships({
        {'X', 'X'},
        {'.', '.'}}) == 1);
    assert(Solution().countBattleships({
        {'X'},
        {'X'},
        {'X'}}) == 1);
    assert(Solution().countBattleships({
        {'.', '.', '.'},
        {'.', '.', '.'},
        {'.', '.', '.'}}) == 0);
    assert(Solution().countBattleships({
        {'X', '.', 'X'},
        {'.', '.', '.'},
        {'X', '.', 'X'}}) == 4);
    assert(Solution().countBattleships({
        {'X', 'X', 'X'},
        {'.', '.', '.'},
        {'X', '.', 'X'}}) == 3);
    assert(Solution().countBattleships({
        {'X', '.', '.', '.'},
        {'X', '.', 'X', 'X'},
        {'.', '.', '.', 'X'}}) == 3);
    assert(Solution().countBattleships({
        {'X', '.', '.', 'X'},
        {'.', 'X', '.', '.'},
        {'X', '.', 'X', '.'},
        {'.', '.', '.', 'X'}}) == 6);
    assert(Solution().countBattleships({
        {'X'}}) == 1);

    return 0;
}
