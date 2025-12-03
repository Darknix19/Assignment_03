#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

char* readLine(FILE* in) {
    size_t cap = 128, len = 0;
    char* buf = malloc(cap);
    if (!buf) { fprintf(stderr, "Allocation failed\n"); exit(EXIT_FAILURE); }
    int c;
    while ((c = fgetc(in)) != EOF) {
        if (c == '\n') break;
        if (len + 1 >= cap) {
            cap *= 2;
            char* tmp = realloc(buf, cap);
            if (!tmp) { free(buf); fprintf(stderr, "Realloc failed\n"); exit(EXIT_FAILURE); }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    if (len == 0 && c == EOF) { free(buf); return NULL; }
    buf[len] = '\0';
    char* exact = realloc(buf, len + 1);
    return exact ? exact : buf;
}

void ensureCapacity(char*** lines, int* capacity, int minCapacity) {
    if (*capacity >= minCapacity) return;
    int newCap = (*capacity == 0) ? 4 : *capacity;
    while (newCap < minCapacity) newCap *= 2;
    char** tmp = realloc(*lines, newCap * sizeof(char*));
    if (!tmp) { fprintf(stderr, "Realloc failed\n"); exit(EXIT_FAILURE); }
    *lines = tmp; *capacity = newCap;
}

void insertLine(char*** lines, int* size, int* capacity, int index, const char* text) {
    if (index < 0 || index > *size) return;
    ensureCapacity(lines, capacity, *size + 1);
    if (index < *size) memmove(&(*lines)[index + 1], &(*lines)[index], (*size - index) * sizeof(char*));
    char* s = malloc(strlen(text) + 1);
    if (!s) { fprintf(stderr, "Allocation failed\n"); exit(EXIT_FAILURE); }
    strcpy(s, text);
    (*lines)[index] = s; (*size)++;
}

void deleteLine(char*** lines, int* size, int index) {
    if (index < 0 || index >= *size) return;
    free((*lines)[index]);
    if (index < *size - 1) memmove(&(*lines)[index], &(*lines)[index + 1], (*size - index - 1) * sizeof(char*));
    (*size)--;
}

void printAllLines(char** lines, int size) {
    for (int i = 0; i < size; i++) printf("%d: %s\n", i, lines[i]);
}

void shrinkToFit(char*** lines, int* capacity, int size) {
    if (*capacity == size) return;
    if (size == 0) { free(*lines); *lines = NULL; *capacity = 0; return; }
    char** tmp = realloc(*lines, size * sizeof(char*));
    if (!tmp) { fprintf(stderr, "Realloc failed\n"); exit(EXIT_FAILURE); }
    *lines = tmp; *capacity = size;
}

void freeAll(char*** lines, int* size, int* capacity) {
    if (*lines) { for (int i = 0; i < *size; i++) free((*lines)[i]); free(*lines); }
    *lines = NULL; *size = 0; *capacity = 0;
}

int saveToFile(const char* filename, char** lines, int size) {
    FILE* f = fopen(filename, "w"); if (!f) return 0;
    fprintf(f, "%d\n", size);
    for (int i = 0; i < size; i++) fprintf(f, "%s\n", lines[i]);
    fclose(f); return 1;
}

int loadFromFile(const char* filename, char*** lines, int* size, int* capacity) {
    FILE* f = fopen(filename, "r"); if (!f) return 0;
    freeAll(lines, size, capacity);
    int count; if (fscanf(f, "%d\n", &count) != 1 || count < 0) { fclose(f); return 0; }
    *lines = NULL; *size = 0; *capacity = 0; ensureCapacity(lines, capacity, count);
    for (int i = 0; i < count; i++) {
        char* line = readLine(f);
        if (!line) { fclose(f); freeAll(lines, size, capacity); return 0; }
        (*lines)[i] = line; (*size)++;
    }
    fclose(f); return 1;
}

int main() {
    char** lines = NULL; int size = 0, capacity = 0;
    insertLine(&lines, &size, &capacity, 0, "First line");
    insertLine(&lines, &size, &capacity, 1, "Second line");
    printAllLines(lines, size);
    deleteLine(&lines, &size, 0);
    printAllLines(lines, size);
    saveToFile("output.txt", lines, size);
    freeAll(&lines, &size, &capacity);
    loadFromFile("output.txt", &lines, &size, &capacity);
    printAllLines(lines, size);
    freeAll(&lines, &size, &capacity);
    return 0;
}