#include <vector>
#include <unordered_set>
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
    std::vector<std::string> findWords(
        std::vector<std::vector<char>> board,
        std::vector<std::string> words)
    {
        if (words.empty() || board.empty())
        {
            return {};
        }

        std::vector<std::string> foundWords;

        for (int y = 0; y < board.size(); ++y)
        {
            for (int x = 0; x < board[y].size(); ++x)
            {
                for (const auto& word : words)
                {
                    findWord(board,
                             word,
                             foundWords,
                             {},
                             0,
                             y,
                             x);
                }
            }
        }

        return foundWords;
    }

private :
    bool findWord(
        const std::vector<std::vector<char>>& board,
        const std::string& word,
        std::vector<std::string>& foundWords,
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
            foundWords.emplace_back(word);

            return true;
        }

        auto seenCoords2 = seenCoords;

        seenCoords2.emplace(y, x);

        return findWord(board, word, foundWords, seenCoords2, n + 1, y - 1, x)
            || findWord(board, word, foundWords, seenCoords2, n + 1, y + 1, x)
            || findWord(board, word, foundWords, seenCoords2, n + 1, y, x - 1)
            || findWord(board, word, foundWords, seenCoords2, n + 1, y, x + 1);
    }
};

inline void check(
    const std::vector<std::string>& words,
    std::vector<std::string> expected)
{
    assert(words == expected);
}

int main()
{
    check(Solution().findWords(
        {{'o', 'a', 'n', 'n'},
         {'e', 't', 'a', 'e'},
         {'i', 'h', 'k', 'r'},
         {'i', 'f', 'l', 'v'}},
        {"oath", "pea", "eat", "rain"}),
          {"oath", "eat"});
    check(Solution().findWords(
        {{'a', 'b'},
         {'c', 'd'}},
        {"abcb"}),
          {});
    check(Solution().findWords(
        {{'a', 'b'},
         {'c', 'd'}},
        {"ab", "ba", "cd", "dc", "ac", "ca", "bd", "db"}),
          {"ab", "ac", "ba", "bd", "cd", "ca", "dc", "db"});

    return 0;
}
