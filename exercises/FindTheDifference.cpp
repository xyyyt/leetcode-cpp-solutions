#include <string>
#include <cassert>

class Solution
{
public :
    char findTheDifference(std::string s, std::string t)
    {
        if (s.size() >= t.size())
        {
            return 0;
        }

        int n = 0;

        while (n < s.size() && s[n] == t[n])
        {
            ++n;
        }

        return t[n];
    }
};

int main()
{
    assert(Solution().findTheDifference("abcd", "abcde") == 'e');
    assert(Solution().findTheDifference("efgh", "eflgh") == 'l');
    assert(Solution().findTheDifference("b", "ab") == 'a');
    assert(Solution().findTheDifference("", "y") == 'y');
    assert(Solution().findTheDifference("xyz", "wxyz") == 'w');
    assert(Solution().findTheDifference("aabb", "ababb") == 'b');
    assert(Solution().findTheDifference("abc!", "abc!?") == '?');
    assert(Solution().findTheDifference("leetcode", "leetcoded") == 'd');
    assert(Solution().findTheDifference("aaa", "aaaa") == 'a');
    assert(Solution().findTheDifference("qwerty", "qwertyy") == 'y');

    return 0;
}
