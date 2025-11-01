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

        // startIOTLP = start Indice Of The Longest Palindrome
        size_t startIOTLP = 0;

        // longestPL = longest Palindrome Length
        size_t longestPL = 1;

        for (int n = 0; n < s.size() - 1; ++n)
        {
            for (int n2 = n + 1; n2 < s.size(); ++n2)
            {
                size_t substrSize = n2 - n;

                if (substrSize < longestPL)
                {
                    continue;
                }

                std::string_view s2(s.data() + n, substrSize + 1);

                if (std::equal(
                    s2.cbegin(),
                    s2.cbegin() + (s2.size() / 2),
                    s2.crbegin()))
                {
                    startIOTLP = n;
                    longestPL = s2.size();
                }
            }
        }

        return std::string(s.data(), startIOTLP, longestPL);
    }
};

int main()
{
    assert(Solution().longestPalindrome("babad") == "bab");
    assert(Solution().longestPalindrome("cbbd") == "bb");
    assert(Solution().longestPalindrome("a") == "a");
    assert(Solution().longestPalindrome("aaaaa") == "aaaaa");
    assert(Solution().longestPalindrome("abc") == "a");
    assert(Solution().longestPalindrome("cbbd") == "bb");
    assert(Solution().longestPalindrome("racecarxyz") == "racecar");
    assert(Solution().longestPalindrome("xyzracecar") == "racecar");
    assert(Solution().longestPalindrome("abacdfgdcaba") == "aba");
    assert(Solution().longestPalindrome("aacabdkacaa") == "aca");
    assert(Solution().longestPalindrome("abccba") == "abccba");
    assert(Solution().longestPalindrome("forgeeksskeegfor") == "geeksskeeg");
    assert(Solution().longestPalindrome("a!b!a") == "a!b!a");
    assert(Solution().longestPalindrome("123454321abc") == "123454321");
    assert(Solution().longestPalindrome("") == "");

    return 0;
}
