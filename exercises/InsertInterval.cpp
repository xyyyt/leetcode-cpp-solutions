#include <vector>
#include <cassert>

class Solution
{
public :
    std::vector<std::vector<int>> insert(
        std::vector<std::vector<int>> intervals,
        std::vector<int> newInterval)
    {
        if (intervals.empty())
        {
            return {newInterval};
        }
        else if (newInterval.empty())
        {
            return intervals;
        }

        std::vector<std::vector<int>> newIntervals;
        std::vector<int> newInterval2 = newInterval;

        newIntervals.reserve(intervals.size());

        for (int n = 0; n < intervals.size(); ++n)
        {
            const auto& currentInterval = intervals[n];

            if (currentInterval[0] > newInterval2[1])
            {
                newIntervals.emplace_back(std::move(newInterval2));
                newInterval2 = currentInterval;
            }
            else if (currentInterval[0] == newInterval2[1]
                     || (currentInterval[0] < newInterval2[0]
                         && currentInterval[1] > newInterval2[0])
                     || (currentInterval[0] < newInterval2[1]
                         && currentInterval[1] > newInterval2[1])
                     || currentInterval[1] == newInterval2[0])
            {
                newInterval2 = mergeIntervals(
                    newInterval2, currentInterval);
            }
            else if (currentInterval[1] < newInterval2[0])
            {
                newIntervals.emplace_back(currentInterval);
            }
        }

        newIntervals.emplace_back(std::move(newInterval2));

        return newIntervals;
    }

private :
    [[nodiscard]]
    inline std::vector<int> mergeIntervals(
        const std::vector<int>& interval,
        const std::vector<int>& interval2) const
    {
        return {std::min(interval[0], interval2[0]),
                std::max(interval[1], interval2[1])};
    }
};

inline void check(
    const std::vector<std::vector<int>>& intervals,
    std::vector<std::vector<int>> expected)
{
    assert(intervals == expected);
}

int main()
{
    check(Solution().insert({{4, 9}}, {1, 3}),
          {{1, 3}, {4, 9}});
    check(Solution().insert({{3, 5}}, {1, 3}),
          {{1, 5}});
    check(Solution().insert({{3, 7}}, {4, 6}),
          {{3, 7}});
    check(Solution().insert({{5, 8}}, {8, 12}),
          {{5, 12}});
    check(Solution().insert({{2, 6}}, {1, 3}),
          {{1, 6}});
    check(Solution().insert({{1, 3}}, {2, 6}),
          {{1, 6}});
    check(Solution().insert({{1, 5}}, {8, 14}),
          {{1, 5}, {8, 14}});
    check(Solution().insert({{1, 3}, {6, 9}}, {2, 5}),
          {{1, 5}, {6, 9}});
    check(Solution().insert({{1, 2}, {3, 5}, {9, 10}}, {6, 7}),
          {{1, 2}, {3, 5}, {6, 7}, {9, 10}});
    check(Solution().insert({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}),
          {{1, 2}, {3, 10}, {12, 16}});

    return 0;
}
