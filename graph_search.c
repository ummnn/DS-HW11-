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
}graphType;

void initialzeGraph(graphType* g);
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void printGraph(graphType* g);


/* �׷��� �����ϴ� �Լ� */
void initilaizeGraph(graphType* g)
{
    g->n= 0;    //�������� 0���� �ʱ�ȭ
    
    for(int v=0;v<MAX_VERTEX;v++){
        g->adjList_H[v] = NULL; //�׷��� ������ ���� ��������� �迭 �ʱ�ȭ
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


    if(u>=g->n || v>=g->n){ //�׷����� ������ u�� v�� �ִ��� Ȯ��
        printf("�׷����� �������� �ʽ��ϴ�\n");
        return;
    }

    node = (graphNode*)malloc(sizeof(graphNode)); //graphNode�� ũ�⸸ŭ �޸� �Ҵ�
    node->vertex = v; //node�� vertex�� v����
    node->link=g->adjList_H[u]; //���԰����� ���� ��带 ����Ʈ�� ù��° ���� ����
    g->adjList_H[u] = node;
}


void printGraph(graphType*g)
{
    graphNode* p;

    for(int i=0;i<(g->n);i++){
        printf("\n\t\t ���� %c�� ��������Ʈ", i);
        p = g->adjList_H[i];
        while (p){
            printf("-> %c",p->vertex); //���� ���
            p=p->link;
        }
    }
}

int main()
{
	printf("[----- [�̵���] [2019038027] -----]\n");
	char command; //��ɾ �����ϴ� ����
	int key;
    graphType* G = (graphType*)malloc(sizeof(graphType)); //�׷��� G

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
		scanf(" %c", &command); //command�� �Է¹޴´�

		switch(command) {
		case 'g': case 'G': //command�� z�� Z�� ��
			initializeGraph(G); //initializeBST�Լ� ����
			break;

		case 'i': case 'I': //command�� i�� I�� ��
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´�
			insertVertex(G, key); //insertVertex�Լ� ����
			break;
		
        case 'e': case 'E': //command�� e�� E�� ��
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´� 
			insertEdge(G, key, key); //insertEdge�Լ� ����
			break;

		case 'd': case 'D': //command�� d�� D�� ��
			dfs(); //dfs�Լ� ����
			break;
		
        case 'b': case 'B': //command�� b�� B�� ��
			bfs(); //bfs�Լ� ����
			break;

		case 'p': case 'P': //command�� p�� P�� ��
			printGraph(); //printStack�Լ� ����
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q�� Q�� ������ �ݺ�

	return 1;
}
