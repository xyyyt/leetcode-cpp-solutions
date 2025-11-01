#include <vector>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    int lengthOfLIS(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return -1;
        }

        int lisLength = 1;

        for (int n = 0; n < nums.size(); ++n)
        {
            for (int n2 = n + 1; n2 < nums.size(); ++n2)
            {
                if (nums[n2] > nums[n])
                {
                    int lisLength2 = 2 + lengthOfLIS(nums, n2, n2 + 1);

                    lisLength = std::max(lisLength, lisLength2);
                }
            }
        }

        return lisLength;
    }

private :
    int lengthOfLIS(
        const std::vector<int>& nums, int n, int n2) const
    {
        if (n >= nums.size())
        {
            return 0;
        }

        int lisLength = 0;

        while (n2 < nums.size())
        {
            if (nums[n2] > nums[n])
            {
                int lisLength2 = 1 + lengthOfLIS(nums, n2, n2 + 1);

                lisLength = std::max(lisLength, lisLength2);
            }

            ++n2;
        }

        return lisLength;
    }
};

int main()
{
    std::cout << Solution().lengthOfLIS({10, 9, 2, 5, 3, 7, 101, 18}) << '\n';
    std::cout << Solution().lengthOfLIS({0, 1, 0, 3, 2, 3}) << '\n';
    std::cout << Solution().lengthOfLIS({7, 7, 7, 7, 7, 7, 7}) << '\n';

    return 0;
}
