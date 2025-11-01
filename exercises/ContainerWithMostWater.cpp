#include <vector>
#include <limits>
#include <cassert>

class Solution
{
public :
    int maxArea(std::vector<int> height)
    {
        if (height.size() < 2)
        {
            return 0;
        }

        int maxAmountOfWater = std::numeric_limits<int>::min();
        int n = 0;
        int n2 = height.size() - 1;

        while (n < n2)
        {
            int amountOfWater = std::min(height[n], height[n2]) * (n2 - n);

            maxAmountOfWater = std::max(maxAmountOfWater, amountOfWater);

            if (height[n] < height[n2])
            {
                ++n;
            }
            else
            {
                --n2;
            }
        }

        return maxAmountOfWater;
    }
};

int main()
{
    assert(Solution().maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
    assert(Solution().maxArea({1, 1}) == 1);
    assert(Solution().maxArea({1, 2}) == 1);
    assert(Solution().maxArea({4, 3, 2, 1, 4}) == 16);
    assert(Solution().maxArea({1, 2, 1}) == 2);
    assert(Solution().maxArea({1, 3, 2, 5, 25, 24, 5}) == 24);
    assert(Solution().maxArea({1000, 1000}) == 1000);
    assert(Solution().maxArea({0, 0, 0, 0}) == 0);
    assert(Solution().maxArea({1}) == 0);
    assert(Solution().maxArea({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 25);

    return 0;
}
