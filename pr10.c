#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define MAX_SIZE 13
#define TRUE     1
#define FALSE    0
#define IMAX     INT_MAX
        
/* データ（隣接行列） */
int adjacent[MAX_SIZE][MAX_SIZE] = {
        {   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // A: 東京
        {  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // B: 埼玉
        {IMAX,  90,   0,IMAX,IMAX, 110, 330,240,IMAX,IMAX,IMAX,IMAX,IMAX},      // C: 群馬
        {  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // D: 千葉
        {IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // E: 茨城
        {IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // F: 栃木
        {IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     // G: 福島
        {IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     // H: 新潟
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     // I: 山形
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     // J: 宮城
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // K: 秋田
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // L: 岩手
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // M: 青森
};

char *graph_data[] = {  // 上記隣接行列の0〜12番目の各要素に対応
        "Tokyo",
        "Saitama",
        "Gunma",
        "Chiba",
        "Ibaraki",
        "Tochigi",
        "Fukushima",
        "Niigata",
        "Yamagata",
        "Miyagi",
        "Akita",
        "Iwate",
        "Aomori"
};


int visited[MAX_SIZE];  /* 調べた頂点を記憶 */
int cost[MAX_SIZE];             /* コスト */
int prev[MAX_SIZE];             /* 直前の頂点 */

void print_path(void)
{
	int i=0;
	for(i=0;i<MAX_SIZE;i++)
		if(prev[i]!=-1)
			 printf("node:%10s prev:%10s cost %d\n",graph_data[i],graph_data[prev[i]],cost[i]);
}

void search(int start)
{
	int i,min=IMAX;
	visited[start]=TRUE;
	for(i=0;i<MAX_SIZE;i++){
		if(adjacent[start][i]!=IMAX && visited[i]==FALSE && cost[i]>adjacent[start][i]+cost[start]){
				cost[i]=adjacent[start][i]+cost[start];
				prev[i]=start;
		}
	}

	for(i=0;i<MAX_SIZE;i++)
		if(visited[i]==FALSE && cost[i]!=IMAX && (min==IMAX || cost[min]>cost[i]) )
				min=i;
	if(min!=IMAX) search(min);
}

int main(void)
{
	int i,j,
			departure,
			arrival,now;
	int path[MAX_SIZE];
	for( i = 0; i < MAX_SIZE; i++ ){
			visited[i] = FALSE;
			cost[i] = IMAX;
			path[i] = -1;
			prev[i]=-1;
	}

	for(i=0;i<MAX_SIZE;i++)
		printf("%d : %s\n",i,graph_data[i]);
	printf("enter depature:");
	scanf("%d",&departure);
	printf("enter arrival: ");
	scanf("%d",&arrival);
	printf("departure is %s,arrival is %s\n",graph_data[departure],graph_data[arrival]);

	cost[departure]=0;
	prev[departure]=0;
	search( departure );

	print_path();

	i=0;
	now=arrival;
	do{
		path[i++]=now;
		now=prev[now];
	}while(now!=departure);
	path[i++]=departure;

	while(i--!=0) printf("[%s]->",graph_data[path[i]]);
	printf(":cost=%d",cost[arrival]);
	return 0;
}
/*************************************************************************
0 : Tokyo
1 : Saitama
2 : Gunma
3 : Chiba
4 : Ibaraki
5 : Tochigi
6 : Fukushima
7 : Niigata
8 : Yamagata
9 : Miyagi
10 : Akita
11 : Iwate
12 : Aomori
enter depature:1
enter arrival: 10
departure is Saitama,arrival is Akita
node:     Tokyo prev:   Saitama cost 30
node:   Saitama prev:     Tokyo cost 0
node:     Gunma prev:   Saitama cost 90
node:     Chiba prev:   Saitama cost 60
node:   Ibaraki prev:   Saitama cost 140
node:   Tochigi prev:   Saitama cost 80
node: Fukushima prev:   Tochigi cost 250
node:   Niigata prev:     Gunma cost 330
node:  Yamagata prev: Fukushima cost 330
node:    Miyagi prev: Fukushima cost 340
node:     Akita prev:  Yamagata cost 520
node:     Iwate prev:    Miyagi cost 520
node:    Aomori prev:     Iwate cost 710
[Saitama]->[Tochigi]->[Fukushima]->[Yamagata]->[Akita]->:cost=520

****************************************************************************/
