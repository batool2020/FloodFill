#include <stdlib.h>
#include <stdio.h>
#include "FloodFill.h"


// Stack Constructor
Stack * create_Stack() {

	Stack * n_stack = (Stack *) malloc(sizeof(Stack));

	n_stack->properties[SPI] = 0;
	n_stack->properties[SSI] = STACKSIZE;

	return n_stack;
}

// Stack Destructor
void delete_Stack (Stack ** sPointer) {

	if (sPointer == 0 || *sPointer == 0) {
		fprintf(stderr, "NULL POINTER\n");
		return;
	}

	free(*sPointer);

	*sPointer = 0;

}


// Checks if this_stack is empty
int is_empty_Stack (Stack * n_stack) {

	//printf("%d\n", n_stack->properties[SPI]);

	if (n_stack->properties[SPI] == 0)
		return 1;
	else return 0;
}

// Pops the top element of this_stack
void pop (Stack * n_stack, Node ** npp) {


	short index;

	index = n_stack->properties[SPI] - 1;

	*npp = n_stack->_stack[index];

	n_stack->properties[SPI] -= 1;

}

// Pushes an element to the top of this_stack
void push (Stack * this_stack, Node * this_node) {

	short index;

	index = this_stack->properties[SPI];

	this_stack->_stack[index] = this_node;

	this_stack->properties[SPI] += 1;
}
