#pragma once

#include"pch.h"
#include"util.h"
#include"errormsg.h"

/**
*    errormsg.c - functions used in all phrases of the compiler
*                        to give error messages about the Tiger program.
**/

bool anyErrors = FALSE;

static string filename = "";

static int lineNum = 1;

int EM_tokPos = 0;

extern FILE * yyin;

typedef struct IntList_  * IntList;

struct IntList_ {
    int i;
    IntList rest;
};

static IntList linePos = NULL;

static IntList intList(int i, IntList rest) {
    IntList il = checked_malloc(sizeof(*il));
    il->i = i;
    il->rest = rest;
    return il;
}

void EM_newline() {
    lineNum++;
    linePos = intList(EM_tokPos, linePos);
}

void EM_error(int pos, string msg, ...) {
    va_list ap;
    IntList lines = linePos;
    int num = lineNum;

    anyErrors = TRUE;
    while (lines && lines->i >= pos) {
        lines = lines->rest;
        num--;
    }

    if (filename) fprintf(stderr, "%s:", filename);
    if (lines) fprintf(stderr, "%d.%d", num, pos - lines->i);
    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

void EM_reset(string fname) {
    anyErrors = FALSE;
    filename = fname;
    lineNum = 1;
    linePos = intList(0, NULL);
    yyin = fopen(filename, "r");
    if (!yyin) {
        EM_error(0, "file %s can not open.", filename);
        exit(1);
    }
}