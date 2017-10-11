#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10

typedef struct stack {
	unsigned int size;
	unsigned int capacity;
	unsigned int *data;
} stack_t;

void stack_init (stack_t *s);
void push (stack_t *s, unsigned int e);
unsigned int pop (stack_t *s);
unsigned int top (stack_t *s);
void expand (stack_t *s);

#endif
