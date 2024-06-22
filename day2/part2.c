//
// Created by downq on 6/21/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum color { r, g, b };

//Determine which games would have been possible if the bag had been loaded
//with only 12 red cubes, 13 green cubes, and 14 blue cubes.
//What is the sum of the IDs of those games?

uintptr_t min(uintptr_t a, uintptr_t b) {
    return a < b ? a : b;
}

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

    while ((read = getline(&line, &len, fp)) != -1) {
        int id;
        int red = 0;
        int maxred = 0;
        int green = 0;
        int maxgreen = 0;
        int blue = 0;
        int maxblue = 0;
        char color[7];
        int count;
        enum color c;
        sscanf(line, "Game %d", &id);
        // printf("Game %d\n", id);
        char *ptr = strchr(line, ':') + 2;
        while (sscanf(ptr, "%d %[^;,\n\r]", &count, color) == 2) {
            // printf("Color: %s, Quantity: %d\n", color, count);

            if (strcmp(color, "red") == 0) {
                red += count;
                maxred = red > maxred ? red : maxred;
            }
            if (strcmp(color, "green") == 0) {
                green += count;
                maxgreen = green > maxgreen ? green : maxgreen;
            }
            if (strcmp(color, "blue") == 0) {
                blue += count;
                maxblue = blue > maxblue ? blue : maxblue;
            }

            // Move the pointer to the next color data
            ptr = strpbrk(ptr, ",;\n\r");
            if (*ptr == '\n' || *ptr == '\r') {
                // if (red > 12 || green > 13 || blue > 14) {
                //     // printf("bad: %s", line);
                //     break;
                // }
                // printf("good: %s", line);
                sum += maxred * maxgreen * maxblue;
                break;
            }
            if (*ptr == ';') {
                // if (red > 12 || green > 13 || blue > 14) {
                //     // printf("bad: %s", line);
                //     break;
                // }
                red = 0;
                green = 0;
                blue = 0;
            }
            if (*ptr)
                ptr += 2;
        }
    }

    printf("Sum: %d\n", sum);
    fclose(fp);
    return 0;
}
