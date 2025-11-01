#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>

class Solution
{
public :
    std::vector<std::vector<std::string>> groupAnagrams(
        std::vector<std::string> strs)
    {
        if (strs.empty())
        {
            return {};
        }

        std::vector<std::vector<std::string>> anagramGroups;
        std::list<std::string_view> strsCopy(
            strs.cbegin(), strs.cend());

        while (!strsCopy.empty())
        {
            std::string_view firstStr = strsCopy.front();
            auto firstStrLetterCounter = getLetterCounter(firstStr);

            strsCopy.pop_front();

            std::vector<std::string> anagramGroup{
                std::string(firstStr.data(), firstStr.size())};
            auto begin = strsCopy.begin();
            auto end = strsCopy.end();

            while (begin != end)
            {
                auto strLetterCounter = getLetterCounter(*begin);

                if (firstStrLetterCounter == strLetterCounter)
                {
                    anagramGroup.emplace_back(*begin);
                    begin = strsCopy.erase(begin);
                }
                else
                {
                    ++begin;
                }
            }

            anagramGroups.emplace_back(std::move(anagramGroup));
        }

        return anagramGroups;
    }

private :
    [[nodiscard]]
    std::unordered_map<char, int> getLetterCounter(
        std::string_view str) const
    {
        std::unordered_map<char, int> letterCounter;

        letterCounter.reserve(str.size());

        for (auto c : str)
        {
            ++letterCounter[c];
        }

        return letterCounter;
    }
};

std::ostream& operator<<(
    std::ostream& os,
    const std::vector<std::vector<std::string>>& anagramGroups) noexcept
{
    if (anagramGroups.empty())
    {
        os << "EMPTY";

        return os;
    }

    for (const auto& anagramGroup : anagramGroups)
    {
        if (anagramGroup.empty())
        {
            continue;
        }

        auto begin = anagramGroup.cbegin();
        auto end = anagramGroup.cend();

        os << '[' << *begin;
        ++begin;

        while (begin != end)
        {
            os << ", " << *begin;
            ++begin;
        }

        os << "]";
    }

    return os;
}

int main()
{
    std::cout << Solution().groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"}) << '\n';
    std::cout << Solution().groupAnagrams({""}) << '\n';
    std::cout << Solution().groupAnagrams({"a"}) << '\n';

    return 0;
}
