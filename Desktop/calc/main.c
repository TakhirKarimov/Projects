/**************************
cos(x) - c
sin(x) - s
tan(x) - t
acos(x) - o
asin(x) - i
atan(x) - a
sqrt(x) - r
ln(x) - n
log(x) - g
mod(x) - m
**************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct stack {
    char sign;
    double num;
    struct stack *next;
} stack;

void notation_func(char expression[257], char notation[257]);
void push(stack **head, char sign, double num);
char pop(stack **head);
int prior(char a);
int pop_parenthesis (stack *head, int exp_i, char notation[257]);
void string_conversion_body (char expression[257], char *find, int size_expression, char char_to_replace);
void string_conversion (char expression[257], int size_expression);
double string_to_double(char expression[257], int *i);
void calc_notation (char expression[257]);
void calc_stack(stack **head);
double calc_one_component_func (stack **head, char sign);
double calc_two_component_func (stack **head, char sign);

int main() {
    char expression[257];
    char notation[257];
    int size = 0;
    while (scanf("%c", &expression[size]) && expression[size] != '=')
        size++;
    expression[size] = '\0';
    string_conversion (expression, size);
    notation_func(expression, notation);
    calc_notation(notation);
    //printf("\n%s", notation);
}

void notation_func(char expression[257], char notation[257]) {
    stack *head = NULL;
    int not_i = 0;
    for(int exp_i = 0; expression[exp_i] != '\0'; exp_i++, not_i++) {
        if (expression[exp_i] == ' ') {
            not_i--;
            continue;
        }
        notation[not_i] = ' ';
        if (expression[exp_i] == '(')
            not_i--;
        if ((expression[exp_i] >= '0' && expression[exp_i] <= '9') || expression[exp_i] == '.' || (expression[exp_i] >= 'a' && expression[exp_i] <= 'z'))
            notation[not_i] = expression[exp_i];
        else if (expression[exp_i] == ')') {
            while (head->sign != '(') {
                notation[not_i++] = pop(&head);
            }
            not_i--;
            pop(&head);
        }
        else {
            if (head != NULL && prior(expression[exp_i]) <= prior(head->sign) && expression[exp_i] != '(') {
                while (head != NULL && prior(expression[exp_i]) <= prior(head->sign)) {
                    notation[not_i++] = pop(&head);
                }
                not_i--;
            }
            push(&head, expression[exp_i], 0);
        }
    }
    while (head != NULL) {
        notation[not_i++] = pop(&head);
    }
    notation[not_i] = '\0';
}

void push(stack **head, char sign, double num) {
    stack *node = (stack*)calloc(1, sizeof(stack));
    node->next = *head;
    node->sign = sign;
    node->num = num;
    *head = node;
}

char pop(stack **head) {
    char res = (*head)->sign;
    stack* tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return res;
}

int prior(char a) {
    int res = -1;
    switch (a) {
        case '(':
        case ')':
            res = 0;
            break;
        case '*':
        case '/':
            res = 2;
            break;
        case '-':
        case '+':
            res = 1;
            break;
        case 'i':
        case 'o':
        case 'a':
        case 'r':
        case 'n':
        case 'g':
        case 'm':
        case 's':
        case 'c':
        case 't':
        case '^':
            res = 3;
            break;
    }
    return res;
}

void string_conversion_body (char expression[257], char *find, int size_expression, char char_to_replace) {
    for (int i = 0; i < size_expression - strlen(find); i++) {
        if (strncmp(expression + i, find, strlen(find)) == 0) {
            for(int j = i + 1; j < strlen(find) + i; j++)
                expression[j] = ' ';
            i += strlen(find);
        }
    }
}

void string_conversion (char expression[257], int size_expression) {
    string_conversion_body(expression, "asin", size_expression, 'i');
    string_conversion_body(expression, "acos", size_expression, 'o');
    string_conversion_body(expression, "atan", size_expression, 'a');
    string_conversion_body(expression, "sqrt", size_expression, 'r');
    string_conversion_body(expression, "ln", size_expression, 'n');
    string_conversion_body(expression, "log", size_expression, 'g');
    string_conversion_body(expression, "mod", size_expression, 'm');
    string_conversion_body(expression, "sin", size_expression, 's');
    string_conversion_body(expression, "cos", size_expression, 'c');
    string_conversion_body(expression, "tan", size_expression, 't');
}

void calc_notation (char notation[257]) { // Переделать в double
    stack *head = NULL;
    int len = strlen(notation);
    double num;
    for (int i = 0; i < len; i++) {
        if (notation[i] == ' ')
            continue;
        if (prior(notation[i]) == -1) {
            push(&head, '\0', string_to_double (notation, &i));
            continue;
        }
        if (prior(notation[i]) != -1) {
            push(&head, notation[i], 0);
            calc_stack(&head);
        }
    }
    printf("%f", head->num);
}

double string_to_double(char notation[257], int *i) {
    double res = atof(notation + (*i));
    while (notation[(*i)] >= '0' && notation[(*i)] <= '9' || notation[(*i)] == '.') {
        (*i)++;
    }
    (*i)--;
    return res;
}

void calc_stack(stack **head) {
    double tmp_num = -1, res = -1;
    char sign = pop(head);
    if (prior(sign) == 3 && sign != 'm' && sign != '^') {
        res = calc_one_component_func(head, sign);
        pop(head);
        push(head, '\0', res);
    }
    else {
        res = calc_two_component_func(head, sign);
        pop(head);
        pop(head);
        push(head, '\0', res);
    }
}

double calc_one_component_func (stack **head, char sign) {
    double res = -1;
    switch (sign) {
            case 'i':
                res = asin((*head)->num);
                break;
            case 'o':
                res = acos((*head)->num);
                break;
            case 'a':
                res = atan((*head)->num);
                break;
            case 'r':
                res = sqrt((*head)->num);
                break;
            case 'n':
                res = log((*head)->num);
                break;
            case 'g':
                res = log10((*head)->num);
                break;
            case 's':
                res = sin((*head)->num);
                break;
            case 'c':
                res = cos((*head)->num);
                break;
            case 't':
                res = tan((*head)->num);
                break;
        }
    return res;
}

double calc_two_component_func (stack **head, char sign) {
    double tmp_num_1 = (*head)->num;
    double tmp_num_2 = (*head)->next->num;
    double res = -1;
    switch (sign) {
        case 'm':
            res = fmod(tmp_num_2, tmp_num_1);
            break;
        case '^':
            res = pow(tmp_num_2, tmp_num_1);
            break;
        case '*':
            res = tmp_num_1 * tmp_num_2;
            break;
        case '/':
            res = tmp_num_2 / tmp_num_1;
            break;
        case '+':
            res = tmp_num_1 + tmp_num_2;
            break;
        case '-':
            res = tmp_num_2 - tmp_num_1;
            break;
    }
    return res;
}