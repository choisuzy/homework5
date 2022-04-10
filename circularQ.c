#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4              /* MAX_QUEUE_SIZE를 4로 정의 */

typedef char element;                 /* element를 char형 타입으로 선언 */
typedef struct {                      /* 타입이 다른 데이터들을 그룹화 */
	element queue[MAX_QUEUE_SIZE];    /* char형으로 선언한 element를 queue[MAX_QUEUE_SIZE]로 선언 */
	int front, rear;                  /* front와 rear를 int형 타입으로 선언 */
}QueueType;                           /* 구조체 호출용 이름  */


QueueType *createQueue();                    /* QueueType으로 반환되는 Queue를 생성하는 *createQueue 함수 선언 */
int freeQueue(QueueType *cQ);                /* 할당된 메모리를 해제하는 freeQueue 함수 선언 */
int isEmpty(QueueType *cQ);                  /* *cQ가 비었는지 확인하는 isEmpty 함수 선언 */
int isFull(QueueType *cQ);                   /* *cQ가 다 찼는지 확인하는 isFull함수 선언 */
void enQueue(QueueType *cQ, element item);   /* *cQ에 저장된 item을 삽입하는 enQueue 함수 선언 */
void deQueue(QueueType *cQ, element* item);  /* *cQ에 저장된 item을 삭제하는 deQueue함수 선언*/
void printQ(QueueType *cQ);                  /* *cQ를 print하는 printQ함수 선언 */
void debugQ(QueueType *cQ);                  /* *cQ를 디버그하는(상태를 보여주는) debugQ함수 선언*/
element getElement();                        /* element를 입력받는 getElement 함수 선언*/


int main(void)
{
	printf("[----- [Choi Suzy]  [2021024135] -----]\n"); 

	QueueType *cQ = createQueue();  /* createQueue()함수를 QueueType의 *cQ에 넣음 */
	element data;                   /* data를 queue에 char형 배열의 요소인 element로 선언 */

	char command;                   /* command를 char형 타입으로 선언 */

	do{
		printf("\n-----------------------------------------------------\n");  /* print */
		printf("                     Circular Q                   \n");       /* print */
		printf("------------------------------------------------------\n");   /* print */
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");   /* print */
		printf("------------------------------------------------------\n");   /* print */

		printf("Command = ");    /* print */
		scanf(" %c", &command);  /* char형 command를 입력자에게 입력받음 */

		switch(command) {        /* command가 ~이면 조건문 */ 
		case 'i': case 'I':      /* command가 i나 I이면 */
			data = getElement(); /* getElement()함수 data에 넣음 */
			enQueue(cQ, data);   /* enQueue함수 호출 */
			break;               /* 조건식 빠져나옴 */
		case 'd': case 'D':      /* command가 d나 D이면 */
			deQueue(cQ,&data);   /* deQueue함수 호출 */
			break;               /* 조건식 빠져나옴 */
		case 'p': case 'P':      /* command가 p나 P이면 */
			printQ(cQ);          /* cQ를 print하는 함수 실행 */
			break;               /* 조건식 빠져나옴 */
		case 'b': case 'B':      /* command가 b나 B이면 */
			debugQ(cQ);          /* debugQ함수 호출 */
			break;               /* 조건식 빠져나옴 */
		case 'q': case 'Q':      /* command가 q나 Q이면 */
			break;               /* 조건식 빠져나옴 */
		default:                 /* 위의 알파벳이 다 아니면 */
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); /* print */
			break;               /* 조건식 빠져나옴 */
		}

	}while(command != 'q' && command != 'Q'); /* command가 q가 아니고 Q가 아니라면 do루프 계속 돎 */


	return 1; /* 1을 반환함 */
}

QueueType *createQueue()    /* QueueType으로 반환되는 *createQueue 함수 정의 */
{
	QueueType *cQ;          /* QueueType *cQ 선언 */
	cQ = (QueueType *)malloc(sizeof(QueueType));  /* QueueType 사이즈만큼 cQ에 동적 메모리 할당 */
	cQ->front = 0;          /* cQ의 front부분을 0으로 지정 */
	cQ->rear = 0;           /* cQ의 rear부분을 0으로 지정 */
	return cQ;              /* cQ를 반환함 */
} 

