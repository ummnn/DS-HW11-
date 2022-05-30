//2019038027 이동현

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10 //최대크기

typedef struct graphNode{ //인접리스트의 노드 구조체
    int vertex;
    struct graphNode* link;
}graphNode;

typedef struct graphType{ //그래프 구조체 
    int n;
    graphNode* adjList_H[MAX_VERTEX]; //그래프 정점에 대한 헤드포인터 배열
}graphType;

void initialzeGraph(graphType* g);
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void printGraph(graphType* g);


/* 그래프 생성하는 함수 */
void initilaizeGraph(graphType* g)
{
    g->n= 0;    //정점개수 0으로 초기화
    
    for(int v=0;v<MAX_VERTEX;v++){
        g->adjList_H[v] = NULL; //그래프 정점에 대한 헤드포인터 배열 초기화
    }
}

/* 정점을 삽입하는 함수 */
void insertVertex(graphType* g, int v)
{
    if(((g->n)+1)>MAX_VERTEX){ //정점의 수가 최대정점의 수보다 크다면
        printf("그래프 정점의 수를 초과하였습니다\n");
        return;
    }

    g->n++; //정점의 수 1증가
}

/* 간선을 삽입하는 함수 */
void insertEdge(graphType* g, int u, int v)
{
    graphNode* node;


    if(u>=g->n || v>=g->n){ //그래프에 정점ㅈ u와 v가 있는지 확인
        printf("그래프에 존재하지 않습니다\n");
        return;
    }

    node = (graphNode*)malloc(sizeof(graphNode)); //graphNode의 크기만큼 메모리 할당
    node->vertex = v; //node의 vertex에 v저장
    node->link=g->adjList_H[u]; //삽입간선에 대한 노드를 리스트의 첫번째 노드로 연결
    g->adjList_H[u] = node;
}


void printGraph(graphType*g)
{
    graphNode* p;

    for(int i=0;i<(g->n);i++){
        printf("\n\t\t 정점 %c의 인접리스트", i);
        p = g->adjList_H[i];
        while (p){
            printf("-> %c",p->vertex); //정점 출력
            p=p->link;
        }
    }
}

int main()
{
	printf("[----- [이동현] [2019038027] -----]\n");
	char command; //명령어를 저장하는 변수
	int key;
    graphType* G = (graphType*)malloc(sizeof(graphType)); //그래프 G

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = g                                       \n");
		printf(" Insert Vertex        = i      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command를 입력받는다

		switch(command) {
		case 'g': case 'G': //command가 z나 Z일 때
			initializeGraph(G); //initializeBST함수 실행
			break;

		case 'i': case 'I': //command가 i나 I일 때
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다
			insertVertex(G, key); //insertVertex함수 실행
			break;
		
        case 'e': case 'E': //command가 e나 E일 때
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다 
			insertEdge(G, key, key); //insertEdge함수 실행
			break;

		case 'd': case 'D': //command가 d나 D일 때
			dfs(); //dfs함수 실행
			break;
		
        case 'b': case 'B': //command가 b나 B일 때
			bfs(); //bfs함수 실행
			break;

		case 'p': case 'P': //command가 p나 P일 때
			printGraph(); //printStack함수 실행
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q나 Q일 때까지 반복

	return 1;
}
