	//Name - DESHMUKH UDAYRAJ SHRIKANT
// Roll - 150101021

	#include<stdio.h>
	#include<stdlib.h>
	#include<time.h>
//Some convenience functions-
void give(int x){printf("%d",x);}
void gives(char* x){printf("%s",x);}
void giveN(){printf("\n");}
void giveT(){printf("\t");}
void giveA(int A[],int n){int i=0;while(i<n)printf("%2d ",A[i++]);giveN();}
int take(){
	int n;
	scanf("%d",&n);
	return n;
}
	void randomInput(int A[],int n){//generates random numbers
	for(int t=0;t<n;t++)A[t]=random()%100; 			//for less space in terminal. remove if wanted.
}
	void takeInput(int A[],int n){ //take User input
		gives("Enter elements -");for(int t=0;t<n;t++)A[t]=take();
	}
	struct node {
		int data;
		struct node* next;
	} ;

	void printLL(struct node* head){
		while(head!=NULL){give(head->data);gives(" ");head=head->next;}
		giveN();
	}

	int isNull(struct node* head){
		if(head==NULL)gives("Head is NULL.\n");
		return head==NULL;
	}

struct node* createNode(int val){
		struct node* t=malloc(sizeof(struct node));
		t->data=val;
		t->next=NULL;
		return t;
	}

void createStack(int A[],int n, struct node* head){
		gives("Stack :  \t");
		if(isNull(head))return;
	struct node* head1=head;//for printing
	
	for(int i=1;i<n;i++){
		struct node* t;
		t=createNode(A[i]);
		head->next=t;
		head=head->next;
	}
	printLL(head1);
}

void Pop(struct node **headptr){
	struct node* toDelete=*headptr;  
	if(isNull(toDelete))return;
	*headptr=toDelete->next;
	free(toDelete);
}

void Push(struct node **headptr,int val){
	struct node* t=createNode(val);
	t->next=*headptr;  //"insert"
	*headptr=t;
}


void Span1(int A[],int n){
	int S[n]; //max number of elements
	int i=0;
	for(int i=0;i<n;i++){
		int op=A[i],curr_streak=1;
		for(int j=i-1;j>=0;j--){
			if(A[j]>op)break;
			else curr_streak++;
		}
		S[i]=curr_streak;
	}
	gives("Spans1 of Array: ");giveT();giveA(S,n);
}

int top(struct node* a){return a->data;}

void Span2(int A[],int n){
	struct node* a=createNode(0);
	int S[n]; //max number of elements
	int i=0;
	for(int i=0;i<n;i++){
		while( a!=NULL && A[top(a)] <= A[i]){
			Pop(&a);
		}
		if((a==NULL)){
			S[i]=i+1;
		}
		else {
			S[i]=i-top(a);
		}
		Push(&a,i);
	}
	gives("Spans2 of Array: ");giveT();giveA(S,n);
}

int main(){
	srand(time(NULL));
	int random=1,n=5;
	gives("\t\tQ4 : FINDING SPAN\n");
	gives("Enter length of the array : ");n=take();
	int *A=malloc(sizeof(int)*n);int *Indices=malloc(sizeof(int)*n);
	gives("User input or randomInput? (0/1)");random=take(); 
	if(random)randomInput(A,n);else takeInput(A,n);
	gives("Generated Array: ");giveT();giveA(A,n);
	Span1(A,n);
	giveN();
	Span2(A,n);

	return 0;
}