#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE_HORIZONTAL 3
#define BOARD_SIZE_VERTICAL BOARD_SIZE_HORIZONTAL
#define BOARD_SIZE (BOARD_SIZE_HORIZONTAL * BOARD_SIZE_VERTICAL)

typedef enum {
    C_EMPTY = 0,
    C_PLAYER_1,
    C_PLAYER_2,
} cell_t;

typedef cell_t board_t[BOARD_SIZE_HORIZONTAL][BOARD_SIZE_VERTICAL];

inline static void print_line() { printf(" — — —\n"); }

inline static bool is_in_bounds(int row, int column) {
    return row >= 0 && row < BOARD_SIZE_HORIZONTAL && column >= 0 &&
           column < BOARD_SIZE_VERTICAL;
}

int get_input() {
    // Use -1 as a default, so we can check if the user input is valid
    int x = -1;

    scanf("%5d", &x); // We use `%5d` to _kinda_ avoid integer overflow

    if (x == -1) {
        printf("Error: invalid input\n");
        exit(1);
    }

    return x;
}

char get_symbol_for_cell(cell_t cell) {
    if (cell == C_PLAYER_1) {
        return 'o';
    }
    if (cell == C_PLAYER_2) {
        return 'x';
    }
    return ' ';
}

void print_board(board_t board) {
    print_line();

    for (int i = 0; i < BOARD_SIZE_HORIZONTAL; i++) {
        printf("|");

        for (int j = 0; j < BOARD_SIZE_VERTICAL; j++) {
            printf("%c|", get_symbol_for_cell(board[i][j]));
        }

        printf("\n");
        print_line();
    }
}

bool is_corner_or_middle(int row, int column) {
    // Top-left
    if (row == 0 && column == 0) {
        return true;
    }

    // Top-right
    if (row == 0 && column == 2) {
        return true;
    }

    // Bottom-left
    if (row == 2 && column == 0) {
        return true;
    }

    // Bottom-right
    if (row == 2 && column == 2) {
        return true;
    }

    // Middle
    if (row == 1 && column == 1) {
        return true;
    }

    return false;
}

bool check_for_win(board_t board, int row, int column) {
    cell_t player = board[row][column];

    // Always check the row and the column
    if (board[row][0] == player && board[row][1] == player &&
        board[row][2] == player) {
        return true;
    }
    if (board[0][column] == player && board[1][column] == player &&
        board[2][column] == player) {
        return true;
    }

    // And then check for diagonals if necessary
    if (!is_corner_or_middle(row, column)) {
        return false;
    }
    // Top-left to bottom-right
    if (board[0][0] == player && board[1][1] == player &&
        board[2][2] == player) {
        return true;
    }
    // Top-right to bottom-left
    if (board[0][2] == player && board[1][1] == player &&
        board[2][0] == player) {
        return true;
    }

    return false;
}

int main() {
    board_t board = {C_EMPTY}; // Initialize everything to `C_EMPTY`
    int row = 0;
    int column = 0;

    print_board(board);

    for (int i = 0; i < BOARD_SIZE; i++) {
        cell_t current_player = i % 2 == 0 ? C_PLAYER_1 : C_PLAYER_2;
        printf("Player %d turn\n", current_player);

        // Ask user for a row and column, until the selected cell is:
        // - Empty
        // - In bounds
        while (true) {
            printf("Row: ");
            row = get_input();
            printf("Column: ");
            column = get_input();

            if (!is_in_bounds(row, column)) {
                printf("This cell is out of bounds!\n");
                continue;
            }

            if (board[row][column] != C_EMPTY) {
                printf("This cell is already used!\n");
                continue;
            }

            break;
        }

        board[row][column] = current_player;
        print_board(board);

        // No winner before turn 5
        if (i < 4) {
            continue;
        }

        if (!check_for_win(board, row, column)) {
            continue;
        }

        printf("Player %d won!\n", current_player);

        return 0;
    }

    printf("It's a tie!\n");

    return 0;
}
