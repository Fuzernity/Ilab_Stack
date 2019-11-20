
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAX_ELEMENTS 10

const unsigned long CANARY_VALUE = 5647382910;
const int NO_ERROR = 0;
const int ERROR_CODE_STACK_FULL = 1;
const int ERROR_CODE_STACK_EMPTYPTR = 2;
const int ERROR_CODE_STACK_HASH_DIFFER = 3;
const int ERROR_CODE_CANARY_1_DIFFER = 4;
const int ERROR_CODE_CANARY_2_DIFFER = 5;
const int ERROR_CODE_ZERO_MAXSIZE = 6;
const int ERROR_CODE_WRONG_ERROR_CODE = 7;

typedef int ElemT;

struct Stack {
    unsigned long canary1;
    unsigned long hash;
    int maxsize;
    ElemT* data;
    int size;
    int errorNum;
    unsigned long canary2;

};

void stackContruct(struct Stack* stk, int maxsize);

void stackPush(struct Stack* stk, ElemT newElem);

ElemT stackPop(struct Stack* stk);

void stackDump(struct Stack* stk, FILE* log);

void stackDestruct(struct Stack* stk);

void errorCheck(struct Stack* stk);

unsigned long hashGenerate(struct Stack* stk);

int main() {

    FILE* log = fopen("logstack.txt", "w");

    struct Stack stk;
    stackContruct(&stk, MAX_ELEMENTS);

    stk.hash = hashGenerate(&stk);



    for (int i = 1; i <= 23; i++) {
        stackPush(&stk, i * i * i * i);
    }

    stackDump(&stk, log);

    stackDestruct(&stk);

    return 0;
}

void stackContruct(struct Stack* stk, int maxsize) {

    stk->canary1 = CANARY_VALUE;
    stk->data = calloc(maxsize, sizeof(ElemT));
    stk->maxsize = maxsize;
    stk->size = 0;
    stk->errorNum = NO_ERROR;
    stk->hash = 0;
    stk->canary2 = CANARY_VALUE;
}

void stackPush(struct Stack* stk, ElemT newElem) {

    stk->hash = hashGenerate(stk);

    errorCheck(stk);

    stk->size++;
    stk->data[stk->size - 1] = newElem;

    if (stk->size == stk->maxsize) {
        stk->maxsize += MAX_ELEMENTS;
        stk->data = realloc(stk->data, stk->maxsize * sizeof(ElemT));
    }

    stk->hash = hashGenerate(stk);
    errorCheck(stk);
}

ElemT stackPop(struct Stack* stk) {

    assert(stk->size != 0);

    stk->hash = hashGenerate(stk);

    errorCheck(stk);

    ElemT popvalue = stk->data[stk->size - 1];
    stk->size--;

    stk->hash = hashGenerate(stk);

    errorCheck(stk);

    return popvalue;

}

void stackDump(struct Stack* stk, FILE* log) {

    errorCheck(stk);

    fprintf(log, "\tThere you can see Stack arguments and elements of its data\n");
    fprintf(log, "\t The size of Stack - %d\n", stk->size);
    fprintf(log, "\t The current elements in dynamic memory - %d\n", stk->maxsize);
    fprintf(log, "\t The current error code - %d\n\n", stk->errorNum);
    fprintf(log, "\t Hash value - %ld\n\n", stk->hash);
    fprintf(log, "\t First canary value - %ld\n", stk->canary1);
    fprintf(log, "\t Second canary value - %ld\n\n", stk->canary2);
    for (int i = 0; i < stk->size; i++) {
        fprintf(log, "{%d} = %d\n", i + 1, stk->data[i]);
    }

    errorCheck(stk);
}

void stackDestruct(struct Stack* stk) {

    free(stk->data);
    stk->maxsize = 0;
    stk->size = 0;
    stk->errorNum = 0;
    stk->hash = 0;

}

void errorCheck(struct Stack* stk) {
    if (stk->size >= stk->maxsize) {
        stk->errorNum = ERROR_CODE_STACK_FULL;
        assert(stk->errorNum != ERROR_CODE_STACK_FULL);
    }
    if (stk == NULL) {
        stk->errorNum = ERROR_CODE_STACK_EMPTYPTR;
        assert(stk->errorNum != ERROR_CODE_STACK_EMPTYPTR);
    }
    if (stk->hash != hashGenerate(stk)) {
        stk->errorNum = ERROR_CODE_STACK_HASH_DIFFER;
        assert(stk->errorNum != ERROR_CODE_STACK_HASH_DIFFER);
    }
    if (stk->canary1 != CANARY_VALUE) {
        stk->errorNum = ERROR_CODE_CANARY_1_DIFFER;
        assert(stk->errorNum != ERROR_CODE_CANARY_1_DIFFER);
    }

    if (stk->canary2 != CANARY_VALUE) {
        stk->errorNum = ERROR_CODE_CANARY_2_DIFFER;
        assert(stk->errorNum != ERROR_CODE_CANARY_2_DIFFER);
    }
    if (stk->maxsize == 0) {
        stk->errorNum = ERROR_CODE_ZERO_MAXSIZE;
        assert(stk->errorNum != ERROR_CODE_ZERO_MAXSIZE);
    }
    if (stk->errorNum > 7) {
        stk->errorNum = ERROR_CODE_WRONG_ERROR_CODE;
        assert(stk->errorNum != ERROR_CODE_WRONG_ERROR_CODE);
    }

}

unsigned long hashGenerate(struct Stack* stk) {

    unsigned long newhash = 3 * stk->maxsize + 3 * stk->size;
    for (int i = 0; i < stk->size; i++) {
        newhash += 3 * stk->data[i];
    }

    return newhash;

}