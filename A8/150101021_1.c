#include<stdio.h>
#include<stdlib.h>

void give(int a){
	printf("%2d ",a);
}
int take(){
	int a;
	scanf("%d",&a);
	return a;
}
void gives(char* a){
	printf("%s",a);
}
void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

void giveA(int A[],int K){
	int i=0;for(i=0;i<K;i++){
		give(A[i]);
	}
	gives("\n");
}

void heapify(int A[],int size, int i){ //initially i is size/2
	if(size<2)return;
	//initially i denotes the rightmost node at height 1
	
	int L=2*i+1;
	int R=2*i+2;
	int m=i; //in m we store the index L or R whichever is minimum.
	
	//if left child exists
	if (L<=size-1){//update m to index of min child

		m= A[L]<A[m]?L:m;
		
		if(R<=size-1){//if right child exists
			m= A[R]<A[m]?R:m;
		}
	}
	if(m!=i){
		swap(&A[i],&A[m]);
		heapify(A,size,m); // recurse on the child which was swapped.
	}
}

void insert_heap(int A[],int* size, int N,int val){
	if(*size==N){
		gives("\tArray overflow\n");
		return;
	}
	int s= *size;
	A[s]=val;
	int node=s;
	//increase size as new element stored at prev size
	*size=s+1; 
	while(node > 0){
		node = (node-1)/2 ; //start from height 1
		heapify(A,*size,node);
	}
} 
 
int extractMin(int A[],int* size){ 
	int min= A[0];
	A[0]=A[*size-1]; //last element is put on top
	heapify(A,*size,0); //heapify again
	*size = *size - 1;
	return min;
}

int main (){
	int N=5,K=5;
	FILE * fp;
	char* filename="test.dat.txt";
	fp=fopen(filename,"r");
	fscanf(fp,"%d",&N);

	int heap[N]; 
	int size=0; // empty heap
	int a,count=0,i=0;
	while(!feof(fp) && count<N){
		fscanf(fp,"%d",&a);
		insert_heap(heap,&size,N,a);
		count++;
	}

	gives("Enter how many elements to output (K) : ");
	K=take(); gives("\n");
	
	for(i=0;i<K;i++){
		give(extractMin(heap,&size));
		gives("\n");
	}
	
	return 0;
}
 