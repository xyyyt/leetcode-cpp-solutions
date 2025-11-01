#include <vector>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    int missingNumber(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return -1;
        }

        std::sort(nums.begin(), nums.end());

        int n = 0;

        while (n < nums.size() - 1)
        {
            if (nums[n + 1] != nums[n] + 1)
            {
                break;
            }

            ++n;
        }

        return nums[n] + 1;
    }
};

int main()
{
    std::cout << Solution().missingNumber({3, 0, 1}) << '\n';
    std::cout << Solution().missingNumber({0, 1}) << '\n';
    std::cout << Solution().missingNumber({9, 6, 4, 2, 3, 5, 7, 0, 1}) << '\n';

    return 0;
}
