#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

class Solution
{
public :
    std::vector<int> findSubstring(
        std::string s, std::vector<std::string> words)
    {
        if (s.empty() || words.empty())
        {
            return {};
        }

        std::vector<std::string> permutations;

        permutations.reserve(std::tgamma(words.size() + 1));
        getAllPermutations(words, permutations, 0);

        std::vector<int> startingIndices;

        for (int n = 0; n < s.size(); ++n)
        {
            for (const auto& permutation : permutations)
            {
                int n2 = n;
                int n3 = 0;

                while (n3 < permutation.size() && n2 < s.size())
                {
                    if (s[n2] != permutation[n3])
                    {
                        break;
                    }

                    ++n2;
                    ++n3;
                }

                if (n3 >= permutation.size())
                {
                    startingIndices.emplace_back(n);

                    break;
                }
            }
        }

        return startingIndices;
    }

private :
    void getAllPermutations(
        std::vector<std::string>& words,
        std::vector<std::string>& permutations,
        int n) const
    {
        if (n >= words.size())
        {
            auto concatAll = [](
                const std::vector<std::string>& words) -> std::string
            {
                std::string permutation;

                for (const auto& word : words)
                {
                    permutation += word;
                }

                return permutation;
            };

            permutations.emplace_back(concatAll(words));

            return;
        }

        for (int n2 = n; n2 < words.size(); ++n2)
        {
            std::swap(words[n], words[n2]);
            getAllPermutations(words, permutations, n + 1);
            std::swap(words[n], words[n2]);
        }
    }
};

inline void check(
    const std::vector<int>& startingIndices,
    std::vector<int> expected)
{
    assert(startingIndices == expected);
}

int main()
{
    check(Solution().findSubstring(
        "barfoothefoobarman", {"foo", "bar"}),
          {0, 9});
    check(Solution().findSubstring(
        "wordgoodgoodgoodbestword", {"word","good","best","word"}),
          {});
    check(Solution().findSubstring(
        "barfoofoobarthefoobarman", {"bar","foo","the"}),
          {6, 9, 12});
    check(Solution().findSubstring(
        "lingmindraboofooowingdingbarrwingmonkeypoundcake", {"fooo","barr","wing","ding","wing"}),
          {13});
    check(Solution().findSubstring(
        "catdogcatdog", {"cat","dog"}),
          {0, 3, 6});
    check(Solution().findSubstring(
        "aaaaaa", {"aa","aa"}),
          {0, 1, 2});
    check(Solution().findSubstring(
        "nothinghere", {"a","b"}),
          {});
    check(Solution().findSubstring(
        "abcabcabc", {"abc","abc"}),
          {0, 3});

    return 0;
}
