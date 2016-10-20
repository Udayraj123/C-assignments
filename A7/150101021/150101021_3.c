//Deshmukh Udayraj
//Roll : 150101021
#include<stdio.h>
#include<stdlib.h>
#define val_deleted 999
#define val_E 99
#define val_popped 100

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
		if(s1->val != val_popped)
			return s1;
		else
			return s2;
	}
	else {
		s1->parent = s2;
		//increase rank of any one of the sets (we set s2 as parent here.)
		if(r1==r2)
			s2->rank++;
		if(s2->val != val_popped)
			return s2;
		else
			return s1;
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
		if(find_set(x)==currHead 
			&& x->val != val_deleted 
			&& x->val != val_popped
			){
			if(x->val != val_E)give(x->val);
		else {gives("E");printf("%d",x->j);}
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
			gives(", "); //to distinguish sets.
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
			nd* elt = make_set(val_E); //set E to alpha so that it wont be extracted
			elt->j=j;//not required for Es
			nodeArray[i+j] = elt;
			if(j<M)j++;
			newset=1;
		}
	}
}

nd* getNextSet(nd* Head,int N,nd* nodeArray[]){
	int j,crossed=0;
	Head=find_set(Head);//get head
	nd* currhead;
	for(j=0;j<N;j++){
		currhead= find_set(nodeArray[j]);
		if(currhead == Head)crossed=1; //after crossing the head, we'll get the next set.
		if(crossed && Head!=currhead )
			break;//this will break at the immediate next non poppedE
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

		if(j>=M){
			printSets(M+N,nodeArray); gives("\n");
			continue;
		}

		//pop that E => make union with the immediate next E
		nextSet=getNextSet(Kj,N+M,nodeArray); //this will give the immediate next E
		if(nextSet==NULL || nextSet->val != val_E){
			// no E ahead;
			Kj->j=j+1;
			printSets(M+N,nodeArray); gives("\n");
			continue;
		}
		else {
		//if there is a E ahead, extract & store in the array.
			Extracted[nextSet->j]=elt->val; //check j-1

			union_set(Kj,nextSet);
			nextSet->val=val_popped;
		}

	//delete that node => set its value out of the domain. 
		elt->val=val_deleted;

	// union with next existing Kj => again do Union
		nextSet=getNextSet(Kj,N+M,nodeArray); //this will give the set next to E
		Kj->j=j+1;
		if(!(nextSet==NULL || nextSet->val ==val_E)){
			//union with Input elements just after next E if they exist
			newSet = union_set(Kj,nextSet);
			newSet->j= j+1;  // SAVE The incremented j IN THE NEW UNIONED SET
		}
		printSets(M+N,nodeArray); gives("\n");
	}

}
int main ( int argc, char *argv[]){
	int i,j,N=9,M=6;

	gives("\t\t Q3: OFFLINE_MIN using disjoint sets datastructure \n\n");
	gives("Please enter N & M - ");
			N=take();
			M=take();

	nd** elements = (nd**)malloc(N * sizeof(nd)); //initialize
	nd** nodeArray = (nd**)malloc((M+N) * sizeof(nd)); //initialize
	nd** K = (nd**)malloc(M * sizeof(nd)); //initialize
	int Extracted[M];
	int a=0;
	takeManual(N,M,elements,nodeArray);

	gives("\n\n Offline min steps: \n");
	printSets(M+N,nodeArray);gives("\n");
	offline_min(N,M,elements,nodeArray,Extracted);

	gives("\n\n Final Extract Min Array: \t");
	giveA(Extracted,M);
	return 0;
}
/*
sample input - paste this in terminal
 4 8 -1 3 -1 9 2 6 -1 -1 -1 1 5 -1 7
 */