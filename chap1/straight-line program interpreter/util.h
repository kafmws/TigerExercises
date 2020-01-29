#pragma once

#include"pch.h"
#include<assert.h>

typedef char* string;

#ifndef __cplusplus

typedef char bool;
#define TRUE 1
#define FALSE 0

#endif // !__cplusplus

void *checked_malloc(int);

string String(const char *);

typedef struct U_boolList_ * U_boolList;

struct U_boolList_ {
    bool head;
    U_boolList tail;
};

U_boolList U_BoolList(bool head, U_boolList tail);