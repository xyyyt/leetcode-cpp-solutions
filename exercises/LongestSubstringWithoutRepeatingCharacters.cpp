#include <unordered_set>
#include <string>
#include <cassert>

class Solution
{
public :
    int lengthOfLongestSubstr(std::string s)
    {
        std::unordered_set<char> charAlreadyMet;
        int longestSubstr = 0;
        int currentSubstrLength = 0;

        charAlreadyMet.reserve(s.size());

        for (auto c : s)
        {
            if (!charAlreadyMet.emplace(c).second)
            {
                longestSubstr = std::max(longestSubstr, currentSubstrLength);
                charAlreadyMet.clear();
                currentSubstrLength = 0;
            }
            else
            {
                ++currentSubstrLength;
            }
        }

        return std::max(longestSubstr, currentSubstrLength);
    }
};

int main()
{
    assert(Solution().lengthOfLongestSubstr("abcabcbb") == 3);
    assert(Solution().lengthOfLongestSubstr("bbbbb") == 1);
    assert(Solution().lengthOfLongestSubstr("pwwkew") == 3);

    return 0;
}
