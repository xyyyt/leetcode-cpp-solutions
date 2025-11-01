#include <string>
#include <cassert>

class Solution
{
public :
    int strStr(std::string haystack, std::string needle)
    {
        if (haystack.empty() || needle.empty())
        {
            return -1;
        }

        int n = 0;

        while (n < haystack.size())
        {
            if (haystack[n] == needle[0])
            {
                int oldN = n;
                int n2 = 0;

                while (n < haystack.size()
                       && n2 < needle.size()
                       && haystack[n] == needle[n2])
                {
                    ++n;
                    ++n2;
                }

                if (n2 == needle.size())
                {
                    return oldN;
                }
            }
            else
            {
                ++n;
            }
        }

        return -1;
    }
};

int main()
{
    assert(Solution().strStr("sadbutsad", "sad") == 0);
    assert(Solution().strStr("leetcode", "leeto") == -1);

    return 0;
}
