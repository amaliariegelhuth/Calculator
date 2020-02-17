#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void pushValStack (int stack[], int *top, int value);
int popValStack (int stack[], int *top);
void pushOpStack (char *stack[], int *top, char *value);
char *popOpStack (char *stack[], int *top);

int main (int argc, char **argv) {
	int i;	
	int size = 50;
	int *valStack = (int*)malloc(size * sizeof(int));
	char **opStack = (char**)malloc(size * sizeof(char*));
	int vTop = -1;
	int oTop = -1;
	int *valTop = &vTop;
	int *opTop = &oTop;
	int n;
	for (i = 1; i < argc; i++) {
		if (*argv[i] == '%' || *argv[i] == 'x' || *argv[i] == '+' || *argv[i] == '^' || *argv[i] == '[') {
			pushOpStack(opStack, opTop, argv[i]);		
		} else if (*argv[i] == ']') {
			char *op = popOpStack(opStack, opTop);
			while(*op != '[') {
				int val1 = popValStack(valStack, valTop);
				int val2 = popValStack(valStack, valTop);
				if (*op == '+') {
					pushValStack(valStack, valTop, (val1 + val2));
				} else if (*op == '%') {
					pushValStack(valStack, valTop, (val2 % val1));
				} else if (*op == 'x') {
					pushValStack(valStack, valTop, (val1 * val2));
				} else {
					pushValStack(valStack, valTop, (pow(val2, val1)));
				}
				op = popOpStack(opStack, opTop);
			}
		} else {
			sscanf(argv[i], "%d", &n);
			pushValStack(valStack, valTop, n);
		}
	}
	while (*opTop > -1) {
		char *op = popOpStack(opStack, opTop);
		int val1 = popValStack(valStack, valTop);
		int val2 = popValStack(valStack, valTop);
		if (*op == '+') {
			pushValStack(valStack, valTop, (val1 + val2));
		} else if (*op == '%') {
			pushValStack(valStack, valTop, (val2 % val1));
		} else if (*op == 'x') {
			pushValStack(valStack, valTop, (val2 * val1));
		} else {
			pushValStack(valStack, valTop, (pow(val2, val1)));
		}
	}
printf("\n	Welcome to C calculator\n\n");
printf("The result is: %d\n", valStack[0]);
return 0;
}

void pushValStack (int stack[], int *top, int value) {
	(*top)++;
	stack[*top] = value;
}
int popValStack (int stack[], int *top) {
	(*top)--;
	return stack[*top + 1];
	
}
void pushOpStack (char *stack[], int *top, char *value) {
	(*top)++;
	stack[*top] = value;
}
char *popOpStack (char *stack[], int *top) {
	(*top)--;
	return stack[*top + 1];
}
