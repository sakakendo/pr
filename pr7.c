#include <stdio.h>
#include <stdlib.h>>
#include <string.h>>
#define KEY_SIZE        8

struct tree{
        struct tree *left;
        int no;
        struct tree *right;
};

/* 数値の入力用関数 */
int get_num(void) {
        int  i;
        int  d = 0;
        int  c = 0;
        rewind(stdin);
        for( i = 0; i < 5 && c != '\n' ; i++ ){ /* 5ケタまで */
         c = getchar();
         if ( c == '\n' ) break;
         d = d * 10 + c - '0';
        }
        rewind(stdin);
        return d;
}

/* ノードの追加 */
struct tree *add_node(int num) {
         struct tree *p;
         p = (struct tree *)malloc(sizeof(struct tree));
         p->left = NULL;
         p->no = num;
         p->right = NULL;
         return p;
}

/* ツリーの作成 */
struct tree *make_tree(struct tree *node, int num) {
         if( node == NULL ){
                 node = add_node(num);
                 return node;
         }
         if ( num > node->no )
                 node->left = make_tree(node->left,num);
         if ( num < node->no )
                 node->right = make_tree(node->right,num);
          return node;
}

/* ツリーの表示 */
void print_tree(struct tree *node) {
         int i;
         static int depth = 0;
          if( node->left != NULL ){
                 depth ++;
                 print_tree(node->left);
                 depth --;
         }
          for( i = 0; i < depth; i++ )
                 printf("\t");
         printf("[%2d]\n",node->no);
          if( node->right != NULL){
                 depth ++;
                 print_tree(node->right);
                 depth --;
         }
}

/* ツリーの探索関数 search を実装 */
void search(struct tree *node,int num){
	if(num>node->no){
		printf("[%d]->",node->no);
		if(node->left ==NULL){
			printf("%d not found",num);	
			exit(1);
		}
		search(node->left,num);
	}else if(num<node->no){
		printf("[%d]->",node->no);
		if(node->right ==NULL){
			printf("%d not found",num);	
			exit(1);
		}
		search(node->right,num);
	}else{
		printf("[%d]\n",node->no);
	}
	
}

int main(void) {
        struct tree *root;
        int i, num;
		char mode[128];
        char c[] = "";
        
        for( i = 0; i < KEY_SIZE; i++ ){
                printf("%d> ",i+1);
                num = get_num();
                if( i == 0 ){
                        root = make_tree(NULL,num);
                }
                else{
                        make_tree(root,num);
                }
        }
        print_tree(root);
        
        /* キー入力により実行が停止されるまで、探索キーの
         * 入力と探索、結果の表示を繰り返す
         */
        while(1){
        	printf("Do you wanna continue(yes/no)?");
        	scanf("%s",mode);
        	if(strcmp(mode,"yes")==0){
				printf("key>");
				num=get_num();
				search(root,num);
			}else{
				printf("end");
				exit(1);
			}
	
		}

        return 0;
}
