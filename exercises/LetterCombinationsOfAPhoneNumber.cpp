#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <string_view>
#include <iostream>

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
        std::string currentCombination) const
    {
        if (lettersFromDigitsIdx >= lettersFromDigits.size())
        {
            combinations.emplace_back(currentCombination);

            return;
        }

        std::string_view letters = lettersFromDigits[lettersFromDigitsIdx];

        for (int n = 0; n < letters.size(); ++n)
        {
            addAllCombinations(
                lettersFromDigits,
                lettersFromDigitsIdx + 1,
                combinations,
                currentCombination + letters[n]);
        }
    }

    inline void removeDuplicates(
        std::vector<std::string>& combinations) const
    {
        std::unordered_set<std::string_view> duplicates;
        auto begin = combinations.begin();
        auto end = combinations.end();

        while (begin != end)
        {
            if (duplicates.find(*begin) != duplicates.cend())
            {
                begin = combinations.erase(begin);
            }
            else
            {
                duplicates.emplace(*begin);
                ++begin;
            }
        }
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::string>& combinations) noexcept
{
    if (combinations.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = combinations.cbegin();
    auto end = combinations.cend();

    os << '[' << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    os << ']';

    return os;
}

int main()
{
    std::cout << Solution().letterCombinations("23") << '\n';
    std::cout << Solution().letterCombinations("") << '\n';
    std::cout << Solution().letterCombinations("2") << '\n';

    return 0;
}
