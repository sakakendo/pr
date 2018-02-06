#include<stdio.h>
#include<stdlib.h>

	int size[] = {2, 3, 5, 7, 9, 15};
	int value[] = {2, 4, 7, 11, 14, 24};
	#define AS (sizeof(size)/sizeof(size[0]))
	#define MAX_M   200

void DynamicProgramming(int N, int Nsize[], int Nvalue[]){
	int i,j;
	int total[MAX_M];
	int choice[MAX_M];
	int repack_total;
	for(i=0;i<=N;i++){
			total[i] = 0;
			choice[i] = -1;
	}
	for(i=0;i<AS;i++){
		printf("i = %d\n",i);
		printf("choice = ");
		for(j=0;j<N;j++)
			if(j>=Nsize[i]){ //when can j-Nsize[i]
				repack_total= total[j-Nsize[i]]+Nvalue[i];
				if(repack_total>total[j]){ //when resize is max
					total[j]=repack_total;
					choice[j]=i;
				}
			}
		for(j=0;j<N;j++)
			printf("%2d ",choice[j]);
		printf("\n");
	}
	printf("\ntotal value:%d\n",total[N-1]);
	while(N-1>=0 && choice[N-1]!=-1){
		printf("choice:%d value:%d\n",choice[N-1],Nvalue[choice[N-1]]);
		N-=Nsize[choice[N-1]];
	}
}

void error(){
	printf("InvalidNumber.\nEnter a number from 1 to 200");
	exit(1);
}

int main(int argc, char *argv[]){
        int m;
	if(argc==2) m = atoi(argv[1]);
	while(0>=m || m>=MAX_M){
		printf("InvalidNumber.\nEnter a number from 1 to 200 => ");
		scanf("%d",&m);
	}
        printf("Size of knapsack is %d\n",m);
        DynamicProgramming(m+1,size,value);
        return 0;
}
