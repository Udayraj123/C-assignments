#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//Below are some functions for convenience.
void swap(int*a,int*b){int t=*b;*b=*a;*a=t;}
void give(int a){printf("%d ",a);}
void gives(char* a){printf("%s ",a);}
void giveA(int* A,int s,int e){	int t=0;	for(t=s;t<e;t++)give(A[t]);}
void cellD(int a){printf("%15d ",a);}
void cellS(char* a){printf("%15s ",a);}

int power(int a,int b){int power=1;while(b--)power*=a;return power;}
int take(){
	int n;
	scanf("%d",&n);
	return n;
}
void randomInput(int A[],int n,int show){//generates random numbers
	int t=0,digits=2;
	int modulo= power(10,digits);
	for(t=0;t<n;t++)A[t]=random()%modulo; 			//for less space in terminal. remove if wanted.
	if(show){gives("  Generated array - \t");giveA(A,0,n);gives("\n");}  	//print generated array.
}


void takeInput(int A[],int n){ //take User input
	int t=0;
	gives("Enter elements -");
	for(t=0;t<n;t++)A[t]=take();
}



int linearSearch(int A[],int s,int * counter){
	int i=0, key=A[s];
	for(i=0;i<s;i++){
		(*counter)++;
		(*counter)++;
		if(key<=A[i])break; //stop at i when key fits in * <= - <
	}
	return i;
}

int binarySearch(int A[],int s,int key,int e,int * counter){
	(*counter)++;
	if(s>=e){
		(*counter)++;
		return A[s]>key?s:s+1;	
	}

	int mid=(s+e)/2, midKey=A[mid], nextToMid=A[mid+1];	

	(*counter)++;(*counter)++;
	if(key>=midKey && key <=nextToMid){
		return mid+1;
	}
	(*counter)++;
	if(key <midKey){return binarySearch(A,s,key,mid,counter);}
	(*counter)++;
	if(key >nextToMid){return binarySearch(A,mid+1,key,e,counter);}

}


void binInsertSort(int A[],int s, int n,int * counter){
	
	if(s==n){(*counter)++; return;}

	int i=0;
	i=binarySearch(A,0,A[s],s,counter); //find position of insertion using binary search

	int now=s;
	while(now!=i){
		(*counter)++;
		swap(&A[now],&A[now-1]);now--;
	}
	binInsertSort(A,s+1,n,counter);	//recurse on sub-array from s+1 to n
}
void linInsertSort(int A[],int s, int n,int * counter){
	
	if(s==n){(*counter)++; return;}

	int i=0;
	i=linearSearch(A,s,counter); //find position of insertion using linear search

	int now=s;
	while(now!=i){
		(*counter)++;
		swap(&A[now],&A[now-1]);now--;
	}
	linInsertSort(A,s+1,n,counter);	//recurse on sub-array from s+1 to n
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
	int comparsionCount=0;
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

void ComparisonTable(int A[],int n){
	int t=0;
		int *B=malloc(sizeof(int)*n);for(t=0;t<n;t++)B[t]=A[t];//exact copy of A for linear sort
		int *C=malloc(sizeof(int)*n);for(t=0;t<n;t++) C[t]=A[t];//exact copy of A for Merge sort
		cellD(n);
		int linearCount=5;
	linInsertSort(B,1,n,&linearCount);//linear
	cellD(linearCount);
	int binaryCount=0;
	binInsertSort(A,1,n,&binaryCount);//binary
	cellD(binaryCount);

	int mergeCount= MergeSort(C,0,n-1);
	cellD(mergeCount);
	if(mergeCount<binaryCount){gives("<- (M<B)");give(n);}//mark whenever merge count<binary count
	gives("\t");
	
	gives("\n");
}

void showLINE(){cellS("N ");cellS(" Linear Count \t");cellS(" Binary Count ");cellS("Merge Count");cellS("\t");cellS("\n");}

void HandleTable(int *A,int n){ //generates table from i =1 to n
	showLINE();
	int i=1;
	while(i<=n){
		int n1=i;int *A=malloc(sizeof(int)*n1);
		randomInput(A,n1,0);//0 is for not showing output array
		ComparisonTable(A,n1);
		i++;
	}
	showLINE();
} 

int main(){
	srand(time(NULL));
	int random=1,n=5,show=0;
	gives("\t\tQ5 : MERGE THRESHOLD\n");
	gives("Enter number of arrays : ");n=take();int *A=malloc(sizeof(int)*n);
	HandleTable(A,n);
	return 0;
}
