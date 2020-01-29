#include"pch.h"
#include"util.h"
#include"slp.h"

A_stm A_CompoundStm(A_stm stm1, A_stm stm2) {
    A_stm stm = checked_malloc(sizeof(*stm));
    stm->kind = A_compoundStm;
    stm->u.compound.stm1 = stm1;
    stm->u.compound.stm2 = stm2;
    return stm;
}

A_stm A_AssignStm(string id, A_exp exp_) {
    A_stm stm = checked_malloc(sizeof(*stm));
    stm->kind = A_assginStm;
    stm->u.assgin.id = id;
    stm->u.assgin.exp = exp_;
    return stm;
}

A_stm A_PrintStm(A_expList exps) {
    A_stm stm = checked_malloc(sizeof(*stm));
    stm->kind = A_printStm;
    stm->u.print.exps = exps;
    return stm;
}

A_exp A_IdExp(string id) {
    A_exp exp = checked_malloc(sizeof(*exp));
    exp->kind = A_idExp;
    exp->u.id = id;
    return exp;
}

A_exp A_NumExp(int num) {
    A_exp exp = checked_malloc(sizeof(*exp));
    exp->kind = A_numExp;
    exp->u.num = num;
    return exp;
}

A_exp A_OpExp(A_exp left, A_binop op, A_exp right) {
    A_exp exp = checked_malloc(sizeof(*exp));
    exp->kind = A_opExp;
    exp->u.op.left = left;
    exp->u.op.op = op;
    exp->u.op.right = right;
    return exp;
}

A_exp A_EseqExp(A_stm stm, A_exp exp_) {
    A_exp exp = checked_malloc(sizeof(*exp));
    exp->kind = A_eseqExp;
    exp->u.eseq.stm = stm;
    exp->u.eseq.exp = exp_;
    return exp;
}

A_expList A_PairExpList(A_exp head, A_expList tail) {
    A_expList expList = checked_malloc(sizeof(*expList));
    expList->kind = A_pairExpList;
    expList->u.pair.head = head;
    expList->u.pair.tail = tail;
    return expList;
}

A_expList A_LastExpList(A_exp last) {
    A_expList expList = checked_malloc(sizeof(*expList));
    expList->kind = A_lastExpList;
    expList->u.last = last;
    return expList;
}
