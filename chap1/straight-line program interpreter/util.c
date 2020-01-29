#include"pch.h"
#include"util.h"

void *checked_malloc(int num) {
    void *p = malloc(num);
    if (!p) {
        fprintf(stderr, "\nRan out of memory!\n");
        exit(1);
    }
    return p;
}

string String(const char *s) {
    char *ss = checked_malloc(strlen(s) + 1);
    strcpy(ss, s);
    return ss;
}

U_boolList U_BoolList(bool head, U_boolList tail) {
    U_boolList bl = checked_malloc(sizeof(*bl));
    bl->head = head;
    bl->tail = tail;
    return bl;
}
