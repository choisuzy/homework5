#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10         /* MAX_STACK_SIZE를 10으로 정의 */
#define MAX_EXPRESSION_SIZE 20    /* MAX_EXPRESSION_SIZE를 20으로 정의 */

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{    /*  enum을 타입으로 지정 */
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;   /* QueueType의 struct  */

char infixExp[MAX_EXPRESSION_SIZE];    /* 크기가 MAX_EXPRESSION_SIZE이고 char형인 배열 infixExp 선언*/
char postfixExp[MAX_EXPRESSION_SIZE];  /* 크기가 MAX_EXPRESSINO_SIZE이고 char형인 배열 postfixExp 선언*/
char postfixStack[MAX_STACK_SIZE];     /* 크기가 MAX_STACK_SIZE이고 char형인 배열 postfixStack 선언*/
int evalStack[MAX_STACK_SIZE];         /* 크기가 MAX_STACK_SIZE이고 int형인 배열 evalStack 선언*/

int postfixStackTop = -1;  /* int형 변수 postfixStackTop을 -1로 선언 */
int evalStackTop = -1;     /* int형 변수 evalStackTop을 -1로 선언 */
int evalResult = 0;        /* int형 변수 evalResult를 0으로 선언 */

void postfixPush(char x);             /* 스택에 push하는 postfixPush 함수 선언 */
char postfixPop();                    /* 스택에서 pop하는 postfixPop 함수 선언 */
void evalPush(int x);                 /* evalStack을 push하는 evalPush 함수 선언 */
int evalPop();                        /* evalStackTop을 pop하는 evalPop 함수 선언 */
void getInfix();                      /* 중위표기식으로 입력받는 getInfix 함수 선언 */
precedence getToken(char symbol);     /* 우선순위를 반환하는 getToken 함수 선언 */
precedence getPriority(char x);       /* 입력자에게 입력받은 x의 값을 우선순위 반환하는 getPriority 함수 선언 */
void charCat(char* c);                /* charCat 함수 선언 */
void toPostfix();                     /* postfix로 바꾸는 toPostfix 함수 선언 */
void debug();                         /* debug 함수 선언 */
void reset();                         /* reset 함수 선언 */
void evaluation();                    /* evaluation 함수 선언 */

int main()
{
	char command;  /* char형 command */
	printf("[----- [Choi Suzy]  [2021024135] -----]\n"); 
	do{
		printf("----------------------------------------------------------------\n"); /* print */
		printf("               Infix to Postfix, then Evaluation               \n");  /* print */
		printf("----------------------------------------------------------------\n"); /* print */
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");  /* print */
		printf("----------------------------------------------------------------\n"); /* print */

		printf("Command = ");    /* print */
		scanf(" %c", &command);  /* char형 command를 입력자에게 입력받음 */

		switch(command) {    /* command가 ~이면 조건문 */
		case 'i': case 'I':  /* command가 i나 I이면 */
			getInfix();      /* getInfix함수 실행 */
			break;           /* 조건식 빠져나옴 */
		case 'p': case 'P':  /* command가 p나 P이면 */
			toPostfix();     /* toPostfix함수 실행 */
			break;           /* 조건식 빠져나옴 */
		case 'e': case 'E':  /* command가 e나 E이면 */
			evaluation();    /* evaluation함수 실행 */
			break;           /* 조건식 빠져나옴 */
		case 'd': case 'D':  /* command가 d나 D이면 */
			debug();         /* debug함수 실행 */
			break;           /* 조건식 빠져나옴 */
		case 'r': case 'R':  /* command가 r이나 R이면 */
			reset();         /* reset함수 실행 */
			break;           /* 조건식 빠져나옴 */
		case 'q': case 'Q':  /* command가 q나 Q이면 */
			break;           /* 조건식 빠져나옴 */
		default:  /* 위의 알파벳이 다 아니면 */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); /* print */
			break; /* 조건식 빠져나옴 */
		}

	}while(command != 'q' && command != 'Q'); /* command가 q가 아니고 Q가 아니라면 do루프 계속 돎 */

	return 1; /* 1을 반환함 */


}

