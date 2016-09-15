#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//Below are some Functions for Convenience.
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
	gives("Enter max no. of digits :");int digits=4;digits=take();
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
	int current_comparisions=0;
	//make a new array to merge two halves into
	int *B=malloc(sizeof(int)*(e-s+1));

	int i=0,j=0,k=0;
	//Copy the smaller one first into new array

	for(i=s,j=mid+1; i<=mid && j<=e;){
	current_comparisions+=2;
		int L=A[i],R=A[j], key;

		if(L>R){ key=R;j++;}	else {key=L;i++;}
	current_comparisions+=1;
		B[k++]=key;
	}

	//when one halve is exhausted-
	while(i<=mid){
	current_comparisions+=1;
		B[k++]=A[i++];
	}
	while(j<=e){
	current_comparisions+=1;
		B[k++]=A[j++];
	}

	//copy back into original array.
	for(i=s,k=0;i<=e;i++){A[i]=B[k++];current_comparisions+=1;}
		return current_comparisions;
}

int MergeSort(int A[],int s,int e){
	int comparsionCount=0; //count comparisions using internal variable.
	if(s==e){
		comparsionCount++;
		return comparsionCount;
	}
	int mid=(s+e)/2;
	comparsionCount+=MergeSort(A,s,mid);
	comparsionCount+=MergeSort(A,mid+1,e);
	comparsionCount+=Merge(A,s,mid,e);
	return comparsionCount;
	}

void HandleMerge(int A[],int n){

	int comparsions=MergeSort(A,0,n-1);
		gives(" Sorted Array :\t");
		giveA(A,0,n);gives("\t");
		gives(" Comparsion Count :\t");
		give(comparsions);
		gives("\n");
}



int main(){
	srand(time(NULL));
	int random=1,n=5,show=1;
	gives("\t\tQ4 : MERGE SORT\n");
	gives("Enter length of the array : ");n=take();int *A=malloc(sizeof(int)*n);
	gives("User input or randomInput? (0/1)");random=take(); 

	if(random)randomInput(A,n,show);else takeInput(A,n);gives("\n");

	HandleMerge(A,n);
	return 0;
}
