#include <string>
#include <string_view>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    int countSubstrings(std::string s)
    {
        if (s.empty())
        {
            return 0;
        }

        int palindromeCounter = 0;

        for (int n = 0; n < s.size(); ++n)
        {
            ++palindromeCounter;

            for (int n2 = n + 1; n2 < s.size(); ++n2)
            {
                std::string_view s2(s.data() + n, (n2 - n) + 1);

                if (std::equal(s2.cbegin(), s2.cend(), s2.crbegin()))
                {
                    ++palindromeCounter;
                }
            }
        }

        return palindromeCounter;
    }
};

int main()
{
    std::cout << Solution().countSubstrings("abc") << '\n';
    std::cout << Solution().countSubstrings("aaa") << '\n';

    return 0;
}
