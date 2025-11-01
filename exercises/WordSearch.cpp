#include <unordered_set>
#include <vector>
#include <list>
#include <string>
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

class Solution
{
public :
    bool exist(std::vector<std::vector<char>> board, std::string word)
    {
        if (word.empty())
        {
            return true;
        }
        else if (board.empty())
        {
            return false;
        }

        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board[y].size(); ++x)
            {
                if (exist(board, word, {}, /* {}, */ Direction::UNKNOWN, y, x, 0))
                {
                    return true;
                }
            }
        }

        return false;
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN, UNKNOWN };

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;
    // using VCSetConstIterator_t = VCSet_t::const_iterator;

    // For debug only
    // using VCList_t = std::list<VCSetConstIterator_t>;

    [[nodiscard]]
    bool exist(
        const std::vector<std::vector<char>>& board,
        std::string_view word,
        const VCSet_t& vcSet,
        // const VCList_t& vcList,
        Direction fromDirection,
        int boardY,
        int boardX,
        int pos) const
    {
        if (pos >= word.size())
        {
            // for (const auto& itFromVCSet : vcList)
            // {
            //     std::cout << "y : "
            //               << itFromVCSet->first
            //               << ", x : "
            //               << itFromVCSet->second
            //               << '\n';
            // }

            return true;
        }

        if (vcSet.find({boardY, boardX}) != vcSet.cend()
            || board[boardY][boardX] != word[pos])
        {
            return false;
        }

        auto moveToCell = [&](
            Direction fromDirection2,
            int boardY2,
            int boardX2,
            int pos2) -> bool
        {
            VCSet_t vcSet2 = vcSet;
            // VCList_t vcList2 = vcList;

            [[maybe_unused]] auto res = vcSet2.emplace(
                boardY, boardX);

            // vcList2.emplace_back(res.first);

            return exist(board,
                         word,
                         vcSet2,
                         // vcList2,
                         fromDirection2,
                         boardY2,
                         boardX2,
                         pos2);
        };

        return (fromDirection != Direction::LEFT
                && boardX - 1 >= 0
                && moveToCell(Direction::RIGHT, boardY, boardX - 1, pos + 1))
            || (fromDirection != Direction::RIGHT
                && boardX + 1 < board[boardY].size()
                && moveToCell(Direction::LEFT, boardY, boardX + 1, pos + 1))
            || (fromDirection != Direction::UP
                 && boardY - 1 >= 0
                 && moveToCell(Direction::DOWN, boardY - 1, boardX, pos + 1))
            || (fromDirection != Direction::DOWN
                && boardY + 1 < board.size()
                && moveToCell(Direction::UP, boardY + 1, boardX, pos + 1));
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().exist(
        {{'A', 'B', 'C', 'E'},{'S', 'F', 'C', 'S'},{'A', 'D', 'E', 'E'}},
        "ABCCED")
              << '\n';
    std::cout << Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "SEE")
              << '\n';
    std::cout << Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "ABCB")
              << '\n';
    std::cout << Solution().exist(
        {{'A', 'B', 'C', 'E'},{'S', 'F', 'C', 'S'},{'A', 'D', 'E', 'E'}},
        "FES")
              << '\n';
    std::cout << Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "SEC")
              << '\n';
    std::cout << Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "DFSA")
              << '\n';
    std::cout << Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "BFDCCE")
              << '\n';

    return 0;
}
