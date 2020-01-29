#include"pch.h"
#include"util.h"
#include"slp.h"

typedef struct table * Table_;

struct table {
    string id;
    int value;
    Table_ tail;
};

Table_ table(string id, int value, Table_ tail);

struct IntAndTable {
    int i;
    Table_ t;
};