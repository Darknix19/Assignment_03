#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastAccess;
};

int findBook(struct Book shelf[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (shelf[i].id == id) return i;
    }
    return -1;
}

int findLeastRecent(struct Book shelf[], int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (shelf[i].lastAccess < shelf[minIndex].lastAccess) {
            minIndex = i;
        }
    }
    return minIndex;
}

int main() {
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];
    int size = 0;
    int time = 0;

    for (int i = 0; i < Q; i++) {
        char op[10];
        scanf("%s", op);

        if (strcmp(op, "ADD") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            int idx = findBook(shelf, size, x);
            if (idx != -1) {
                shelf[idx].popularity = y;
                shelf[idx].lastAccess = ++time;
            } else {
                if (size < capacity) {
                    shelf[size].id = x;
                    shelf[size].popularity = y;
                    shelf[size].lastAccess = ++time;
                    size++;
                } else {
                    int removeIdx = findLeastRecent(shelf, size);
                    shelf[removeIdx].id = x;
                    shelf[removeIdx].popularity = y;
                    shelf[removeIdx].lastAccess = ++time;
                }
            }
        } else if (strcmp(op, "ACCESS") == 0) {
            int x;
            scanf("%d", &x);
            int idx = findBook(shelf, size, x);
            if (idx != -1) {
                shelf[idx].lastAccess = ++time;
                printf("%d\n", shelf[idx].popularity);
            } else {
                printf("-1\n");
            }
        }
    }
    return 0;
}