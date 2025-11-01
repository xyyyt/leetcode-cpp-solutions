#include <cmath>
#include <iostream>

class Solution
{
public :
    bool isHappy(int n)
    {
        n = std::abs(n);

        while (n >= 10)
        {
            int sum = 0;

            do
            {
                sum += std::pow(n % 10, 2);
                n /= 10;
            }
            while (n > 0);

            n = sum;
        }

        return n == 1;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().isHappy(19) << '\n';
    std::cout << Solution().isHappy(2) << '\n';
    std::cout << Solution().isHappy(1) << '\n';
    std::cout << Solution().isHappy(-4) << '\n';
    std::cout << Solution().isHappy(-10) << '\n';
    std::cout << Solution().isHappy(-16) << '\n';

    return 0;
}
