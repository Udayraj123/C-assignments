//Name - Udayraj Deshmukh 
//Roll - 150101021
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Below are some Functions for Convenience.
void swap(int*a,int*b){int t=*b;*b=*a;*a=t;}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void give(int a){printf("%2d ",a);}
void give2(int a){printf("%10d ",a);}
void gives(char* a){printf("%s ",a);}
void giveA(int* A,int s,int e){	int t=0;	for(t=s;t<e;t++)give(A[t]);}

void randomInput(int A[],int n,int show){//generates random numbers
	int t=0;
	for(t=0;t<n;t++)A[t]=random()%100; 			//for less space in terminal. remove if wanted.
	if(show){gives("  Random array - \t");giveA(A,0,n);gives("\n");}  	//print generated array.
}

void insertionSort(int A[],int n){ //as sorting is required to give distinct count in the differences
	for(int i=1;i<n;i++){
		int key=A[i];
		int j=i-1;
		while(j>=0 && key<A[j]){
			A[j+1]=A[j];
			j--;
		}
		A[j+1]=key;
	}
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

nd* makeTree(int A[],int n){
	nd* root=NULL; //empty tree.
	for(int i=0;i<n;i++){
		root=insert(A[i],root); //CHECK FOR BUGS HERE
	}
	return root;
}

int maxDepth(nd* root){
	if(root==NULL){return 0;} // empty tree.
	return 1+max(maxDepth(root->right),maxDepth(root->left));
}
int minDepth(nd* root){
	if(root==NULL){return 0;} // empty tree.
	return 1+min(minDepth(root->right),minDepth(root->left));
}

void giveDistinctCount(int A[],int n){
	insertionSort(A,n);

	int i=0,num=0;
	int distinct[n],counts[n]; //size n as max all elements can be distinct.
	
	while(i<n){
		int counter=0;
		int key=A[i];
		while(key == A[i]){i++;counter++;} //increase counter when encountered same element
		counts[num]=counter;
		distinct[num]=key;
		num++;
	}

	//Print Table
	gives("Difference \t");	gives("\t");	gives("Counts \t");gives("\n");
	for(int t=0;t<num;t++){
		give2(distinct[t]);gives("\t");		give2(counts[t]);gives("\n");
	}

}

int main(){
	srand(time(NULL));
	int n=100,n2=50;
	int A[n], diffs[n2];
	gives("Q1. Finding largest & smallest levels in binary tree. Press any key to continue."); getchar();
	gives(" S.N.   ");gives("Largest level:\t");	gives("Smallest level:\t");	gives("Difference : \t");gives("\n");
	for(int k=0;k<n2;k++){
		randomInput(A,n,0);
		nd* root= makeTree(A,n);
		int maxD= maxDepth(root);
		int minD= minDepth(root);
		int diff=maxD-minD;
		diffs[k]=diff;
		give(k+1); gives("\t");give2(maxD); gives("\t");	give2(minD); gives("\t");		give2(diff); gives("\t");gives("\n");
	} 
	
	gives("\n");
	giveDistinctCount(diffs,n2);

	return 0;
}
