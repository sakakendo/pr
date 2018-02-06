#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 32

/***
®”‚¶‚á‚È‚¢‚Æ‚«‚Í-1‚ª•\¦‚³‚ê‚é‚æ‚¤‚É‚È‚Á‚Ä‚¢‚é 
***/

int str2int(char *str) {
	int n=0,i,x=1;
	char *head=str;
//	printf("str2int %s length %d\n",str,strlen(str));
	for(i=0;i<strlen(head);i++){
		str--;
//		printf("%c",*(str+strlen(head)));
		if(*(str+strlen(head))<'0' || '9'<*((str)+strlen(str))) return -1;
		if('a' <= *(str+strlen(head)) &&  *((str)+strlen(str))<='z') return -1;
		if('A' <= *(str+strlen(head)) &&  *((str)+strlen(str))<='Z') return -1;
		n+=(*((str)+strlen(head))-'0')*x;
		x*=10;
	}
	return n;

}
int get_num2(int *a, int *b)
{
	char *buf= (char*)malloc(BUF_SIZE+1);
	fgets(buf, BUF_SIZE, stdin);
	*(buf+strlen(buf))='\0';
	char *tmp = (char*)malloc(strlen(buf)),*head;
	head = tmp;
	while(*buf!=' ')		*tmp++=*buf++;
	*tmp='\0';
	*a=str2int(head);
	head=tmp;
	buf++;
	while(*buf !='\n')   *tmp++=*buf++;
	*tmp='\0';
	*b=str2int(head++);
	if(*a == -1 && *b == -1) return 0;
	if(*a == -1 || *b == -1) return 1;
	return 2;


}


int main(void)
{
	int a, b, r;

	printf(">");
	r = get_num2(&a, &b);

	printf("a = %d, b = %d, r = %d\n", a, b, r);

	return 0;
}
