#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Solution
{
public :
    std::vector<std::string> removeAnagrams(std::vector<std::string> words)
    {
        if (words.size() < 2)
        {
            return words;
        }

        auto it = words.begin() + 1;
        int n = 1;

        while (n < words.size())
        {
            std::string s = words[n - 1];
            std::string s2 = words[n];

            std::sort(s.begin(), s.end());
            std::sort(s2.begin(), s2.end());

            if (s == s2)
            {
                it = words.erase(it);
            }
            else
            {
                ++it;
                ++n;
            }
        }

        return words;
    }
};

std::ostream& operator<<(
    std::ostream& os, const std::vector<std::string>& words) noexcept
{
    if (words.empty())
    {
        os << "EMPTY";

        return os;
    }

    auto begin = words.cbegin();
    auto end = words.cend();

    os << *begin;
    ++begin;

    while (begin != end)
    {
        os << ", " << *begin;
        ++begin;
    }

    return os;
}

int main()
{
    std::cout << Solution().removeAnagrams({"abba", "baba", "bbaa", "cd", "cd"}) << '\n';
    std::cout << Solution().removeAnagrams({"a", "b", "c", "d", "e"}) << '\n';
    std::cout << Solution().removeAnagrams({"a", "b", "a"}) << '\n';

    return 0;
}
