#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define HEIGHT 3
#define WIDTH 3

char AI = 'O';
char HUMAN = 'X';

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

typedef struct {
    int row;
    int col;
} Position;

char const players[] = {'X', 'O'};
enum Player currPlayer = X;

char board[HEIGHT][WIDTH] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};

void printBoard(char board[HEIGHT][WIDTH]) {
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

enum Result checkForWin(char board[HEIGHT][WIDTH], char piece) {
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

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == ((piece == 'X') ? 'O' : 'X')) {
            return LOSE;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == ((piece == 'X') ? 'O' : 'X')) {
            return LOSE;
        }
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == ((piece == 'X') ? 'O' : 'X')) {
        return LOSE;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == ((piece == 'X') ? 'O' : 'X')) {
        return LOSE;
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

int minimax(int depth, bool isMaximising, double alpha, double beta) {
    enum Result result = checkForWin(board, AI);
    if (result == WIN) {
        return 1;
    } else if (result == LOSE) {
        return -1;
    } else if (result == DRAW) {
        return 0;
    } 

    if (isMaximising) {
        double bestScore = -INFINITY;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    int score = minimax(depth + 1, false, alpha, beta);
                    board[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                    }
                    if (alpha > score) {
                        alpha = score;
                    }
                    if (alpha >= beta) {
                        break;
                    }
                } 
            }
        }
        return bestScore;
    }
    else {
        double bestScore = INFINITY;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = HUMAN;
                    int score = minimax(depth + 1, true, alpha, beta);
                    board[i][j] = ' ';
                    if (score < bestScore) {
                        bestScore = score;
                    }
                    if (beta < score) {
                        beta = score;
                    }
                    if (beta <= alpha) {
                        break;
                    }
                } 
            }
        }
        return bestScore;
    }
}

void aiMove(int depth, double alpha, double beta) {
    Position bestMove;
    double bestScore = -INFINITY;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int score = minimax(depth, false, alpha, beta);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.row = i;
                    bestMove.col = j;
                    
                }
            }
        }
    }
    board[bestMove.row][bestMove.col] = AI;

    enum Result result = checkForWin(board, AI);
    if (result == WIN) {
        printf("AI WON!\n");
        printBoard(board);
        exit(0);
    } else if (result == LOSE) {
        printf("HUMAN WON!\n");
        printBoard(board);
        exit(0);
    } else if (result == DRAW) {
        printf("DRAW\n");
        printBoard(board);
        exit(0);
    } else {
        if (currPlayer == X) {
            currPlayer = O;
        } else {
            currPlayer = X;
        }
    }
}


void handleTurn(enum Player *player) {
    char playerChar = HUMAN;

    int row, col;
    printf("Enter your move, %c, using this format: `row col`\n", playerChar);
    printBoard(board);
    scanf("%d %d", &row, &col);
    while (row > HEIGHT || col > WIDTH || board[row][col] != ' ') {
        printf("Invalid move, reenter your move, %c, using this format: `row col`\n", playerChar);
        printBoard(board);
        scanf("%d %d", &row, &col);
    }
    board[row][col] = playerChar;

    /* Check for win and exit at win/loss/draw */
    enum Result result = checkForWin(board, AI);
    if (result == WIN) {
        printf("AI WON!\n");
        printBoard(board);
        exit(0);
    } else if (result == LOSE) {
        printf("HUMAN WON!\n");
        printBoard(board);
        exit(0);
    } else if (result == DRAW) {
        printf("DRAW\n");
        printBoard(board);
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
        if (currPlayer == X) {
            handleTurn(&currPlayer);
        } else {
            aiMove(0, -INFINITY, INFINITY);
        }
    }
}
