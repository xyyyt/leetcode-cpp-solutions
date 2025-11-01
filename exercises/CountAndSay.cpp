#include <string>
#include <cassert>

// Iterative solution
class Solution
{
public :
    std::string countAndSay(int n)
    {
        if (n <= 0)
        {
            return "";
        }

        std::string s = "1";

        for (int n2 = 1; n2 < n; ++n2)
        {
            std::string s2;
            int n3 = 0;

            while (n3 < s.size())
            {
                char c = s[n3++];
                int n4 = 1;

                while (n3 < s.size() && s[n3] == c)
                {
                    ++n3;
                    ++n4;
                }

                s2 += std::to_string(n4);
                s2 += c;
            }

            s = std::move(s2);
        }

        return s;
    }
};

// // Recursive solution
// class Solution
// {
// public :
//     std::string countAndSay(int n)
//     {
//         if (n <= 0)
//         {
//             return "";
//         }
//         else if (n == 1)
//         {
//             return "1";
//         }

//         std::string prev = countAndSay(n - 1);
//         std::string s;
//         int n2 = 0;

//         while (n2 < prev.size())
//         {
//             char c = prev[n2++];
//             int n3 = 1;

//             while (n2 < prev.size() && prev[n2] == c)
//             {
//                 ++n2;
//                 ++n3;
//             }

//             s += std::to_string(n3);
//             s += c;
//         }

//         return s;
//     }
// };

int main()
{
    assert(Solution().countAndSay(1) == "1");
    assert(Solution().countAndSay(2) == "11");
    assert(Solution().countAndSay(3) == "21");
    assert(Solution().countAndSay(4) == "1211");
    assert(Solution().countAndSay(5) == "111221");
    assert(Solution().countAndSay(6) == "312211");
    assert(Solution().countAndSay(7) == "13112221");
    assert(Solution().countAndSay(8) == "1113213211");

    return 0;
}
