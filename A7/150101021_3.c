#include<stdio.h>
#include<stdlib.h>
#define alpha 999

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
	int val,
	visit,//for printing
	rank,//for union by rank
	j; //for ordering the extract_min output
	struct node *parent;// for path compression
}nd ;


nd* make_set(int val){
	nd* newNode = (nd*)malloc(sizeof(nd));
	newNode->val = val;
	newNode->visit=0; //for printing
	newNode->rank=0; //for union by rank
	newNode->j= 0; //for ordering the extract_min output
	newNode->parent = newNode; // for path compression
	return newNode;
}

nd* find_set(nd* x){
	if(x != x->parent)
		x->parent = find_set( x->parent ); //path compression
	return x->parent;
}

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
			printf("%d.%d",x->val,x->j);
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
void takeManual(int N,int M,nd* elements[],nd* nodeArray[]){
	int a ,j=0,i=0,newset=1;
	gives("Enter elements (please enter -1 for E) : \n");
		//update final one at end
	while((i+j)<(N+M) || j<M){
		a=take();
		if(a>0 && a<=N && i<N){
			nd* elt = make_set(a); //initialize the nodes of the graph
			elt->j=j;
			nodeArray[i+j] = elt; //to contain all nodes including Es
			elements[a-1]=elt; //to contain only element nodes
			if(newset==0) {
				union_set(nodeArray[i+j-1],elt); //this is forming Kj
			}
			newset=0;
			i++;
		}
		else {
			nd* elt = make_set(alpha); //set E to alpha so that it wont be extracted
			// elt->j=j;//not required for Es
			nodeArray[i+j] = elt;
			if(j<M)j++;
			newset=1;
		}
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

//for each i, get rep of Kj which contains i. _/
// then put extracted[j]=i
// then collapse Kj by union with next empty or nonempty Kj
//make_set NULL ones to ALPHA so that we'll never take them out.

nd* getnextSet(nd* Head,int N,nd* nodeArray[]){
	int j,crossed=0;
	nd* currhead;
	for(j=0;j<N;j++){
		currhead= find_set(nodeArray[j]);
		if(currhead == Head)crossed=1; //after crossing the head, we'll get the next set.
		if(crossed && Head!=currhead)break;//this will break at the immediate next E
	}
	if(j==N)return NULL;
	return currhead;
}


void offline_min(int N,int M,nd* elements[],nd* nodeArray[],int Extracted[]){
	int i,j;
	nd* elt,*Kj,*nextSet,*newSet;

	for(i=0;i<N;i++){
		elt=elements[i];
		Kj = find_set(elt);
		j = Kj->j;

		gives("\n extract-");printf("%d.%d",elt->val,j);
		if(j>=M){
			gives("\tNOPE");
			continue;
		}

	//delete that node => set its value to alpha 

	//pop that E => make union with ith node
		nextSet=getnextSet(Kj,N+M,nodeArray); //this will give the immediate next E
		if(nextSet==NULL){
			Kj->j=j+1;
			gives("\tno E ahead");
			continue;
		}
		else union_set(Kj,nextSet);

		gives("\n");
		Extracted[j]=elt->val; //check j-1
		elt->val=alpha; //consider alpha2
		printSets(M+N,nodeArray);
		gives("\n");

	// union with next existing Kj => again do Union
		nextSet=getnextSet(Kj,N+M,nodeArray); //this will give the set next to E
		Kj->j=j+1;
		if(nextSet==NULL){
			continue;
		}
		else {
			newSet = union_set(Kj,nextSet);
				// gives(" +j_");give(newSet->val);
				// SAVE The incremented j IN THE NEW UNIONED SET
			newSet->j= j+1;
		}
	}

}
int main ( int argc, char *argv[]){
	int i,j,N=9,M=6;
	gives("Please enter N & M - ");
			// N=take();
			// M=take();

	nd** elements = (nd**)malloc(N * sizeof(nd)); //initialize
	nd** nodeArray = (nd**)malloc((M+N) * sizeof(nd)); //initialize
	nd** K = (nd**)malloc(M * sizeof(nd)); //initialize
	int Extracted[M];
	int a=0;
	takeManual(N,M,elements,nodeArray);

//print given data
	gives("\nRecorded sets I(j): \n");
	printSets(M+N,nodeArray);
//now in offline minimum, we are going from minimum=1 to max=n and seeing if it was inserted before the Extract
	gives("\n offline min : \n");
	offline_min(N,M,elements,nodeArray,Extracted);
	gives("\n processed: \n");
	printSets(M+N,nodeArray);

	gives("\n\n Extracted Array: \n");
	giveA(Extracted,M);
	return 0;
}
/*
 4 8 -1 3 -1 9 2 6 -1 -1 -1 1 5 -1 7
 */