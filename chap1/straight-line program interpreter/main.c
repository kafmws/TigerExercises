#include"pch.h"
#include"slp.h"
#include"prog.h"
#include"interp.h"

int maxargs(A_stm stm);

int maxargsExp(A_exp exp) {
    int max = 0;
    if (exp->kind == A_opExp) {
        if (max < maxargsExp(exp->u.op.left)) max = maxargsExp(exp->u.op.left);
        if (max < maxargsExp(exp->u.op.right)) max = maxargsExp(exp->u.op.right);
    }
    else if (exp->kind == A_eseqExp) {
        if (max < maxargs(exp->u.eseq.stm)) max = maxargs(exp->u.eseq.stm);
        if (max < maxargsExp(exp->u.eseq.exp)) max = maxargsExp(exp->u.eseq.exp);
    }
    return max;
}

int maxargs(A_stm stm) {
    int max = 0;
    if (stm->kind == A_printStm) {
        int cnt = 1;
        A_expList p = stm->u.print.exps;
        while (p->kind != A_lastExpList) {
            cnt++;
            if (max < maxargsExp(p->u.pair.head)) max = maxargsExp(p->u.pair.head);
            p = p->u.pair.tail;
        }
        if (max < maxargsExp(p->u.last)) max = maxargsExp(p->u.last);
        if (max < cnt) max = cnt;
    }
    else if (stm->kind == A_assginStm) {
        if (max < maxargsExp(stm->u.assgin.exp)) max = maxargsExp(stm->u.assgin.exp);
    }
    else if (stm->kind == A_compoundStm) {
        if (max < maxargs(stm->u.compound.stm1)) max = maxargs(stm->u.compound.stm1);
        if (max < maxargs(stm->u.compound.stm2)) max = maxargs(stm->u.compound.stm2);
    }
    return max;
}

Table_ update(Table_ t, string id, int value) {
    return table(id, value, t);
}

int lookup(Table_ t, string key) {
    return strcmp(key, t->id) == 0 ? t->value : lookup(t->tail, key);
}

Table_ interpStm(A_stm stm, Table_ t);

struct IntAndTable interpExp(A_exp exp, Table_ t) {
    switch (exp->kind) {
    case A_idExp: return (struct IntAndTable) { lookup(t, exp->u.id), t }; break;
    case A_numExp: return (struct IntAndTable) { exp->u.num, t }; break;
    case A_opExp:
    {
        struct IntAndTable tl = interpExp(exp->u.op.left, t);
        struct IntAndTable tr = interpExp(exp->u.op.right, tl.t);
        switch (exp->u.op.op) {
        case A_plus:
            return (struct IntAndTable) { tl.i + tr.i, tr.t }; break;
        case A_minus:
            return (struct IntAndTable) { tl.i - tr.i, tr.t }; break;
        case A_times:
            return (struct IntAndTable) { tl.i * tr.i, tr.t }; break;
        case A_div:
            return (struct IntAndTable) { tl.i / tr.i, tr.t }; break;
        default: return (struct IntAndTable) { 0, t };
        }
        break;
    }
    case A_eseqExp:
        return interpExp(exp->u.eseq.exp, interpStm(exp->u.eseq.stm, t));
        break;
    default: return (struct IntAndTable) { 0, t };
    }
}

Table_ interpStm(A_stm stm, Table_ t) {
    switch (stm->kind) {
    case A_compoundStm:
        return interpStm(stm->u.compound.stm2, interpStm(stm->u.compound.stm1, t));
        break;
    case A_assginStm:
    {
        struct IntAndTable it = interpExp(stm->u.assgin.exp, t);
        return update(it.t, stm->u.assgin.id, it.i);
    }break;
    case A_printStm:
    {
        struct IntAndTable it = interpExp(stm->u.print.exps->u.last, t);
        printf("%d", it.i);
        return stm->u.print.exps->kind != A_lastExpList ?
            interpStm((printf(" "), A_PrintStm(stm->u.print.exps->u.pair.tail)), it.t) : (printf("\n"), it.t);
    }
    break;
    default: return t;
    }
}

A_stm prog4();

int main() {
    printf("%d", maxargs(prog()));
    printf("%d", maxargs(prog4()));
    //int b = 3;
    //printf("%d %d", b-3, b = printf("%d", 1 + 2, b, b - 3, 5));
    printf("\n");
    Table_ t = interpStm(prog(), NULL);
    return 0;
}

A_stm prog4() {
    return  A_CompoundStm(
        A_AssignStm(String("a"), A_OpExp(A_NumExp(5), A_plus, A_NumExp(3))),
        A_CompoundStm(
            A_AssignStm(String("b"), A_EseqExp(
                A_PrintStm(
                    A_PairExpList(A_IdExp(String("a")),
                        A_LastExpList(
                            A_EseqExp(
                                A_PrintStm(
                                    A_PairExpList(A_EseqExp(prog(), A_NumExp(4)),
                                        A_PairExpList(A_NumExp(5),
                                            A_PairExpList(A_IdExp(String("a")), A_LastExpList(A_IdExp("a")))))), 
                                A_OpExp(A_IdExp(String("a")), A_minus, A_NumExp(1)))))),
                A_OpExp(A_NumExp(10), A_times, A_IdExp(String("a"))))),
            A_PrintStm(A_LastExpList(A_IdExp(String("b"))))
        )
    );
}