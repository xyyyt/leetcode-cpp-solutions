#include <vector>
#include <limits>
#include <iostream>

class Solution
{
public :
    int maxJumps(std::vector<int> arr, int d)
    {
        if (arr.empty() && !(1 <= d && d <= arr.size()))
        {
            return -1;
        }

        int jumpCounterMax = std::numeric_limits<int>::min();

        for (int n = 0; n < arr.size(); ++n)
        {
            jumpCounterMax =
                std::max(jumpCounterMax,
                         maxJumps(arr, d, 1, n));
        }

        return jumpCounterMax;
    }

private :
    [[nodiscard]]
    int maxJumps(
        const std::vector<int>& arr,
        int d,
        int jumpCounter,
        int pos) const
    {
        int jumpCounterMax = jumpCounter;

        for (int n = 1; n <= d; ++n)
        {
            int pos2 = pos + n;

            if (pos2 >= arr.size() || arr[pos] <= arr[pos2])
            {
                break;
            }

            jumpCounterMax =
                std::max(jumpCounterMax,
                         maxJumps(arr, d, jumpCounter + 1, pos2));
        }

        for (int n = 1; n <= d; ++n)
        {
            int pos2 = pos - n;

            if (pos2 < 0 || arr[pos] <= arr[pos2])
            {
                break;
            }

            jumpCounterMax =
                std::max(jumpCounterMax,
                         maxJumps(arr, d, jumpCounter + 1, pos2));
        }

        return jumpCounterMax;
    }
};

int main()
{
    std::cout << Solution().maxJumps({6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12}, 2) << '\n';
    std::cout << Solution().maxJumps({3, 3, 3, 3, 3}, 3) << '\n';
    std::cout << Solution().maxJumps({7, 6, 5, 4, 3, 2, 1}, 1) << '\n';
}
