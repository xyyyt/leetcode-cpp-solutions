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
            return -1;
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

    return 0;
}
