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
        return (s.empty() || wordDict.empty()) ?
            false : _wordBreak(s, wordDict);
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

    return 0;
}
