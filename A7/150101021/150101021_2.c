//Name - Udayraj Deshmukh
//Roll - 150101021
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
	int val,visit,rank;
	// int index; // this is used to access parent of the node
	struct node *parent;//* head,* next;
}nd ;


nd* make_set(int val){
	nd* newNode = (nd*)malloc(sizeof(nd));
	newNode->val = val;
	newNode->visit=0;
	newNode->rank=0;
	newNode->parent = newNode;
	return newNode;
}

//follows path compression method-
nd* find_set(nd* x){
	if(x != x->parent)
		x->parent = find_set( x->parent ); //path compression
	return x->parent;
}


// follows Union by rank method -
nd * union_set(nd* x1, nd* x2){
	nd* s1=find_set(x1);
	nd* s2=find_set(x2);
	if(s1==s2)return s1; //no union if from same set.
	int r1=s1->rank, r2=s2->rank;
	if(r1 > r2){
		//make larger ranked set the parent of smaller ranked set
		s2->parent = s1; 
		//no change to rank here
		return s1;
	}
	else {
		s1->parent = s2; 
		//increase rank of any one of the sets (we set s2 as parent here.)
		if(r1==r2)
			s2->rank++;
		return s2;
	}	
}

//print a single set.
void printSetOf(int N, nd* currHead,nd * nodeArray[]){
	//x is any element. Get its head first-
	int i;
	gives("{ ");
	for(i=0;i<N;i++){
		//print all the nodes whose set representative is currHead.
		nd* x = nodeArray[i];
		if(find_set(x)==currHead) {
			give(x->val);
			gives(" ");
		}
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
		currHead = find_set(nodeArray[i]);
		if(currHead->visit==0){ //print the set if its head is unexplored yet.
		//now print those whose head is currHead.	
			printSetOf(N, currHead,nodeArray);
			gives(" , "); //to distinguish sets.
			currHead->visit=1;
		}
	}
}

//function to handle manual input
void takeManual(int N,nd* nodeArray[]){
	int i,a;
	gives("Enter values of elements one by one : \n");
	for (i=0;i<N;i++){
		a=take();
		nodeArray[i] = make_set(a); //initialize the nodes of the set
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

void showMenu(int N,nd* nodeArray[]){
	//the Menu Interface for choosing between find set & union set
	int choice;
	gives("\nEnter your choice : \n 1.find_set\n 2.union_set\n 0.exit\n"); choice=take();
	gives("\n");
	switch(choice){

		case 1:
		gives("Enter x :");int x=take();
		nd * xObj = getObject(x,N,nodeArray);
		if(xObj!=NULL){
			//output the representative of x
			gives("Set representative of x is : \t");
			give( find_set(xObj)->val );
		}
		else {
			gives("Invalid value - "); give(x);gives("\n");
		}
		break;


		case 2:
		gives("Enter x1 & x2 :");
		int x1=take(),x2=take();
		nd* xObj1 = getObject(x1,N,nodeArray);
		nd* xObj2 = getObject(x2,N,nodeArray);
		if(xObj1 != NULL && xObj2!=NULL ){
			gives("Disjoint sets after union : \t");
			union_set(xObj1,xObj2);
		}
		else {
			gives("Invalid values - "); give(x1); give(x2);gives("\n");
		}
		//output the disjoint sets- 
		printSets(N,nodeArray);
		break;
		

		case 0:
		gives("Exiting the program.\n"); return;
		break;
		default:
		gives("Please enter valid choice : ");
		break;
	}
	showMenu(N,nodeArray);

}

int main ( int argc, char *argv[]){
	int i,j,N=8;
	gives("\t\t Q2: Union by Rank & Path Compression \n\n");
	gives("Please enter Number of elements N - ");
	N=take();
	//initialize
	nd** nodeArray = (nd**)malloc(N * sizeof(nd)); 
	
	//take user input
	takeManual(N,nodeArray); 

	//print given data
	gives("\nRecorded sets: \n");
	printSets(N,nodeArray);
	
	// Start menu based navigation-
	showMenu(N,nodeArray);

	return 0;
}