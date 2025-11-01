#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>

class Solution
{
public :
    bool validPalindrome(std::string s)
    {
        if (s.empty())
        {
            return true;
        }

        s.erase(std::remove_if(s.begin(),
                               s.end(),
                               [](char c) noexcept -> bool
                               {
                                   return !std::isalnum(c);
                               }),
                s.end());

        if (s.empty())
        {
            return true;
        }

        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        if (std::equal(
            s.cbegin(), s.cbegin() + (s.size() / 2), s.crbegin()))
        {
            return true;
        }

        for (int n = 0; n < s.size(); ++n)
        {
            std::string s2;

            s2.reserve(s.size());

            for (int n2 = 0; n2 < s.size(); ++n2)
            {
                if (n == n2)
                {
                    continue;
                }

                s2.push_back(s[n2]);
            }

            if (std::equal(
                s2.cbegin(), s2.cbegin() + (s2.size() / 2), s2.crbegin()))
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    assert(Solution().validPalindrome("aba"));
    assert(Solution().validPalindrome("abca"));
    assert(!Solution().validPalindrome("abc"));
    assert(Solution().validPalindrome("aac"));
    assert(Solution().validPalindrome("caa"));
    assert(!Solution().validPalindrome("abccaa"));
    assert(Solution().validPalindrome("deeee"));
    assert(Solution().validPalindrome("aaaaabaaaaa"));
    assert(Solution().validPalindrome("123421"));
    assert(Solution().validPalindrome("a!ba"));
    assert(!Solution().validPalindrome("abcdef"));
    assert(Solution().validPalindrome(""));
    assert(Solution().validPalindrome("z"));
    assert(Solution().validPalindrome("ab"));

    return 0;
}
