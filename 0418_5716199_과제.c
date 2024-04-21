#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <string.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct Stacktype {
	// element data[];
	element* data;
	int capacity;
	int top;
} StackType;


// create : 이미 만들었음, StackType의 변수를 선언하면 만들어짐
// delete : 할수 없음

// init 
void init(StackType* sptr, int ofs) {
	sptr->data = (element*)malloc(sizeof(StackType) * ofs);
	sptr->top = -1;
	sptr->capacity = ofs;
}

// is_full
int is_full(StackType* sptr) {
	// printf("[is_full] top = %d, capacity = %d\n", sptr->top, sptr->capacity);
	if (sptr->top == sptr->capacity - 1) {
		sptr->capacity = sptr->capacity * 2;
		sptr->data = (element*)realloc(sptr->data, sptr->capacity * sizeof(element));

	}
	return 0;
}

int is_empty(StackType* sptr) {
	return (sptr->top == -1);
}

// push
void push(StackType* sptr, element item) {

	if (is_full(sptr)) {
		fprintf(stderr, "Stack is full\n");
		return;
	}
	else {
		sptr->top = sptr->top + 1;
		sptr->data[sptr->top] = item;
	}
}

element pop(StackType* sptr) {
	element r;
	if (is_empty(sptr)) {
		fprintf(stderr, "stack is empty\n");
		return -1;
	}
	else {
		// r = sptr->stack[sptr->top];
		// sptr->top = sptr->top - 1;
		// return r;
		return (sptr->data[(sptr->top)--]);
	}
}

element peek(StackType* sptr) {

	element r;
	if (is_empty(sptr)) {
		fprintf(stderr, "stack is empty\n");
		return -1;
	}
	else {
		// r = stack[top];
		// top = top - 1;
		// return r;
		return (sptr->data[sptr->top]);
	}
}

void stack_print(StackType* sptr) {
	for (int i = sptr->top; i >= 0; i--) {
		printf("[%d]", sptr->data[i]);
	}
}

int eval(char* expr) {
	int len;
	StackType s;

	init(&s, 20);
	len = strlen(expr);
	for (int i = 0; expr[i] != '\0'; i++) {
		int ch = expr[i];
		int value;
		int op1, op2;


		printf("\nexpression : %c\n", expr[i]);
		if ((ch == '+') || (ch == '-')
			|| (ch == '*') || (ch == '/')) {
			op1 = pop(&s);
			op2 = pop(&s);
			/* if (ch == '+') {
				value = op1 + op2;
				push(&s, value);
			} else if (ch == '-') {
				value = op1 - op2;
				push(&s, value);
			} else if (ch == '*') {
				value = op1 * op2;
				push(&s, value);
			} else {
				value = op1 / op2;
				push(&s, value);
			}
			*/
			switch (ch) {
			case '+': push(&s, op2 + op1); break;
			case '-':push(&s, op2 - op1); break;
			case '*':push(&s, op2 * op1); break;
			case '/':push(&s, op2 / op1); break;
			default:;
			}
		}
		else if ((ch >= '0') && (ch <= '9')) {
			value = ch - '0';
			push(&s, value);
		}

	}
	return (pop(&s));
}

int prec(char op) {
	switch (op) {
	case'(':
	case')':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	return -1;
}

void infix_to_postfix(char expr[]) {
	int len = strlen(expr);
	char top_op;
	StackType s;

	init(&s, MAX_STACK_SIZE);

	for (int i = 0; i < len; i++) {
		switch (expr[i]) {
		case '+':
		case '-':
		case '/':
		case '*':
			while (!is_empty(&s) && peek(&s) != '(' && prec(expr[i]) <= prec((char)peek(&s))) {
				printf("%c", pop(&s));
			}
			push(&s, (int)expr[i]);
			break;
		case '(':
			push(&s, (int)expr[i]);
			break;
		case ')':
			while (!is_empty(&s) && peek(&s) != '(') {
				printf("%c", pop(&s));
			}
			if (!is_empty(&s) && peek(&s) == '(') 
				pop(&s); 
			break;
		default:
			printf("%c", expr[i]);
			break;
		}
	}

	while (!is_empty(&s)) {
		printf("%c", (char)pop(&s));
	}
}


int main() {
	char infixExpression[MAX_STACK_SIZE];
	char postfixExpression[MAX_STACK_SIZE];

	while (1) {
		printf("다음과 같은 메뉴로 동작하는 프로그램 입니다.\n");
		printf("1, 중위식을 입력받음\n");
		printf("2, 중위식을 후위식으로 변환\n");
		printf("3, 후위식을 계산\n");
		printf("4, 종료\n");
		printf("메뉴를 선택하세요: ");

		int choice;
		scanf_s("%d", &choice);
		int result;

		switch (choice) {
		case 1:
			printf("중위식을 입력하세요: ");
			getchar();
			fgets(infixExpression, sizeof(infixExpression), stdin);
			printf("입력된 중위식: %s\n", infixExpression);
			break;
		case 2:
			printf("중위식을 입력하세요: ");
			getchar(); 
			fgets(infixExpression, sizeof(infixExpression), stdin);
			printf("중위식을 후위식으로 변환한 값: ");
			infix_to_postfix(infixExpression);
			 
			break;
		case 3:
			printf("후위식을 계산 : ");
			getchar(); 
			fgets(postfixExpression, sizeof(postfixExpression), stdin);
			result = eval(postfixExpression);
			printf("Result : %d\n", result);
			break;

		case 4:

			printf("프로그램을 종료합니다.\n");
			exit(0);
		default:
			printf("잘못된 메뉴 선택입니다. 다시 선택하세요: \n");
			break;
		}
	}
	return 0;
}