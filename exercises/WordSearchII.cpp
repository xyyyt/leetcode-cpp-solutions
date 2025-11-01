#include <vector>
#include <unordered_set>
// #include <list>
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
    std::vector<std::string> findWords(
        std::vector<std::vector<char>> board,
        std::vector<std::string> words)
    {
        if (words.empty() || board.empty())
        {
            return {};
        }

        std::vector<std::string> wordsFound;

        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board[y].size(); ++x)
            {
                for (const auto& word : words)
                {
                    exist(board,
                          word,
                          wordsFound,
                          {},
                          /* {}, */
                          Direction::UNKNOWN,
                          y,
                          x,
                          0);
                }
            }
        }

        return wordsFound;
    }

private :
    enum class Direction : uint8_t { LEFT, RIGHT, UP, DOWN, UNKNOWN };

    // VC = Visited Cell
    using VCSet_t = std::unordered_set<std::pair<int, int>>;
    // using VCSetConstIterator_t = VCSet_t::const_iterator;

    // For debug only
    // using VCList_t = std::list<VCSetConstIterator_t>;

    bool exist(
        const std::vector<std::vector<char>>& board,
        std::string_view word,
        std::vector<std::string>& wordsFound,
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

            wordsFound.emplace_back(word);

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
                         wordsFound,
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

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::string>& words) noexcept
{
    if (words.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = words.cbegin();
    auto end = words.cend();

    os << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    return os;
}

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().findWords(
        {{'o', 'a', 'n', 'n'},
         {'e', 't', 'a', 'e'},
         {'i', 'h', 'k', 'r'},
         {'i', 'f', 'l', 'v'}},
        {"oath", "pea", "eat", "rain"})
              << '\n';
    std::cout << Solution().findWords(
        {{'a', 'b'}, {'c', 'd'}},
        {"abcb"})
              << '\n';
    std::cout << Solution().findWords(
        {{'a', 'b'}, {'c', 'd'}},
        {"ab", "ba", "cd", "dc", "ac", "ca", "bd", "db"})
              << '\n';

    return 0;
}
