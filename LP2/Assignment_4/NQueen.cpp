#include <bits/stdc++.h>
using namespace std;

class NQueens
{
    void solve(int row, int &n, vector<vector<int>> &board, vector<bool> &column, vector<bool> &leftDiagonal, vector<bool> &rightDiagonal, vector<vector<vector<int>>> &result)
    {
        if (row == n)
        {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++)
        {
            if (!column[col] && !leftDiagonal[row + col] && !rightDiagonal[n - 1 + col - row])
            {
                board[row][col] = 1;
                column[col] = true;
                leftDiagonal[row + col] = true;
                rightDiagonal[n - 1 + col - row] = true;

                solve(row + 1, n, board, column, leftDiagonal, rightDiagonal, result);

                board[row][col] = 0;
                column[col] = false;
                leftDiagonal[row + col] = false;
                rightDiagonal[n - 1 + col - row] = false;
            }
        }
    }

public:
    vector<vector<vector<int>>> BranchAndBound(int n, vector<vector<int>> &board)
    {
        vector<vector<vector<int>>> result;

        vector<bool> leftDiagonal(2 * n - 1, false);
        vector<bool> rightDiagonal(2 * n - 1, false);
        vector<bool> column(n, false);

        solve(0, n, board, column, leftDiagonal, rightDiagonal, result);

        return result;
    }
};

int main()
{
    int n = 4;
    NQueens obj;

    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<vector<int>>> result = obj.BranchAndBound(n, board);

    cout << "\n N Queens Puzzle Solutions by Branch and Bound & Backtracking for N = " << n + 1 << "\n"
         << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << "----- Solution " << i + 1 << " ----- \n"
             << endl;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                cout << result[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "Thank you for using the program. \n"
         << endl;

    return 0;
}