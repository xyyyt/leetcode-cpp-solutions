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

    return 0;
}
