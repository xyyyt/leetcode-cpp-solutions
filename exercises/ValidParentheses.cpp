#include <string>
#include <stack>
#include <iostream>

class Solution
{
public :
    bool isValid(std::string s)
    {
        if (s.empty())
        {
            return false;
        }

        std::stack<char> openingChars;

        for (auto c : s)
        {
            if (c == ')' || c == ']' || c == '}')
            {
                if (openingChars.empty())
                {
                    return false;
                }

                char openingChar = openingChars.top();

                openingChars.pop();

                if (!(openingChar == '(' && c == ')'
                      || openingChar == '[' && c == ']'
                      || openingChar == '{' && c == '}'))
                {
                    return false;
                }

                continue;
            }

            openingChars.emplace(c);
        }

        return openingChars.empty();
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().isValid("()") << '\n';
    std::cout << Solution().isValid("()[]{}") << '\n';
    std::cout << Solution().isValid("(]") << '\n';
    std::cout << Solution().isValid("([])") << '\n';

    return 0;
}
