#include<stdio.h>
#include<stdlib.h>

//Below are some functions for convenience.
void give(int a){
	printf("%2d ",a);
}
int take(){
	int a;
	scanf("%d ",&a);
	return a;
}
void gives(char* a){
	printf("%s",a);
}
void giveA(int* A,int e){ int t=0,s=0;	for(t=s;t<e;t++)give(A[t]);gives("\n");}

typedef struct node  {
	int val,id;
	struct node * head,* next;
}nd ;
//there is a nodes array,
//there is a representative array, with node index same as its
//each head is maintained

nd* find_set(int x, int N,nd* nodeArray[]){
	int i;
	for(i=0;i<N;i++){
		if(nodeArray[i]->val==x)break;
	}
	if(i==N)return NULL;
	return nodeArray[i]->head;
}

nd * union_set(int x1, int x2,int N,nd* nodeArray[], int size[]){
	nd* s1=find_set(x1,N,nodeArray);
	nd* s2=find_set(x2,N,nodeArray);
	if(s1==s2)return s1;
	int z1=size[s1->id], z2=size[s2->id];
	if(z1<z2){
		nd* e1=s1;
		while( e1!=NULL){
			e1->head=s2;
			e1=e1->next;
		}
		nd* e2=s2;
		while( e2->next!=NULL)e2=e2->next;
		e2->next=s1;
		size[s2->id]=z1+z2;;
		return s2;
	}
	else{
		nd* e2=s2;
		while( e2!=NULL){
			e2->head=s1;
			e2=e2->next;
		}
		nd* e1=s1;
		while( e1->next!=NULL)e1=e1->next;
		e1->next=s2;
		size[s1->id]=z1+z2;
		return s1;
	}	
}


nd* make_set(int val,int id){
	nd* newNode = (nd*)malloc(sizeof(nd));
	newNode->val=val;
	newNode->id=id;
	newNode->head = newNode;
	newNode->next = NULL;
	return newNode;
}

void printSets(int N,nd* nodeArray[]){
	int i;
	nd* currSetRep = nodeArray[0]->head;
	nd * currHead;
	for(i=0;i<N;i++){
		currHead=nodeArray[i]->head;
		if(currHead != currSetRep){
			//Assumption : same set elements shall occur serially
			currSetRep=currHead;
			gives(" .\t"); //to distinguish sets.
		}
		give(nodeArray[i]->val);gives(" ");
	}
}

int main ( int argc, char *argv[]){
	int i,j,N=4;
	FILE * fp=fopen("sets.txt","r");
	// FILE * fp=fopen(argv[1],"r");
    fscanf(fp,"%d",&N); //take first line to N

    nd** nodeArray = (nd**)malloc(N * sizeof(nd));
    int a;
    int size[N];


    gives("Input read from file: \n");
    for (i=0;i<N;i++){
    	fscanf(fp,"%d",&a);
		if(a<N && a>=0){ //accept positive integers id less than N
			give(a); gives("\t");
			nodeArray[i] = make_set(a,i); //initialize the nodes of the graph
			size[i]=1; // initial size = 1
		}
		else {
			gives("Invalid id-");give(a);gives("\n");
			gives("Please keep values starting from 0 inside sets.txt");
			// i--;
			return 0;
		}
	}
	fclose(fp);

//print given data
	gives("\nRecorded sets: \n");
	printSets(N,nodeArray);
	int choice;
	choice=take();
	gives("\nEnter your choice : \n1.find_set\n2.union_set\n0.exit\n");
	switch(choice){
		case 1:
		gives("Enter x :");int x=take();
		gives("Set representative of x is : \t");give(find_set(x,N,nodeArray)->val);
		break;
		case 2:
		gives("Enter x1 & x2 :");int x1=take(),x2=take();
		gives("Disjoint sets after union : \t");
		union_set(x1,x2,N,nodeArray,size);
		printSets(N,nodeArray);
		break;
		case 0:
		break;
		default:
		break;
	}	

	return 0;
}