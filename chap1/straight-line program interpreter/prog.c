#include"pch.h"
#include"slp.h"
#include"prog.h"

A_stm prog() {
    return  A_CompoundStm(
        A_AssignStm(String("a"), A_OpExp(A_NumExp(5), A_plus, A_NumExp(3))),
        A_CompoundStm(
            A_AssignStm(String("b"), A_EseqExp(
                A_PrintStm(
                    A_PairExpList(A_IdExp(String("a")),
                        A_LastExpList(A_OpExp(A_IdExp(String("a")), A_minus, A_NumExp(1))))),
                A_OpExp(A_NumExp(10), A_times, A_IdExp(String("a"))))),
            A_PrintStm(A_LastExpList(A_IdExp(String("b"))))
        )
    );
}