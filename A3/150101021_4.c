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
void giveA(int* A,int s,int e){	int t=0;for(t=s;t<e;t++)give(A[t]);}

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
	
	if(num>=data)root->right=insert(num,root->right);//put duplicates into right trees
	
	else if(num<data)root->left=insert(num,root->left);

	return root; //return for above two cases
}



int maxHeight(nd* root){// this takes O(n) time
	if(root==NULL){return 0;} // empty tree.
	return 1+max(maxHeight(root->right),maxHeight(root->left));
}

void inorder(nd *root){
    if(root == NULL)return;

    inorder(root->left);//first prints left bottommost number
    give(root->data); //print data.
    inorder(root->right);
}

nd* makeTree(int A[],int n){
	nd* root=NULL; //empty tree.
	for(int i=0;i<n;i++){
		root=insert(A[i],root);
	}
	return root;
}
int diameter(nd * root)
{
   if (root == NULL)return 0; //empty tree
 
  //maxHeights of left and right sub-trees
  int leftMax = maxHeight(root->left); 			// this takes O(n) time
  int rightMax	 = maxHeight(root->right);	// this takes O(n) time
 
  // diameters of left and right sub-trees 
  int leftD = diameter(root->left);
  int rightD = diameter(root->right);
 
  // leftMax + rightMax + 1 is basically the length of the path joining bottom most elements of left & right subtrees.
  return max(leftMax + rightMax + 1, max(leftD, rightD));
} 



int main(){
	srand(time(NULL));
	int n=30;

	gives("\t\tQ4 : DIAMETER OF TREE (O(nlogn))\n");
	gives("Enter number of elements in tree : ");n=take();

	int A[n],u,v;
	randomInput(A,n,0);gives("\n"); //makes an random array.

	nd* root= makeTree(A,n);
	gives("Inorder :\t");	inorder(root);gives("\n");
	gives("Height of tree:\t");give(maxHeight(root));gives("\n");

clock_t begin = clock();
//RUNNING TIME FOR FINIDING DIAMETER
	gives("Diameter of tree:\t");give(diameter(root));gives("\n");

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
gives("\nRunning time (seconds) : "); printf("%f",time_spent);gives("\n");
	
	return 0;
}
