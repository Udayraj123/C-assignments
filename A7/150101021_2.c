#include<stdio.h>
#include<stdlib.h>

//Below are some functions for convenience.
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
void giveA(int* A,int e){ int t=0,s=0;	for(t=s;t<e;t++)give(A[t]);gives("\n");}

typedef struct node  {
	int val,visit;
	int index; // this is used to access parent of the node
	struct node * head,* next;
}nd ;

nd* find_set(nd* x){
	if(x != parentArray[x->index])
		parentArray[x->index] = find_set( parentArray[x->index] );
	return parentArray[x->index];
}

nd * union_set(nd* x1, nd* x2, int rank[]){
	nd* s1=find_set(x1);
	nd* s2=find_set(x2);

	if(s1==s2)return s1;
	int z1=rank[s1->index], z2=rank[s2->index];
	if(z1 > z2){
		
	}
	else {
		nd* e2=s2;
		while( e2!=NULL){
			e2->head=s1;
			e2=e2->next;
		}
		nd* e1=s1;
			//attach shorter one to its end
		while( e1->next!=NULL)e1=e1->next;
		e1->next=s2;

			//update size
		size[s1->index]=z1+z2;
		return s1;
	}	
}
}

nd* make_set(int val, int index){
	nd* newNode = (nd*)malloc(sizeof(nd));
	newNode->val = val;
	newNode->visit=0;
	newNode->index = index;//the index in input sequence acts like its id
	newNode->head = newNode;
	newNode->next = NULL;
	return newNode;
}

//print a single set.
void printSetOf(nd* x){
	//x is any element. Get its head first-
	nd* head = x->head;
	gives("{ ");
	while(head!=NULL){
		give(head->val);
		if(head->next!=NULL)gives(",");
		head=head->next;
	}
	gives("}");
}

//this is used for ease of printing
void reset(int N,nd* nodeArray[]){
	int i; 
	for(i=0;i<N;i++)
		nodeArray[i]->visit=0;
}
void printSets(int N,nd* nodeArray[]){
	int i;
	reset(N,nodeArray);
	nd * currHead;
	for(i=0;i<N;i++){
		currHead=nodeArray[i]->head;
		if(currHead->visit==0){ //print the set if its head is unexplored yet.
			printSetOf(nodeArray[i]);
			gives(" , "); //to distinguish sets.
			currHead->visit=1;
		}
	}
}

//function to handle manual input
void takeManual(int N,nd* nodeArray[],int size[]){
	int i,a;
	gives("Enter values of elements one by one : \n");
	for (i=0;i<N;i++){
		a=take();
		//update final one at end
		nodeArray[i] = make_set(a,i); //initialize the nodes of the graph
		size[i]=1; // initial size = 1
	}
}

//get node object from user inputted integer value 
nd* getObject(int x,int N,nd* nodeArray[]){
	int i;
	for(i=0;i<N;i++){
		if(nodeArray[i]->val==x)break;
	}
	if(i==N)return NULL; //element not found
	return nodeArray[i];
}

void showMenu(int N,nd* parentArray[],nd* nodeArray[],int size[]){
	int choice;
	gives("\nEnter your choice : \n1.find_set\n2.union_set\n0.exit\n"); choice=take();
	gives("\n");
	switch(choice){
		case 1:
		gives("Enter x :");int x=take();
		nd * xObj = getObject(x,N,nodeArray);
		if(xObj!=NULL){
			gives("Set representative of x is : \t");
			give( find_set(xObj)->val );
		}
		else {
			gives("Invalid value - "); give(x);gives("\n");
		}
		break;
		case 2:
		gives("Enter x1 & x2 :");int x1=take(),x2=take();
		nd* xObj1 = getObject(x1,N,nodeArray);
		nd* xObj2 = getObject(x2,N,nodeArray);
		if(xObj1 != NULL && xObj2!=NULL ){
			gives("Disjoint sets after union : \t");
			union_set(xObj1,xObj2,size);
		}
		else {
			gives("Invalid values - "); give(x1); give(x2);gives("\n");
		}
		printSets(N,nodeArray);
		break;
		case 0:
		gives("Exiting the program.\n"); return;
		break;
		default:
		gives("Please enter valid choice : ");
		break;
	}
	showMenu(N,nodeArray,size);

}

int main ( int argc, char *argv[]){
	int i,j,N=4,fileInput=0;
	FILE * fp;
	//can take file from command line argument too if provided
	if(argc>2)fp=fopen(argv[1],"r");
	else {
		gives("File input or Manual Input ? ( 1/0 ) : "); fileInput=take();
		if(fileInput){
			gives("Opening local input file- sets.txt\n");
			fp=fopen("sets.txt","r");
		}
		else {
			gives("Please enter N - ");
			N=take();
		}
	}
	if(fileInput)fscanf(fp,"%d",&N); //take first line to N //this is for command line file too.
	
	nd** nodeArray = (nd**)malloc(N * sizeof(nd)); //initialize
	nd** parentArray = (nd**)malloc(N * sizeof(nd)); //initialize
	int a, size[N],rank[N];

	if(!fileInput)takeManual(N,parentArray,nodeArray,size,rank);
	else{
		gives("Input read from file: \n");
		for (i=0;i<N;i++){
			fscanf(fp,"%d",&a);
			give(a); gives("\t");
			nodeArray[i] = make_set(a,i); //initialize the nodes of the graph
			parentArray[i] = nodeArray[i]; //initial self parent
			size[i]=1; // initial size = 1
			rank[i]=0; // initial rank = 0
		}
		fclose(fp);
	}

//print given data
	gives("\nRecorded sets: \n");
	printSets(N,nodeArray);
	// Start menu based navigation-
	showMenu(N,parentArray,nodeArray,size,rank);

	return 0;
}