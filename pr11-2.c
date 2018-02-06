#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define MAX_SIZE 13
#define TRUE     1
#define FALSE    0
#define IMAX     10000

int adjacent[MAX_SIZE][MAX_SIZE] = {
        {   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  0: 東京
        {  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  1: 埼玉
        {IMAX,  90,   0,IMAX,IMAX, 110, 330,240,IMAX,IMAX,IMAX,IMAX,IMAX},      //  2: 群馬
        {  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  3: 千葉
        {IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  4: 茨城
        {IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  5: 栃木
        {IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     //  6: 福島
        {IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     //  7: 新潟
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     //  8: 山形
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     //  9: 宮城
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // 10: 秋田
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // 11: 岩手
        {IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // 12: 青森
};

char *graph_data[] = {
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


int d[MAX_SIZE][MAX_SIZE];
int pre_vertex[MAX_SIZE][MAX_SIZE];

void init(void)
{
    /* 実装せよ */
	int i,j;
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			d[i][j]=adjacent[i][j];
			pre_vertex[i][j]=i;
		}
	}
}

void search(void)
{
	int i,j,k;
	for(i=0;i<MAX_SIZE;i++){
		for(j=0;j<MAX_SIZE;j++){
			for(k=0;k<MAX_SIZE;k++){
				if(d[i][j]>d[i][k]+d[k][j]){
					d[i][j]=d[i][k]+d[k][j];
					pre_vertex[i][j]=pre_vertex[k][j];
				}
			}
		}
	}
	printf("%10s"," ");
	for(i=0;i<MAX_SIZE;i++)
		printf("%10s",graph_data[i]);
	printf("\n");
	for(i=0;i<MAX_SIZE;i++){
		printf("%10s",graph_data[i]);
		for(j=0;j<MAX_SIZE;j++){
			printf("%10d",d[i][j]);
		}
		printf("\n");
	}
}

void print_path2(int *route,int pos){
	while(pos>=0) printf("-| %s |-",graph_data[route[pos--]]);
}

int print_path(int p, int q)
{
    int x = q,cost=0;
	int pos=0,route[10];
    do{
		route[pos++]=x;
		cost+=d[x][pre_vertex[p][x]];
        x = pre_vertex[p][x];
    }while(x != p);
	route[pos]=x;
	print_path2(route,pos);
	return cost;
}

int name2num(char *name){
	int i;
	for(i=0;i<MAX_SIZE;i++)
		if(strcmp(name,graph_data[i])==0) return i;
	printf("都市名が存在しません．もう一度到着都市を入力して下さい． :");
	return -1;
}

int main(void)
{
	int i,j,d,a;
        int h,begin,end,flag;
        char start[10],destination[10];
    init();
    search();
	for(i=0;i<MAX_SIZE;i++) printf("%10s:",graph_data[i]);
	printf("\n");
	while(1){
		printf("出発都市を入力して下さい． : ");
		do{
			scanf("%s",start);
		}while((d=name2num(start)) ==-1);
		printf("到着都市を入力して下さい． : ");
		do{
			scanf("%s",destination);
		}while((a=name2num(destination)) ==-1 );
		printf("コストは%3dです．\n",print_path(d,a));
	}

    return 0;
}
/****************************************************************************************************************************************
$ gcc pr11-2.c  ;./a.out 
     Tokyo:   Saitama:     Gunma:     Chiba:   Ibaraki:   Tochigi: Fukushima:   Niigata:  Yamagata:    Miyagi:     Akita:     Iwate:    Aomori:
出発都市を入力して下さい． : Tokyo
到着都市を入力して下さい． : Fukushima
-| Tokyo |--| Saitama |--| Tochigi |--| Fukushima |-コストは280です．
出発都市を入力して下さい． : Tokyo
到着都市を入力して下さい． : Aomori
-| Tokyo |--| Saitama |--| Tochigi |--| Fukushima |--| Miyagi |--| Iwate |--| Aomori |-コストは740です．
出発都市を入力して下さい． : Fukushima
到着都市を入力して下さい． : Iwate
-| Fukushima |--| Miyagi |--| Iwate |-コストは270です
****************************************************************************************************************************************/

/***************************************************************************************************************************************
 * graph_data
               Tokyo   Saitama     Gunma     Chiba   Ibaraki   Tochigi Fukushima   Niigata  Yamagata    Miyagi     Akita     Iwate    Aomori
     Tokyo         0        30       120        40       170       110       280       360       360       370       550       550       740
   Saitama        30         0        90        60       140        80       250       330       330       340       520       520       710
     Gunma       120        90         0       150       210       110       280       240       360       370       550       550       740
     Chiba        40        60       150         0       130       140       310       390       390       400       580       580       770
   Ibaraki       170       140       210       130         0       100       260       450       340       350       530       530       720
   Tochigi       110        80       110       140       100         0       170       350       250       260       440       440       630
 Fukushima       280       250       280       310       260       170         0       520        80        90       270       270       460
   Niigata       360       330       240       390       450       350       520         0       600       610       790       790       980
  Yamagata       360       330       360       390       340       250        80       600         0        60       190       240       430
    Miyagi       370       340       370       400       350       260        90       610        60         0       250       180       370
     Akita       550       520       550       580       530       440       270       790       190       250         0       110       300
     Iwate       550       520       550       580       530       440       270       790       240       180       110         0       190
    Aomori       740       710       740       770       720       630       460       980       430       370       300       190         0

***************************************************************************************************************************************/
