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
            if (isAnagram(words[n - 1], words[n]))
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

private :
    [[nodiscard]]
    inline bool isAnagram(
        std::string s, std::string s2) const
    {
        std::sort(s.begin(), s.end());
        std::sort(s2.begin(), s2.end());

        return s == s2;
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
    check(Solution().removeAnagrams({"abc", "bca", "cab", "xyz", "zyx", "yxz"}),
          {"abc", "xyz"});
    check(Solution().removeAnagrams({"aa", "aa", "aa"}),
          {"aa"});
    check(Solution().removeAnagrams({"ab", "ba", "abc", "cba", "abcd", "dcba"}),
          {"ab", "abc", "abcd"});
    check(Solution().removeAnagrams({"x", "xx", "xxx", "x"}),
          {"x", "xx", "xxx", "x"});
    check(Solution().removeAnagrams({"listen", "silent", "enlist", "google", "gogole"}),
          {"listen", "google"});
    check(Solution().removeAnagrams({"rat", "tar", "art", "car", "arc"}),
          {"rat", "car"});
    check(Solution().removeAnagrams({"one", "two", "three"}),
          {"one", "two", "three"});
    check(Solution().removeAnagrams({"zzz", "zzz", "zzz", "az", "za"}),
          {"zzz", "az"});
    check(Solution().removeAnagrams({"a", "ab", "ba", "abc", "cab", "bca", "abcd"}),
          {"a", "ab", "abc", "abcd"});

    return 0;
}
