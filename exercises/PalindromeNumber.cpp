#include <utility>
#include <cassert>

class Solution
{
public :
    bool isPalindrome(int x)
    {
        if (x < 0)
        {
            return false;
        }

        int denominator = 1;

        do
        {
            denominator *= 10;
        }
        while (denominator <= x);

        denominator /= 10;

        int reversedX = 0;

        for (int copyX = x, exponent = 1; denominator > 0; exponent *= 10)
        {
            reversedX = reversedX + (copyX / denominator) * exponent;
            copyX %= denominator;
            denominator /= 10;
        }

        return reversedX == x;
    }
};

int main()
{
    assert(Solution().isPalindrome(121));
    assert(!Solution().isPalindrome(-121));
    assert(!Solution().isPalindrome(10));
    assert(Solution().isPalindrome(0));
    assert(Solution().isPalindrome(1221));
    assert(Solution().isPalindrome(12321));
    assert(!Solution().isPalindrome(123));
    assert(Solution().isPalindrome(1001));
    assert(!Solution().isPalindrome(1234322));
    assert(!Solution().isPalindrome(123456789));
    assert(Solution().isPalindrome(7));

    return 0;
}
