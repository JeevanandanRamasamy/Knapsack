#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **table, *weights, *values, total = 0;
char **items;

int getval(int r, int c) {
    if (r < 0 || c < 0)
        return 0;
    else
        return table[r][c];
}

int getweight(int r, int c) {
    if (r < 0 || c < 0)
        return 0;
    else
        return r + 1;
}

void filltable(int r, int c) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if ((weights[j] + getweight(i - weights[j], j - 1)) <= (i + 1) && values[j] + getval(i - weights[j], j - 1) > getval(i, j - 1))
                table[i][j] = values[j] + getval(i - weights[j], j - 1);
            else
                table[i][j] = getval(i, j - 1);
        }
    }
}

void printitems(int r, int c) {
    if (r < 0)
        return;
    if (!c) {
        if (table[r][c] > 0) {
            total += weights[c];
            printf("%s\n", items[c]);
        }
        return;
    }
    if (table[r][c] == table[r][c - 1])
        printitems(r, c - 1);
    else {
        printitems(r - weights[c], c - 1);
        total += weights[c];
        printf("%s\n", items[c]);
    }
}

int main(int argc, char **argv) {
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL)
        return 0;
    int limit = atoi(argv[1]);
    if (limit <= 0)
        return 0;
    int w, v, num;
    char i[32];
    fscanf(fp, "%d", &num);
    items = malloc(num * sizeof(char *));
    for (int j = 0; j < num; ++j)
        items[j] = malloc(32 * sizeof(char));
    weights = malloc(num * sizeof(int));
    values = malloc(num * sizeof(int));
    table = malloc(limit * sizeof(int *));
    table[0] = malloc(num * limit * sizeof(int));
    for (int j = 1; j < limit; ++j)
        table[j] = table[j - 1] + num;
    for (int j = 0; j < num; ++j) {
        if (fscanf(fp, "%31s %d %d", i, &w, &v) > 0) {
            strcpy(items[j], i);
            weights[j] = w;
            values[j] = v;
        }
    }
    filltable(limit, num);
    printitems(limit - 1, num - 1);
    printf("%d / %d\n", table[limit - 1][num - 1], total);
    for (int j = 0; j < num; ++j)
        free(items[j]);
    free(items);
    free(weights);
    free(values);
    free(table[0]);
    free(table);
    return EXIT_SUCCESS;
}