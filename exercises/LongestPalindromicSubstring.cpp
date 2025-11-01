#include <string>
#include <string_view>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    std::string longestPalindrome(std::string s)
    {
        if (s.empty())
        {
            return {};
        }

        size_t startIndiceOfTheLongestPalindrome = 0;
        size_t longestPalindromeLength = 0;

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
                    startIndiceOfTheLongestPalindrome = n;
                    longestPalindromeLength = std::max(
                        longestPalindromeLength, s2.size());
                }
            }
        }

        return std::string(
            s.data(),
            startIndiceOfTheLongestPalindrome,
            longestPalindromeLength);
    }
};

int main()
{
    std::cout << Solution().longestPalindrome("babad") << '\n';
    std::cout << Solution().longestPalindrome("cbbd") << '\n';

    return 0;
}
