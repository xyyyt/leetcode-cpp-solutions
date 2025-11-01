#include <vector>
#include <unordered_set>
#include <cassert>

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
    inline bool isValidGrid(
        const std::vector<std::vector<char>>& board,
        int row,
        int column) const
    {
        return checkRows<_GRID_ROW_MAX, _GRID_COLUMN_MAX>(board, row, column)
            && checkColumns<_GRID_ROW_MAX, _GRID_COLUMN_MAX>(board, row, column);
    }

    template <
        int _GRID_ROW_MAX, int _GRID_COLUMN_MAX>
    inline bool checkRows(
        const std::vector<std::vector<char>>& board,
        int row,
        int column) const
    {
        for (int m = row; m < row + _GRID_ROW_MAX; ++m)
        {
            std::unordered_set<char> seen;

            for (int n = column; n < column + _GRID_COLUMN_MAX; ++n)
            {
                if (board[m][n] == EMPTY_CELL)
                {
                    continue;
                }

                if (!seen.emplace(board[m][n]).second)
                {
                    return false;
                }
            }
        }

        return true;
    }

    template <
        int _GRID_ROW_MAX, int _GRID_COLUMN_MAX>
    inline bool checkColumns(
        const std::vector<std::vector<char>>& board,
        int row,
        int column) const
    {
        for (int n = column; n < column + _GRID_COLUMN_MAX; ++n)
        {
            std::unordered_set<char> seen;

            for (int m = row; m < row + _GRID_ROW_MAX; ++m)
            {
                if (board[m][n] == EMPTY_CELL)
                {
                    continue;
                }

                if (!seen.emplace(board[m][n]).second)
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
    assert(Solution().isValidSudoku({
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}}));
    assert(!Solution().isValidSudoku({
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}}));
    assert(Solution().isValidSudoku({
        {'2','7','.','.','4','.','.','9','.'},
        {'.','.','4','2','.','9','.','.','.'},
        {'.','1','.','.','.','.','6','.','.'},
        {'.','.','.','5','.','.','4','.','.'},
        {'5','.','.','.','3','.','.','.','2'},
        {'.','.','9','.','.','7','.','.','.'},
        {'.','.','1','.','.','.','.','3','.'},
        {'.','.','.','7','.','6','9','.','.'},
        {'.','4','.','.','1','.','.','2','5'}}));
    assert(!Solution().isValidSudoku({
        {'1','1','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}}));
    assert(!Solution().isValidSudoku({
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'5','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}}));
    assert(!Solution().isValidSudoku({
        {'5','3','5','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}}));
    assert(Solution().isValidSudoku({
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','4','.','.','.','.'},
        {'.','.','.','6','.','1','.','.','.'},
        {'.','.','.','.','9','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'}}));

    return 0;
}
