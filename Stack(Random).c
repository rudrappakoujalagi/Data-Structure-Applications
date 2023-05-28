#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 20
typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return (s->top == -1);
}

int isFull(Stack* s) {
    return (s->top == MAX_STACK_SIZE - 1);
}

void push(Stack* s, int num) {
    if (isFull(s)) {
        printf("Stack is full, cannot push element!\n");
        return;
    }
    s->data[++(s->top)] = num;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty, cannot pop element!\n");
        return -1;
    }
    return s->data[(s->top)--];
}

int main() {
    FILE *input, *output;
    int num, i;
    Stack s;
    initStack(&s);

    srand(time(NULL));
    input = fopen("input.txt", "w");
    for (i = 0; i < MAX_STACK_SIZE; i++) {
        num = rand()  % 100;
        fprintf(input, "%d\n", num);
    }
    fclose(input);

    input = fopen("input.txt", "r");
    output = fopen("outpt.txt", "w");
    while (fscanf(input, "%d", &num) != EOF) {
        push(&s, num);
    }

    while (!isEmpty(&s)) {
        fprintf(output, "%d\n", pop(&s));
    }

    fclose(input);
    fclose(output);

    return 0;
}
