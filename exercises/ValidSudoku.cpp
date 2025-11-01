#include <vector>
#include <unordered_set>
#include <iostream>

class Solution
{
public :
    bool isValidSudoku(std::vector<std::vector<char>> board)
    {
        if (board.empty())
        {
            return false;
        }

        for (int n = 0; n < NUMBER_OF_GRID; ++n)
        {
            if (!isValidGrid<GRID_ROW_MAX, GRID_COLUMN_MAX>(
                board,
                (n / GRID_ROW_MAX) * GRID_ROW_MAX,
                (n * GRID_COLUMN_MAX) % BOARD_COLUMN_MAX))
            {
                return false;
            }
        }

        return isValidGrid<BOARD_ROW_MAX, BOARD_COLUMN_MAX>(board, 0, 0);
    }

private :
    static constexpr int BOARD_ROW_MAX = 9;
    static constexpr int BOARD_COLUMN_MAX = 9;
    static constexpr int NUMBER_OF_GRID = 9;
    static constexpr int GRID_ROW_MAX = 3;
    static constexpr int GRID_COLUMN_MAX = 3;
    static constexpr char EMPTY_CELL = '.';

    template <
        int _GRID_ROW_MAX, int _GRID_COLUMN_MAX>
    bool isValidGrid(
        const std::vector<std::vector<char>>& board,
        int row,
        int column) const
    {
        return checkRows<_GRID_ROW_MAX, _GRID_COLUMN_MAX>(board, row, column)
            && checkColumns<_GRID_ROW_MAX, _GRID_COLUMN_MAX>(board, row, column);
    }

    template <
        int _GRID_ROW_MAX, int _GRID_COLUMN_MAX>
    bool checkRows(
        const std::vector<std::vector<char>>& board,
        int row,
        int column) const
    {
        for (int n = row; n < row + _GRID_ROW_MAX; ++n)
        {
            std::unordered_set<char> charAlreadyUsed;

            for (int n2 = column; n2 < column + _GRID_COLUMN_MAX; ++n2)
            {
                if (board[n][n2] == EMPTY_CELL)
                {
                    continue;
                }

                if (!charAlreadyUsed.emplace(board[n][n2]).second)
                {
                    return false;
                }
            }
        }

        return true;
    }

    template <
        int _GRID_ROW_MAX, int _GRID_COLUMN_MAX>
    bool checkColumns(
        const std::vector<std::vector<char>>& board,
        int row,
        int column) const
    {
        for (int n = column; n < column + _GRID_COLUMN_MAX; ++n)
        {
            std::unordered_set<char> charAlreadyUsed;

            for (int n2 = row; n2 < row + _GRID_ROW_MAX; ++n2)
            {
                if (board[n2][n] == EMPTY_CELL)
                {
                    continue;
                }

                if (!charAlreadyUsed.emplace(board[n2][n]).second)
                {
                    return false;
                }
            }
        }

        return true;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << Solution().isValidSudoku({
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}})
              << '\n';
    std::cout << Solution().isValidSudoku({
            {'8','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}})
              << '\n';

    return 0;
}
