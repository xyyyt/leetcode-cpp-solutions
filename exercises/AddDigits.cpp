#include <cmath>
#include <iostream>

class Solution
{
public :
    int addDigits(int num)
    {
        int res = std::abs(num);

        while (res >= 10)
        {
            int sum = 0;

            do
            {
                sum += res % 10;
                res /= 10;
            }
            while (res > 0);

            res = sum;
        }

        return (num < 0) ? -res : res;
    }
};

int main()
{
    std::cout << Solution().addDigits(38) << '\n';
    std::cout << Solution().addDigits(0) << '\n';
    std::cout << Solution().addDigits(127) << '\n';
    std::cout << Solution().addDigits(6) << '\n';
    std::cout << Solution().addDigits(-27) << '\n';
    std::cout << Solution().addDigits(-4) << '\n';

    return 0;
}
