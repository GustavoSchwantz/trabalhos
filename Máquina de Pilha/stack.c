#include "stack.h"

void stack_init (stack_t *s) 
{
	s->data = (unsigned int*) malloc ( INITIAL_CAPACITY * sizeof (unsigned int) );

	if (s->data == NULL) {
		printf ("Enable to allocate memory\n");
                exit (EXIT_FAILURE);
	}

	s->size = 0;
	s->capacity = INITIAL_CAPACITY;
}

void push (stack_t *s, unsigned int e)
{
	if (s->size == s->capacity) 
		expand (s);

	s->data [ s->size++ ] = e;
}

unsigned int pop (stack_t *s)
{
	return (s->size == 0) ? s->data [ s->size ] : s->data [ --s->size ];
}

unsigned int top (stack_t *s)
{
	return (s->size == 0) ? s->data [ 0 ] : s->data [ s->size - 1 ];
}

void expand (stack_t *s)
{
	unsigned int *od = s->data;
        
        s->data = (unsigned int*) malloc ( 2 * s->capacity * sizeof (unsigned int) );

        if (s->data == NULL) {
                printf ("Enable to allocate memory\n");
                exit (EXIT_FAILURE);
        }

	int i;

	for (i = 0; i < s->capacity; ++i)
		s->data [i] = od [i];

        s->capacity = 2 * s->capacity;

	free (od);
}

