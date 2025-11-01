#include <unordered_set>
#include <queue>
#include <cassert>

class Solution
{
public :
    int nthUglyNumber(int n)
    {
        using UglyHeap_t = std::priority_queue<
            long long,
            std::vector<long long>,
            std::greater<long long>>;

        std::unordered_set<long long> seenUgly;
        UglyHeap_t uglyHeap;
        int uglyCount = 1;

        uglyHeap.emplace(1);

        while (true)
        {
            auto ugly = uglyHeap.top();

            uglyHeap.pop();

            if (uglyCount >= n)
            {
                return ugly;
            }

            ++uglyCount;

            if (auto ugly2 = ugly * 2;
                seenUgly.find(ugly2) == seenUgly.cend())
            {
                seenUgly.emplace(ugly2);
                uglyHeap.push(ugly2);
            }

            if (auto ugly3 = ugly * 3;
                seenUgly.find(ugly3) == seenUgly.cend())
            {
                seenUgly.emplace(ugly3);
                uglyHeap.push(ugly3);
            }

            if (auto ugly5 = ugly * 5;
                seenUgly.find(ugly5) == seenUgly.cend())
            {
                seenUgly.emplace(ugly5);
                uglyHeap.push(ugly5);
            }
        }
    }
};

int main()
{
    assert(Solution().nthUglyNumber(10) == 12);
    assert(Solution().nthUglyNumber(1) == 1);
    assert(Solution().nthUglyNumber(15) == 24);
    assert(Solution().nthUglyNumber(20) == 36);
    assert(Solution().nthUglyNumber(50) == 243);
    assert(Solution().nthUglyNumber(100) == 1536);
    assert(Solution().nthUglyNumber(1690) == 2123366400);

    return 0;
}
