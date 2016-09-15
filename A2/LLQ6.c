//Name - DESHMUKH UDAYRAJ SHRIKANT
// Roll - 150101021

	#include<stdio.h>
	#include<stdlib.h>
	#include<time.h>
//Some convenience functions-
	void give(int x){printf("%2d",x);}
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
		while(head!=NULL){give(head->data);gives("-");head=head->next;}
		giveN();
	}

	// part i
struct node* createNode(int val){
		struct node* t=malloc(sizeof(struct node));
		t->data=val;
		t->next=NULL;
		return t;
	}
struct node* createLL(int A[],int n,int loopPos){
		struct node* head=createNode(A[0]);
		gives("Linked List : \t");
		struct node* head1=head;//for printing
		struct node* looperNode=head;//for adding loop
		if(loopPos==-1 || loopPos>=n)looperNode=NULL;
		for(int i=1;i<n;i++){
			struct node* t;
			t=createNode(A[i]);
			head->next=t;
			head=head->next;
			if(i==loopPos)looperNode=t;
		}
		printLL(head1);
		gives("Position=");give(loopPos);
		giveT();
		for(int i=0;i<loopPos;i++)gives("___");gives("^");
		giveN();giveN();//extra
		
		//Connect looperNode to last element 
		head->next=looperNode; //currently the last node

return head1;
	}


void CheckCycle(struct node* head){
	struct node* ptr1=head;
	struct node* ptr2=head;
	struct node* next_to_ptr2=head->next;
	while(ptr1->next!=NULL && ptr2!= NULL){//any null means no cycle.
		
		ptr1=ptr1->next; //one step

		next_to_ptr2=ptr2->next;
		if(next_to_ptr2==NULL)break;
		ptr2=next_to_ptr2->next; // two steps with caution taken of null element at first step.
	
		if(ptr1==ptr2){gives("YES\n");return;}//first check is on 1,2 then 2,4 3,6..
	}
	
	//when either ptr reached a null-
	gives("NO\n");
}

	int main(){
		srand(time(NULL));
		int random=1,n=5;
		gives("\t\t Q6.FINDING A CYCLE in a Linked List : \n\n");
		gives("Enter length of the input array : ");n=take();int *A=malloc(sizeof(int)*n);
		if(random)randomInput(A,n);else takeInput(A,n);
		gives("Random Array: \t");giveT();giveA(A,n);
	int loopPos=n/2;
		gives("LoopNode : user position,random position or no loop? (0/1/-1)");random=take(); 
		if(random==-1)loopPos=-1;
		else if(random)loopPos=rand()%n;
		else {gives("Enter loop position : ");loopPos=take();}

	struct node* head=createLL(A,n,loopPos);//first initialize head.
	gives("Check for Loop:  ");CheckCycle(head);giveN();
	return 0;
	}