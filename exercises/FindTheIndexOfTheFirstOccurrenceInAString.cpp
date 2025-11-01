#include <string>
#include <cassert>

class Solution
{
public :
    int strStr(std::string haystack, std::string needle)
    {
        if (needle.empty())
        {
            return 0;
        }
        else if (haystack.empty())
        {
            return -1;
        }

        for (int n = 0; n < haystack.size(); ++n)
        {
            if (haystack[n] == needle[0])
            {
                int n2 = n;
                int n3 = 0;

                while (n2 < haystack.size()
                       && n3 < needle.size()
                       && haystack[n2] == needle[n3])
                {
                    ++n2;
                    ++n3;
                }

                if (n3 >= needle.size())
                {
                    return n;
                }
            }
        }

        return -1;
    }
};

int main()
{
    assert(Solution().strStr("sadbutsad", "sad") == 0);
    assert(Solution().strStr("sadbutsad", "but") == 3);
    assert(Solution().strStr("leetcode", "leeto") == -1);
    assert(Solution().strStr("hello", "ll") == 2);
    assert(Solution().strStr("aaaaa", "bba") == -1);
    assert(Solution().strStr("mississippi", "issip") == 4);
    assert(Solution().strStr("abcabcabcabc", "cab") == 2);
    assert(Solution().strStr("abababab", "abab") == 0);
    assert(Solution().strStr("abababab", "bab") == 1);
    assert(Solution().strStr("", "") == 0);
    assert(Solution().strStr("a", "") == 0);
    assert(Solution().strStr("", "a") == -1);
    assert(Solution().strStr("a", "a") == 0);
    assert(Solution().strStr("abc", "c") == 2);

    return 0;
}
