#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    bool wordBreak(std::string s, std::vector<std::string> wordDict)
    {
        return (!wordDict.empty()) ? _wordBreak(s, wordDict) : false;
    }

private :
    [[nodiscard]]
    bool _wordBreak(
        std::string_view s, const std::vector<std::string>& wordDict) const
    {
        if (s.empty())
        {
            return true;
        }

        for (const auto& word : wordDict)
        {
            std::string_view prefix(
                s.data(), std::min(s.size(), word.size()));

            if (prefix == word
                && _wordBreak(s.substr(word.size()), wordDict))
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    assert(Solution().wordBreak(
        "leetcode", {"leet", "code"}));
    assert(Solution().wordBreak(
        "applepenapple", {"apple", "pen"}));
    assert(!Solution().wordBreak(
        "catsandod", {"cats", "dog", "sand", "and", "cat"}));
    assert(Solution().wordBreak(
         "banana", {"ban", "ba", "na"}));
    assert(Solution().wordBreak(
         "cars", {"car", "ca", "rs"}));
    assert(!Solution().wordBreak(
         "aaaaab", {"a", "aa", "aaa", "aaaa"}));
    assert(!Solution().wordBreak(
         "helloworldx", {"hello", "world"}));
    assert(Solution().wordBreak(
         "", {"a", "b"}));
    assert(!Solution().wordBreak(
         "anything", {}));
    assert(Solution().wordBreak(
         "aaaaaaa", {"aaaa", "aaa"}));

    return 0;
}
