#include <stdio.h>
#define MAX_VERTEX_NUM 10

typedef struct{
	int edge;
	struct Node* link;
}Node;

typedef struct{
	int vertex;
	struct Node* link;
}Head;

Node* Initialize();

int main()
{
	char command;
	int vertx_num=0;
	int initial = 0;//초기화가 진행됐는지 확인한다.
	Head* head=NULL;
	printf("[----------------------- [서종원] [2018038031] -----]\n");

	do{
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

		switch(command) {
		case 'z': case 'Z':
			head=Initialize();
			initial++;
			break;
		case 'q': case 'Q':
			if(initial){

			}
			break;
		case 'v': case 'V':
			if(initial){
			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'e': case 'E':
			if(initial){

			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'd': case 'D':
			if(initial){

			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'b': case 'B':
			if(initial){

			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		case 'p': case 'P':
			if(initial){

			}
			else
				printf("초기화를 먼저 실행해주세요\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

void Initialize(Head** head){
	head*=(Head*)malloc(sizeof(Head)*MAX_VERTEX_NUM);
	for(int i=0;i<MAX_VERTEX_NUM;i++){
		head[i]->vertex=0;
		head[i]->link=NULL;
	}
}

int Insert_Vertex(Head* head,int vertex_num){

	if(vertex_num>=MAX_VERTEX_NUM)
		return -1;

	head[vertex_num].vertex=vertex_num;
	return 0;
}
int Insert_Edge(Head* head,int from,int to){
	Node* new=(Node*)malloc(sizeof(Node));
	Node* tmp=NULL;
	if(head[from]==from&&head[to]==to){
		new->edge=to;
		new->link=NULL;
		if(!head[from].link)
			head[from].link=new;
		else
		tmp=head[from].link;
		while(tmp->link)
			tmp=tmp->link;
		tmp->link=new;
		return 0;
	}
	else
		return -1;

}
