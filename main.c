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

char const players[] = {'X', 'O'};

enum Player curr_player = X;

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

void handle_turn(enum Player *player) {
    char player_char;
    if (*player == X) {
        player_char = 'X';
    } else {
        player_char = 'O';
    }

    int row, col;
    printf("Enter your move, %c, using this format: `row col`\n", player_char);
    print_board(board);
    scanf("%d %d", &row, &col);
    board[row][col] = player_char;

    /* Check for win and exit at win/loss/draw */
    enum Result result = check_for_win(board, player_char);
    if (result == WIN) {
        printf("%c WON!\n", player_char);
        print_board(board);
        exit(0);
    } else if (result == LOSE) {
        if (*player == X) {
            printf("O WON!\n");
            print_board(board);
            exit(0);
        } else {
            printf("X WON!\n");
            print_board(board);
            exit(0);
        }
    } else if (result == DRAW) {
        printf("DRAW\n");
        print_board(board);
        exit(0);
    } else {
        if (*player == X) {
            *player = O;
        } else {
            *player = X;
        }
    }

}

int main() {
    while (true) {
        handle_turn(&curr_player);
    }
}
