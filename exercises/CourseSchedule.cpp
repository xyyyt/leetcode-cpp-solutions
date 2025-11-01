#include <vector>
#include <unordered_set>
#include <iostream>

class Solution
{
public :
    bool canFinish(
        int numCourses, std::vector<std::vector<int>> prerequisites)
    {
        if (prerequisites.empty())
        {
            return false;
        }
        else if (numCourses < 2)
        {
            return true;
        }

        for (int n = 0; n < prerequisites.size(); ++n)
        {
            if (prerequisites[n][1] == prerequisites[n][0])
            {
                continue;
            }

            if (canFinish(
                numCourses,
                prerequisites,
                {prerequisites[n][1], prerequisites[n][0]},
                prerequisites[n][0]))
            {
                return true;
            }
        }

        return false;
    }

private :
    [[nodiscard]]
    bool canFinish(
        int numCourses,
        const std::vector<std::vector<int>>& prerequisites,
        const std::unordered_set<int>& visitedCourses,
        int currentCourse) const
    {
        if (visitedCourses.size() == numCourses)
        {
            return true;
        }

        for (int n = 0; n < prerequisites.size(); ++n)
        {
            if (prerequisites[n][1] == currentCourse
                && visitedCourses.find(
                   prerequisites[n][0]) == visitedCourses.cend())
            {
                std::unordered_set<int> visitedCourses2 = visitedCourses;

                visitedCourses2.emplace(prerequisites[n][0]);

                if (canFinish(
                    numCourses,
                    prerequisites,
                    visitedCourses2,
                    prerequisites[n][0]))
                {
                    return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().canFinish(
        2, {{1, 0}})
              << '\n';
    std::cout << Solution().canFinish(
        2, {{1, 0}, {0, 1}})
              << '\n';
    std::cout << Solution().canFinish(
        4, {{1, 4}, {2, 4}, {3, 1}, {3, 2}})
              << '\n';
    std::cout << Solution().canFinish(
        4, {{1, 0}, {1, 2}, {3, 1}, {2, 3}, {2, 4}, {4, 5}, {2, 5}})
              << '\n';
    std::cout << Solution().canFinish(
        6, {{1, 0}, {1, 2}, {3, 1}, {3, 2}, {2, 4}, {4, 5}, {2, 5}})
              << '\n';

    return 0;
}
