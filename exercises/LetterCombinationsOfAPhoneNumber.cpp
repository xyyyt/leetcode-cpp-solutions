#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <cassert>

using namespace std::string_view_literals;

class Solution
{
public :
    std::vector<std::string> letterCombinations(std::string digits)
    {
        if (digits.empty())
        {
            return {};
        }

        const std::unordered_map<int, std::string_view> DIGIT_TO_LETTERS =
        {
            {2, "abc"sv},
            {3, "def"sv},
            {4, "ghi"sv},
            {5, "jkl"sv},
            {6, "mno"sv},
            {7, "pqrs"sv},
            {8, "tuv"sv},
            {9, "wxzy"sv}
        };
        std::vector<std::string_view> lettersFromDigits;

        lettersFromDigits.reserve(digits.size());

        for (auto c : digits)
        {
            lettersFromDigits.emplace_back(DIGIT_TO_LETTERS.at(c - 48));
        }

        std::vector<std::string> combinations;

        addAllCombinations(lettersFromDigits, 0, combinations, "");
        removeDuplicates(combinations);

        return combinations;
    }

private :
    void addAllCombinations(
        const std::vector<std::string_view>& lettersFromDigits,
        int lettersFromDigitsIdx,
        std::vector<std::string>& combinations,
        std::string combination) const
    {
        if (lettersFromDigitsIdx >= lettersFromDigits.size())
        {
            combinations.emplace_back(std::move(combination));

            return;
        }

        auto letters = lettersFromDigits[lettersFromDigitsIdx];

        for (int n = 0; n < letters.size(); ++n)
        {
            addAllCombinations(
                lettersFromDigits,
                lettersFromDigitsIdx + 1,
                combinations,
                combination + letters[n]);
        }
    }

    inline void removeDuplicates(
        std::vector<std::string>& combinations) const
    {
        std::sort(combinations.begin(), combinations.end());

        auto last = std::unique(combinations.begin(), combinations.end());

        combinations.erase(last, combinations.end());
    }
};

inline void check(
    const std::vector<std::string>& combinations,
    std::vector<std::string> expected)
{
    assert(combinations == expected);
}

int main()
{
    check(Solution().letterCombinations("23"),
          {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"});
    check(Solution().letterCombinations(""),
          {});
    check(Solution().letterCombinations("2"),
          {"a", "b", "c"});

    return 0;
}
