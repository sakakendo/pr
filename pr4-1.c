#include <stdio.h>
#include<stdlib.h> 
#include<string.h>
#define BUF_SIZE 32

int checksp(int c)
{
    if(c==' ' || c=='\t' || c=='\n') return 1;
	if('a'<=c && c<='z') return 2;
	if('A'<=c && c<='Z') return 2;
	if(c=='!') return 2;
    return 0;
}

void compress(char *s)
{
    char *p,*stmp=s,*tmp;
    int l;
    tmp=p=(char *)malloc(strlen(s));
    while( checksp(*s)==1 ){
      s++;
    }
    while(*s!='\0'){
    	if(checksp(*s)!=1 ){
    		*p++=*s;
    		//p++;    			
		}else{
			if(checksp(*(s+1))==2){
				*p++=*s;
			}
		}
      s++;
    }
    *p='\0';
	strcpy(stmp,tmp);
}


int main(void)
{
    char s[] = "     Nice to \n meet \t you    ,  Jack !\n     I'm      Mike \n\t\t .    ";

    printf("Before = \"%s\"\n",s);
    compress(s);

    printf("After  = \"%s\"\n",s);

    return 0;
}
