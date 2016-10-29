#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100

void convertToRPN(char str[]);
int hasLowerPrecedence(char firstOperator, char secondOperator);
double calculatePostfix(char str[]);
int tokenise(char str[], int start, char result[]);

const int MAX_STRING = 256;

char operators[4] = { '-', '+', '/', '*'};
char infixExpression[MAX_STRING];
char rpnExpression[MAX_STRING];

struct characterStack
{
	char stackElements[MAX_SIZE];
	int top;
};

typedef struct characterStack CHARACTER_STACK;
CHARACTER_STACK s;

void push(char element);
char pop(void);
int isEmpty(void);

struct numberStack
{
	double numberElements[MAX_SIZE];
	int numberTop;
};

typedef struct numberStack NUMBER_STACK;
NUMBER_STACK numbers;

void pushNumber(double element);
double popNumber(void);
int isNumberStackEmpty(void);

int main()
{
	printf("Please enter a normal infix expression: ");

	double answer = 0.0;
	s.top = -1;
	numbers.numberTop = -1;
	
	fgets(infixExpression, MAX_STRING, stdin);

	convertToRPN(infixExpression);

	int index = 0;

	printf("The corresponding rpn expression is: ");

	while (rpnExpression[index] != '\0')
	{
	    printf("%c", rpnExpression[index]);
	    index++;
	}

	answer = calculatePostfix(rpnExpression);
	printf("\nThe answer to the postfix expression is: %lf\n", answer);
}

void convertToRPN(char str[])
{
	char result[MAX_STRING];

	int start = 0;
	int outputIndex = 0;
	
	while (start != -1)
	{
		start = tokenise(str, start, result);
		
		if (isdigit(result[0]))
		{
			int index = 0;

			while (result[index] != '\0')
			{
				rpnExpression[outputIndex] = result[index];

				outputIndex++;
				index++;
			}
			rpnExpression[outputIndex] = ' ';
			outputIndex++;
		}
		else if (result[0] == '(')
		{
			push(result[0]);	
		}
		else if	(result[0] == '+' || result[0] == '-' || result[0] =='*' ||
			result[0] == '/')
		{
			while (hasLowerPrecedence(result[0], s.stackElements[s.top]) && s.top >= 0)
			{
				char higherOperator = pop();
				rpnExpression[outputIndex] = higherOperator;

				outputIndex++;

				rpnExpression[outputIndex] = ' ';
				outputIndex++;
			}

			push(result[0]);
		}
		else if (result[0] == ')')
		{
			char stackOperator = pop();

			while (stackOperator != '(' && s.top >= 0)
			{	
				rpnExpression[outputIndex] = stackOperator;

				outputIndex++;

				rpnExpression[outputIndex] = ' ';
				outputIndex++;

				stackOperator = pop();
			}
		}
	}

	while (!isEmpty())
	{
	    char stackToken = pop();
	    rpnExpression[outputIndex] = stackToken;

	    outputIndex++;
	}

	rpnExpression[outputIndex] = '\0';
}

int hasLowerPrecedence(char firstOperator, char secondOperator)
{
	int firstIndex = 0;
	int secondIndex = 0;

	if (secondOperator != '(')
	{
		while (operators[firstIndex] != firstOperator)
		{
			firstIndex++;
		}

		while (operators[secondIndex] != secondOperator)
		{
			secondIndex++;
		}

		if (secondIndex >= firstIndex     )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

double calculatePostfix(char str[])
{
	char result[MAX_STRING];
	int start = 0;
	double answer = 0.0;

	while ( start != -1)
        {
		start = tokenise(str, start, result);
		
		if (result[0] == '+')
		{
		  double secondOperand = popNumber();
		  double firstOperand = popNumber();
		
		  answer = (firstOperand + secondOperand);
		
		  pushNumber(answer);
		}
		else if (result[0] == '-')
		{
			double secondOperand = popNumber();
			double firstOperand = popNumber();
			answer = (firstOperand - secondOperand);
		
			  pushNumber(answer);
		}
		else if (result[0]== '*')
		{
			double secondOperand = popNumber();
			double firstOperand = popNumber();
			answer = (firstOperand * secondOperand);
		
			pushNumber(answer);
		}
		else if (result[0] == '/')
		{
			double secondOperand = popNumber();
			double firstOperand = popNumber();
			answer = (firstOperand / secondOperand);
			
			pushNumber(answer);
		}
		else
		{	
			double element = atof(result);
		
			pushNumber(element);
		}
	}

	return answer;
}

int tokenise(char str[], int start, char result[])
{
  	while (str[start] == ' ' && str[start] != '\0'&& str[start] != '\n')
	{
	  start++;
	}

	int index = 0;

	while (str[start] != ' ' && str[start] != '\0' && str[start] != '\n')
	{
	    result[index] = str[start];
	    start++;
	    index++;	
	}

	result[index] = '\0';

	if (str[start] == '\0' || str[start] == '\n'  )
	{
		return -1;
	}
	else
	{
		return start;
	}
}

void push(char element)
{

  	if (s.top == (MAX_SIZE - 1))
  	{
	        printf("Stack is Full \n");
  		return;
  	}
  	else
  	{
		s.top = s.top + 1;
		s.stackElements[s.top] = element;
  	}
	return;
}

char pop()
{
	char element;

	element = s.stackElements[s.top];
	s.top = s.top - 1;

	return(element);
}

int isEmpty()
{
	if (s.top == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void pushNumber(double element)
{
        if (numbers.numberTop == (MAX_SIZE - 1))
  	{
	        printf("Stack is Full \n");
  		return;
  	}
  	else
  	{
		numbers.numberTop = numbers.numberTop + 1;
		numbers.numberElements[numbers.numberTop] = element;
  	}
	return;
}

double popNumber()
{
	double element;

	element = numbers.numberElements[numbers.numberTop];
	numbers.numberTop = numbers.numberTop - 1;

	return(element);
}

int isNumberStackEmpty()
{
	if (numbers.numberTop == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
