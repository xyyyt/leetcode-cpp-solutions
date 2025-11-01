#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    std::vector<std::string> findAllConcatenatedWordsInADict(
        std::vector<std::string> words)
    {
        if (words.empty())
        {
            return {};
        }

        std::vector<std::string> concatenatedWords;

        concatenatedWords.reserve(words.size());

        for (int n = 0; n < words.size(); ++n)
        {
            findAllConcatenatedWordsInADict(words, concatenatedWords, 0, n);
        }

        return concatenatedWords;
    }

private :
    bool findAllConcatenatedWordsInADict(
        const std::vector<std::string>& words,
        std::vector<std::string>& concatenatedWords,
        int substrStart,
        int pos) const
    {
        const auto& word = words[pos];

        if (substrStart >= word.size())
        {
            concatenatedWords.emplace_back(word);

            return true;
        }

        std::string_view substr =
            std::string_view(word).substr(substrStart);

        for (int n = 0; n < words.size(); ++n)
        {
            if (n == pos)
            {
                continue;
            }

            const auto& word2 = words[n];
            size_t word2Size = word2.size();

            if (substr.size() < word2Size)
            {
                continue;
            }

            std::string_view substrPrefix(substr.data(), word2Size);

            if (substrPrefix == word2
                && findAllConcatenatedWordsInADict(
                       words,
                       concatenatedWords,
                       substrStart + word2Size,
                       pos))
            {
                return true;
            }
        }

        return false;
    }
};

std::ostream& operator<<(
    std::ostream& os, std::vector<std::string> concatenatedWords) noexcept
{
    if (concatenatedWords.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = concatenatedWords.cbegin();
    auto end = concatenatedWords.cend();

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
    std::cout << Solution().findAllConcatenatedWordsInADict(
        {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"})
              << '\n';
    std::cout << Solution().findAllConcatenatedWordsInADict(
        {"cat","dog","catdog"})
              << '\n';

    return 0;
}
