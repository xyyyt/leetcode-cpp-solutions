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
            int j = i;

            while (j != 0)
            {
                oneBitCounter += ((j % 2) != 0);
                j /= 2;
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
    check(Solution().countBits(2), {0, 1, 1});
    check(Solution().countBits(5), {0, 1, 1, 2, 1, 2});

    return 0;
}
