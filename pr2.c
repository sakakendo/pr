
#include <stdio.h>
#include<string.h>
#define BF 1
#define KMP 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

int brute_force_search(char text[], char pattern[])
{
    int i,t=0,p=0,tmp=0;
      do{
        printf("%c",pattern[p]);
        if(text[t+tmp]==pattern[p]){
          tmp++;
          p++;
          if(p==strlen(pattern)){
            printf("---success\n");
            return t;
          }
        }else{
          t++;
          p=tmp=0;
          printf("--failed\n");
      for(i=0;i<t;i++) printf(" ");
        }
      }while(1);
}

void init_next(char pattern[])
{
  int i,j,k,m;
  for(i=0;i<strlen(pattern);i++){
    next[i]=1;
  }
  for (j = 0; j < strlen(pattern); j++ ) {
    if ( j < 1 )
        next[j] = 1;
    else {
        for ( k = 1; k < j; k++ ) {
            for ( m = k; m < j && pattern[m] == pattern[m-k]; m++ ) ;
            if ( m == j )
                break;
        }
        next[j] = k;
    }
}
}

int kmp_search(char text[], char pattern[])
{
    int i,t=0,p=0,tmp=0;
      for(i=0;i<t;i++) printf(" ");
      do{
        printf("%c",pattern[p]);
        if(text[t+tmp]==pattern[p]){
          tmp++;
          p++;
          if(p==strlen(pattern)){
            printf("---success\n");
            return t;
          }
        }else{
          t+=next[p];
          p=tmp=0;
          printf("--failed\n");
          for(i=0;i<t;i++) printf(" ");
        }
      }while(1);
}

int main(void)
{
    char text[TEXT_LENGTH+1];
    char pattern[PATN_LENGTH+1];
    int position,i,j;
    char *strings[]={
        "xxxtartartayx",
        "tartay",
        "pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko",
        "pyokopyokomu"
    };
    for(i=0;i<2;i++){
      strcpy(text,strings[i*2]);
      strcpy(pattern,strings[i*2+1]);
      printf("text : %s pattern : %s\n",text,pattern);
#if BF
      printf("--- B F ---\n");
      printf("%s\n",text);
      position = brute_force_search(text, pattern);
      printf("position=%d\n",position);
#endif

#if KMP
      printf("--- KMP ---\n");
      init_next(pattern);
      for(j=0;j<strlen(pattern);j++){
        printf("%c: next[%2d] = %d\n",pattern[j],j,next[j]);
      }
      printf("%s\n",text);
      position = kmp_search(text, pattern);
      printf("position=%d\n",position);
#endif
    }
    return 0;
}


/***********************************************
text : xxxtartartayx pattern : tartay
--- B F ---
xxxtartartayx
t--failed
 t--failed
  t--failed
   tartay--failed
    t--failed
     t--failed
      tartay---success
position=6
--- KMP ---
t: next[ 0] = 1
a: next[ 1] = 1
r: next[ 2] = 2
t: next[ 3] = 3
a: next[ 4] = 3
y: next[ 5] = 3
xxxtartartayx
t--failed
 t--failed
  t--failed
   tartay--failed
      tartay---success
position=6
text : pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko pattern : pyokopyokomu
--- B F ---
pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko
pyokopyokomu--failed
 p--failed
  p--failed
   p--failed
    p--failed
     pyokop--failed
      p--failed
       p--failed
        p--failed
         p--failed
          p--failed
           p--failed
            pyokopyokomu--failed
             p--failed
              p--failed
               p--failed
                p--failed
                 pyokop--failed
                  p--failed
                   p--failed
                    p--failed
                     p--failed
                      p--failed
                       p--failed
                        pyokopyokom--failed
                         p--failed
                          p--failed
                           p--failed
                            p--failed
                             pyokopyokom--failed
                              p--failed
                               p--failed
                                p--failed
                                 p--failed
                                  pyokopyokomu---success
position=34
--- KMP ---
p: next[ 0] = 1
y: next[ 1] = 1
o: next[ 2] = 2
k: next[ 3] = 3
o: next[ 4] = 4
p: next[ 5] = 5
y: next[ 6] = 5
o: next[ 7] = 5
k: next[ 8] = 5
o: next[ 9] = 5
m: next[10] = 5
u: next[11] = 11
pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko
pyokopyokomu--failed
           p--failed
            pyokopyokomu--failed
                       p--failed
                        pyokopyokom--failed
                             pyokopyokom--failed
                                  pyokopyokomu---success
position=34
***********************************************/
