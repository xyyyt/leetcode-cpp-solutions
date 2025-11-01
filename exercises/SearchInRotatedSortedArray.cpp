#include <vector>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    int search(std::vector<int> nums, int target)
    {
        if (nums.empty())
        {
            return -1;
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

            if (nums[mid] == target)
            {
                return mid;
            }

            if (nums[mid] < target || nums[high] > target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        auto it = std::lower_bound(
            nums.cbegin() + low,
            nums.cbegin() + (high + 1),
            target);

        return (it != nums.cend() && *it == target) ?
            it - nums.cbegin() : -1;
    }
};

int main()
{
    std::cout << Solution().search({4, 5, 6, 7, 0, 1, 2}, 0) << '\n';
    std::cout << Solution().search({4, 5, 6, 7, 0, 1, 2}, 3) << '\n';
    std::cout << Solution().search({1}, 0) << '\n';
    std::cout << Solution().search({1}, 1) << '\n';
    std::cout << Solution().search({1, 2, 3, 4, 5, 6, 7}, 2) << '\n';
    std::cout << Solution().search({1, 2, 3, 4, 5, 6, 7}, 7) << '\n';
    std::cout << Solution().search({3, 4, 5, 6, 7, 1, 2}, 5) << '\n';
    std::cout << Solution().search({3, 4, 5, 6, 7, 1, 2}, 1) << '\n';

    return 0;
}
