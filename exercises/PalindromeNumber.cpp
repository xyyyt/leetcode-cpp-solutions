#include <utility>
#include <iostream>

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
    std::cout << std::boolalpha;
    std::cout << Solution().isPalindrome(121) << '\n';
    std::cout << Solution().isPalindrome(-121) << '\n';
    std::cout << Solution().isPalindrome(10) << '\n';

    return 0;
}
