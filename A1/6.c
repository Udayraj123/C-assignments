#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//Below are some functions for convenience.
void swap(int*a,int*b){int t=*b;*b=*a;*a=t;}
void give(int a){printf("%d ",a);}
void gives(char* a){printf("%s ",a);}
void giveA(int* A,int s,int e){	int t=0;	for(t=s;t<e;t++)give(A[t]);}
int power(int a,int b){int power=1;while(b--)power*=a;return power;}
int take(){
	int n;
	scanf("%d",&n);
	return n;
}
void randomInput(int A[],int n,int show){//generates random numbers
	int t=0;int digits=2;
	int modulo= power(10,digits);
for(t=0;t<n;t++)A[t]=random()%modulo; 			//for less space in terminal. remove if wanted.
if(show){gives("  Generated array - \t");giveA(A,0,n);gives("\t");}  	//print generated array.
}

void takeInput(int A[],int n){ //take User input
	int t=0;
	gives("Enter elements -");
	for(t=0;t<n;t++)A[t]=take();
}


void Merge(int A[],int s,int mid,int e){
//make a new array to merge two halves into
	int *B=malloc(sizeof(int)*(e-s+1));

	int i=0,j=0,k=0;

	//Copy the smaller one first into new array
	for(i=s,j=mid+1; i<=mid && j<=e;){
		int L=A[i],R=A[j], key;
		if(L>R){ key=R;j++;}	else {key=L;i++;}
		B[k++]=key;
	}

//when one halve is exhausted-
	while(i<=mid){
		B[k++]=A[i++]; 
	}
	while(j<=e){
		B[k++]=A[j++]; 
	}

//copy back into original array.
	for(i=s,k=0;i<=e;i++){A[i]=B[k++]; }
}

void MergeSort(int A[],int s,int e){
if(s==e){return;}//0 1 | 2
int mid=(s+e)/2;// midKey=A[mid], nextToMid=A[mid+1];	
MergeSort(A,s,mid);
MergeSort(A,mid+1,e);
Merge(A,s,mid,e);
}

int properBinarySearch(int key,int A[],int s,int e){
	int mid=(s+e)/2;
	int midKey=A[mid];
	if(s>e){return -1;}
	if(key==midKey)return mid;
	if(key>midKey)return properBinarySearch(key,A,mid+1,e);
	if(key<midKey)return properBinarySearch(key,A,s,mid-1);
	return -1;
}

void Q6(int A[],int B[],int n,int m){
 int once=1;
	int i=0,found=0;
	for(i=0;i<n;i++){
		int a=A[i];
		int b=m-a;
		if(b<0)continue;
		int pos=properBinarySearch(b,B,0,n-1);

		if(pos!=-1){
			if(once){once=0; gives("Found!\n a\tb\n");}
			give(a);gives("\t");give(b);gives("\n");
			found=1;
		}
	}
	if(!found)gives("Not found!\n");
}

int main(){
	srand(time(NULL));
	int random=1,n,m;
	gives("\t\tQ6 : FINDING m = a + b\n");
	gives("Enter length of the arrays : ");n=take();int *A=malloc(sizeof(int)*n);int *A2=malloc(sizeof(int)*n);
	
	gives("User input or randomInput? (0/1)");random=take(); 
	if(random)randomInput(A,n,1);else takeInput(A,n);gives("\n");
	if(random)randomInput(A2,n,1);else takeInput(A2,n);gives("\n");
	
	MergeSort(A,0,n-1);gives("Sorted Array 1 \t");giveA(A,0,n);gives("\n");
	MergeSort(A2,0,n-1);gives("Sorted Array 2 \t");giveA(A2,0,n);gives("\n");

	gives("Enter m : ");m=take();
	Q6(A,A2,n,m);

	return 0;
}
