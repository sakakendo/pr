#include<stdio.h>

#define TRUE            1
#define FALSE           0
#define MAX_SIZE        11

int adjacent[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE];
int open_list[MAX_SIZE]; /* ÉLÉÖÅ[ */

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


void init_graph(void)
{
	int i=0,j=0;

	for( i=0;i<MAX_SIZE;i++){
		while(*graph_data[i]!='\0'){
			adjacent[i][*graph_data[i]-'A']=1;
			graph_data[i]++;
		}
	}
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			printf("%d",adjacent[i][j]);
		}
		printf("\n");
	}

}

void init_queue(int *q)
{
	int i;
	for( i = 0; i < MAX_SIZE; i++ ){
		q[i] = -1;
	}
}

void print_queue(int *q)
{
	int i;
	printf("open_list = {");
	for( i = 0; i < MAX_SIZE; i++ )
		if( q[i] != -1 )
			printf("%c",q[i]+'A');
	printf("}\n");
}

int check_queue(int *q,int d)
{
	int i;
	for( i = 0; i < MAX_SIZE;i++ )
		if( q[i] == d ) return TRUE;
	return FALSE; 
}

void enqueue(int *q, int d)
{
	printf("searching ...%c\n",d+'A');
	while(*q!=-1) q++;
	*q=d;
	
}

int dequeue(int *q)
{
	while(*q!=-1){
		*q=*(q+1);
		q++;
	}
}

void search(int now, int end)
{
	int i=0,j=0;
	enqueue(open_list,now);
	print_queue(open_list);
	visited[now]=1;

	while(check_queue(open_list,end)==FALSE){
		now=open_list[0];
		dequeue(open_list);
		for(i=0;i<MAX_SIZE;i++){
			if(adjacent[now][i]==1 && visited[i]!=1){
				enqueue(open_list,i);
				print_queue(open_list);
				visited[i]=1;

			}
		}
	}
	printf("Found.\n");

}

int main(void)
{
	init_graph();
	init_queue(open_list);
	search(0, 10 );         /* A Ç©ÇÁ K ÇÃåoòH */
	return 0;
}