int freeQueue(QueueType *cQ)  /* QueueType *cQ를 free하는 함수 정의 */
{
    if(cQ == NULL) return 1;  /* cQ가 비었다면 1을 반환함 */
    free(cQ);                 /* cQ가 비어있지 않다면 cQ를 해제시킴 */
    return 1;                 /* 1을 반환함 */
}

element getElement()          /* element를 입력받는 getElement 함수 정의 */
{
	element item;               /* item을 queue에 element로 선언 */
	printf("Input element = "); /* print */
	scanf(" %c", &item);        /* char형의 item을 입력자에게 입력받음 */
	return item;                /* 입력받은 item을 반환함 */
}


int isEmpty(QueueType *cQ)  /* *cQ가 비었는지 확인하는 isEmpty 함수 정의 */
{
	if (cQ->front == cQ->rear){ /* cQ의 front부분과 cQ의 rear부분이 같다면 */
		printf("Circular Queue is empty!");  /* print */
		return 1;    /* 1을 반환함 */
	}
	else return 0;   /* if 조건에 해당하지 않는다면 0을 반환함 */
}

int isFull(QueueType *cQ)  /* *cQ가 다 찼는지 확인하는 isFull함수 정의 */
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { /* MAX_QUEUE_SIZE만큼 동적할당한 cQ의 rear+1 부분과 cQ의 front부분이 같다면 */
		printf(" Circular Queue is full!");   /* print */
		return 1;   /* 1을 반환함 */
	}
	else return 0;  /* if 조건에 해당하지 않는다면 0을 반환함 */
}

void enQueue(QueueType *cQ, element item) /* *cQ에 item을 삽입하는 enQueue 함수 정의 */
{ 
	if(isFull(cQ)) return; /* isFull함수의 값이 true이면 바로 enQueue 함수를 나옴 */
	else {                 /* if 조건에 해당하지 않는다면 */
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; /* cQ의 rear값이 증가하고 그곳으로 이동 */
		cQ->queue[cQ->rear] = item; /* (cQ의 queue)의 cQ의 rear부분에 item을 넣음 */
	}
}

void deQueue(QueueType *cQ, element *item) /* *cQ에 item을 삭제하는 deQueue함수 정의 */
{
	if(isEmpty(cQ)) return; /* isEmpty함수의 값이 true이면 return */
	else {                  /* if 조건에 해당하지 않는다면 */
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;  /* cQ의 front값이 증가하고 그곳으로 이동 */
		*item = cQ->queue[cQ->front]; /* (cQ의 queue)의 cQ의 front부분을 *item에 넣음  */
		return; /* 반환함 */
	}
}


void printQ(QueueType *cQ) /* *cQ를 출력하는 printQ함수 정의 */
{
	int i, first, last;    /* i, first, last를 int형으로 지정 */

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; /* cQ의 front값을 증가하고 first에 넣음  */
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;   /* cQ의 rear값을 증가하고 last에 넣음  */

	printf("Circular Queue : ["); /* print */

	i = first;  /* first를 i에 넣음 */
	while(i != last){ /* i가 last가 아니라면 계속 도는 while문 */
		printf("%3c", cQ->queue[i]); /* cQ의 queue[i] 배열 부분을 print */
		i = (i+1)%MAX_QUEUE_SIZE;    /* i의 값을 증가하고 i에 넣음  */

	}
	printf(" ]\n"); /* print */
}


void debugQ(QueueType *cQ)  /* *cQ를 디버그하는(상태를 보여주는) debugQ함수 정의 */
{

	printf("\n---DEBUG\n"); /* print */
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) /* MAX_QUEUE_SIZE번 동안 for루프 돈다. */
	{
		if(i == cQ->front) { /* i가 cQ의 front부분과 같다면 */
			printf("  [%d] = front\n", i);  /* i를 넣어 print */
			continue; /* if조건에 해당하지 않을 때까지 계속함 */
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); /* i와 cQ의 queue[i]부분을 차례대로 넣어 print */

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); /* cQ의 front부분과 cQ의 rear부분을 차례대로 넣어 print */
}