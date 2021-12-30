#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 100

typedef struct node{
    
    char NU;
    struct node *left;
    struct node *right;


}node;
void pre_order(node * root){
if (root==NULL){
  return;
}else{
  printf("%c" , root->NU);
  pre_order(root->left);
  pre_order(root->right);
} 
}
void post_order(node*root){
  if (root==NULL){
  return;
}else{
  post_order(root->left);
  post_order(root->right);
  printf("%c" , root->NU);
}
}
void in_order(node*root){
  if (root==NULL){
  return;
}else{
  in_order(root->left);
  printf("%c" , root->NU);
  in_order(root->right);
}
}
int push (char*s , char c , int*top , int size){
if(*top==size-1)
  return 0;
else {
  (*top)++;
  s[*top]=c;
  return 1;
}

}
char pop (char*s , int*top){
if(*top==-1)
return '%';
else {
  return s[(*top)--];
}
}
int isoperator(char k ){
  if(k=='+'|| k=='-'||k=='*'||k=='/' || k == 'P' || k == 'M'){
    return 1;
  }else {
    return 0;
  }

}
int order( char p){
  if(p=='+'|| p=='-'){
    return 1;
  }else{
    return 2;
  }
}
  void push_node(node**s ,int *top , int size,node* n  ){
    if (*top==size-1){
      return ;
    }else{
      s[++(*top)]=n;
    }
  }
  node* pop_node(node **s , int *top ){
    if(*top==-1){
      return NULL;
    }else {
      return s[(*top)--];
    }
  }


void in_to_post(char*infix , char*postfix){
int i=0;
int j=0;
int top=-1;
char o;
char temp_stack[MAX];
while (i<strlen(infix)){
  if(isdigit(infix[i])){
    postfix[j]=infix[i];
    j++;
    
  }else if (isoperator(infix[i])){
    if (top==-1){
      push(temp_stack , infix[i] , &top , strlen(infix));
    }
    else if(top != -1){
      
      while (top != -1 && order(infix[i]) <= order(temp_stack[top])){
        o=pop(temp_stack , &top);
        postfix[j]=o;
        j++;
      }
      push(temp_stack , infix[i], &top , strlen(infix));
    }

  }
  i++;
}

while (top!=-1){
  o=pop(temp_stack , &top);
        postfix[j]=o;
        j++;
}

postfix[j]='\0';

}
node* create_tree( char*postfix){
  int top=-1;
  node* stack[MAX],*right , *left;
  node *n;
  int i=0;
  while(i<strlen(postfix)){
    if(isdigit(postfix[i])){
      n=(node*)malloc(sizeof(node));
      n->NU=postfix[i];
      i++;
      push_node(stack , &top , strlen(postfix), n);
     
    }else if (isoperator(postfix[i])){
      n=(node*)malloc(sizeof(node));
      n->NU=postfix[i];
      right=pop_node(stack , &top);
      
      left=pop_node(stack , &top);
      n->left =left;
      n->right = right;
      push_node( stack , &top , strlen(postfix), n);
      i++;
    }
  }
  return stack[top];
}
int calculate_tree(node*root){
  int n1=0, n2=0;
  int x;
  if(root==NULL){
    return 0;
  }
  if (isdigit(root->NU)){
    
    
    return root->NU - '0';
  }
  n1=calculate_tree(root->left);
  n2=calculate_tree(root->right);
  
  switch(root->NU){
    case '+':
      return n1+n2;
    case '-':
      return n1-n2;
    case '*':
      return n1*n2;
    case '/':
      if (n2==0){
        printf("division by 0 : impossible");
      }else{
        return n1/n2;
      }
      

  }

  return 0;


}
void menu(void){
  printf("\n\t hello dear user \n\t");
  printf("\n\t 1. enter your in_order expression \n\t ");
  printf("\n\t 2. ino_rder expression  \n\t ");
  printf("\n\t 3. pre_order expression \n\t ");
  printf("\n\t 4. post_order expression \n\t ");
  printf("\n\t 5. compute your expression \n\t ");
  printf("\n\t 6.exit \n\t ");
}



int main(void){
  
int choice , i = 0 , r;
node* stack[MAX] , *root;
char infix[MAX] , postfix[MAX];


do {
  menu();
printf("input your choice : ");
scanf("%d" , &choice);
switch (choice){
  case 1:
  printf("\n\tenter your in_order expression \n\t ");
  scanf(" %[^\n]" , infix);
  while (i<strlen(infix)){
    if(infix[i]=='+' && infix[i-1]=='+')
        infix[i]='1';      
    else if(infix[i]=='-' && infix[i-1]=='-')
        infix[i]='1';
    
    i++;
  }
  /*
  */

 
 
  in_to_post(infix , postfix);
  
   
  root=create_tree(postfix);
  
    

  break;
  case 2:
  in_order(root);
  break;
 
  case 3:
  printf("\t\n the pre_order is : ");
  pre_order(root);
  break;
  
  case 4:
  printf("\t\n the post _order is : ");
  post_order(root);
  break;

  case 5:
  printf("\t\n the result is : ");
  r=calculate_tree(root);
  printf("%d" , r);
  break;
  case 6:
  printf("thank you dear user ");
  break;
  default :
  printf("please enter a valid input");
}


}while (choice!=6);

return 0;
}


