#include"pch.h"
#include"util.h"
#include"slp.h"
#include"interp.h"

Table_ table(string id, int value, Table_ tail) {
    Table_ t = checked_malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}
