/* グラフ構造の深さ優先探索 */

#include<stdio.h>
#include <stdlib.h>
#define TRUE      1
#define FALSE     0
#define MAX_SIZE 11

typedef struct character{
        int  no;                        /* キー */
        char name;                      /* 名前 */
        struct character *next_addr;    /* 次のデータのアドレス */
}CELL;

char *graph_data[] = {
        "CI",           /* A : C I */
        "DGH",          /* B : D G H */
        "ADG",          /* C : A D G */
        "BCHIJ",        /* D : B C H I J */
        "FHJ",          /* E : F H J */
        "EGK",          /* F : E G K */
        "BCF",          /* G : B C F */
        "BDEJ",         /* H : B D E J */
        "AD",           /* I : A D */
        "DEHK",         /* J : D E H K */
        "FJ"            /* K : F J */
};

CELL *adjacent[MAX_SIZE]; /* 隣接リスト */
int visited[MAX_SIZE];
int path[MAX_SIZE];

/* リスト構造で並んでいる様子を表示する */
void disp(void) {
    CELL *current_addr;
	int i;
    printf("隣接リスト:\n");
    for( i = 0; i < MAX_SIZE; i++ ){
    	current_addr=adjacent[i];
    	while(current_addr!=NULL){
    		printf("-|%c|-",current_addr->name);
    		current_addr=current_addr->next_addr;
		}
		printf("\n");
    	
	}
}

void add(int parent, int child) {
        CELL *p;
        CELL *q;
         p = (CELL *)malloc(sizeof(CELL));
        p->no = child;
        p->name = 'A' + child;
        p->next_addr = NULL;
         q = adjacent[parent];
        while ( q->next_addr != NULL ) {
                q = q->next_addr;
        }
        q->next_addr = p;
}

void init_graph(void) {
    CELL *current_addr,*p;
	int i,j;
    for( i = 0; i < MAX_SIZE; i++ ){
    	p=(CELL*)malloc(sizeof(CELL));
    	p->no=i;
    	p->name='A'+i;
    	p->next_addr=NULL;
    	adjacent[i]=p;
	}
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;graph_data[i][j]!='\0';j++){
			add(i,graph_data[i][j]-'A');
		}
	}
}

void print_path(int num) {
        int i;
        for( i = 0; i <= num; i++ ){
                 printf("%c ", path[i] + 'A' );
        }
        printf("\n");
}

//depth-first search
 void search(int num, int now, int end) {

	 CELL *current;
	 current=adjacent[now];
	 visited[adjacent[now]->no]=1;
	 path[num]=current->no;
	 if(current->no ==end){
		 print_path(num);
		 visited[now]=0;
		 return ;
	 }
	 while((current=current->next_addr)!= NULL ){
		 if(visited[current->no]==0) search(num+1,current->no,end);
	 }
	 visited[now]=0;
}

//width-first search
void search_width(int num, int now, int end) {

	 CELL *current;
	 current=adjacent[now];
	 visited[adjacent[now]->no]=1;
	 path[num]=current->no;
	 if(current->no ==end){
		 print_path(num);
		 visited[now]=0;
		 return ;
	 }
	 while((current=current->next_addr)!= NULL ){
		 if(visited[current->no]==0) search(num+1,current->no,end);
	 }
	 visited[now]=0;
}

int main(void) {
        init_graph();
        disp();
        search( 0, 0, 10 );
        return 0;
}
