/* Number of ways a robot can move from top left corner to bottom right given that some of cells cannot be entered */

#include <iostream>
#include <vector>

#define NO_OF_CELL 3

using namespace std;

bool is_valid_cell(int row, int col, int n) {
    bool valid_row = row >= 0 && row < n;
    bool valid_col = col >= 0 && col < n;
    return valid_row && valid_col;
}

int number_of_paths(int maze[NO_OF_CELL][NO_OF_CELL], int row, int col, int n) {

    if (row == n - 1 && col == n - 1) {
        return 1;
    }

    if (is_valid_cell(row, col, n) && maze[row][col]> -1) {
        return  number_of_paths(maze, row + 1, col, n) + number_of_paths(maze, row, col + 1, n);
    }

    if (maze[row][col] == -1) return 0;
    return 0;
}

int number_of_paths_dp(int maze[NO_OF_CELL][NO_OF_CELL], int n) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (j == n - 1 && i == n - 1) {
                maze[i][j] = 1;
            }
            else {
                if (maze[i][j] == -1) continue;
                int down = 0, right = 0;
                if (is_valid_cell(i + 1, j, n) && maze[i+1][j] != -1 ) {
                    down = maze[i + 1][j];
                }
                if (is_valid_cell(i, j + 1, n) && maze[i][j+1] != -1) {
                    right = maze[i][j + 1];
                }
                maze[i][j] = down + right;
            }
        }
    }
    return maze[0][0];
}

int main() {
    int maze[NO_OF_CELL][NO_OF_CELL] = { {0, 0 ,-1},
                                         {0, 0, 0},
                                         {-1, 0, 0} };
    //cout << "Number of paths: " << number_of_paths(maze, 0, 0, NO_OF_CELL);
    cout << "number of paths: " << number_of_paths_dp(maze, NO_OF_CELL);
    return 0;
}