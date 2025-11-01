#include <vector>
#include <unordered_map>
#include <cassert>

class Solution
{
public :
    std::vector<int> intersection(const std::vector<int>& nums1,
                                  const std::vector<int>& nums2)
    {
        std::unordered_map<int, int> numCounter;

        numCounter.reserve(nums1.size());

        for (auto num : nums1)
        {
            numCounter[num] = 0;
        }

        for (auto num : nums2)
        {
            if (auto it = numCounter.find(num);
                it != numCounter.end())
            {
                ++it->second;
            }
        }

        std::vector<int> nums3;

        nums3.reserve(numCounter.size());

        for (auto [num, counter] : numCounter)
        {
            if (counter > 0)
            {
                nums3.emplace_back(num);
            }
        }

        return nums3;
    }
};

inline void check(
    const std::vector<int>& nums,
    std::vector<int> expected)
{
    assert(nums == expected);
}

int main()
{
    check(Solution().intersection({1, 2, 2, 1}, {2, 2}), {2});
    check(Solution().intersection({4, 9, 5}, {9, 4, 9, 8, 4}), {9, 4});

    return 0;
}
