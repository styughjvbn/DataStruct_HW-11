#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 10//그래프의 최대 정점 수

typedef struct {//인접리스트의 리스트 노드와 해드노드를 구현
	int key;
	struct Node* link;
}Node;

void Initialize();//초기화
int Insert_Vertex(int);//정점 추가
int Insert_Edge(int, int);//간선 추가
void DFS(int);//깊이우선탐색
void BFS(int);//넓이우선탐색
void Print_Graph();//그래프 출력
void Quit();//해제 및 종료
int ready(int );//탐색 준비

/*넓이우선탐색을 위한 큐*/
Node* queue[MAX_VERTEX_NUM];
int front = -1;
int rear = -1;
Node* deQueue();
void enQueue(Node* aNode);

int vertex_num = 0;//정점의 개수
Node* head = NULL;//그래프 전체의 해드
short int visit[MAX_VERTEX_NUM] = { 0 };//방문 플래그

int main()
{
	char command;
	int from, to, v,vertex;
	int initial = 0;//초기화가 진행됐는지 확인한다.

	printf("[------------------- [서종원] [2018038031] --------------------]\n");

	do {
		printf("\n");
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
			vertex_num = 0;//초기화가 진행된다면 정점의 수를 0으로 만든다.
			break;
		case 'q': case 'Q':
			if (initial)
				Quit();
			break;
		case 'v': case 'V':
			if (initial) {
				printf("현재 입력된 번호 : ");
				for(int i=0;i<MAX_VERTEX_NUM;i++)//현재 존재하는 정점의 번호들을 출력한다.
					if(head[i].key==i)
						printf("[%d]  ",i);
				printf("\n");
				printf("추가할 정점의 번호를 입력하시오 :");
				fflush(stdout);
				scanf("%d", &vertex);//추가될 정점의 번호를 입력받는다.
				if (Insert_Vertex(vertex) == 0)//정점 추가가 성공한다면 정점의 수를 +1한다.
					vertex_num++;
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'e': case 'E':
			if (initial) {
				printf("간선을 이을 두 정점을 입력하세요\n");
				fflush(stdout);
				scanf("%d %d", &from, &to);//간선을 이을 두 정점을 입력받은후에
				Insert_Edge(from, to);//양쪽정점에 링크를 연결한다.
				Insert_Edge(to, from);
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'd': case 'D':
			if (initial) {
				printf("깊이우선탐색을 시작할 정점을 선택하세요\n");
				fflush(stdout);
				scanf("%d", &v);//깊이우선탐색을 시작할 정점을 입력받는다.
				if(ready(v)==0)
					DFS(v);
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'b': case 'B':
			if (initial) {
				printf("넓이우선탐색을 시작할 정점을 선택하세요\n");
				fflush(stdout);
				scanf("%d", &v);//넓이우선탐색을 시작할 정점을 입력받는다.
				BFS(v);
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
void Print_Graph() {//그래프를 출력한다.
	Node* tmp = NULL;
	printf("정점의 개수 : %d\n", vertex_num);//정점의 개수를 출력한다.
	for (int i = 0; i<MAX_VERTEX_NUM; i++) {//정점의 최대개수만큼 반복한다.
		if(head[i].key==i){//i번호를 가지는 정점이 존재한다면 출력한다.
			printf("[%d] : ", head[i].key);//정점의 번호를 출력한다.
			tmp = head[i].link;//i번호를 가진 정점에 인접하는 정점들을 출력하기위해 링크를 임시로 저장받는다.
			for (; tmp; tmp = tmp->link)//인접하는 정점들을 모두 출력한다.
				printf("   [%d]", tmp->key);
			printf("\n");
		}

	}
}
void Initialize() {//초기화
	if (head)//인접리스트 배열이 비어있지않다면 해제
		Quit();
	head = (Node*)malloc(sizeof(Node) * MAX_VERTEX_NUM);//head에 인접리스트 배열공간 할당
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {//정점이 추가되었는지 판단하기 위한 초기화
		head[i].key = -1;
		head[i].link = NULL;
	}
}

int Insert_Vertex(int vertex) {//정점 추가
	if (vertex >= MAX_VERTEX_NUM||vertex<0){//정점에 부여될 수 있는 번호에 포함되지 않는다면 -1을 리턴한다.
		printf("정점에 부여될 수 있는 번호에 포함되지 않습니다.\n");
		return -1;
	}
	if(head[vertex].key==vertex){//이미 추가된 정점이라면 안내메시지 출력후 종료한다.
		printf("이미 존재하는 정점입니다.\n");
		return -1;
	}
	head[vertex].key = vertex;//최대 정점의 수를 넘기지않았다면 입력받은 번호의 정점을 추가한다.
	return 0;//성공(0)을 리턴한다.
}

int Insert_Edge(int from, int to) {//간선 추가 - 탐색을 실시할때 번호가 작은 정점부터 탐색을 하기 위해 정점의 인접정점들을 오름차순으로 추가한다.
	Node* new = NULL;//새로 추가될 간선이다.
	Node* tmp = NULL;//
	Node* tmp_ = &head[from];//
	if (head[from].key == from && head[to].key == to) {//출발지와 목적지의 정점이 존재한다면 간선을 추가한다.
		new = (Node*)malloc(sizeof(Node));//새로 추가될 간선의 공간을 할당받는다.
		new->key = to;
		new->link = NULL;
		if (head[from].link == NULL){//출발지의 정점의 인접정점이 1개도 없다면 바로 뒤에 연결한다.
			head[from].link = new;
			return 0;
		}
		else {//1개이상 존재한다면 오름차순으로 추가한다.
			tmp = head[from].link;
			while (tmp != NULL) {//마지막까지 검사한다.
				if (to < tmp->key) {
					new->link = tmp;
					tmp_->link = new;
					return 0;
				}
				else if (to == tmp->key)//이미 목적지와의 간선이 존재한다면 함수를 종료한다.
					return 0;
				tmp_ = tmp;//다음으로 이동한다.
				tmp = tmp->link;
			}
			tmp_->link = new;//목적지의 정점의 번호가 제일 크다면 마지막에 추가한다.
			return 0;
		}
	}
	printf("해당 번호를 가진 정점이 존재하지 않습니다.\n");//실패했다면 안내메시지를 출력한다.
	return -1;
}

void DFS(int v) {//깊이 우선탐색
	Node* tmp;
	visit[v] = 1;//처음으로 받은 정점의 방문플래그를 set한다.
	printf("%5d", head[v].key);//정점의 번호를 출력한다.
	for (tmp = head[v].link; tmp; tmp = tmp->link)//정점의 모든 인접정점을 방문한다.
		if (!visit[tmp->key])//인접정점이 방문되지 않은 정점이라면
			DFS(tmp->key);//방문한다.
}

void BFS(int v) {//넓이 우선탐색
	Node* temp;
	rear = front = -1;//큐를 초기화한다.
	if(ready(v)==-1)
		return;

	enQueue(&head[v]);//시작정점을 인큐한다.
	visit[v] = 1;//시작정점의 방문플래그를 set한다.
	while (1) {
		temp = deQueue();//디큐한다.
		if (!temp)//큐가 비었다면 종료한다.
			break;
		printf("%5d", temp->key);//디큐한 정점의 번호를 출력한다.
		for (temp = temp->link; temp; temp = temp->link) //디큐한 정점의 인접정점을 모두 검사한다.
			if (!visit[temp->key]) {//인접정점이 방문되지 않은 정점이라면
				enQueue(&head[temp->key]);//인큐하고
				visit[temp->key] = 1;//방문플래그를 set한다.
			}

	}
}
Node* deQueue()//디큐
{
	if (front == rear)//큐가 비었다면
		return NULL;//NULL 리턴
	else//아니라면 front 리턴
		return queue[++front];
}

void enQueue(Node* aNode)//인큐
{
	if (rear + 1 >= MAX_VERTEX_NUM)//큐가 꽉찼다면
		printf("큐가 꽉찼습니다\n");//안내메시지출력
	else//아니라면 rear에 저장
		queue[++rear] = aNode;
}

void Quit() {//초기화 및 해제
	Node* tmp = NULL;
	Node* temp = NULL;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {//추가된 모든 정점의 인접리스트를 해제한다.
		if(head[i].key==i){//i번호를 가지는 정점이 있다면
			tmp = head[i].link;//연결리스트를 해제한다.
			while (tmp) {
				temp = tmp;
				tmp = tmp->link;
				free(temp);
			}
		}
	}
	free(head);//그래프의 해드를 초기화한다.
	head = NULL;
}

int ready(int v){
	if(head[v].key!=v){
		printf("존재하지 않는 번호의 정점입니다.\n");
		return -1;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++)//탐색을 시작하기 전에 방문플래그배열을 초기화한다.
		visit[i] = 0;
	return 0;
}
