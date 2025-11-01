#include <vector>
#include <cassert>

class Solution
{
public :
    int subarraySum(std::vector<int> nums, int k)
    {
        if (nums.empty())
        {
            return 0;
        }

        int sumOfSubarrays = 0;

        for (int n = 0; n < nums.size(); ++n)
        {
            int currentSum = nums[n];

            if (currentSum == k)
            {
                ++sumOfSubarrays;
            }

            for (int n2 = n + 1; n2 < nums.size(); ++n2)
            {
                currentSum += nums[n2];

                if (currentSum == k)
                {
                    ++sumOfSubarrays;
                }
            }
        }

        return sumOfSubarrays;
    }
};

int main()
{
    assert(Solution().subarraySum({1, 1, 1}, 2) == 2);
    assert(Solution().subarraySum({1, 2, 3}, 3) == 2);
    assert(Solution().subarraySum({5, 5, 5}, 100) == 0);
    assert(Solution().subarraySum({0, 0, 0}, 0) == 6);
    assert(Solution().subarraySum({7}, 7) == 1);
    assert(Solution().subarraySum({7}, 3) == 0);
    assert(Solution().subarraySum({3, 4, -7, 1, 3, 3, 1, -4}, 7) == 4);
    assert(Solution().subarraySum({1, 2, 1, 2, 1}, 3) == 4);
    assert(Solution().subarraySum({}, 0) == 0);
    assert(Solution().subarraySum({1, 1, 1, 1, 1, 1}, 2) == 5);

    return 0;
}
