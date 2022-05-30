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
	int visited[MAX_VERTEX]; //정점을 방문했는지 표시하는 배열
}graphType;

typedef struct stackNode{ //스택 구조체
	int data;
	struct stackNode* link;
}stackNode;

void initializeGraph(graphType* g);
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void printGraph(graphType* g);
void freeGraph(graphType* g);
void dfs(graphType* g, int v);

int isStackEmpty(void);
void push(int item);
int pop(void);

stackNode* top;

int main()
{
	printf("[----- [이동현] [2019038027] -----]\n");
	char command; //명령어를 저장하는 변수
	int u;
	int v;
    graphType* G = (graphType*)malloc(sizeof(graphType)); //그래프 G

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = g                                       \n");
		printf(" Insert Vertex        = i      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search (x)      = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //command를 입력받는다

		switch(command) {
		case 'g': case 'G': //command가 g나 G일 때
			initializeGraph(G); //initializeGraph함수 실행
			break;

		case 'i': case 'I': //command가 i나 I일 때
			printf("정점을 입력하세요 = ");
			scanf("%d", u); //key를 입력받는다
			insertVertex(G, u); //insertVertex함수 실행
			break;
		
        case 'e': case 'E': //command가 e나 E일 때
			printf("간선을 입력하세요= num,num: ");
			scanf("%d,%d", &u,&v ); //간선을 입력받는다 
			insertEdge(G, u, v); //insertEdge함수 실행
			break;

		case 'd': case 'D': //command가 d나 D일 때
            printf("정점을 입력하세요 = ");
			scanf("%d", &v ); //정점을 입력받는다 
			dfs(G,v); //dfs함수 실행
			break;
		
        /*case 'b': case 'B': //command가 b나 B일 때
			bfs(); //bfs함수 실행
			break;*/

		case 'p': case 'P': //command가 p나 P일 때
			printGraph(G); //printGraph함수 실행
			break;
		
		case 'q': case 'Q': //command가 q나 Q일 때
			freeGraph(G); //freeGraph함수 실행
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q나 Q일 때까지 반복

	return 1;
}

/* 그래프 생성하는 함수 */
void initializeGraph(graphType* g)
{
    g->n= 0;    //정점개수 0으로 초기화
    
    for(int v=0;v<MAX_VERTEX;v++){
        g->adjList_H[v] = NULL; //그래프 정점에 대한 헤드포인터 배열 초기화
		g->visited[v] = 0;
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


    if(u>=g->n || v>=g->n){ //그래프에 정점 u와 v가 있는지 확인
        printf("그래프에 존재하지 않습니다\n");
        return;
    }

    node = (graphNode*)malloc(sizeof(graphNode)); //graphNode의 크기만큼 메모리 할당
    node->vertex = v; //node의 vertex에 v저장
    node->link=g->adjList_H[u]; //삽입간선에 대한 노드를 리스트의 첫번째 노드로 연결
    g->adjList_H[u] = node;
}

/* 그래프를 출력하는 함수 */
void printGraph(graphType*g)
{
    graphNode* p;

    for(int i=0;i<(g->n);i++){
        printf("\n\t\t 정점 %d의 인접리스트", i);
        p = g->adjList_H[i];
        while (p){
            printf("-> %d",p->vertex); //정점 출력
            p=p->link;
        }
    }
}

/* 메모리 할당 해제 함수 */
void freeGraph(graphType* g)
{
	free(g); //메모리 할당 해제
}

/* 스택이 비어있는지 체크하는 함수 */
int isStackEmpty(void)
{
	if (top == NULL) return 1; //비어있을경우 1반환
	else return 0;
}

/* 스택의 top에 값을 삽입하는 함수 */
void push(int item)
{
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode)); //stackNode의 크기만큼 메모리 할당
	temp->data = item;
	temp->link = top;
	top = temp;
}

/* 스택의 top에서 값을 삭제하는 연산 */
int pop(void)
{
	int item;
	stackNode* temp = top;

	if(isStackEmpty()){ //스택이 비었을 경우
		printf("\n\n 스택이 비었습니다. \n");
		return 0;
	}

	else {
		item = temp->data;
		top = temp->link; //top위치 이동
		free(temp); //삭제한 노드 메모리 반환
		return item; //삭제한 값 리턴
	}
}

/* 깊이 우선 탐색 함수 */
void dfs(graphType* g, int v)
{
	graphNode* w;
	top = NULL; //스택의 top설정
    push(v);    //정점v 스택에 푸시
	g->visited[v] = 1; //v를 방문했으므로 visited배열 1로 저장
	printf("%d",v);

	while(!isStackEmpty()){
		w=g->adjList_H[v]; //인접정점이 있는 동안 수행

		while(w){ //정점w를 방문하지 않았을 경우
			if(!g->visited[w->vertex]){
				push(w->vertex);		 //정점 w를 스택에 푸시
				g->visited[w->vertex]=1; //정점 w에 대해 1(방문)로 설정 
				printf("d",w->vertex);   //정점 출력
				v=w->vertex;
				w=g->adjList_H[v];
			}

			else{ //이미 방문한 경우
				w = w->link;
			}
		}
        
		v=pop(); //현재 정점에서 더이상 순회할 정점이 없는 경우 pop

	} //스택이 공백일 경우 탐색 종료

}
