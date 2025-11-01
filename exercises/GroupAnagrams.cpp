#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <string_view>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<std::string>> groupAnagrams(
        std::vector<std::string> strs)
    {
        if (strs.empty())
        {
            return {};
        }

        std::vector<std::vector<std::string>> anagramGroups;
        std::list<std::string_view> strsCopy(
            strs.cbegin(), strs.cend());

        while (!strsCopy.empty())
        {
            auto firstStr = strsCopy.front();
            auto firstStrLetterCounter = getLetterCounter(firstStr);

            strsCopy.pop_front();

            std::vector<std::string> anagramGroup{
                std::string(firstStr.data(), firstStr.size())};
            auto begin = strsCopy.begin();
            auto end = strsCopy.end();

            while (begin != end)
            {
                auto strLetterCounter = getLetterCounter(*begin);

                if (firstStrLetterCounter == strLetterCounter)
                {
                    anagramGroup.emplace_back(*begin);
                    begin = strsCopy.erase(begin);
                }
                else
                {
                    ++begin;
                }
            }

            anagramGroups.emplace_back(std::move(anagramGroup));
        }

        return anagramGroups;
    }

private :
    [[nodiscard]]
    std::unordered_map<char, int> getLetterCounter(
        std::string_view str) const
    {
        std::unordered_map<char, int> letterCounter;

        letterCounter.reserve(str.size());

        for (auto c : str)
        {
            ++letterCounter[c];
        }

        return letterCounter;
    }
};

inline void check(
    const std::vector<std::vector<std::string>>& anagramGroups,
    std::vector<std::vector<std::string>> expected)
{
    assert(anagramGroups == expected);
}

int main()
{
    check(Solution().groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"}),
          {{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}});
    check(Solution().groupAnagrams({""}),
          {{""}});
    check(Solution().groupAnagrams({"a"}),
          {{"a"}});
    check(Solution().groupAnagrams({"abc", "bca", "cab", "xyz", "zyx", "yxz"}),
          {{"abc", "bca", "cab"}, {"xyz", "zyx", "yxz"}});
    check(Solution().groupAnagrams({"listen", "silent", "enlist", "google", "gogole"}),
          {{"listen", "silent", "enlist"}, {"google", "gogole"}});
    check(Solution().groupAnagrams({"rat", "tar", "art", "car"}),
          {{"rat", "tar", "art"}, {"car"}});
    check(Solution().groupAnagrams({"loop", "polo", "pool", "lopo", "test"}),
          {{"loop", "polo", "pool", "lopo"}, {"test"}});
    check(Solution().groupAnagrams({"abc", "def", "ghi"}),
          {{"abc"}, {"def"}, {"ghi"}});
    check(Solution().groupAnagrams({"aa", "aa", "aa"}),
          {{"aa", "aa", "aa"}});
    check(Solution().groupAnagrams({"one", "neo", "eon", "two"}),
          {{"one", "neo", "eon"}, {"two"}});
    check(Solution().groupAnagrams({"dusty", "study", "cat", "tac", "act"}),
          {{"dusty", "study"}, {"cat", "tac", "act"}});
    check(Solution().groupAnagrams({"abcd", "bcad", "dabc", "efgh"}),
          {{"abcd", "bcad", "dabc"}, {"efgh"}});
    check(Solution().groupAnagrams({"", "b", "bb", "bbb"}),
          {{""}, {"b"}, {"bb"}, {"bbb"}});

    return 0;
}
