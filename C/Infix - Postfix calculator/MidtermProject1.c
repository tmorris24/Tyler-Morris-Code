/*COP3502C Midterm Assignment One
Program written by Tyler Morris
PID: 4826071*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define SIZE 50
#define EMPTY -1

//Structure for Characters.

struct stack {

    char items[SIZE];
    int top;

};

//Structure for Integers.

struct intstack {

    int items[SIZE];
    int top;
};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
char top(struct stack* stackPtr);
char* menu();
int isBalancedParenthesis(char* infix);
int isOperand(char c);
int isOperator(char c);
int getOperatorPriority(char c);
int convertToInt(char c);
int calculate(int a, int b, char op);
char* convertToPostfix(char* postFix);
int evaluate(char* postFix);
void int_initialize(struct intstack* stackPtr);
int int_full(struct intstack* stackPtr);
int int_push(struct intstack* stackPtr, int value);
int int_empty(struct intstack* stackPtr);
int int_pop(struct intstack* stackPtr);
int int_top(struct intstack* stackPtr);



int main(void){

    //Create dynamically allocated strings

    char* postFix= (char*)malloc(102*sizeof(char));
    char* str = (char*)malloc(51*sizeof(char));

    // Begin Main Program

    while(strcmp(str = menu(), "exit")!=0){
        if (isBalancedParenthesis(str)){
            printf("\nParenthesis are Balanced\n");
            postFix = convertToPostfix(str);
            if(evaluate(postFix))
                break;
        }
        else{
            printf("\nParenthesis imbalanced\n");
            break;
        }
    }

    //Free strings.

    free(str);
    free(postFix);
    return 0;
}

char* menu(){
    char input[51];
    int valid = 0;
    char infix[51];
    char* inPtr;
    inPtr = (char*)malloc(51 * sizeof(char));

    printf("Welcome to Tyler's infix to postfix converter!\nPlease choose an option.\nEnter e to begin.\nEnter x to exit.\n");

//If e the program takes a input including spaces. If x the program places "exit" into the string. All other inputs will cause the program to loop.

    while(valid == 0){
        gets(input);
        if (strcmp(input, "e") == 0){
            printf("\nPlease enter an infix expression!\n");
            printf("Infix Expression:");
            gets(inPtr);
            while(strlen(inPtr) > 50){
                printf("\n String too large! Please user 50 characters or less!");
                gets(inPtr);
            }
            valid++;
        }
        else if(strcmp(input, "x") == 0){
            printf("\nThank you for using my converter!\n");
            strcpy(inPtr, "exit");
            valid++;
        }
        else{
            printf("\nInvalid input. Please enter a valid input.\n");
        }
    }

    //Using gets is dangerous however we needed to be able to include spaces. The assignment sheet declares that no input larger than 50 characters will be used.

    return inPtr;
}

int isBalancedParenthesis(char* infix){
    struct stack* instack = (struct stack*) malloc(sizeof(struct stack));
    int i;
    int insize;
    char check;
//Initialize Characer Stack
    initialize(instack);
    insize = strlen(infix);
//For every iteration of the loop, we push opening parentheses and pop until an opening parentheses when encountering a closed one. At the end we check if the stack is empty, if so the expression is valid.
    for(i = 0; i < insize; i++){
        if(infix[i] == '('){
            push(instack, infix[i]);
           }
        if (infix[i] == ')'){
            if(empty(instack) != 1){
                while(instack->items[instack->top] != '('){
                    pop(instack);
                }
                pop(instack);
            }
            else{
                return 0;
            }
        }
    }
    if(empty(instack)){
        return 1;
    }
    else{
        return 0;
    }
}
//Here we convert to Postfix using the rules from the lecture, as well as adding spaces between each operand and Operator.
//The way we have the loop set up allows up to differentiate between single digit and multi digit numbers in the postfix expression.
char* convertToPostfix(char* infix){
    int i = 0, j = 0;
    struct stack* instack1 = (struct stack*)malloc(sizeof(struct stack));
    int l = strlen(infix);
    char item = infix[i];
    char* postFix = (char*)malloc(102*sizeof(char));
    initialize(instack1);

    for(i = 0; i < l; i++){
            item = infix[i];
        if(isOperand(item)){
            postFix[j] = item;
            j++;
            if((isOperand(infix[i+1]) != 1)){
                postFix[j] = ' ';
                j++;
            }
        }
        if(item == '('){
            push(instack1, item);
           }
        if(item == ')'){
            while(top(instack1) != EMPTY && top(instack1) != '('){
                postFix[j] = pop(instack1);
                j++;
                postFix[j] = ' ';
                j++;
            }
            if(top(instack1) == '('){
                pop(instack1);
               }
        }
        if(isOperator(item)){
            while(isOperator(top(instack1)) == 1 && getOperatorPriority(top(instack1)) >= getOperatorPriority(item)){
                postFix[j] = pop(instack1);
                j++;
                postFix[j] = ' ';
                j++;
            }
            push(instack1, item);
        }

    }
    while(top(instack1) != EMPTY){
        postFix[j] = pop(instack1);
        j++;
        postFix[j] = ' ';
                j++;
    }
    postFix[j] = '\0';
    printf("\nPostfix Expression: %s\n", postFix);
    return postFix;
}
//He we evaluate the postfix expression. Using a loop, we can use something like the number conversion rules we learned in lecture in order to convert multi digit numbers.

int evaluate(char *postFix){
    struct intstack* stack = (struct intstack*)malloc(sizeof(struct intstack));
    int i = 0;
    int l = strlen(postFix);
    int A;
    int B;
    int eval;
    int sum = 0;
    int num1;
    int num2;

    int_initialize(stack);

    for(i = 0; i < l; i++){
        if(isOperand(postFix[i])){
            num1 = convertToInt(postFix[i]);
            while(isOperand(postFix[i+1]) == 1){
                num1 = num1*10;
                num2 = convertToInt(postFix[i+1]);
                num1 = num1 + num2;
                i++;
            }

            int_push(stack, num1);
        }
        if(isOperator(postFix[i])){
            B = int_pop(stack);
            A = int_pop(stack);
            eval = calculate(B, A, postFix[i]);
            int_push(stack, eval);
        }
    }
    sum = int_pop(stack);
    printf("\nEvaluation: %d\n", sum);
    return 1;
}
//We calculate two operands with an operator using a switch statement.

int calculate(int B, int A, char op){
    int eval;
    switch(op){
        case '^':
        eval = pow(A, B);
        break;

        case '*':
        eval = A * B;
        break;

        case '/':
        eval = A / B;
        break;

        case '%':
        eval = A % B;
        break;

        case '+':
        eval = A + B;
        break;

        case '-':
        eval = A - B;
        break;
    }

    return eval;
}
//Here we check if an input is an operand. It makes the process easier since only positive integers numbers are used for the input.
int isOperand(char value){
    if(value >= '0' && value <= '9')
        return 1;
    else
        return 0;

}
//Here we check to see if an input is an operator.
int isOperator(char value){
    if (value == '+' || value == '-' || value == '*' || value == '/' || value == '^' || value == '%')
        return 1;
    else
        return 0;
}
//Here we get the priority of an operator encountered. Weights come from the lecture. A switch statement could have been used.

int getOperatorPriority(char op){
    int priority = -0;
    if(op == '+' || op == '-')
        priority = 1;
    if(op == '*' || op == '/' || op == '%')
        priority = 2;
    if(op == '^')
        priority = 3;
    return priority;
}
//Here we convert a character to an integer. This could be extended to allow for numbers represented by letters.
int convertToInt(char target){
    int conv;
    conv = target-'0';
    return conv;
}
//Functions pulled from MultiStack.c
// We have character and integer versions of all stack commands in order to be able to work with both types of stacks.
void initialize(struct stack* stackPtr) {
     stackPtr->top = -1;
}

int push(struct stack* stackPtr, char value) {

    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 0;
}

int full(struct stack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

int empty(struct stack* stackPtr) {
    return (stackPtr->top == -1);
}

char pop(struct stack* stackPtr) {

    char retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

char top(struct stack* stackPtr) {

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}

int int_top(struct intstack* stackPtr) {

    // Take care of the empty case.
    if (int_empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}

int int_pop(struct intstack* stackPtr) {

    int retval;

    // Check the case that the stack is empty.
    if (int_empty(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

void int_initialize(struct intstack* stackPtr) {
     stackPtr->top = -1;
}

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int int_push(struct intstack* stackPtr, int value) {

    // Check if the stack is full.
    if (int_full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int int_full(struct intstack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int int_empty(struct intstack* stackPtr) {
    return (stackPtr->top == -1);
}
