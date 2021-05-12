#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 10

typedef struct {
	int key;
	struct Node* link;
}Node;

void Initialize();
int Insert_Vertex(int vertex_num);
int Insert_Edge(int from, int to);
void DFS(int v);
void Print_Graph();

Node* head = NULL;
short int visit[MAX_VERTEX_NUM] = { 0 };

int main()
{
	char command;
	int vertex_num = 0;
	int from, to, v;
	int initial = 0;//초기화가 진행됐는지 확인한다.

	printf("[------------------ [서종원] [2018038031] -------------------]\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Grape     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			Initialize();
			initial++;
			break;
		case 'q': case 'Q':
			if (initial) {

			}
			break;
		case 'v': case 'V':
			if (initial) {
				if (Insert_Vertex(vertex_num)==0)
					vertex_num++;
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'e': case 'E':
			if (initial) {
				printf("간선을 이을 두 정점을 입력하세요\n");
				fflush(stdout);
				scanf("%d %d", &from, &to);
				Insert_Edge(from, to);
				Insert_Edge(to, from);
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'd': case 'D':
			if (initial) {
				printf("깊이우선탐색을 시작할 정점을 선택하세요\n");
				fflush(stdout);
				scanf("%d", &v);
				for (int i = 0; i < MAX_VERTEX_NUM; i++)
					visit[i] = 0;
				DFS(v);
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'b': case 'B':
			if (initial) {

			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'p': case 'P':
			if (initial) {
				Print_Graph();
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 1;
}
void Print_Graph() {
	Node* tmp = NULL;
	for (int i = 0; head[i].key != -1;i++) {
		printf("[%d] : ", head[i].key);
		tmp = head[i].link;
		for (; tmp; tmp = tmp->link)
			printf("   [%d]", tmp->key);
		printf("\n");
	}
}
void Initialize() {
	if (head) {//인접리스트 배열이 비어있지않다면 해제
		//해제
	}

	head = (Node*)malloc(sizeof(Node) * MAX_VERTEX_NUM);//head에 인접리스트 배열공간 할당
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {//초기화
		head[i].key = -1;
		head[i].link = NULL;
	}

}

int Insert_Vertex(int vertex_num) {

	if (vertex_num >= MAX_VERTEX_NUM)
		return -1;

	head[vertex_num].key = vertex_num;
	return 0;
}

int Insert_Edge(int from, int to) {
	Node* new = (Node*)malloc(sizeof(Node));
	Node* tmp = NULL;
	Node* tmp_ = head;
	if (head[from].key == from && head[to].key == to) {
		new->key = to;
		new->link = NULL;
		if (head[from].link == NULL)
			head[from].link = new;
		else {
			tmp = head[from].link;
			while (tmp) {
				if (to < tmp->key) {
					new->link = tmp;
					tmp_->link = new;
					return 0;
				}
				tmp_ = tmp;
				tmp = tmp->link;
			}
			tmp_->link = new;
			return 0;
		}
	}
	return -1;
}

void DFS(int v) {

	Node* tmp;
	visit[v] = 1;
	printf("%5d", head[v].key);
	for (tmp = head[v].link; tmp; tmp = tmp->link)
		if (!visit[tmp->key])
			DFS(tmp->key);
}
