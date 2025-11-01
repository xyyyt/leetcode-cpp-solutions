#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<std::string> removeAnagrams(
        std::vector<std::string> words)
    {
        if (words.size() < 2)
        {
            return words;
        }

        auto it = words.begin() + 1;
        int n = 1;

        while (n < words.size())
        {
            std::string s = words[n - 1];
            std::string s2 = words[n];

            std::sort(s.begin(), s.end());
            std::sort(s2.begin(), s2.end());

            if (s == s2)
            {
                it = words.erase(it);
            }
            else
            {
                ++it;
                ++n;
            }
        }

        return words;
    }
};

inline void check(
    const std::vector<std::string>& words,
    std::vector<std::string> expected)
{
    assert(words == expected);
}

int main()
{
    check(Solution().removeAnagrams({"abba", "baba", "bbaa", "cd", "cd"}),
          {"abba", "cd"});
    check(Solution().removeAnagrams({"a", "b", "c", "d", "e"}),
          {"a", "b", "c", "d", "e"});
    check(Solution().removeAnagrams({"a", "b", "a"}),
          {"a", "b", "a"});

    return 0;
}
