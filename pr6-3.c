#include <stdio.h>
#include<stdlib.h>

#define ERROR    -1
#define HASH_SIZE  9
typedef struct character {
	int no;                         /* キー */
	char name[16];                  /* 名前 */
//	struct character *next_addr;    /* 次のデータのアドレス */
} CHARACTER;
CHARACTER *HashTable[HASH_SIZE];

/* 数値の入力用関数 */
int get_num(void)
{
	int  i;
	int  d = 0;
	int  c = 0;
	rewind(stdin);
	for( i = 0; i < 5 && c != '\n' ; i++ ) {
		/* 5ケタまで */
		c = getchar();
		if ( c == '\n' ) break;
		d = d * 10 + c - '0';
	}
	rewind(stdin);
	return d;
}

/* ハッシュ表からリスト構造で並んでいる様子を表示する */
void disp(void)
{
	int i = 0;
	struct character *current_addr;
	for( i = 0; i < HASH_SIZE; i++ ) {
		if(HashTable[i]!=NULL){
			printf("-|%d| %d| %s|-\n",i,HashTable[i]->no,HashTable[i]->name);
		}else{
			printf("-|%d| | |-\n",i);
		}
	}
}

/* ハッシュ値の計算 */
int hash(int h)
{
	return h % HASH_SIZE;
}

/* データの追加 */
void add(void)
{
	struct character *p=malloc(sizeof(struct character));
	int i, j,k=0;
	int h;
	/* 追加データのためのメモリを確保 */
	printf("NO＝");
	p->no = get_num();
	printf("名前＝");
	fgets(p->name,16,stdin);
	for( j=0; p->name[j] != '\n' && j != 15; j++ );
	p->name[j] = '\0';
	/* ↑改行コードを削除するための処理 */
	h = hash( p->no );

	while(HashTable[h]!=NULL) h=hash(p->no+(++k));
	if( HashTable[h] == NULL ) {
		HashTable[h]=p;
	}

	disp();
}

/* データの削除 */
int del(void)
{
	int i, h;
	struct character *current_addr,*head,*target,*before_addr;
	int point;
	disp();
	if(search()==ERROR){
		printf("NOT FOUND\n");
		return ERROR;
	}else{
		printf("DELETE SUCCEED\n");
		HashTable[h]=NULL;
	}
}

/* データの探索 */
int search(void)
{
	int i, h;
	struct character *current_addr,*head,*target;
	int point;
	printf("NO＝");
	point = get_num();
	h = hash(point);
	for(i=0;i<HASH_SIZE;i++){
		h = hash(point+i);
		if(HashTable[h]!=NULL && HashTable[h]->no==point){
			printf("found -|%d| %d| %s|-\n",h,HashTable[h]->no,HashTable[h]->name);
			return h;
		}
	}
	printf("NOT FOUND\n");
	return ERROR;
}


/* メニュー */
int menu(void)
{
	int c;
	while( 1 ) {
		printf("1.表\示\n");      // 課題5と同様の理由で，"表"と"示"の間に"\"を挿入
		printf("2.追加\n");
		printf("3.削除\n");
		printf("4.探索\n");
		printf("5.終了\n");
		c = get_num();
		if( c >= 1 && c <= 5 )  break;
		else                                    printf("1?5までの数字を入力してください\n");
	}
	switch( c ) {
		case 1:
			disp();
			break;
		case 2:
			add();
			break;
		case 3:
			del();
			break;
		case 4:
			search();
			break;
		case 5:
			return 1;
	}
	return 0;
}

int main(void)
{
	int i, end = 0;
	/* ハッシュ表を初期化 */
	for( i = 0; i < HASH_SIZE; i++ )
		HashTable[i] = NULL;
	while( !end ) {
		end = menu();
	}
	return 0;
}
