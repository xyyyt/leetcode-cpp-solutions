#include <unordered_map>
#include <string>
#include <iostream>

class Solution
{
public :
    int firstUniqueChar(std::string s)
    {
        if (s.empty())
        {
            return -1;
        }

        std::unordered_map<char, int> charCounter;

        charCounter.reserve(s.size());

        for (auto c : s)
        {
            ++charCounter[c];
        }

        for (int n = 0; n < s.size(); ++n)
        {
            if (charCounter[s[n]] == 1)
            {
                return n;
            }
        }

        return -1;
    }
};

int main()
{
    std::cout << Solution().firstUniqueChar("leetcode") << '\n';
    std::cout << Solution().firstUniqueChar("loveleetcode") << '\n';
    std::cout << Solution().firstUniqueChar("aabb") << '\n';

    return 0;
}
