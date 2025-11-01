#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>

namespace std
{
    template <>
    struct hash<std::vector<int>>
    {
        [[nodiscard]]
        size_t operator()(const std::vector<int>& v) const noexcept
        {
            size_t h = 0;

            for (auto n : v)
            {
                h ^= std::hash<int>()(n);
            }

            return h;
        }
    };

    template <>
    struct equal_to<std::vector<int>>
    {
        [[nodiscard]]
        bool operator()(
            const std::vector<int>& lhs, const std::vector<int>& rhs) const
        {
            if (lhs.size() != rhs.size())
            {
                return false;
            }

            std::vector<int> lhsCopy = lhs;
            std::vector<int> rhsCopy = rhs;

            std::sort(lhsCopy.begin(), lhsCopy.end());
            std::sort(rhsCopy.begin(), rhsCopy.end());

            return lhsCopy == rhsCopy;
        }
    };
};

class Solution
{
public :
    std::vector<std::vector<int>>
        combinationSum(std::vector<int> candidates, int target)
    {
        if (candidates.empty())
        {
            return {};
        }

        std::unordered_set<std::vector<int>> uniqueCombinations;

        combinationSum(
            candidates,
            target,
            uniqueCombinations,
            {},
            0,
            0);

        return std::vector<std::vector<int>>(
            std::move_iterator(uniqueCombinations.begin()),
            std::move_iterator(uniqueCombinations.end()));
    }

private :
    void combinationSum(
        std::vector<int>& candidates,
        int target,
        std::unordered_set<std::vector<int>>& uniqueCombinations,
        const std::vector<int>& currentCombination,
        int currentSum,
        int pos) const
    {
        if (pos >= candidates.size())
        {
            return;
        }

        for (int n = pos; n < candidates.size(); ++n)
        {
            std::swap(candidates[pos], candidates[n]);

            std::vector<int> currentCombination2(
                currentCombination.cbegin(),
                currentCombination.cend());
            int currentSum2 = currentSum;

            while (true)
            {
                currentCombination2.emplace_back(candidates[pos]);
                currentSum2 += candidates[pos];

                if (currentSum2 > target)
                {
                    break;
                }
                else if (currentSum2 == target)
                {
                    uniqueCombinations.emplace(
                        std::move(currentCombination2));

                    break;
                }

                combinationSum(
                    candidates,
                    target,
                    uniqueCombinations,
                    currentCombination2,
                    currentSum2,
                    pos + 1);
            }

            std::swap(candidates[pos], candidates[n]);
        }
    }
};

std::ostream& operator<<(
    std::ostream& os,
    const std::vector<std::vector<int>>& combinations) noexcept
{
    if (combinations.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& combination : combinations)
    {
        if (combination.empty())
        {
            continue;
        }

        auto begin = combination.cbegin();
        auto end = combination.cend();

        os << '[' << *begin;
        ++begin;

        while (begin != end)
        {
            os << ", " << *begin;
            ++begin;
        }

        os << ']';
    }

    return os;
}

int main()
{
    std::cout << Solution().combinationSum({2, 3, 6, 7}, 7) << '\n';
    std::cout << Solution().combinationSum({2, 3, 5}, 8) << '\n';
    std::cout << Solution().combinationSum({2}, 1) << '\n';

    return 0;
}
