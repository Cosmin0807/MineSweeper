#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "TablaStruct.h"

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    Block** table = NULL;
    double HighScore1 = INT_MIN, HighScore2 = INT_MIN, HighScore3 = INT_MIN;
    StartJoc(table, &HighScore1, &HighScore2, &HighScore3);
    while (1) {
        printf("Do you want to play again?\n1. Yes\n2. No\n");
        int aleg = 0;
        scanf("%d", &aleg);
        printf("\n");
        if (aleg == 1)
            StartJoc(table, &HighScore1, &HighScore2, &HighScore3);
        else if (aleg == 2)
                return 0;
            else printf("Invalid choise");
    }
    return 0;
}