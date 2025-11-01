#include <string>
#include <string_view>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::string longestPalindrome(std::string s)
    {
        if (s.empty())
        {
            return {};
        }

        // startIOTLP = start Incice Of The Longest Palindrome
        size_t startIOTLP = 0;

        // longestPL = longest Palindrome Length
        size_t longestPL = 0;

        for (int n = 0; n < s.size() - 1; ++n)
        {
            for (int n2 = n + 1; n2 < s.size(); ++n2)
            {
                std::string_view s2(s.data() + n, (n2 - n) + 1);

                if (std::equal(
                        s2.cbegin(),
                        s2.cbegin() + (s2.size() / 2),
                        s2.crbegin()))
                {
                    startIOTLP = n;
                    longestPL = std::max(longestPL, s2.size());
                }
            }
        }

        return std::string(s.data(), startIOTLP, longestPL);
    }
};

int main()
{
    assert(Solution().longestPalindrome("babad") == "aba");
    assert(Solution().longestPalindrome("cbbd") == "bb");

    return 0;
}
