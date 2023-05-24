#include "TablaStruct.h"

Block** createTable(int rows, int cols){
    Block** table = (Block**)calloc(rows, sizeof(Block*));
    for (int i = 0; i < rows; i++){
        table[i] = (Block*)calloc(cols, sizeof(Block));
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            table[i][j].isMine = 0;
            table[i][j].isRevealed = 0;
            table[i][j].isFlagged = 0;
            table[i][j].numMines = 0;
        }
    }
    return table;
}

//Free memory for the table
void freeTable(Block** table, int rows){
    for(int i = 0; i < rows; i++)
        free(table[i]);
    free(table);
}

//Print the table
void printTable(Block** table, int rows, int cols) {
    printf("     ");
    for(int i = 0; i < cols; i++)
        if (i < 10)
            printf("%d   ", i);
        else
            printf("%d  ", i);
    printf("\n");
    for(int i = 0; i < rows; i++){
        if (i < 10)
            printf("%d  ", i);
        else
            printf("%d ", i);
        for(int j = 0; j < cols; j++){
            if(table[i][j].isRevealed == 1){
                if(table[i][j].isMine == 1){
                    printf("  X ");
                } else {
                    printf("  %d ", table[i][j].numMines);
                }
            } else if(table[i][j].isFlagged == 1){
                printf("  F ");
            } else{
                printf("  ∎ ");
            }
        }
        printf("\n");
    }
}

//Print the table with all the mines revealed
void printMinesRevealed(Block** table, int rows, int cols) {
    printf("     ");
    for(int i = 0; i < cols; i++)
        if (i < 10)
            printf("%d   ", i);
        else
            printf("%d  ", i);
    printf("\n");
    for(int i = 0; i < rows; i++){
        if (i < 10)
            printf("%d  ", i);
        else
            printf("%d ", i);
        for(int j = 0; j < cols; j++){
            if(table[i][j].isMine == 1){
                printf("  X ");
            } else {
                printf("  %d ", table[i][j].numMines);
            }
        }
        printf("\n");
    }
}

//Generate random mines
void GenMines(Block** table, int rows, int cols, int mines){
    int i = 0, j = 0;
    while (mines > 0){
        i = rand() % rows;
        j = rand() % cols;
        if (table[i][j].isMine == 0){
            table[i][j].isMine = 1;
            mines--;
        }
    }
}

//Count the number of mines around a block
void countMines(Block** table, int rows, int cols) {
    int count = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            count = 0;
            if (table[i][j].isMine == 0){
                if (i > 0 && j > 0 && table[i-1][j-1].isMine == 1)
                    count++;
                if (i > 0 && table[i-1][j].isMine == 1)
                    count++;
                if (i > 0 && j < cols-1 && table[i-1][j+1].isMine == 1)
                    count++;
                if (j > 0 && table[i][j-1].isMine == 1)
                    count++;
                if (j < cols-1 && table[i][j+1].isMine == 1)
                    count++;
                if (i < rows-1 && j > 0 && table[i+1][j-1].isMine == 1)
                    count++;
                if (i < rows-1 && table[i+1][j].isMine == 1)
                    count++;
                if (i < rows-1 && j < cols-1 && table[i+1][j+1].isMine == 1)
                    count++;
                table[i][j].numMines = count;
            }
        }
    }
}

int CheckWin(Block** table, int rows, int cols, int mines){
    int count = 0, nrMines = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (table[i][j].isRevealed == 1)
                count++;
        }
    }
    if (count == rows*cols-mines){
        printf("You win!\n");
        printMinesRevealed(table, rows, cols);
        return 1;
    }
    for (int i = 0 ; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (table[i][j].isMine == 1 && table[i][j].isFlagged == 1)
                nrMines++;
    if (nrMines == mines){
        printf("You win!\n");
        printMinesRevealed(table, rows, cols);
        return 1;
    }
    return 0;
}

void Reveal(Block** table, int rows, int cols, int i, int j){
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        return;
    if (table[i][j].isRevealed == 1)
        return;
    if (table[i][j].isMine == 1)
        return;
    if (table[i][j].numMines != 0){
        table[i][j].isRevealed = 1;
        return;
    }
    table[i][j].isRevealed = 1;
    Reveal(table, rows, cols, i-1, j-1);
    Reveal(table, rows, cols, i-1, j);
    Reveal(table, rows, cols, i-1, j+1);
    Reveal(table, rows, cols, i, j-1);
    Reveal(table, rows, cols, i, j+1);
    Reveal(table, rows, cols, i+1, j-1);
    Reveal(table, rows, cols, i+1, j);
    Reveal(table, rows, cols, i+1, j+1);
}

