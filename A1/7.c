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
	int t=0;
	int digits=2;
	int modulo= power(10,digits);
	for(t=0;t<n;t++)A[t]=random()%modulo; 			//for less space in terminal. remove if wanted.
	if(show){gives("  Generated array - \t");giveA(A,0,n);gives("\t");}  	//print generated array.
}


void takeInput(int A[],int n){ //take User input
	int t=0;
	gives("Enter elements -");
	for(t=0;t<n;t++)A[t]=take();
}


int Merge(int A[],int s,int mid,int e){
 int current_inversions=0;
	//make a new array to merge two halves into
	int *B=malloc(sizeof(int)*(e-s+1));

	int i=0,j=0,k=0;
	for(i=s,j=mid+1; i<=mid && j<=e;){
		int L=A[i],R=A[j], key;
	/***

	Number of inversions is equal to total of the numbers left in L (the left array) when an element from R is placed into new array.

	***/
		int num_left_in_L=mid-i+1;
		if(L>R){ current_inversions+=(num_left_in_L) ;key=R;j++;}	else {key=L;i++;}
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
		return current_inversions;
}

int MergeSort(int A[],int s,int e){
	static int inversions=0;
	if(s==e){return inversions;}
		int mid=(s+e)/2;// midKey=A[mid], nextToMid=A[mid+1];	
		MergeSort(A,s,mid);
		MergeSort(A,mid+1,e);
		inversions+=Merge(A,s,mid,e);
	return inversions;
}

void HandleMerge(int A[],int n ){

	int totalInversions=MergeSort(A,0,n-1);
	gives("  Sorted Array- \t");giveA(A,0,n);
		gives("\n Inversions Count=");
		give(totalInversions);gives("\t");
		gives("\n");
}


int main(){
	srand(time(NULL));
	int random=1,n=5,show=0;
	gives("\t\tQ7 : INVERSION COUNT\n");
	gives("Enter length of the array : ");n=take();int *A=malloc(sizeof(int)*n);
	gives("User input or randomInput? (0/1)");random=take(); 

	if(random)randomInput(A,n,1);else takeInput(A,n);gives("\n");

	HandleMerge(A,n);
	return 0;
}
