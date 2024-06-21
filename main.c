#include <stdio.h>
#include <stdlib.h>

int scanLine(char *line, int len);

int checkNumber(char *line);

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

    while ((read = getline(&line, &len, fp)) != -1)
        sum += scanLine(line, read);

    printf("Sum: %d\n", sum);
    fclose(fp);

    return 0;
}

int scanLine(char *line, int len) {
    int a = 0;
    int b = 0;
    int tmp = 0;
    int count = 0;
    while (count++ < len) {
        tmp = checkNumber(line);
        if (!a)
            a = tmp;
        if (tmp)
            b = tmp;
        line++;
    }
    // printf("%d%d\n", a, b);
    return 10 * a + b;
}

//return 0 on not found
//return 1-9 on found
int checkNumber(char *line) {
    switch (*line) {
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'o':
            line++;
            if (*line == 'n') {
                line++;
                if (*line == 'e')
                    return 1;
            }
            break;
        case 't':
            line++;
            switch (*line) {
                case 'w':
                    line++;
                    if (*line == 'o')
                        return 2;
                    break;
                case 'h':
                    line++;
                    if (*line == 'r') {
                        line++;
                        if (*line == 'e') {
                            line++;
                            if (*line == 'e')
                                return 3;
                        }
                    }
                    break;
            }
            break;
        case 'f':
            line++;
            switch (*line) {
                case 'o':
                    line++;
                    if (*line == 'u') {
                        line++;
                        if (*line == 'r')
                            return 4;
                    }

                    break;
                case 'i':
                    line++;
                    if (*line == 'v') {
                        line++;
                        if (*line == 'e')
                            return 5;
                    }
                    break;
            }
            break;
        case 's':
            line++;
            switch (*line) {
                case 'i':
                    line++;
                    if (*line == 'x')
                        return 6;
                    break;
                case 'e':
                    line++;
                    if (*line == 'v') {
                        line++;
                        if (*line == 'e') {
                            line++;
                            if (*line == 'n')
                                return 7;
                        }
                    }
                    break;
            }
            break;
        case 'e':
            line++;
            if (*line == 'i') {
                line++;
                if (*line == 'g') {
                    line++;
                    if (*line == 'h') {
                        line++;
                        if (*line == 't')
                            return 8;
                    }
                }
            }
            break;
        case 'n':
            line++;
            if (*line == 'i') {
                line++;
                if (*line == 'n') {
                    line++;
                    if (*line == 'e')
                        return 9;
                }
            }
            break;
    }

    return 0;
}
