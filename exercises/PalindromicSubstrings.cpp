#include <string>
#include <string_view>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    int countSubstrings(std::string s)
    {
        if (s.empty())
        {
            return 0;
        }

        int counter = 0;

        for (int n = 0; n < s.size(); ++n)
        {
            ++counter;

            for (int n2 = n + 1; n2 < s.size(); ++n2)
            {
                std::string_view s2(s.data() + n, (n2 - n) + 1);

                if (std::equal(
                    s2.cbegin(),
                    s2.cbegin() + (s2.size() / 2),
                    s2.crbegin()))
                {
                    ++counter;
                }
            }
        }

        return counter;
    }
};

int main()
{
    assert(Solution().countSubstrings("abc") == 3);
    assert(Solution().countSubstrings("aaa") == 6);
    assert(Solution().countSubstrings("aaaa") == 10);
    assert(Solution().countSubstrings("abccba") == 9);
    assert(Solution().countSubstrings("racecar") == 10);
    assert(Solution().countSubstrings("121") == 4);
    assert(Solution().countSubstrings("a!a") == 4);
    assert(Solution().countSubstrings("") == 0);
    assert(Solution().countSubstrings("z") == 1);
    assert(Solution().countSubstrings("abbaeae") == 11);
    assert(Solution().countSubstrings("ababa") == 9);

    return 0;
}
