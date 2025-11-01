#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

class Solution
{
public :
    bool isPalindrome(std::string s)
    {
        s.erase(std::remove_if(s.begin(),
                               s.end(),
                               [](char c) noexcept -> bool
                               {
                                   return !std::isalnum(c);
                               }),
                s.end());

        if (s.empty())
        {
            return true;
        }

        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        return std::equal(
            s.cbegin(), s.cbegin() + (s.size() / 2), s.crbegin());
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().isPalindrome("A man, a plan, a canal: Panama") << '\n';
    std::cout << Solution().isPalindrome("race a car") << '\n';
    std::cout << Solution().isPalindrome(" ") << '\n';

    return 0;
}
