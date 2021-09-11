#include <stdio.h>

#define N 9
#define UNASSIGNED 0

void pretty_print_matrix(int puzzle[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d", puzzle[row][col]);
            if (col % 3 == 2) printf("|");
        }
        if (row % 3 == 2) printf("\n-----------");
        printf("\n");
    }
}

int find_empty(int puzzle[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (puzzle[*row][*col] == UNASSIGNED) return 1;
        }
    }
    return 0;
}


int is_exist_row(int puzzle[N][N], int n, int row) {
    for (int col = 0; col < N; col++) {
        if (puzzle[row][col] == n) return 1;
    }
    return 0;
}

int is_exist_col(int puzzle[N][N], int n, int col) {
    for (int row = 0; row < N; row++) {
        if (puzzle[row][col] == n) return 1;
    }
    return 0;
}

int is_exist_box(int grid[N][N], int start_row, int start_col, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + start_row][col + start_col] == num) {
                return 1;
            }
        }
    }
    return 0;
}


int is_safe(int puzzle[N][N], int n, int row, int col) {
    if (is_exist_row(puzzle, n, row) || is_exist_col(puzzle, n, col)) {
        return 0;
    }

    // Check if safe in grid
    int start_row = row - (row % 3);
    int start_col = col - (col % 3);
    if (is_exist_box(puzzle, start_row, start_col, n)) {
        return 0;
    }
    return 1;
}

// Recursive Function to solve puzzle by backtracking
int solve(int puzzle[N][N]) {
    // Terminating Condition
    int r = 0;
    int c = 0;

    if (!find_empty(puzzle, &r, &c)) {
        // If all cells are not zero and filled up return true (1), print board too
        return 1;
    }

    // Backtracking logic
    // Loop through 1 to N
    for (int n = 1; n <= N; n++) {
        // Check if 1 can be placed in next empty cell
        if (is_safe(puzzle, n, r, c)) {

            // If yes, place it
            puzzle[r][c] = n;

            // Call the function recursively
            if (solve(puzzle)) {
                return 1;
            }

            // If the function doesn't return true, backtrack after head recursion
            puzzle[r][c] = UNASSIGNED;
        }
    }

    return 0;
}


int main() {
    printf("STARTING\n");

    int puzzle[N][N] =
            {{0, 0, 0, 0, 0, 3, 2, 9, 0},
             {0, 8, 6, 5, 0, 0, 0, 0, 0},
             {0, 2, 0, 0, 0, 1, 0, 0, 0},
             {0, 0, 3, 7, 0, 5, 1, 0, 0},
             {9, 0, 0, 0, 0, 0, 0, 0, 8},
             {0, 0, 2, 9, 0, 8, 3, 0, 0},
             {0, 0, 0, 4, 0, 0, 0, 8, 0},
             {0, 4, 7, 1, 0, 0, 0, 0, 0}};

    if (solve(puzzle)) {
        pretty_print_matrix(puzzle);
    } else {
        printf("No solution");
    }

//    pretty_print_matrix();
    return 0;
}

