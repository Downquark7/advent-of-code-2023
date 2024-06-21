//
// Created by downq on 6/21/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum color { r, g, b };

//Determine which games would have been possible if the bag had been loaded
//with only 12 red cubes, 13 green cubes, and 14 blue cubes.
//What is the sum of the IDs of those games?

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
        int red;
        int green;
        int blue;
        char color[7];
        int count;
        enum color c;
        sscanf(line, "Game %d", &id);
        char *ptr = strchr(line, ':') + 2;
        while (sscanf(ptr, "%d %[^,;]%*[,;] ", &count, color) == 2) {
            printf("Color: %s, Quantity: %d\n", color, count);

            // Move the pointer to the next color data
            ptr = strchr(ptr, ',') ? strchr(ptr, ',') + 2 : strchr(ptr, ';') + 2;
        }
    }

    printf("Sum: %d\n", sum);
    fclose(fp);
    return 0;
}
