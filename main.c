#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAX_ELEMENTS 100

const int ERROR_CODE_STACK_FULL = 1;
const int ERROR_CODE_STACK_EMPTYPTR = 2;
const int ERROR_CODE_STACK_HASH_DIFFER = 3;

typedef int ElemT;

struct Stack {
    unsigned int hash;
    int maxsize;
    ElemT* data;
    int size;
    int errorNum;

};

void stackContruct(struct Stack* stk, int maxsize);

void stackPush(struct Stack* stk, ElemT newElem);

ElemT stackPop(struct Stack* stk);

void stackDump(struct Stack* stk);

void stackDestruct(struct Stack* stk);

int errorCheck(struct Stack* stk);

unsigned int hashGenerate(struct Stack* stk);

int hashCheck(struct Stack* stk);

int main() {

    struct Stack stk;
    stackContruct(&stk, MAX_ELEMENTS);

    stk.hash = hashGenerate(&stk);

    int n = 0;
    printf("Enter stack elem number: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int new;
        scanf("%d", &new);
        stackPush(&stk, new);

    }
    stackDump(&stk);
    printf("\n");

    printf("%d\n", stackPop(&stk));
    printf("%d", stk.size);

    stackDestruct(&stk);

    return 0;
}

void stackContruct(struct Stack* stk, int maxsize) {

    stk->data = calloc(maxsize, sizeof(ElemT));
    stk->maxsize = maxsize;
    stk->size = 0;
    stk->errorNum = 0;
    stk->hash = 0;
}

void stackPush(struct Stack* stk, ElemT newElem) {

    stk->hash = hashGenerate(stk);

    if (errorCheck(stk) == 1) {
        printf("\n\tERROR DETECTED! ERROR CODE -> %d\n", stk->errorNum);
        assert(stk->errorNum == ERROR_CODE_STACK_FULL);
        assert(stk->errorNum == ERROR_CODE_STACK_EMPTYPTR);
        assert(stk->errorNum == ERROR_CODE_STACK_HASH_DIFFER);
    }

    if (stk->size + 1 == stk->maxsize) {
        stk->maxsize += MAX_ELEMENTS;
        stk->data = realloc(stk, stk->maxsize);
    }

    stk->size++;

    stk->data[stk->size - 1] = newElem;

    stk->hash = hashGenerate(stk);

    if (errorCheck(stk) == 1) {
        printf("\n\tERROR DETECTED! ERROR CODE -> %d\n", stk->errorNum);
        assert(stk->errorNum == ERROR_CODE_STACK_FULL);
        assert(stk->errorNum == ERROR_CODE_STACK_EMPTYPTR);
        assert(stk->errorNum == ERROR_CODE_STACK_HASH_DIFFER);
    }
}

ElemT stackPop(struct Stack* stk) {

    stk->hash = hashGenerate(stk);

    if (errorCheck(stk) == 1) {
        printf("\n\tERROR DETECTED! ERROR CODE -> %d\n", stk->errorNum);
        assert(stk->errorNum == ERROR_CODE_STACK_FULL);
        assert(stk->errorNum == ERROR_CODE_STACK_EMPTYPTR);
        assert(stk->errorNum == ERROR_CODE_STACK_HASH_DIFFER);
    }

    ElemT popvalue = stk->data[stk->size - 1];
    stk->size--;

    stk->hash = hashGenerate(stk);

    if (errorCheck(stk) == 1) {
        printf("\n\tERROR DETECTED! ERROR CODE -> %d\n", stk->errorNum);
        assert(stk->errorNum == ERROR_CODE_STACK_FULL);
        assert(stk->errorNum == ERROR_CODE_STACK_EMPTYPTR);
        assert(stk->errorNum == ERROR_CODE_STACK_HASH_DIFFER);
    }

    return popvalue;

}

void stackDump(struct Stack* stk) {

    if (errorCheck(stk) == 1) {
        printf("\n\tERROR DETECTED! ERROR CODE -> %d\n", stk->errorNum);
        assert(stk->errorNum == ERROR_CODE_STACK_FULL);
        assert(stk->errorNum == ERROR_CODE_STACK_EMPTYPTR);
        assert(stk->errorNum == ERROR_CODE_STACK_HASH_DIFFER);
    }

    for (int i = 0; i < stk->size; i++) {
        printf("%d ", stk->data[i]);
    }

    if (errorCheck(stk) == 1) {
        printf("\n\tERROR DETECTED! ERROR CODE -> %d\n", stk->errorNum);
        assert(stk->errorNum == ERROR_CODE_STACK_FULL);
        assert(stk->errorNum == ERROR_CODE_STACK_EMPTYPTR);
        assert(stk->errorNum == ERROR_CODE_STACK_HASH_DIFFER);
    }

}

void stackDestruct(struct Stack* stk) {

    free(stk->data);
    stk->maxsize = 0;
    stk->size = 0;
    stk->errorNum = 0;

}

int errorCheck(struct Stack* stk) {
    if (stk->size >= stk->maxsize) {
        stk->errorNum = ERROR_CODE_STACK_FULL;
        return 1;
    }

    if (stk == NULL) {
        stk->errorNum = ERROR_CODE_STACK_EMPTYPTR;
        return 1;
    }

    if (stk->hash != hashGenerate(stk)) {
        stk->errorNum = ERROR_CODE_STACK_HASH_DIFFER;
        return 1;
    }

    return 0;
}

unsigned int hashGenerate(struct Stack* stk) {

    unsigned int newhash = stk->maxsize * stk->maxsize + stk->size * stk->size;
    for (int i = 0; i < stk->size; i++) {
        newhash += stk->data[i] * stk->data[i];
    }

    return newhash;

}