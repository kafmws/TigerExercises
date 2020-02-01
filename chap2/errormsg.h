#pragma once

#include"pch.h"
#include"util.h"

extern int EM_tokPos;

extern bool EM_anyErrors;

void EM_newline();

void EM_error(int, string, ...);

void EM_impossible(string, ...);

void EM_reset(string filename);