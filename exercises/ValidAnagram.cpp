#include <algorithm>
#include <iostream>

class Solution
{
public :
    bool isAnagram(std::string s, std::string t)
    {
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());

        return s == t;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().isAnagram("anagram", "nagaram") << '\n';
    std::cout << Solution().isAnagram("rat", "car") << '\n';

    return 0;
}