void postfixPush(char x)  /* 스택에 push하는 postfixPush 함수 정의 */
{
    postfixStack[++postfixStackTop] = x; /* postfixStack 배열의 postfixStackTop에서 증가된 부분에 x를 넣음 */ /* 현재 top위치보다 하나 올린 위치에 저장 */
}

char postfixPop()  /* 스택에서 pop하는 postfixPop 함수 정의 */
{
	char x;  /* char형 x */
    if(postfixStackTop == -1)  /* postfixStackTop이 -1이면 */
        return '\0';  /* \0을 반환함 */
    else {   /* if 조건에 해당하지 않는다면 */
    	x = postfixStack[postfixStackTop--]; /* x에 postfixStack 배열에서 감소시킨 postfixStackTop를 저장 */ /* 현재 top위치보다 하나 내린 위치에 저장 */
    }
    return x; /* x를 반환함 */
} 

void evalPush(int x)  /* evalStack을 push하는 evalPush 함수 정의 */
{
    evalStack[++evalStackTop] = x; /* evalStack 배열의 evalStackTop에서 증가된 부분에 x를 넣음 */ /* 현재 top위치보다 하나 올린 위치에 저장 */
}	

int evalPop()  /* evalStackTop을 pop하는 evalPop 함수 정의 */
{
    if(evalStackTop == -1) /* evalStackTop이 -1이면 */
        return -1; /* -1을 반환함 */
    else  /* if 조건에 해당하지 않는다면 */
        return evalStack[evalStackTop--]; /* evalStack[evalStackTop--]을 반환함 */
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()  /* 중위표기식으로 입력받는 getInfix 함수 정의 */
{
    printf("Type the expression >>> "); /* print */
    scanf("%s",infixExp); /* infixExp를 입력자에게 입력받음 */
}

precedence getToken(char symbol) /* 우선순위를 반환하는 getToken 함수 정의 */
{
	switch(symbol) {  /* symbol이 ~이면 조건문 */
	case '(' : return lparen; /* symbol이 (이면 왼쪽 괄호를 반환함 */
	case ')' : return rparen; /* symbol이 )이면 오른쪽 괄호를 반환함 */
	case '+' : return plus;   /* symbol이 +이면 덧셈을 반환함 */
	case '-' : return minus;  /* symbol이 -이면 뺄셈을 반환함 */
	case '/' : return divide; /* symbol이 /이면 나눗셈을 반환함 */
	case '*' : return times;  /* symbol이 *이면 곱셈을 반환함 */
	default : return operand; /* 위의 기호가 아니면 피연산자를 반환함 */
	}
}

precedence getPriority(char x) /* 입력자에게 입력받은 x의 값을 우선순위 반환하는 getPriority 함수 정의 */
{
	return getToken(x); /* getToken(x)를 반환함 */
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)  /* charCat 함수 정의 */
{
	if (postfixExp == '\0') /* postfixExp가 \0이면 */
		strncpy(postfixExp, c, 1); /* postfixExp를 c에 문자열 하나 복사함 */
	else  /* if 조건에 해당하지 않으면 */
		strncat(postfixExp, c, 1); /* postfixExp를 c에 문자열 하나 붙여넣음 */
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() /* postfix로 바꾸는 toPostfix 함수 정의 */
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp; /* infixExp를 char형 포인터 exp에 넣음 */
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') /* *exp가 \0이 아니면 while문을 계속 돌음 */
	{
		if(getPriority(*exp) == operand) /* getPriority(*exp)가 operand이면 */
		{
			x = *exp; /* *exp를 x에 넣음 */
        	charCat(&x); /* charCat함수 실행 */
		}
        else if(getPriority(*exp) == lparen) { /* getPriority(*exp)가 lparen이면 */

        	postfixPush(*exp); /* postfixPush 함수 실행 */
        }
        else if(getPriority(*exp) == rparen) /* getPriority(*exp)가 rparen이면 */
        {
        	while((x = postfixPop()) != '(') { /* x에 postfixPop함수를 넣은 것이 (가 아니면 while문 반복 */
        		charCat(&x); /* charCat 함수 실행 */
        	}
        }
        else /* getPriority(*exp)가 위에 나온 것이 다 아니면 */
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) /* postfixStack[postfixStackTop]의 우선순위가 *exp의 우선순위보다 높은 동안 while문 반복 */
            {
            	x = postfixPop(): /* postfixPop함수를 x에 넣음 */
            	charCat(&x); /* charCat 함수 실행 */
            }
            postfixPush(*exp); /* postfixPush 함수 실행 */
        }
        exp++; /* exp 증가 */
	}

    while(postfixStackTop != -1) /* postfixStackTop이 -1이 아니면 while문을 계속 돌음 */
    {
    	x = postfixPop(); /* postfixPop함수를 x에 넣음 */
    	charCat(&x); /* charCat 함수 실행*/
    }

}

