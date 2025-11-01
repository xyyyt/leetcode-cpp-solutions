#include <vector>
#include <limits>
#include <iostream>

class Solution
{
public :
    int coinChange(std::vector<int> coins, int amount)
    {
        if (coins.empty())
        {
            return -1;
        }

        constexpr int MAX_VALUE = std::numeric_limits<int>::max();
        int fewestNbOfCoins = MAX_VALUE;
        // std::vector<int> usedCoins;

        coinChange(coins, amount, fewestNbOfCoins, /* usedCoins, */ 0, 0, /* {}, */ 0);

        // std::cout << "fewestNbOfCoins : "
        //           << fewestNbOfCoins
        //           << ", usedCoins : ";

        // for (auto coin : usedCoins)
        // {
        //     std::cout << coin << ' ';
        // }

        // std::cout << '\n';

        return (fewestNbOfCoins < MAX_VALUE) ? fewestNbOfCoins : -1;
    }

private :
    void coinChange(
        std::vector<int>& coins,
        int amount,
        int& fewestNbOfCoins,
        // std::vector<int>& usedCoins,
        int currentAmount,
        int currentNbOfCoins,
        // const std::vector<int>& currentUsedCoins,
        int n) const
    {
        if (n >= coins.size())
        {
            return;
        }

        for (int n2 = 0; n2 < coins.size(); ++n2)
        {
            std::swap(coins[n], coins[n2]);

            // std::vector<int> currentUsedCoins2 = currentUsedCoins;
            int currentAmount2 = currentAmount;
            int currentNbOfCoins2 = currentNbOfCoins;

            while (true)
            {
                // currentUsedCoins2.emplace_back(coins[n]);
                currentAmount2 += coins[n];
                ++currentNbOfCoins2;

                if (currentAmount2 >= amount)
                {
                    break;
                }

                coinChange(
                    coins,
                    amount,
                    fewestNbOfCoins,
                    // usedCoins,
                    currentAmount2,
                    currentNbOfCoins2,
                    // currentUsedCoins2,
                    n + 1);
            }

            if (currentAmount2 == amount)
            {
                // std::cout << "currentNbOfCoins2 : "
                //           << currentNbOfCoins2
                //           << ", currentUsedCoins2 : ";

                // for (auto coin : currentUsedCoins2)
                // {
                //     std::cout << coin << ' ';
                // }

                // std::cout << '\n';

                if (fewestNbOfCoins > currentNbOfCoins2)
                {
                    fewestNbOfCoins = currentNbOfCoins2;
                    // usedCoins = std::move(currentUsedCoins2);
                }
            }

            std::swap(coins[n], coins[n2]);
        }
    }
};

int main()
{
    std::cout << Solution().coinChange({1, 2, 5}, 11) << '\n';
    std::cout << Solution().coinChange({2}, 3) << '\n';
    std::cout << Solution().coinChange({1}, 0) << '\n';

    return 0;
}
