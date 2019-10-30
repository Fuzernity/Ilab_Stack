#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAXELEMENTS 2000

typedef int ElemT;

struct Stack {

    unsigned int maxElems;
    ElemT* elems;
    int elemCount;
    int errorNum;

};

void stackContruct(struct Stack* stk, unsigned int maxELements);

void stackPush(struct Stack* stk, ElemT newElem);

int stackPop(struct Stack* stk);

void stackPrint(struct Stack* stk);

void stackDestruct(struct Stack* stk);

void errorCheck(struct Stack* stk);

int main() {

    struct Stack stk;
    stackContruct(&stk, MAXELEMENTS);

    for (int i = 0; i < 5; i++) {
        int new;
        scanf("%d", &new);
        stackPush(&stk, new);

    }
    stackPrint(&stk);
    printf("\n");

    printf("%d\n", stackPop(&stk));
    printf("%d", stk.elemCount);

    stackDestruct(&stk);

    return 0;
}

void stackContruct(struct Stack* stk, unsigned int maxELements) {

    stk->maxElems = maxELements;
    stk->elemCount = 0;
    stk->elems = calloc(maxELements, sizeof(ElemT));
    stk->errorNum = 0;

}

void stackPush(struct Stack* stk, ElemT newElem) {

    stk->elems[stk->elemCount++] = newElem;

}

int stackPop(struct Stack* stk) {

    return stk->elems[stk->elemCount-- - 1];

}

void stackPrint(struct Stack* stk) {

    for (int i = 0; i < stk->elemCount; i++) {
        printf("%d ", stk->elems[i]);
    }

}

void stackDestruct(struct Stack* stk) {

    free(stk->elems);
    stk->maxElems = 0;
    stk->elemCount = 0;
    stk->errorNum = 0;

}
