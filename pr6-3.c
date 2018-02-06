#include <stdio.h>
#include<stdlib.h>

#define ERROR    -1
#define HASH_SIZE  9
typedef struct character {
	int no;                         /* �L�[ */
	char name[16];                  /* ���O */
//	struct character *next_addr;    /* ���̃f�[�^�̃A�h���X */
} CHARACTER;
CHARACTER *HashTable[HASH_SIZE];

/* ���l�̓��͗p�֐� */
int get_num(void)
{
	int  i;
	int  d = 0;
	int  c = 0;
	rewind(stdin);
	for( i = 0; i < 5 && c != '\n' ; i++ ) {
		/* 5�P�^�܂� */
		c = getchar();
		if ( c == '\n' ) break;
		d = d * 10 + c - '0';
	}
	rewind(stdin);
	return d;
}

/* �n�b�V���\���烊�X�g�\���ŕ���ł���l�q��\������ */
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

/* �n�b�V���l�̌v�Z */
int hash(int h)
{
	return h % HASH_SIZE;
}

/* �f�[�^�̒ǉ� */
void add(void)
{
	struct character *p=malloc(sizeof(struct character));
	int i, j,k=0;
	int h;
	/* �ǉ��f�[�^�̂��߂̃��������m�� */
	printf("NO��");
	p->no = get_num();
	printf("���O��");
	fgets(p->name,16,stdin);
	for( j=0; p->name[j] != '\n' && j != 15; j++ );
	p->name[j] = '\0';
	/* �����s�R�[�h���폜���邽�߂̏��� */
	h = hash( p->no );

	while(HashTable[h]!=NULL) h=hash(p->no+(++k));
	if( HashTable[h] == NULL ) {
		HashTable[h]=p;
	}

	disp();
}

/* �f�[�^�̍폜 */
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

/* �f�[�^�̒T�� */
int search(void)
{
	int i, h;
	struct character *current_addr,*head,*target;
	int point;
	printf("NO��");
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


/* ���j���[ */
int menu(void)
{
	int c;
	while( 1 ) {
		printf("1.�\\��\n");      // �ۑ�5�Ɠ��l�̗��R�ŁC"�\"��"��"�̊Ԃ�"\"��}��
		printf("2.�ǉ�\n");
		printf("3.�폜\n");
		printf("4.�T��\n");
		printf("5.�I��\n");
		c = get_num();
		if( c >= 1 && c <= 5 )  break;
		else                                    printf("1?5�܂ł̐�������͂��Ă�������\n");
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
	/* �n�b�V���\�������� */
	for( i = 0; i < HASH_SIZE; i++ )
		HashTable[i] = NULL;
	while( !end ) {
		end = menu();
	}
	return 0;
}
