#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define HEIGHT 3
#define WIDTH 3

enum Result {
    WIN,
    LOSE,
    DRAW,
    CONTINUE,
};

enum Player {
    X,
    O,
};

char board[HEIGHT][WIDTH] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};

void print_board(char board[HEIGHT][WIDTH]) {
    printf("-------------\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                printf("|");
            }
            printf(" %c ", board[i][j]);
            printf("|");
        }
        printf("\n-------------\n");
    }
    printf("\n");
}

enum Result check_for_win(char board[HEIGHT][WIDTH], char piece) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == piece) {
            return WIN;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == piece) {
            return WIN;
        }
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == piece) {
        return WIN;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == piece) {
        return WIN;
    }

    bool draw = true;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == ' ') {
                draw = false;
            }
        }
    }
    if (draw) {
        return DRAW;
    }

    return CONTINUE;

}

void handle_turn(enum Player curr_player) {
    char player;
    if (curr_player == 0) {
        player = 'X';
    } else {
        player = 'O';
    }

    int row, col;
    printf("Enter your move, %c, using this format: `row col`\n", player);
    print_board(board);
    scanf("%d %d", &row, &col);
    board[row][col] = player;

    /* Check for win and exit at win/loss/draw */
    enum Result result = check_for_win(board, curr_player);
    if (result == WIN) {
        printf("%c WON!", player);
    } else if (result == LOSE) {
        if (curr_player == O) {
            printf("O WON!");
            exit(0);
        } else {
            printf("X WON!");
            exit(0);
        }
    } else if (result == DRAW) {
        printf("DRAW");
        exit(0);
    } else {
        if (curr_player == X) {
            curr_player = O;
        } else {
            curr_player = X;
        }
    }

}

int main() {

    enum Player curr_player = X;

    while (true) {
        handle_turn(curr_player);
    }
}
