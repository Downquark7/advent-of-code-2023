//
// Created by downq on 6/23/2024.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("../puzzle.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int sum = 0;

    if (fp == NULL) {
        printf("failed to open puzzle.txt\n");
        return 1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf(line);
        // int id = atoi(&line[5]);
        // printf("card %d\n", atoi(&line[5]));
        // int key[10];
        // for (int i = 0; i < 10; i++)
        //     key[i] = atoi(&line[10 + 3 * i]);
        // printf("%d ", atoi(&line[10 + 3 * i]));
        // printf("\n");
        char map[100] = {0};
        for (int i = 0; i < 25; i++)
            map[atoi(&line[41 + 3 * i])] = 1;
        // printf("%d ", atoi(&line[41 + 3 * i]));
        // printf("\n");
        int value = 1;
        for (int i = 0; i < 10; i++) {
            int key = atoi(&line[10 + 3 * i]);
            if (map[key])
                value *= 2;
        }
        value /= 2;
        sum += value;
    }

    printf("Sum: %d\n", sum);
    fclose(fp);
}
