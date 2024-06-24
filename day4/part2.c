//
// Created by downq on 6/23/2024.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("puzzle.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int sum = 0;

    if (fp == NULL) {
        printf("failed to open puzzle.txt\n");
        return 1;
    }

    int cardCountMap[200];
    for (int i = 0; i < 200; i++)
        cardCountMap[i] = 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        int id = atoi(&line[5]);
        // printf("id = %d\n", id);
        char map[100];
        for (int i = 0; i < 100; i++)
            map[i] = 0;
        for (int i = 0; i < 25; i++)
            map[atoi(&line[41 + 3 * i])] = 1;
        int matches = 0;
        for (int i = 0; i < 10; i++) {
            int key = atoi(&line[10 + 3 * i]);
            if (map[key])
                matches++;
        }
        for (int i = id; i < id + matches; i++) {
            cardCountMap[i] += cardCountMap[id - 1];
            // printf("cardCountMap[%d] = %d\n", i, cardCountMap[i]);
        }
        // printf("matches = %d\ncardCountMap[id - 1] = %d\n", matches, cardCountMap[id - 1]);
        sum += cardCountMap[id - 1];
    }

    printf("Sum: %d\n", sum);
    fclose(fp);
}
