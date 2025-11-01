#include <algorithm>
#include <string>
#include <cassert>

class Solution
{
public :
    bool isAnagram(std::string s, std::string t)
    {
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());

        return s == t;
    }
};

int main()
{
    assert(Solution().isAnagram("anagram", "nagaram"));
    assert(!Solution().isAnagram("rat", "car"));
    assert(Solution().isAnagram("", ""));
    assert(!Solution().isAnagram("a", ""));
    assert(Solution().isAnagram("aabb", "baba"));
    assert(!Solution().isAnagram("aabb", "abca"));
    assert(!Solution().isAnagram("Listen", "Silent"));
    assert(Solution().isAnagram("a!b", "b!a"));
    assert(!Solution().isAnagram("ab!", "a!c"));

    return 0;
}
