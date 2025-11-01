#include <vector>
#include <iostream>

class Solution
{
public :
    int searchInsert(std::vector<int> nums, int target)
    {
        int n = 0;

        while (n < nums.size())
        {
            if (nums[n] >= target)
            {
                break;
            }

            ++n;
        }

        return n;
    }
};

int main()
{
    std::cout << Solution().searchInsert({1, 3, 5, 6}, 5) << '\n';
    std::cout << Solution().searchInsert({1, 3, 5, 6}, 2) << '\n';
    std::cout << Solution().searchInsert({1, 3, 5, 6}, 7) << '\n';

    return 0;
}
