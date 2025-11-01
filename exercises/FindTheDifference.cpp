#include <string>
#include <iostream>

class Solution
{
public :
    char findTheDifference(std::string s, std::string t)
    {
        if (s.size() >= t.size())
        {
            return 0;
        }

        int n = 0;

        while (n < s.size() && s[n] == t[n])
        {
            ++n;
        }

        return t[n];
    }
};

int main()
{
    std::cout << Solution().findTheDifference("abcd", "abcde") << '\n';
    std::cout << Solution().findTheDifference("efgh", "eflgh") << '\n';
    std::cout << Solution().findTheDifference("b", "ab") << '\n';
    std::cout << Solution().findTheDifference("", "y") << '\n';

    return 0;
}