void debug()  /* debug 함수 정의 */
{
	printf("\n---DEBUG\n"); /* print */
	printf("infixExp =  %s\n", infixExp); /* infixExp의 값을 print */
	printf("postExp =  %s\n", postfixExp); /* postfixExp의 값을 print */
	printf("eval result = %d\n", evalResult); /* evalResult의 값을 print */

	printf("postfixStack : "); /* print */
	for(int i = 0; i < MAX_STACK_SIZE; i++) /* MAX_STACK_SIZE번 동안 for루프 돈다. */
		printf("%c  ", postfixStack[i]); /* postfixStack[i]를 print */

	printf("\n"); /* print */

}

void reset() /* reset 함수 정의 */
{
	infixExp[0] = '\0';   /* infixExp배열의 처음 부분을 null로 지정 */
	postfixExp[0] = '\0'; /* postfixExp배열의 처음 부분을 null로 지정 */

	for(int i = 0; i < MAX_STACK_SIZE; i++)  /* MAX_STACK_SIZE번 동안 for루프 돈다. */
		postfixStack[i] = '\0'; /* postfixExp배열의 i 부분을 null로 지정 */
         
	postfixStackTop = -1; /* postfixStackTop에 -1을 넣음 */
	evalStackTop = -1;    /* evalStackTop에 -1을 넣음 */
	evalResult = 0;       /* evalResult에 0을 넣음 */
}
void evaluation() /* evaluation 함수 정의 */
{
	int opr1, opr2, i; /* opr1, opr2, i을 int형으로 지정 */

	int length = strlen(postfixExp); /* strlen(postfixExp)을 int형 length에 담음 */
	char symbol; /* char형 symbol */
	evalStackTop = -1; /* evalStackTop에 -1을 넣음 */

	for(i = 0; i < length; i++)  /* length번 동안 for루프 돈다. */
	{
		symbol = postfixExp[i];  /* postfixExp[i]배열을 symbol에 넣음 */
		if(getToken(symbol) == operand) { /* getToken(symbol)이 operand이면 */
			evalPush(symbol - '0'); /* evalPush 함수 실행 */
		}
		else {  /* if 조건에 해당하지 않으면 */
			opr2 = evalPop(); /* evalPop함수를 실행하고 opr2에 넣음 */
			opr1 = evalPop(); /* evalPop함수를 실행하고 opr1에 넣음 */
			switch(getToken(symbol)) {  /* getToken(symbol)이 ~이면 조건문 */
			case plus: evalPush(opr1 + opr2); break;   /* getToken(symbol)이 plus이면 evalPush(opr1 + opr2)를 실행하고 조건문을 빠져나감 */
			case minus: evalPush(opr1 - opr2); break;  /* getToken(symbol)이 minus이면 evalPush(opr1 - opr2)를 실행하고 조건문을 빠져나감 */
			case times: evalPush(opr1 * opr2); break;  /* getToken(symbol)이 times이면 evalPush(opr1 * opr2)를 실행하고 조건문을 빠져나감 */
			case divide: evalPush(opr1 / opr2); break; /* getToken(symbol)이 divide이면 evalPush(opr1 / opr2)를 실행하고 조건문을 빠져나감 */
			default: break; /* getToken(symbol)이 위에 나온 것들이 아니면 그냥 조건문을 빠져나감 */
			}
		}
	}
	evalResult = evalPop(); /* evalPop함수를 evalResult에 넣음 */
}