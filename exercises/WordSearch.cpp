#include <unordered_set>
#include <vector>
#include <string>
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
    bool exist(
        std::vector<std::vector<char>> board, std::string word)
    {
        if (board.empty())
        {
            return false;
        }
        else if (word.empty())
        {
            return true;
        }

        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board[y].size(); ++x)
            {
                if (exist(board, word, {}, 0, y, x))
                {
                    return true;
                }
            }
        }

        return false;
    }

private :
    [[nodiscard]]
    bool exist(
        const std::vector<std::vector<char>>& board,
        const std::string& word,
        const std::unordered_set<std::pair<int, int>>& seenCoords,
        int n,
        int y,
        int x) const
    {
        if ((y < 0 || y >= board.size())
            || (x < 0 || x >= board[y].size())
            || seenCoords.find({y, x}) != seenCoords.cend()
            || board[y][x] != word[n])
        {
            return false;
        }
        else if (n >= word.size() - 1)
        {
            return true;
        }

        auto seenCoords2 = seenCoords;

        seenCoords2.emplace(y, x);

        return exist(board, word, seenCoords2, n + 1, y - 1, x)
            || exist(board, word, seenCoords2, n + 1, y + 1, x)
            || exist(board, word, seenCoords2, n + 1, y, x - 1)
            || exist(board, word, seenCoords2, n + 1, y, x + 1);
    }
};

int main()
{
    assert(Solution().exist(
        {{'A', 'B', 'C', 'E'},{'S', 'F', 'C', 'S'},{'A', 'D', 'E', 'E'}},
        "ABCCED"));
    assert(Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "SEE"));
    assert(!Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "ABCB"));
    assert(!Solution().exist(
        {{'A', 'B', 'C', 'E'},{'S', 'F', 'C', 'S'},{'A', 'D', 'E', 'E'}},
        "FES"));
    assert(Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "SEC"));
    assert(Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "DFSA"));
    assert(!Solution().exist(
        {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
        "BFDCCE"));

    return 0;
}
