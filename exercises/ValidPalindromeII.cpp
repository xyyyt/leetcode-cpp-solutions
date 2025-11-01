#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

class Solution
{
public :
    bool validPalindrome(std::string s)
    {
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
    std::cout << std::boolalpha;
    std::cout << Solution().validPalindrome("aba") << '\n';
    std::cout << Solution().validPalindrome("abca") << '\n';
    std::cout << Solution().validPalindrome("abc") << '\n';

    return 0;
}
