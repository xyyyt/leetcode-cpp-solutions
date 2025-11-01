#include <vector>
#include <limits>
#include <iostream>

class Solution
{
public :
    int findMin(std::vector<int> nums)
    {
        if (nums.empty())
        {
            return std::numeric_limits<int>::min();
        }

        int low = 0;
        int high = nums.size() - 1;

        while (low < high)
        {
            if (nums[low] < nums[high])
            {
                break;
            }

            int mid = (low + high) / 2;

            if (nums[mid] > nums[high])
            {
                low = mid + 1;
            }
            else
            {
                high = mid;
            }
        }

        return nums[low];
    }
};

int main()
{
    std::cout << Solution().findMin({3, 4, 5, 1, 2}) << '\n';
    std::cout << Solution().findMin({4, 5, 6, 7, 0, 1, 2}) << '\n';
    std::cout << Solution().findMin({11, 13, 15, 17}) << '\n';
    std::cout << Solution().findMin({-1, -5, -4, -3, -2}) << '\n';

    return 0;
}
