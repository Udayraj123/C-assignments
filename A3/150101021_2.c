//Name - Udayraj Deshmukh 
//Roll - 150101021
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Below are some Functions for Convenience.
void swap(int*a,int*b){int t=*b;*b=*a;*a=t;}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int take(){int a;  scanf("%d",&a);return a;}
void give(int a){printf("%2d ",a);}
void give2(int a){printf("%10d ",a);}
void gives(char* a){printf("%s ",a);}
void giveA(int* A,int s,int e){	int t=0;	for(t=s;t<e;t++)give(A[t]);}

void randomInput(int A[],int n,int show){//generates random numbers
	int t=0;
	for(t=0;t<n;t++)A[t]=random()%100; 			//for less space in terminal. remove if wanted.
	if(show){gives("  Random array - \t");giveA(A,0,n);gives("\n");}  	//print generated array.
}

typedef struct node{
int data;
struct node *left, *right;
}nd;

nd* createNode(int num){
	nd* node=(nd*)malloc(sizeof(nd));
	node->data=num;
	node->left=NULL;
	node->right=NULL;
return node;
}

nd* insert(int num,nd* root){
	if(root==NULL){root=createNode(num);return root;} //every insertion is done at a leafnode.
	
	int data=root->data;
	
	if(num>=data)root->right=insert(num,root->right);		//if given number is more than that of root, insert in right tree.
	
	else if(num<data)root->left=insert(num,root->left); //if given number is less than that of root, insert in left tree.

	return root; //return for above two cases
}

nd* makeTree(int A[],int n){
	nd* root=NULL; //empty tree.
	for(int i=0;i<n;i++){
		root=insert(A[i],root);  //insert each element
	}
	return root;
}

int countLeaves(nd* root){
	int t=0; //this will hold the value of number of leaves.
	if(root==NULL)return 0; // empty tree, no leaf
	else if(root->right==NULL && root->left ==NULL)return 1; // a node with both null => a leaf
	t+=countLeaves(root->right); //add right leaves
	t+=countLeaves(root->left);//add left leaves
	return t;
}

int main(){
	srand(time(NULL));

	int n=100,n2=50;
	gives("\t\tQ2 : COUNTING NUMBER OF LEAVES IN BINARY TREES\n");
	gives("Enter number of trees: ");n2=take();
	gives("Enter number of elements in each tree : ");n=take();
	int A[n];

gives(" S.N.   ");gives("leaves : \t");gives("\n");

	for(int k=0;k<n2;k++){
		randomInput(A,n,0);
		nd* root= makeTree(A,n);
		int leaves= countLeaves(root);
		give(k+1);give2(leaves); gives("\n");
	} 
	return 0;

}
