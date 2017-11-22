#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 0  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 0  /* 1:�ʏ�ŁC  0:�ԕ���   */
#define LOOP   1  /* 1:���[�v�ŁC0:�ċA��   */

#define N 30000

int l_search(int data[], int target)
{
    int i=0, count = 0;
#if NORMAL   /* �ʏ�� */
    for ( i = 0; i < N; i++ ){
        if ( target == data[i] ) {
            return i;
        }
	}

	return -1;
#else        /* �ԕ��� */
    data[N]=target;
    while(data[i]!=target){
	    i++; 
    }
//    printf("not found");
    if(i!=N) return i;

    return -1;
#endif
}

/* �N�C�b�N�\�[�g */
void quick(int n[],int left,int right){
  int kt,pib=left;
  int tmp;
  for(int k=left+1;k<=right;k++){
    if(n[k]<n[pib]){
      kt=k;
      while(kt!=pib && n[kt]<=n[pib] /*&& kt!=100*/){
        tmp=n[kt];
        n[kt]=n[kt-1];
        n[kt-1]=tmp;
        kt--;
      }
      pib++;
    }
  }
  if(left<pib) quick(n,left,pib-1);
  if(pib<right) quick(n,pib+1,right);
  return ;
}


/* �񕪒T�� */
int b_search(int data[], int low, int high, int target)
{
    int mid;

#if LOOP 
    while(1){
	    if(high<=low+2){
	    	return -1;	
		} 
		mid=(high-low)/2+low;

	    if(data[mid]>data[target]){
		    high=mid-1;
	    }else if(data[mid]<data[target]){
		    low=mid+1;
	    }else if(data[mid]==data[target]){
		    return mid;
	    }

    }

#else
    if(high<=low){
		return -1;	
	} 

    mid=(high-low)/2+low;
    if(data[mid]>data[target]){
	    b_search(data,low,mid-1,target);
    }else if(data[mid]<data[target]){
	    b_search(data,mid+1,high,target);
    }else if(data[mid]==data[target]){
//    	printf("found");
	    return mid;
    }
#endif
}

/* ���C�� */
int main(void)
{
    int a[N+1], i, target, work[N+1], index;
    double sec;
    clock_t passege0,passege;
    for( i = 0; i < N; i++ ) work[i] = rand() % N;
    

#if LINEAR
#else
    quick(work,0,N-1);
    for( i = 0; i < N; i++ ) printf("%d\n",work[i]);  
	getchar();  
#endif
	passege0 = clock();
    for( target = N/2-500; target < N/2+500; target++ ) {
#if LINEAR 
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 )
            printf("O\n");
        else
            printf("X\n");
    }
	passege = clock();
    sec = (double)(passege-passege0) / CLOCKS_PER_SEC;
    printf("\n %.3f\n",sec);
	printf("%d %d %d  %f\n",LINEAR,NORMAL,LOOP,sec);
/*	printf("\t%d\t%d\t%d\t%f\n",LINEAR,NORMAL,LOOP,sec);*/
    return 0;
}
