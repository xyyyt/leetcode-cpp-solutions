#include <vector>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    bool containsDuplicate(std::vector<int> nums)
    {
        std::sort(nums.begin(), nums.end());

        for (int n = 0; n < nums.size() - 1; ++n)
        {
            if (nums[n] == nums[n + 1])
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().containsDuplicate({1, 2, 3, 1}) << '\n';
    std::cout << Solution().containsDuplicate({1, 2, 3, 4}) << '\n';
    std::cout << Solution().containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}) << '\n';

    return 0;
}
