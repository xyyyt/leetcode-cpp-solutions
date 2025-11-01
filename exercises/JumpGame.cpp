#include <vector>
#include <iostream>

class Solution
{
public :
    bool jump(std::vector<int> nums)
    {
        return (!nums.empty()) ? jump(nums, 0) : false;
    }

private :
    [[nodiscard]]
    bool jump(const std::vector<int>& nums, int pos) const
    {
        if (pos >= nums.size())
        {
            return false;
        }
        else if (pos == nums.size() - 1)
        {
            return true;
        }

        for (int n = 1; n <= nums[pos]; ++n)
        {
            if (jump(nums, pos + n))
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
    std::cout << Solution().jump({2, 3, 1, 1, 4}) << '\n';
    std::cout << Solution().jump({3, 2, 1, 0, 4}) << '\n';

    return 0;
}
