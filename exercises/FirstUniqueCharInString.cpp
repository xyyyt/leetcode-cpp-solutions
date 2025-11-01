#include <unordered_map>
#include <string>
#include <cassert>

class Solution
{
public :
    int firstUniqueChar(std::string s)
    {
        if (s.empty())
        {
            return -1;
        }

        std::unordered_map<char, int> charCounter;

        charCounter.reserve(s.size());

        for (auto c : s)
        {
            ++charCounter[c];
        }

        for (int n = 0; n < s.size(); ++n)
        {
            if (charCounter[s[n]] == 1)
            {
                return n;
            }
        }

        return -1;
    }
};

int main()
{
    assert(Solution().firstUniqueChar("leetcode") == 0);
    assert(Solution().firstUniqueChar("loveleetcode") == 2);
    assert(Solution().firstUniqueChar("aabb") == -1);
    assert(Solution().firstUniqueChar("abcabcde") == 6);
    assert(Solution().firstUniqueChar("z") == 0);
    assert(Solution().firstUniqueChar("aaabcccdeeef") == 3);
    assert(Solution().firstUniqueChar("abcdefghijklmno") == 0);
    assert(Solution().firstUniqueChar("aabbccddeeffg") == 12);
    assert(Solution().firstUniqueChar("") == -1);
    assert(Solution().firstUniqueChar("aaaaaaa") == -1);

    return 0;
}
