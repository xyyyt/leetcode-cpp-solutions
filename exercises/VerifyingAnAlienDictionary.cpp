#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>

class Solution
{
public :
    bool isAlienSorted(
        std::vector<std::string> words, std::string order)
    {
        constexpr size_t REQUIRED_ORDER_LENGTH = 26;

        if (words.empty() || order.size() != REQUIRED_ORDER_LENGTH)
        {
            return false;
        }

        auto orderMap = getOrderMap(order);

        for (int n = 0; n < words.size() - 1; ++n)
        {
            int n2 = 0;

            while (n2 < words[n].size()
                   && n2 < words[n + 1].size()
                   && words[n][n2] == words[n + 1][n2])
            {
                ++n2;
            }

            if (n2 < words[n].size()
                && (n2 >= words[n + 1].size()
                    || orderMap.at(words[n][n2])
                    > orderMap.at(words[n + 1][n2])))
            {
                return false;
            }
        }

        return true;
    }

private :
    using OrderMap_t = std::unordered_map<char, int>;

    [[nodiscard]]
    inline OrderMap_t getOrderMap(const std::string& order) const
    {
        OrderMap_t orderMap;

        orderMap.reserve(order.size());

        for (int n = 0; n < order.size(); ++n)
        {
            orderMap[order[n]] = n;
        }

        return orderMap;
    }
};

int main()
{
    assert(Solution().isAlienSorted(
        {"hello", "leetcode"}, "hlabcdefgijkmnopqrstuvwxyz"));
    assert(!Solution().isAlienSorted(
        {"word", "world", "row"}, "worldabcefghijkmnpqstuvxyz"));
    assert(!Solution().isAlienSorted(
        {"apple", "app"}, "abcdefghijklmnopqrstuvwxyz"));
    assert(Solution().isAlienSorted(
        {"goo","good", "goodd", "goodddd"}, "zorlnabcefghijkmdpqstuvxyw"));
    assert(Solution().isAlienSorted(
        {"good", "good"}, "zorlnabcefghijkmdpqstuvxyw"));
    assert(!Solution().isAlienSorted(
        {"badd", "bad"}, "uorldkbcefghijamnpqstwvxyz"));

    return 0;
}
