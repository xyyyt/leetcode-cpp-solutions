#include <iostream>

class Solution
{
public :
    bool isUgly(int n)
    {
        for (int i = 1; i < n; ++i)
        {
            if (n % i == 0 && i != 1 && i != 2 && i != 3 && i != 5)
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().isUgly(6) << '\n';
    std::cout << Solution().isUgly(1) << '\n';
    std::cout << Solution().isUgly(14) << '\n';

    return 0;
}
