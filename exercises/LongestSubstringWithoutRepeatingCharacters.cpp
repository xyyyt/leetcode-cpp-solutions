#include <iostream>
#include <unordered_set>
#include <string>

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
    std::cout << Solution().lengthOfLongestSubstr("abcabcbb") << '\n';
    std::cout << Solution().lengthOfLongestSubstr("bbbbb") << '\n';
    std::cout << Solution().lengthOfLongestSubstr("pwwkew") << '\n';

    return 0;
}
