//
// Created by downq on 6/22/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(char grid[140][141]) {
    FILE *fp = fopen("../puzzle.txt", "r");
    char *line = NULL;
    size_t len = 141;
    ssize_t read;
    int sum = 0;

    if (fp == NULL) {
        printf("failed to open puzzle.txt\n");
        return;
    }

    int r = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        for (int c = 0; c < 140; c++)
            grid[r][c] = line[c];
        grid[r][140] = 0;
        r++;
    }
    fclose(fp);
    free(line);
}

int isSymbol(const char c) {
    char list[] = "#$%&*+-/=@";
    for (int i = 0; i < strlen(list); i++)
        if (c == list[i])
            return 1;
    return 0;
}

int isNumber(const char c) {
    return c >= '0' && c <= '9';
}

int checkBounds(int r, int c) {
    return r >= 0 && r < 140 && c >= 0 && c < 140;
}

int hasAdjacentSymbol(char grid[140][141], int r, int c, int len) {
    for (int y = -1; y <= 1; y++)
        for (int x = -1; x <= len; x++)
            if (checkBounds(r + y, c + x) && isSymbol(grid[r + y][c + x]))
                return 1;
    return 0;
}

int main(void) {
    char grid[140][141];
    readFile(grid);
    int sum = 0;
    for (int r = 0; r < 140; r++)
        for (int c = 0; c < 140; c++) {
            int c2 = c;
            while (isNumber(grid[r][c2]))
                c2++;
            if (c2 > c) {
                if (hasAdjacentSymbol(grid, r, c, c2 - c)) {
                    int num = atoi(&grid[r][c]);
                    sum += num;
                }
                c = c2;
            }
        }
    printf("sum: %d\n", sum);
    return 0;
}
