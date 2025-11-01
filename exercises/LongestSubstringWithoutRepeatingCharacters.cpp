#include <unordered_set>
#include <string>
#include <cassert>

class Solution
{
public :
    int lengthOfLongestSubstr(std::string s)
    {
        if (s.empty())
        {
            return 0;
        }

        std::unordered_set<char> seen;
        int longestSubstr = 0;
        int left = 0;
        int right = 0;

        while (right < s.size())
        {
            if (seen.emplace(s[right]).second)
            {
                ++right;
            }
            else
            {
                longestSubstr = std::max(longestSubstr, right - left);

                while (left < right && s[left] != s[right])
                {
                    ++left;
                }

                while (left < right && s[left] == s[right])
                {
                    ++left;
                }

                ++right;
            }
        }

        return std::max(longestSubstr, right - left);
    }
};

int main()
{
    assert(Solution().lengthOfLongestSubstr("abcabcbb") == 3);
    assert(Solution().lengthOfLongestSubstr("bbbbb") == 1);
    assert(Solution().lengthOfLongestSubstr("pwwkew") == 3);
    assert(Solution().lengthOfLongestSubstr("abcdef") == 6);
    assert(Solution().lengthOfLongestSubstr("abba") == 2);
    assert(Solution().lengthOfLongestSubstr("a!b!c") == 3);
    assert(Solution().lengthOfLongestSubstr("123451234") == 5);
    assert(Solution().lengthOfLongestSubstr("") == 0);
    assert(Solution().lengthOfLongestSubstr("z") == 1);
    assert(Solution().lengthOfLongestSubstr("dvdf") == 3);
    assert(Solution().lengthOfLongestSubstr("abcdefghijklmnopqrstuvwxyza") == 26);

    return 0;
}
