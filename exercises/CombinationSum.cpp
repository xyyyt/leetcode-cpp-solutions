#include <vector>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> combinationSum(
        const std::vector<int>& candidates, int target)
    {
        if (candidates.empty())
        {
            return {};
        }

        std::vector<std::vector<int>> combinations;

        for (int n = 0; n < candidates.size(); ++n)
        {
            combinationSum(candidates,
                           target,
                           combinations,
                           0,
                           {},
                           n);
        }

        removeDuplicates(combinations);

        return combinations;
    }

private :
    void combinationSum(
        const std::vector<int>& candidates,
        int target,
        std::vector<std::vector<int>>& combinations,
        int sum,
        std::vector<int> combination,
        int n) const
    {
        while (true)
        {
            sum += candidates[n];
            combination.emplace_back(candidates[n]);

            if (sum >= target)
            {
                break;
            }

            for (int n2 = 0; n2 < candidates.size(); ++n2)
            {
                if (n2 == n)
                {
                    continue;
                }

                combinationSum(candidates,
                               target,
                               combinations,
                               sum,
                               combination,
                               n2);
            }
        }

        if (sum == target)
        {
            combinations.emplace_back(std::move(combination));
        }
    }

    inline void removeDuplicates(
        std::vector<std::vector<int>>& combinations) const
    {
        for (auto& combination : combinations)
        {
            std::sort(combination.begin(), combination.end());
        }

        std::sort(combinations.begin(), combinations.end());

        auto last = std::unique(combinations.begin(), combinations.end());

        combinations.erase(last, combinations.end());
    }
};

inline void check(
    const std::vector<std::vector<int>>& combinations,
    std::vector<std::vector<int>> expected)
{
    assert(combinations == expected);
}

int main()
{
    check(Solution().combinationSum({2, 3, 6, 7}, 7),
          {{2, 2, 3}, {7}});
    check(Solution().combinationSum({2, 3, 5}, 8),
          {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}});
    check(Solution().combinationSum({2}, 1),
          {});
    check(Solution().combinationSum({4, 5}, 3),
          {});
    check(Solution().combinationSum({7}, 21),
          {{7, 7, 7}});
    check(Solution().combinationSum({7}, 20),
          {});
    check(Solution().combinationSum({2, 3, 5}, 1),
          {});

    return 0;
}
