#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 10//�׷����� �ִ� ���� ��

typedef struct {//��������Ʈ�� ����Ʈ ���� �ص��带 ����
	int key;
	struct Node* link;
}Node;

void Initialize();//�ʱ�ȭ
int Insert_Vertex(int);//���� �߰�
int Insert_Edge(int, int);//���� �߰�
void DFS(int);//���̿켱Ž��
void BFS(int);//���̿켱Ž��
void Print_Graph();//�׷��� ���
void Quit();//���� �� ����
int ready(int );//Ž�� �غ�

/*���̿켱Ž���� ���� ť*/
Node* queue[MAX_VERTEX_NUM];
int front = -1;
int rear = -1;
Node* deQueue();
void enQueue(Node* aNode);

int vertex_num = 0;//������ ����
Node* head = NULL;//�׷��� ��ü�� �ص�
short int visit[MAX_VERTEX_NUM] = { 0 };//�湮 �÷���

int main()
{
	char command;
	int from, to, v,vertex;
	int initial = 0;//�ʱ�ȭ�� ����ƴ��� Ȯ���Ѵ�.

	printf("[------------------- [������] [2018038031] --------------------]\n");

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
			vertex_num = 0;//�ʱ�ȭ�� ����ȴٸ� ������ ���� 0���� �����.
			break;
		case 'q': case 'Q':
			if (initial)
				Quit();
			break;
		case 'v': case 'V':
			if (initial) {
				printf("���� �Էµ� ��ȣ : ");
				for(int i=0;i<MAX_VERTEX_NUM;i++)//���� �����ϴ� ������ ��ȣ���� ����Ѵ�.
					if(head[i].key==i)
						printf("[%d]  ",i);
				printf("\n");
				printf("�߰��� ������ ��ȣ�� �Է��Ͻÿ� :");
				fflush(stdout);
				scanf("%d", &vertex);//�߰��� ������ ��ȣ�� �Է¹޴´�.
				if (Insert_Vertex(vertex) == 0)//���� �߰��� �����Ѵٸ� ������ ���� +1�Ѵ�.
					vertex_num++;
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'e': case 'E':
			if (initial) {
				printf("������ ���� �� ������ �Է��ϼ���\n");
				fflush(stdout);
				scanf("%d %d", &from, &to);//������ ���� �� ������ �Է¹����Ŀ�
				Insert_Edge(from, to);//���������� ��ũ�� �����Ѵ�.
				Insert_Edge(to, from);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'd': case 'D':
			if (initial) {
				printf("���̿켱Ž���� ������ ������ �����ϼ���\n");
				fflush(stdout);
				scanf("%d", &v);//���̿켱Ž���� ������ ������ �Է¹޴´�.
				if(ready(v)==0)
					DFS(v);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'b': case 'B':
			if (initial) {
				printf("���̿켱Ž���� ������ ������ �����ϼ���\n");
				fflush(stdout);
				scanf("%d", &v);//���̿켱Ž���� ������ ������ �Է¹޴´�.
				BFS(v);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'p': case 'P':
			if (initial) {
				Print_Graph();
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 1;
}
void Print_Graph() {//�׷����� ����Ѵ�.
	Node* tmp = NULL;
	printf("������ ���� : %d\n", vertex_num);//������ ������ ����Ѵ�.
	for (int i = 0; i<MAX_VERTEX_NUM; i++) {//������ �ִ밳����ŭ �ݺ��Ѵ�.
		if(head[i].key==i){//i��ȣ�� ������ ������ �����Ѵٸ� ����Ѵ�.
			printf("[%d] : ", head[i].key);//������ ��ȣ�� ����Ѵ�.
			tmp = head[i].link;//i��ȣ�� ���� ������ �����ϴ� �������� ����ϱ����� ��ũ�� �ӽ÷� ����޴´�.
			for (; tmp; tmp = tmp->link)//�����ϴ� �������� ��� ����Ѵ�.
				printf("   [%d]", tmp->key);
			printf("\n");
		}

	}
}
void Initialize() {//�ʱ�ȭ
	if (head)//��������Ʈ �迭�� ��������ʴٸ� ����
		Quit();
	head = (Node*)malloc(sizeof(Node) * MAX_VERTEX_NUM);//head�� ��������Ʈ �迭���� �Ҵ�
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {//������ �߰��Ǿ����� �Ǵ��ϱ� ���� �ʱ�ȭ
		head[i].key = -1;
		head[i].link = NULL;
	}
}

int Insert_Vertex(int vertex) {//���� �߰�
	if (vertex >= MAX_VERTEX_NUM||vertex<0){//������ �ο��� �� �ִ� ��ȣ�� ���Ե��� �ʴ´ٸ� -1�� �����Ѵ�.
		printf("������ �ο��� �� �ִ� ��ȣ�� ���Ե��� �ʽ��ϴ�.\n");
		return -1;
	}
	if(head[vertex].key==vertex){//�̹� �߰��� �����̶�� �ȳ��޽��� ����� �����Ѵ�.
		printf("�̹� �����ϴ� �����Դϴ�.\n");
		return -1;
	}
	head[vertex].key = vertex;//�ִ� ������ ���� �ѱ����ʾҴٸ� �Է¹��� ��ȣ�� ������ �߰��Ѵ�.
	return 0;//����(0)�� �����Ѵ�.
}

int Insert_Edge(int from, int to) {//���� �߰� - Ž���� �ǽ��Ҷ� ��ȣ�� ���� �������� Ž���� �ϱ� ���� ������ ������������ ������������ �߰��Ѵ�.
	Node* new = NULL;//���� �߰��� �����̴�.
	Node* tmp = NULL;//
	Node* tmp_ = &head[from];//
	if (head[from].key == from && head[to].key == to) {//������� �������� ������ �����Ѵٸ� ������ �߰��Ѵ�.
		new = (Node*)malloc(sizeof(Node));//���� �߰��� ������ ������ �Ҵ�޴´�.
		new->key = to;
		new->link = NULL;
		if (head[from].link == NULL){//������� ������ ���������� 1���� ���ٸ� �ٷ� �ڿ� �����Ѵ�.
			head[from].link = new;
			return 0;
		}
		else {//1���̻� �����Ѵٸ� ������������ �߰��Ѵ�.
			tmp = head[from].link;
			while (tmp != NULL) {//���������� �˻��Ѵ�.
				if (to < tmp->key) {
					new->link = tmp;
					tmp_->link = new;
					return 0;
				}
				else if (to == tmp->key)//�̹� ���������� ������ �����Ѵٸ� �Լ��� �����Ѵ�.
					return 0;
				tmp_ = tmp;//�������� �̵��Ѵ�.
				tmp = tmp->link;
			}
			tmp_->link = new;//�������� ������ ��ȣ�� ���� ũ�ٸ� �������� �߰��Ѵ�.
			return 0;
		}
	}
	printf("�ش� ��ȣ�� ���� ������ �������� �ʽ��ϴ�.\n");//�����ߴٸ� �ȳ��޽����� ����Ѵ�.
	return -1;
}

void DFS(int v) {//���� �켱Ž��
	Node* tmp;
	visit[v] = 1;//ó������ ���� ������ �湮�÷��׸� set�Ѵ�.
	printf("%5d", head[v].key);//������ ��ȣ�� ����Ѵ�.
	for (tmp = head[v].link; tmp; tmp = tmp->link)//������ ��� ���������� �湮�Ѵ�.
		if (!visit[tmp->key])//���������� �湮���� ���� �����̶��
			DFS(tmp->key);//�湮�Ѵ�.
}

void BFS(int v) {//���� �켱Ž��
	Node* temp;
	rear = front = -1;//ť�� �ʱ�ȭ�Ѵ�.
	if(ready(v)==-1)
		return;

	enQueue(&head[v]);//���������� ��ť�Ѵ�.
	visit[v] = 1;//���������� �湮�÷��׸� set�Ѵ�.
	while (1) {
		temp = deQueue();//��ť�Ѵ�.
		if (!temp)//ť�� ����ٸ� �����Ѵ�.
			break;
		printf("%5d", temp->key);//��ť�� ������ ��ȣ�� ����Ѵ�.
		for (temp = temp->link; temp; temp = temp->link) //��ť�� ������ ���������� ��� �˻��Ѵ�.
			if (!visit[temp->key]) {//���������� �湮���� ���� �����̶��
				enQueue(&head[temp->key]);//��ť�ϰ�
				visit[temp->key] = 1;//�湮�÷��׸� set�Ѵ�.
			}

	}
}
Node* deQueue()//��ť
{
	if (front == rear)//ť�� ����ٸ�
		return NULL;//NULL ����
	else//�ƴ϶�� front ����
		return queue[++front];
}

void enQueue(Node* aNode)//��ť
{
	if (rear + 1 >= MAX_VERTEX_NUM)//ť�� ��á�ٸ�
		printf("ť�� ��á���ϴ�\n");//�ȳ��޽������
	else//�ƴ϶�� rear�� ����
		queue[++rear] = aNode;
}

void Quit() {//�ʱ�ȭ �� ����
	Node* tmp = NULL;
	Node* temp = NULL;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {//�߰��� ��� ������ ��������Ʈ�� �����Ѵ�.
		if(head[i].key==i){//i��ȣ�� ������ ������ �ִٸ�
			tmp = head[i].link;//���Ḯ��Ʈ�� �����Ѵ�.
			while (tmp) {
				temp = tmp;
				tmp = tmp->link;
				free(temp);
			}
		}
	}
	free(head);//�׷����� �ص带 �ʱ�ȭ�Ѵ�.
	head = NULL;
}

int ready(int v){
	if(head[v].key!=v){
		printf("�������� �ʴ� ��ȣ�� �����Դϴ�.\n");
		return -1;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++)//Ž���� �����ϱ� ���� �湮�÷��׹迭�� �ʱ�ȭ�Ѵ�.
		visit[i] = 0;
	return 0;
}
