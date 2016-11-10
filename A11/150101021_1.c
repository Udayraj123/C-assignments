#include <stdio.h>

char* dig[]={"%d","%2d","%3d","%4d"};
char* lin[]={"%s","%2s","%3s","%4s"};
char* minD=" %2d ";
char* minS=" %2s ";
void swap(int *a,int *b){int t=*a; *a=*b; *b=t; }
void give(int d){printf(minD,d);}
void gives(char* s){printf("%s",s); }
int take(){int n; scanf("%d",&n); return n; }


void dashLine(int n){while(n--)printf(minS,"--");gives("\n");}
void empty(){printf(minS," ");}


void giveA(int A[],int n){
	int i; for(i=0;i<n;i++)give(A[i]);
	gives("\n");
}
void selA(int A[],int n,int n1,int n2){
	int i; for(i=0;i<n;i++)
	if(i==n1 || i==n2)
		give(A[i]);
	else
		empty();
	gives("\n");
}

void takeInput(int A[],int n){
	gives("Enter terms of the Array:");

	int i; for(i=0;i<n;i++){
		A[i]=take();
	}
}

int getMin(int A[],int start,int N){
	int i;
	int minIndex=start;
	int min=A[minIndex];
	for (i = start; i < N; ++i){
		if(A[i]<min){
			min=A[i];
			minIndex=i;
		}
	}
	return minIndex;
}

void selSort(int A[],int N){

	int i=0,minIndex;
	for (i = 0; i < N-1; ++i){
		minIndex=getMin(A,i,N);
		
		if(i!=minIndex) {
			swap(&A[i],&A[minIndex]);
			//printing only those swapped
			selA(A,N,i,minIndex);
			dashLine(N);
		}

	}

}

int main() {
//get max digit number for formatting
	//update the minD for it
	gives("Enter number of terms in Array: ");
	int n=take();
	int A[n];
	takeInput(A,n);
	giveA(A,n);
	dashLine(n);
	selSort(A,n);

	gives("\n\t Final Sorted array : ");
	giveA(A,n);

	return 0;
}