//function to reveal all the blocks around a block that are not flagged
void revealAll(Block** table, int rows, int cols, int i, int j) {
    int nrFlags = 0;
    if (table[i][j].numMines == 0)\
        return;
    if (table[i][j].isRevealed == 0) {
        printf("This block is not revealed yet\n");
        return;
    }
    if (table[i][j].isFlagged == 1) {
        printf("This block is flagged\n");
        return;
    }
    if (i > 0 && j > 0 && table[i-1][j-1].isFlagged == 1) 
        nrFlags++;
    if (i > 0 && table[i-1][j].isFlagged == 1)
        nrFlags++;
    if (i > 0 && j < cols-1 && table[i-1][j+1].isFlagged == 1)
        nrFlags++;
    if (j > 0 && table[i][j-1].isFlagged == 1) 
        nrFlags++;
    if (j < cols-1 && table[i][j+1].isFlagged == 1)
        nrFlags++;
    if (i < rows-1 && j > 0 && table[i+1][j-1].isFlagged == 1)
        nrFlags++;
    if (i < rows-1 && table[i+1][j].isFlagged == 1) 
        nrFlags++;
    if (i < rows-1 && j < cols-1 && table[i+1][j+1].isFlagged == 1)
        nrFlags++;
    if (nrFlags == table[i][j].numMines){
        if (i > 0 && j > 0 && table[i-1][j-1].isFlagged == 0)
            Reveal(table, rows, cols, i-1, j-1);
        if (i > 0 && table[i-1][j].isFlagged == 0)
            Reveal(table, rows, cols, i-1, j);
        if (i > 0 && j < cols-1 && table[i-1][j+1].isFlagged == 0)
            Reveal(table, rows, cols, i-1, j+1);
        if (j > 0 && table[i][j-1].isFlagged == 0)
            Reveal(table, rows, cols, i, j-1);
        if (j < cols-1 && table[i][j+1].isFlagged == 0)
            Reveal(table, rows, cols, i, j+1);
        if (i < rows-1 && j > 0 && table[i+1][j-1].isFlagged == 0)
            Reveal(table, rows, cols, i+1, j-1);
        if (i < rows-1 && table[i+1][j].isFlagged == 0)
            Reveal(table, rows, cols, i+1, j);
        if (i < rows-1 && j < cols-1 && table[i+1][j+1].isFlagged == 0)
            Reveal(table, rows, cols, i+1, j+1);
    } else {
        printf("The number of flags around this block is not equal to the number of mines around this block\n");
    }
}
void StartJoc(Block** table, double* HighScore1, double* HighScore2, double* HighScore3) {
    char comanda[100], option = 0;
    int rows = 0, cols = 0, mines = 0, dif = 0, ok = 0;
    printf("Select Difficulty:\n 1. Easy\n 2. Medium\n 3. Hard\n");
    scanf("%d", &dif);
    switch (dif) {
        case 1:
            rows = 8;
            cols = 8;
            mines = 10;
            break;
        case 2:
            rows = 16;
            cols = 16;
            mines = 40;
            break;
        case 3:
            rows = 25;
            cols = 25;
            mines = 99;
            break;
        default:
            printf("Invalid option\n");
            return;
    }
    table = createTable(rows, cols);
    GenMines(table, rows, cols, mines);
    countMines(table, rows, cols);
    time_t startTime, endTime;
    double seconds = 0.0;
    startTime = time(NULL);
    //printTable(table, rows, cols);
    //printMinesRevealed(table, rows, cols);
    while(1) {
        printTable(table, rows, cols);
        int x = 0, y = 0;
        printf("To reveal write: x y R\nTo flag write: x y F\nTo unflag write: x y U\nTo reveal all neighbour blocks of a block write: x y A\nTo exit write: Exit\n");
        scanf("%s", comanda);
        if (strcmp(comanda, "Exit") == 0) {
            freeTable(table, rows);
            return;
        }
        if (comanda[0] < '0' || comanda[0] > '9') {
            printf("Invalid command\n");
        } else {
            x = atoi(comanda);
            scanf(" %d %c", &y, &option); 
            if (x < 0 || x >= rows || y < 0 || y >= cols) {
                printf("Invalid block\n");
            } else {
                if (option == 'F' || option == 'f')
                    if (table[x][y].isRevealed == 0)
                        table[x][y].isFlagged = 1;
                if (option == 'U' || option == 'u')
                    table[x][y].isFlagged = 0;
                if (option == 'A' || option == 'a')
                    revealAll(table, rows, cols, x, y);
                if (option == 'R' || option == 'r'){
                    if (table[x][y].isMine == 1) {
                        printMinesRevealed(table, rows, cols);
                        printf("You lost\n");
                        break;
                    }
                    Reveal(table, rows, cols, x, y);
                    ok = CheckWin(table, rows, cols, mines);
                    if (ok == 1)
                        break;
                }
            }
        }
    }
    endTime = time(NULL);
    seconds = difftime(endTime, startTime);
    int nrMinesGuess = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (table[i][j].isMine == 1 && table[i][j].isFlagged == 1)
                nrMinesGuess++;
    double scor = nrMinesGuess;
    if (ok == 1) {
        if (seconds < 500)
            scor += 100;
        else if (seconds < 1000)
                scor += 50;
            else scor += 10;
    }
    printf("Time: %.2lf\n", seconds);
    printf("Score: %.2lf\n", scor);
    switch (dif) {
        case 1:
            if (scor > *HighScore1)
                *HighScore1 = scor;
            printf("HighScore: %.2lf\n", *HighScore1);
            break;
        case 2:
            if (scor > *HighScore2)
                *HighScore2 = scor;
            printf("HighScore: %.2lf\n", *HighScore2);
            break;
        case 3:
            if (scor > *HighScore3)
                *HighScore3 = scor;
            printf("HighScore: %.2lf\n", *HighScore3);
            break;
    }
    freeTable(table, rows);
}

//function to calculate the score
