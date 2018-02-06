
#include <stdio.h>
#include<string.h>
#define BF 1
#define KMP 1
#define BM 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 256
int next[PATN_LENGTH];
int skip[PATN_LENGTH];

#define uchar unsigned char
#define max(a,b) ((a)>(b)?a:b)

int brute_force_search(char text[], char pattern[])
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
          t++;
          p=tmp=0;
          printf("--failed\n");
      for( i=0;i<t;i++) printf(" ");
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

void init_skip(uchar pattern[])
{
	int i,patn_len;
  patn_len=strlen(pattern);
  for( i = 0; i < 256; i++ )
  skip[i] = patn_len;
  for( i = 0; i < patn_len; i++ ){
    skip[pattern[i]] = patn_len - i - 1;
  }
  for( i = 0; i < patn_len; i++ ){
    printf("pattern[%2d] skip[%c(%d)]=%2d\n",i,pattern[i],pattern[i],skip[pattern[i]]);
  }
}


int bm_search(uchar text[], uchar pattern[]) {
  int i,j,text_len,patn_len,tmp;
  text_len=strlen(text);
  patn_len=strlen(pattern);
  i=0;
  tmp=strlen(pattern)-1;
  while(1){
    for(j=0;j<i+tmp;j++) printf(" ");
    printf("%c",pattern[tmp]);
    if(text[i+tmp]==pattern[tmp]){
      if(tmp==0){
        printf("--success\n");
        return i;
      }
      tmp--;
    }else{
      printf("--failure");
      if(i==strlen(text)-strlen(pattern)) return -1;
//      printf("%d %c %d",skip[text[i+tmp]],strlen(pattern)-tmp);
//      i+=skip[text[i+tmp]];
      i+=max(skip[text[i+tmp]],strlen(pattern)-tmp);
      tmp=strlen(pattern)-1;
    }
    printf("\n");
  }
}

int main(void)
{
    char text[TEXT_LENGTH+1];
    char pattern[PATN_LENGTH+1];
    int position,i,j;
    char *strings[]={
        "aabbabcabc",
        "abcab",
        "pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko",
        "pyokopyokomu",
        "xxxtartartayx",
        "tartay"
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


#if BM
    printf("--- B M ---\n");
    init_skip(pattern);
    printf("%s\n",text);
    position = bm_search(text, pattern);
    printf("position=%d\n",position);
#endif

    }
    return 0;
}


/***********************************************
text : aabbabcabc pattern : abcab
--- B F ---
aabbabcabc
ab--failed
 abc--failed
  a--failed
   a--failed
    abcab---success
position=4
--- KMP ---
a: next[ 0] = 1
b: next[ 1] = 1
c: next[ 2] = 2
a: next[ 3] = 3
b: next[ 4] = 3
aabbabcabc
ab--failed
 abc--failed
   a--failed
    abcab---success
position=4
--- B M ---
pattern[ 0] skip[a(97)]= 1
pattern[ 1] skip[b(98)]= 0
pattern[ 2] skip[c(99)]= 2
pattern[ 3] skip[a(97)]= 1
pattern[ 4] skip[b(98)]= 0
aabbabcabc
    b--failure
     b
    a
   c--failure
        b
       a
      c
     b
    a--success
position=4
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
--- B M ---
pattern[ 0] skip[p(112)]= 6
pattern[ 1] skip[y(121)]= 5
pattern[ 2] skip[o(111)]= 2
pattern[ 3] skip[k(107)]= 3
pattern[ 4] skip[o(111)]= 2
pattern[ 5] skip[p(112)]= 6
pattern[ 6] skip[y(121)]= 5
pattern[ 7] skip[o(111)]= 2
pattern[ 8] skip[k(107)]= 3
pattern[ 9] skip[o(111)]= 2
pattern[10] skip[m(109)]= 1
pattern[11] skip[u(117)]= 0
pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko
           u--failure
                       u--failure
                                   u--failure
                                        u--failure
                                             u
                                            m
                                           o
                                          k
                                         o
                                        y
                                       p
                                      o
                                     k
                                    o
                                   y
                                  p--success
position=34
***********************************************/
