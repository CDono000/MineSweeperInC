#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void increment(int sq, int* board){
    if (sq >= 0 && sq < 480 && *(board+sq) != -1){
        *(board+sq) += 1;
    }
}

int uncover(int sq, int* board, int* found){
    if (sq >= 0 && sq < 480){
        if (*(board+sq) == -1){return 0;}
        *(found+sq) = 1;
        if (*(board + sq) == 0){
            uncover(sq+30, board, found);
            uncover(sq-30, board, found);
            // Checks for left squares
            if (sq > 0 && div(sq, 30).quot == div(sq-1, 30).quot){
                uncover(sq-1, board, found);
                uncover(sq-31, board, found);
                uncover(sq+29, board, found);
            }
            // Checks for right squares
            if (sq < 439 && div(sq, 30).quot == div(sq+1, 30).quot){
                uncover(sq+1, board, found);
                uncover(sq+31, board, found);
                uncover(sq-29, board, found);
            }
        }
        return 1;
    }
    return 0;
}

void printboard(int* board, int* found){
    int i;
    int rows[16] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    int row = 0;
    printf("%*s", 3, "");
    for (i = 0; i < 30; i++){printf("%*d", 3, (i+1));}
    for (i = 0; i < 480; ++i){
        if (i%30 == 0){printf("\n%*c", 3, rows[row]); row++;}
        if (*(found+i)){printf("%*d", 3, *(board+i));}
        else {printf("%*c", 3, '?');}
    }
    printf("\n");
}

int main(){
    srand((unsigned)time(NULL));
    // 30 x 16 board
    int board[480];
    int found[480];
    int mineCount = 99;
    int i;
    for (i=0;i<480;i++){board[i]=0;found[i]=0;}
    for (i=0;i<mineCount;++i){
        int sq = rand()%480;
        while (board[sq] == -1){sq = rand()%480;}
        board[sq] = -1;

        increment(sq+30, board);
        increment(sq-30, board);
        // Checks for left squares
        if (sq > 0 && div(sq, 30).quot == div(sq-1, 30).quot){
            increment(sq-1, board);
            increment(sq-31, board);
            increment(sq+29, board);
        }
        // Checks for right squares
        if (sq < 439 && div(sq, 30).quot == div(sq+1, 30).quot){
            increment(sq+1, board);
            increment(sq+31, board);
            increment(sq-29, board);
        }
    }
    uncover(240, board, found);
    printboard(board, found);
}