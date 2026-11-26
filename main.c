#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void increment(int sq, int* board){
    if (sq >= 0 && sq < 480 && *(board+sq) != -1){
        *(board+sq) += 1;
    }
}

int in(int item, int* array, int arrayLength){
    int i;
    for (i=0;i<arrayLength;++i){
        if (*(array+i) == item){return 1;}
    }
    return 0;
}

int uncover(int sq, int* board, int* found){
    if (sq >= 0 && sq < 480){
        if (*(board+sq) == -1){return 0;}
        *(found+sq) = 1;
        if (*(board + sq) == 0){
            int toCheck[200];
            int index = 0;
            int max = 1;
            toCheck[0] = sq;
            while (index < max){
                if (toCheck[index] >= 0 && toCheck[index] < 480){
                    *(found + toCheck[index]) = 1;
                    if (*(board + toCheck[index]) == 0){
                        if (!(*(found + toCheck[index]-30))){toCheck[max++] = toCheck[index] - 30;}
                        if (!(*(found + toCheck[index]+30))){toCheck[max++] = toCheck[index] + 30;}
                        // Checks for left squares
                        if (toCheck[index]%30 > 0){
                            if (!(*(found + toCheck[index]-1))){toCheck[max++] = toCheck[index] - 1;}
                            if (!(*(found + toCheck[index]-31))){toCheck[max++] = toCheck[index] - 31;}
                            if (!(*(found + toCheck[index]+29))){toCheck[max++] = toCheck[index] + 29;}
                        }
                        // Checks for right squares
                        if (toCheck[index] < 29){
                            if (!(*(found + toCheck[index]+1))){toCheck[max++] = toCheck[index] + 1;}
                            if (!(*(found + toCheck[index]+31))){toCheck[max++] = toCheck[index] + 31;}
                            if (!(*(found + toCheck[index]-29))){toCheck[max++] = toCheck[index] - 29;}
                        }
                    }
                }
                index++;
            }
        }
        return 1;
    }
    return 0;
}

void printboard(int* board, int* found, int* flags, int flagCount){
    printf("\n");
    int i;
    int rows[16] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    int row = 0;
    printf("%*s", 3, "");
    for (i = 0; i < 30; i++){printf("%*d", 3, (i+1));}
    for (i = 0; i < 480; ++i){
        if (i%30 == 0){printf("\n%*c", 3, rows[row]); row++;}
        if (in(i, flags, flagCount)){printf("%*c", 3, 'F');}
        else if (*(found+i)){printf("%*d", 3, *(board+i));}
        else {printf("%*c", 3, '?');}
    }
    printf("\n");
}

int won(int flagCount, int* flags, int* board){
    if (flagCount < 99){return 0;}
    int i;
    for (i=0;i<99;++i){
        if (*(board + *(flags+i)) != -1){return 0;}
    }
    return 1;
}

int main(){
    srand((unsigned)time(NULL));
    // 30 x 16 board
    int board[480];
    int found[480];
    int mineCount = 99;
    int flags[99];
    int flagCount = 0;
    int i;
    for (i=0;i<480;i++){board[i]=0;found[i]=0;}
    for (i=0;i<mineCount;++i){
        flags[i]=0;
        int sq = rand()%480;
        while (board[sq] == -1){sq = rand()%480;}
        board[sq] = -1;

        increment(sq+30, board);
        increment(sq-30, board);
        // Checks for left squares
        if (sq % 30 > 0){
            increment(sq-1, board);
            increment(sq-31, board);
            increment(sq+29, board);
        }
        // Checks for right squares
        if (sq % 30 < 29){
            increment(sq+1, board);
            increment(sq+31, board);
            increment(sq-29, board);
        }
    }
    printboard(board, found, flags, flagCount);
    // while (!won(flagCount, flags, board)){
    //     continue;
    // }
}