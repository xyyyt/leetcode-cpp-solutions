#include <string>
#include <memory>
#include <vector>
#include <cassert>

class Solution
{
public :
    std::vector<std::string> generateParenthesis(int n)
    {
        if (n <= 0)
        {
            return {};
        }

        std::vector<std::string> combinations;

        generateAllCombinations(combinations, "", n * 2, 0);

        return combinations;
    }

private :
    [[nodiscard]]
    inline bool validParentheses(
        const std::string& s) const noexcept
    {
        if (s.empty())
        {
            return false;
        }

        int balance = 0;

        for (auto c : s)
        {
            if (c == '(')
            {
                ++balance;
            }
            else
            {
                --balance;

                if (balance < 0)
                {
                    return false;
                }
            }
        }

        return balance == 0;
    }

    void generateAllCombinations(
        std::vector<std::string>& combinations,
        std::string current,
        int n,
        int n2) const
    {
        if (n2 >= n)
        {
            if (validParentheses(current))
            {
                combinations.emplace_back(std::move(current));
            }

            return;
        }

        generateAllCombinations(
            combinations, current + '(', n, n2 + 1);
        generateAllCombinations(
            combinations, current + ')', n, n2 + 1);
    }
};

inline void check(
    const std::vector<std::string>& combinations,
    std::vector<std::string> expected)
{
    assert(combinations == expected);
}

int main()
{
    check(Solution().generateParenthesis(0),
          {});
    check(Solution().generateParenthesis(1),
          {"()"});
    check(Solution().generateParenthesis(2),
          {"(())", "()()"});
    check(Solution().generateParenthesis(3),
          {"((()))", "(()())", "(())()", "()(())", "()()()"});
    check(Solution().generateParenthesis(4),
          {"(((())))", "((()()))", "((())())", "((()))()",
           "(()(()))", "(()()())", "(()())()", "(())(())",
           "(())()()", "()((()))", "()(()())", "()(())()",
           "()()(())", "()()()()"});
    check(Solution().generateParenthesis(5),
          {"((((()))))", "(((()())))", "(((())()))", "(((()))())",
           "(((())))()", "((()(())))", "((()()()))", "((()())())",
           "((()()))()", "((())(()))", "((())()())", "((())())()",
           "((()))(())", "((()))()()", "(()((())))", "(()(()()))",
           "(()(())())", "(()(()))()", "(()()(()))", "(()()()())",
           "(()()())()", "(()())(())", "(()())()()", "(())((()))",
           "(())(()())", "(())(())()", "(())()(())", "(())()()()",
           "()(((())))", "()((()()))", "()((())())", "()((()))()",
           "()(()(()))", "()(()()())", "()(()())()", "()(())(())",
           "()(())()()", "()()((()))", "()()(()())", "()()(())()",
           "()()()(())", "()()()()()"});

    return 0;
}
