#include "stack.h"
#include <string.h>

int main (int argc, char *argv [])
{
	stack_t stack;

	stack_init (&stack); 
	
	FILE *file;

	if ( (file = fopen (argv [1], "r")) == NULL ) {
		printf ("Enable to open the file");
		exit (EXIT_FAILURE);
	}

        char str [10];
       
	while ( fscanf (file, "%s", str) != EOF) {

		if ( !strcmp (str, "PUSH") ) {
			unsigned int op;
			fscanf (file, "%u", &op);
			push (&stack, op);
		}
		else if ( !strcmp (str, "SOMA") ) {
                        unsigned int op1 = pop (&stack);
			unsigned int op2 = pop (&stack);

			push (&stack, op1 + op2);
		}
		else if ( !strcmp (str, "MULT") ) {
                        unsigned int op1 = pop (&stack);
                        unsigned int op2 = pop (&stack);

                        push (&stack, op1 * op2);
                }
                else if ( !strcmp (str, "DIV") ) {
                        unsigned int op1 = pop (&stack);
                        unsigned int op2 = pop (&stack);

                        push (&stack, op1 / op2);
                }
                else if ( !strcmp (str, "SUB") ) {
                        unsigned int op1 = pop (&stack);
                        unsigned int op2 = pop (&stack);

                        push (&stack, op1 - op2);
                }
                else if ( !strcmp (str, "PRINT") ) 
                        printf ("%u\n", top (&stack));
	}

	fclose (file);
	free (stack.data);

	return 0;
}

