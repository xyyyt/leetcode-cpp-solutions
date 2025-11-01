#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

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

std::ostream& operator<<(
    std::ostream& os, const std::vector<int>& startingIndices) noexcept
{
    if (startingIndices.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = startingIndices.begin();
    auto end = startingIndices.cend();

    os << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    return os;
}

int main()
{
    std::cout << Solution()
        .findSubstring("barfoothefoobarman", {"foo", "bar"})
              << '\n';
    std::cout << Solution()
        .findSubstring("wordgoodgoodgoodbestword", {"word","good","best","word"})
              << '\n';
    std::cout << Solution()
        .findSubstring("barfoofoobarthefoobarman", {"bar","foo","the"})
              << '\n';

    return 0;
}
