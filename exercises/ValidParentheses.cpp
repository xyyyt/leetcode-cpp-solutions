#include <string>
#include <stack>
#include <cassert>

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

                auto openingChar = openingChars.top();

                openingChars.pop();

                if (!(openingChar == '(' && c == ')'
                      || openingChar == '[' && c == ']'
                      || openingChar == '{' && c == '}'))
                {
                    return false;
                }
            }
            else
            {
                openingChars.emplace(c);
            }
        }

        return openingChars.empty();
    }
};

int main()
{
    assert(Solution().isValid("()"));
    assert(Solution().isValid("()[]{}"));
    assert(!Solution().isValid("(]"));
    assert(Solution().isValid("([])"));
    assert(!Solution().isValid("({})][()"));
    assert(!Solution().isValid("}{()]["));

    return 0;
}
