#include <vector>
#include <cassert>

class Solution
{
public :
    int subarraySum(std::vector<int> nums, int k)
    {
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

    return 0;
}
