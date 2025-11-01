#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

class Solution
{
public :
    std::vector<int> intersection(
        const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        if (nums1.empty() || nums2.empty())
        {
            return {};
        }

        std::unordered_map<int, int> numCounters;

        numCounters.reserve(nums1.size());

        for (auto num : nums1)
        {
            numCounters[num] = 0;
        }

        for (auto num : nums2)
        {
            if (auto it = numCounters.find(num);
                it != numCounters.end())
            {
                ++it->second;
            }
        }

        std::vector<int> nums3;

        nums3.reserve(numCounters.size());

        for (auto [num, counter] : numCounters)
        {
            if (counter > 0)
            {
                nums3.emplace_back(num);
            }
        }

        return nums3;
    }
};

template <typename T>
std::vector<T> cloneAndSort(const std::vector<T>& v)
{
    auto res = v;

    std::sort(res.begin(), res.end());

    return res;
}

inline void check(
    const std::vector<int>& nums,
    std::vector<int> expected)
{
    assert(cloneAndSort(nums) == cloneAndSort(expected));
}

int main()
{
    check(Solution().intersection({1, 2, 2, 1}, {2, 2}), {2});
    check(Solution().intersection({4, 9, 5}, {9, 4, 9, 8, 4}), {4, 9});
    check(Solution().intersection({1, 3, 5}, {2, 4, 6}), {});
    check(Solution().intersection({4, 9, 5}, {9, 4, 5}), {4, 5, 9});
    check(Solution().intersection({1, 1, 1, 2, 2}, {1, 2, 2, 2}), {1, 2});
    check(Solution().intersection({}, {1, 2, 3}), {});
    check(Solution().intersection({}, {}), {});
    check(Solution().intersection({7, 8, 9}, {0, 7, 100}), {7});
    check(Solution().intersection({1000, 2000, 3000}, {3000, 4000}), {3000});
    check(Solution().intersection({-1, -2, -3}, {-3, 0, 3}), {-3});
    check(Solution().intersection({1, 2, 3, 4, 5}, {3, 3, 3, 3}), {3});

    return 0;
}
