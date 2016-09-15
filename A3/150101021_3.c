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
	
	if(num>data)root->right=insert(num,root->right); //HANDLE ONLY UNIQUE RANDOM NUMBERS
	
	else if(num<data)root->left=insert(num,root->left);

	return root; //return for above two cases
}

nd* makeTree(int A[],int n){
	nd* root=NULL; //empty tree.
	for(int i=0;i<n;i++){
		root=insert(A[i],root);
	}
	return root;
}

//Since only one node per level is traveresed, this is an O(logn) algorithm.
nd *findLCA(nd* root, int n1, int n2)
{
    if (root == NULL) return NULL;

    
    // If both n1 and n2 are smaller than root, then LCA lies in left
   if (root->data > n1 && root->data > n2)return findLCA(root->left, n1, n2); 
    
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2)return findLCA(root->right, n1, n2);

    return root;
}
 

void inorderPrint(nd *root){
    if(root == NULL)return;

    inorderPrint(root->left);//first print left bottommost number
    give(root->data);
    inorderPrint(root->right);
}


int main(){
	srand(time(NULL));
	int n=30;

	gives("\t\tQ3 : FINDING LCA OF NODES u AND v - O(logn) method\n");
	gives("Enter number of elements in tree : ");n=take();
	
	int A[n],u,v;
	randomInput(A,n,0);gives("\n");
//menu-	
	nd* root= makeTree(A,n);
	gives("Inorder print(distinct) :\t");	inorderPrint(root);gives("\n");
	nd* root2=root;

	gives("References: \n");
	gives("Leftmost branch: ");while(root2!=NULL){give2(root2->data);root2=root2->left;} //THESE ARE PRINTED FOR REFERENCE
	gives("\n");
	
	root2=root;
	gives("Rightmost branch: ");	while(root2!=NULL){give2(root2->data);root2=root2->right;}//THESE ARE PRINTED FOR REFERENCE
	gives("\n");
	
	gives("Enter two nodes u & v from the tree- ");u=take();v=take();
	u>v?swap(&u,&v):1; //make u < v

clock_t begin = clock();
//Running time for finding LCA
	nd* LCA=findLCA(root,u,v);
	if(LCA!=NULL){gives("LCA node : ");give(LCA->data);}
	else gives("Given keys not in tree!");

clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
gives("\nRunning time (seconds) : "); printf("%f",time_spent);gives("\n");

	return 0;

}
