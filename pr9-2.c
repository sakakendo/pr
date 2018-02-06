#include<stdio.h>

#define TRUE            1
#define FALSE           0
#define MAX_SIZE        13

int visited[MAX_SIZE];
int depth[MAX_SIZE];
int open_list[MAX_SIZE]; /* キュー */

int adjacent[MAX_SIZE][MAX_SIZE] = {    /* 隣接行列 */
	{0,1,0,1,0,0,0,0,0,0,0,0,0},
	{1,0,1,1,1,1,0,0,0,0,0,0,0},
	{0,1,0,0,0,1,1,1,0,0,0,0,0},
	{1,1,0,0,1,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,1,1,0,0,0,0,0,0},
	{0,1,1,0,1,0,1,0,0,0,0,0,0},
	{0,0,1,0,1,1,0,1,1,1,0,0,0},
	{0,0,1,0,0,0,1,0,1,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,1,0,0},
	{0,0,0,0,0,0,1,0,1,0,1,1,0},
	{0,0,0,0,0,0,0,0,1,1,0,1,1},
	{0,0,0,0,0,0,0,0,0,1,1,0,1},
	{0,0,0,0,0,0,0,0,0,0,1,1,0}
};

char *graph_data[] = {  // 上記隣接行列の0?12番目の各要素に対応
	"  Tokyo  ",
	" Saitama ",
	"  Gunma  ",
	"  Chiba  ",
	" Ibaraki ",
	" Tochigi ",
	"Fukushima",
	" Niigata ",
	" Yamagata",
	"  Miyagi ",
	"  Akita  ",
	"  Iwate  ",
	" Aomori  "
};

/* グラフの表示 */
void disp(void)
{
	int h,i;

	printf("隣接行列：\n");
	for(h=0;h<MAX_SIZE;h++){
		for(i=0;i<MAX_SIZE;i++)
			printf("%d ",adjacent[h][i]);
		printf("\n");
	}
	printf("\n");
}

/* キューの初期化 */
void init_queue(int *q)
{
	int i;
	for( i = 0; i < MAX_SIZE; i++ ){
		q[i] = -1;
	}
}

void print_queue(int now,int *q)
{
	int i,j;
	for(j=0;j<15*(depth[q[i]]);j++) printf(" ");
	printf("[ %8s ]->[ %8s ](%d)\n",graph_data[now],graph_data[q[1]],depth[q[i]]);
//	printf("[ %8s ]->[ %8s ] (now:%d,q[i]:%d,i:%d)\n",graph_data[now],graph_data[q[1]],now,depth[q[i]],i);
//	printf("%s %d %d, %s %d %d\n",graph_data[now],now,depth[now],graph_data[i],i,depth[i]);
	/*
	for( i = 1; i < MAX_SIZE; i++ ){
		if( q[i] != -1 ){
			for(j=0;j<15*(depth[q[i]]-1);j++) printf(" ");
//			printf("[ %8s ]->[ %8s ] (now:%d,q[i]:%d,i:%d)\n",graph_data[now],graph_data[q[i]],now,depth[q[i]],i);
		}
	}
	*/
}
void enqueue(int *q, int d)
{
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

int check_queue(int *q,int d)
{
	int i;
	for( i = 0; i < MAX_SIZE;i++ )
		if( q[i] == d ) return TRUE;
	return FALSE; 
}

/* 経路の探索（幅優先探索） */
void search(int now, int end)
{
	int i=0,j=0;
	enqueue(open_list,now);
//	print_queue(depth[now],open_list);
	visited[now]=1;

	while(check_queue(open_list,end)==FALSE){
		now=open_list[0];
//		dequeue(open_list);
		for(i=0;i<MAX_SIZE;i++){
			if(adjacent[now][i]==1 && visited[i]!=1){
				enqueue(open_list,i);
//				dequeue(open_list);
				depth[i]=depth[now]+1;
//				printf("%s %d %d, %s %d %d\n",graph_data[now],now,depth[now],graph_data[i],i,depth[i]);
				print_queue(now,open_list);
//				print_queue(depth[i],open_list);
				visited[i]=1;
			}
		}
		dequeue(open_list);
//		print_queue(now,open_list);
	}
	printf("Found.\n");


}

/* メイン関数 */
int main(void)
{
	init_queue(open_list);
	disp();
	search(0, 12);         /* Tokyo から Aomori の経路 */
	return 0;
}
/*
隣接行列：
0 1 0 1 0 0 0 0 0 0 0 0 0 
1 0 1 1 1 1 0 0 0 0 0 0 0 
0 1 0 0 0 1 1 1 0 0 0 0 0 
1 1 0 0 1 0 0 0 0 0 0 0 0 
0 1 0 1 0 1 1 0 0 0 0 0 0 
0 1 1 0 1 0 1 0 0 0 0 0 0 
0 0 1 0 1 1 0 1 1 1 0 0 0 
0 0 1 0 0 0 1 0 1 0 0 0 0 
0 0 0 0 0 0 1 1 0 0 1 0 0 
0 0 0 0 0 0 1 0 1 0 1 1 0 
0 0 0 0 0 0 0 0 1 1 0 1 1 
0 0 0 0 0 0 0 0 0 1 1 0 1 
0 0 0 0 0 0 0 0 0 0 1 1 0 

[   Tokyo   ]->[  Saitama  ](0)
[   Tokyo   ]->[  Saitama  ](0)
               [  Saitama  ]->[   Chiba   ](1)
               [  Saitama  ]->[   Chiba   ](1)
               [  Saitama  ]->[   Chiba   ](1)
                              [   Gunma   ]->[  Ibaraki  ](2)
                              [   Gunma   ]->[  Ibaraki  ](2)
                                             [ Fukushima ]->[  Niigata  ](3)
                                             [ Fukushima ]->[  Niigata  ](3)
                                                            [  Yamagata ]->[   Miyagi  ](4)
                                                            [   Miyagi  ]->[   Akita   ](4)
                                                                           [   Akita   ]->[   Iwate   ](5)
Found.
*/
