//2019038027 �̵���

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10 //�ִ�ũ��

typedef struct graphNode{ //��������Ʈ�� ��� ����ü
    int vertex;
    struct graphNode* link;
}graphNode;

typedef struct graphType{ //�׷��� ����ü 
    int n;
    graphNode* adjList_H[MAX_VERTEX]; //�׷��� ������ ���� ��������� �迭
	int visited[MAX_VERTEX]; //������ �湮�ߴ��� ǥ���ϴ� �迭
}graphType;

typedef struct stackNode{ //���� ����ü
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
	printf("[----- [�̵���] [2019038027] -----]\n");
	char command; //��ɾ �����ϴ� ����
	int u;
	int v;
    graphType* G = (graphType*)malloc(sizeof(graphType)); //�׷��� G

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
		scanf(" %c", &command); //command�� �Է¹޴´�

		switch(command) {
		case 'g': case 'G': //command�� g�� G�� ��
			initializeGraph(G); //initializeGraph�Լ� ����
			break;

		case 'i': case 'I': //command�� i�� I�� ��
			printf("������ �Է��ϼ��� = ");
			scanf("%d", u); //key�� �Է¹޴´�
			insertVertex(G, u); //insertVertex�Լ� ����
			break;
		
        case 'e': case 'E': //command�� e�� E�� ��
			printf("������ �Է��ϼ���= num,num: ");
			scanf("%d,%d", &u,&v ); //������ �Է¹޴´� 
			insertEdge(G, u, v); //insertEdge�Լ� ����
			break;

		case 'd': case 'D': //command�� d�� D�� ��
            printf("������ �Է��ϼ��� = ");
			scanf("%d", &v ); //������ �Է¹޴´� 
			dfs(G,v); //dfs�Լ� ����
			break;
		
        /*case 'b': case 'B': //command�� b�� B�� ��
			bfs(); //bfs�Լ� ����
			break;*/

		case 'p': case 'P': //command�� p�� P�� ��
			printGraph(G); //printGraph�Լ� ����
			break;
		
		case 'q': case 'Q': //command�� q�� Q�� ��
			freeGraph(G); //freeGraph�Լ� ����
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q�� Q�� ������ �ݺ�

	return 1;
}

/* �׷��� �����ϴ� �Լ� */
void initializeGraph(graphType* g)
{
    g->n= 0;    //�������� 0���� �ʱ�ȭ
    
    for(int v=0;v<MAX_VERTEX;v++){
        g->adjList_H[v] = NULL; //�׷��� ������ ���� ��������� �迭 �ʱ�ȭ
		g->visited[v] = 0;
    }
}

/* ������ �����ϴ� �Լ� */
void insertVertex(graphType* g, int v)
{
    if(((g->n)+1)>MAX_VERTEX){ //������ ���� �ִ������� ������ ũ�ٸ�
        printf("�׷��� ������ ���� �ʰ��Ͽ����ϴ�\n");
        return;
    }

    g->n++; //������ �� 1����
}

/* ������ �����ϴ� �Լ� */
void insertEdge(graphType* g, int u, int v)
{
    graphNode* node;


    if(u>=g->n || v>=g->n){ //�׷����� ���� u�� v�� �ִ��� Ȯ��
        printf("�׷����� �������� �ʽ��ϴ�\n");
        return;
    }

    node = (graphNode*)malloc(sizeof(graphNode)); //graphNode�� ũ�⸸ŭ �޸� �Ҵ�
    node->vertex = v; //node�� vertex�� v����
    node->link=g->adjList_H[u]; //���԰����� ���� ��带 ����Ʈ�� ù��° ���� ����
    g->adjList_H[u] = node;
}

/* �׷����� ����ϴ� �Լ� */
void printGraph(graphType*g)
{
    graphNode* p;

    for(int i=0;i<(g->n);i++){
        printf("\n\t\t ���� %d�� ��������Ʈ", i);
        p = g->adjList_H[i];
        while (p){
            printf("-> %d",p->vertex); //���� ���
            p=p->link;
        }
    }
}

/* �޸� �Ҵ� ���� �Լ� */
void freeGraph(graphType* g)
{
	free(g); //�޸� �Ҵ� ����
}

/* ������ ����ִ��� üũ�ϴ� �Լ� */
int isStackEmpty(void)
{
	if (top == NULL) return 1; //���������� 1��ȯ
	else return 0;
}

/* ������ top�� ���� �����ϴ� �Լ� */
void push(int item)
{
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode)); //stackNode�� ũ�⸸ŭ �޸� �Ҵ�
	temp->data = item;
	temp->link = top;
	top = temp;
}

/* ������ top���� ���� �����ϴ� ���� */
int pop(void)
{
	int item;
	stackNode* temp = top;

	if(isStackEmpty()){ //������ ����� ���
		printf("\n\n ������ ������ϴ�. \n");
		return 0;
	}

	else {
		item = temp->data;
		top = temp->link; //top��ġ �̵�
		free(temp); //������ ��� �޸� ��ȯ
		return item; //������ �� ����
	}
}

/* ���� �켱 Ž�� �Լ� */
void dfs(graphType* g, int v)
{
	graphNode* w;
	top = NULL; //������ top����
    push(v);    //����v ���ÿ� Ǫ��
	g->visited[v] = 1; //v�� �湮�����Ƿ� visited�迭 1�� ����
	printf("%d",v);

	while(!isStackEmpty()){
		w=g->adjList_H[v]; //���������� �ִ� ���� ����

		while(w){ //����w�� �湮���� �ʾ��� ���
			if(!g->visited[w->vertex]){
				push(w->vertex);		 //���� w�� ���ÿ� Ǫ��
				g->visited[w->vertex]=1; //���� w�� ���� 1(�湮)�� ���� 
				printf("d",w->vertex);   //���� ���
				v=w->vertex;
				w=g->adjList_H[v];
			}

			else{ //�̹� �湮�� ���
				w = w->link;
			}
		}
        
		v=pop(); //���� �������� ���̻� ��ȸ�� ������ ���� ��� pop

	} //������ ������ ��� Ž�� ����

}
