//
// Created by downq on 6/22/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//10 or 140
#define WIDTH 140

void readFile(char grid[140][WIDTH + 1]) {
    FILE *fp = fopen("../puzzle.txt", "r");
    char *line = NULL;
    size_t len = WIDTH + 1;
    ssize_t read;
    int sum = 0;

    if (fp == NULL) {
        printf("failed to open puzzle.txt\n");
        return;
    }

    int r = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        for (int c = 0; c < WIDTH; c++)
            grid[r][c] = line[c];
        grid[r][WIDTH] = 0;
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

int isNum(const char c) {
    return c >= '0' && c <= '9';
}

int checkBounds(int r, int c) {
    return r >= 0 && r < 140 && c >= 0 && c < WIDTH;
}

int hasAdjacentSymbol(char grid[140][WIDTH + 1], int r, int c, int len) {
    for (int y = -1; y <= 1; y++)
        for (int x = -1; x <= len; x++)
            if (checkBounds(r + y, c + x) && isSymbol(grid[r + y][c + x]))
                return 1;
    return 0;
}

int leftNum(char grid[140][WIDTH + 1], int r, int c) {
    while (checkBounds(r, c) && isNum(grid[r][c]))
        c--;
    c++;
    int output = atoi(&grid[r][c]);
    printf("%d\n", output);
    return output;
}

// int rightNum(char grid[140][WIDTH + 1], int r, int c) {
//     int output = atoi(&grid[r][c]);
//     return output;
// }

int getRatioPart2(char grid[140][WIDTH + 1], int locations[8], int r, int c) {
    int rOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int cOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    for (int i = 0; i < 8; i++) {
        if (locations[i]) {
            locations[i] = 0;
            if (i <= 2) {
                locations[0] = 0;
                locations[1] = 0;
                locations[2] = 0;
            }
            if (i >= 5) {
                locations[5] = 0;
                locations[6] = 0;
                locations[7] = 0;
            }
            return leftNum(grid, rOffsets[i] + r, cOffsets[i] + c);
        }
    }
}

//012
//3 4
//567
int getRatio(char grid[140][WIDTH + 1], int r, int c) {
    int locations[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int rOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int cOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    for (int i = 0; i < 8; i++)
        locations[i] = checkBounds(r + rOffsets[i], c + cOffsets[i]) && isNum(grid[r + rOffsets[i]][c + cOffsets[i]]);
    for (int i = 0; i < 8; i++) {
        printf("%d ", locations[i]);
    }
    printf("\n");
    if (locations[0] && !locations[1] && locations[2])
        return leftNum(grid, r + rOffsets[0], c + cOffsets[0]) * leftNum(grid, r + rOffsets[2], c + cOffsets[2]);
    if (locations[5] && !locations[6] && locations[7])
        return leftNum(grid, r + rOffsets[5], c + cOffsets[5]) * leftNum(grid, r + rOffsets[7], c + cOffsets[7]);
    return getRatioPart2(grid, locations, r, c) * getRatioPart2(grid, locations, r, c);
}

int main(void) {
    char grid[140][WIDTH + 1];
    readFile(grid);
    int sum = 0;
    for (int r = 0; r < WIDTH; r++) {
        for (int c = 0; c < WIDTH; c++) {
            if (grid[r][c] == '*') {
                sum += getRatio(grid, r, c);
            }
        }
    }
    printf("sum: %d\n", sum);
    return 0;
}
