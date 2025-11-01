#include <vector>
#include <cstddef>
#include <cassert>

class Solution
{
public :
    std::vector<int> countBits(int n)
    {
        std::vector<int> ans;
        size_t max = n + 1;

        ans.reserve(max);

        for (int i = 0; i < max; ++i)
        {
            int oneBitCounter = 0;

            for (int j = i; j != 0; j /= 2)
            {
                oneBitCounter += ((j % 2) != 0);
            }

            ans.emplace_back(oneBitCounter);
        }

        return ans;
    }
};

inline void check(
     const std::vector<int>& ans,
     std::vector<int> expected)
{
    assert(ans == expected);
}

int main()
{
    check(Solution().countBits(0), {0});
    check(Solution().countBits(1), {0, 1});
    check(Solution().countBits(2), {0, 1, 1});
    check(Solution().countBits(5), {0, 1, 1, 2, 1, 2});
    check(Solution().countBits(10), {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2});

    return 0;
}
