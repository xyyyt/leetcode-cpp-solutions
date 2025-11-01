#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cassert>

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
            findAllConcatenatedWordsInADict(
                words, concatenatedWords, 0, n);
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

        auto substr = std::string_view(
            word).substr(substrStart);

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

            std::string_view substrPrefix(
                substr.data(), word2Size);

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

inline void check(
    const std::vector<std::string>& concatenatedWords,
    std::vector<std::string> expected)
{
    assert(concatenatedWords == expected);
}

int main()
{
    check(Solution().findAllConcatenatedWordsInADict(
        {"cat","cats","catsdogcats","dog","dogcatsdog",
         "hippopotamuses","rat","ratcatdogcat"}),
        {"catsdogcats", "dogcatsdog", "ratcatdogcat"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"cat","dog","catdog"}),
        {"catdog"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"a","b","ab","abc","abcd","abcab","abcabc"}),
        {"ab","abcab","abcabc"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"tree","house","treehouse","home","homehouse","househome"}),
        {"treehouse","homehouse","househome"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"star","light","starlight","moon","moonstar","moonstarlight"}),
        {"starlight","moonstar","moonstarlight"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"blue","berry","blueberry","black","blackberry","berryblue"}),
        {"blueberry","blackberry","berryblue"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"sun","flower","sunflower","sunflow","flowersun"}),
        {"sunflower","flowersun"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"rock","star","rockstar","rockrock","starrock"}),
        {"rockstar","rockrock","starrock"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"base","ball","baseball","ballbase","ballball"}),
        {"baseball","ballbase","ballball"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"rain","bow","rainbow","rainrain","bowrain"}),
        {"rainbow","rainrain","bowrain"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"note","book","notebook","booknote","notebooknote"}),
        {"notebook","booknote","notebooknote"});
    check(Solution().findAllConcatenatedWordsInADict(
        {"pan","cake","pancake","cakepan","pancakepan"}),
        {"pancake","cakepan","pancakepan"});

    return 0;
}
