    //Name- Deshmukh Udayraj
//Roll - 150101021

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void swap(int*a,int*b)
{
	int t=*b;
	*b=*a;
	*a=t;
}

//Below are some functions for convenience.
void give(int a)
{
	printf("%2d ",a);
}
void gives(char* a)
{
	printf("%s",a);
}
void giveA(int* A,int e){	int t=0,s=0;	for(t=s;t<e;t++)give(A[t]);gives("\n");}

int take()
{
	int n;
	scanf("%d",&n);
	return n;
}

typedef struct adjNode  {
	int id;
	struct adjNode * next;
}
adjNode ;

typedef struct node {
	int id,E,visit;
	adjNode * adjHead;
} nd;


nd* createNode(int id){
	nd* newNode = (nd*)malloc(sizeof(nd));
	newNode->id=id;
	newNode->E=0;
	newNode->visit=0;
	newNode->adjHead = NULL;
	return newNode;
}

void makeEdge(nd * Node,int id){
	//attaches ids of connected nodes
	adjNode * adjHead1 = Node->adjHead;
	if(adjHead1==NULL){ //First edge
		adjHead1 = (adjNode*)malloc(sizeof(adjNode)); // make new adjNode at end
		adjHead1 -> id = id;
		adjHead1 -> next =NULL; //set last one to NULL
		Node->adjHead=adjHead1;
	}
	else{
		while(adjHead1->next !=NULL)adjHead1 = adjHead1 -> next; //traverse to last id
		adjHead1 -> next = (adjNode*)malloc(sizeof(adjNode)); // make new adjNode at end
		adjHead1 = adjHead1 -> next;
		adjHead1 -> id = id;
		adjHead1 -> next =NULL; //set last one to NULL
	}

	Node->E++;
}

void reset(nd* nodeArray[],int N,int d[],int f[],int* t){
	int j;
	*t=0;
	for (j=0;j<N;j++){
		d[j]= N+1; //set to infinity/sentinel
		f[j]= 0; //initial value
		nodeArray[j]->visit=0;
	}
}


void DFS_visit(nd * curr_node,nd * nodeArray[],int d[],int f[],int* t){
	//set distance time color
	d[curr_node->id -1]= *t;
	*t = *t+1;
	curr_node->visit++; //makes gray

	adjNode * head = curr_node->adjHead;//head points to current node's adj list
	//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];
		if(near_node->visit==0){//White
			DFS_visit(near_node,nodeArray,d,f,t);
		}
		head=head->next;
	}
	//at this point all neighbours are explored.
	curr_node->visit++;
	f[curr_node->id-1] = *t;
}

/*
For edge u,v
1. If v is visited for the first time as we traverse the edge (u, v), then the edge is a tree edge.
2. Else, v has already been visited:
(a) If v is an ancestor of u, then edge (u, v) is a back edge.
(b) Else, if v is a descendant of u, then edge (u, v) is a forward edge.
(c) Else, if v is neither an ancestor or descendant of u, then edge (u, v) is a cross edge.
*/

void sortByF(int top[],int f[],int N){
	int max=0,prevMax=2*N,j,topIndex,i;
	for (i=0;i<N;i++){
		max=0;
		topIndex=i;
		for (j=0;j<N;j++){
			if(f[j] < prevMax  &&  f[j] > max){
				max=f[j];
				topIndex=j;
			}
		}
		prevMax=f[topIndex];
		top[i]=topIndex;
	}

}

void findSCCs(int N,nd * nodeArray[],nd * nodeArrayT[]){
	int t=0,d[N],f[N],top[N];
	reset(nodeArray,N,d,f,&t);
	int j;
	for (j=0;j<N;j++){
		nd* curr_node = nodeArray[j];
		if(curr_node->visit==0){
			//1st traversal
			DFS_visit(curr_node,nodeArray,d,f,&t);
		}
	}
	sortByF(top,f,N);
	giveA(f,N);
	giveA(top,N);
	return;
	//reset after getting the order in finishing times
	reset(nodeArray,N,d,f,&t);
	reset(nodeArrayT,N,d,f,&t);

	int j2;
	for (j=0;j<N;j++){
		j2=top[j];
		nd* curr_node = nodeArrayT[j2];
		if(curr_node->visit==0){
			//2st traversal on transpose
			DFS_visit(curr_node,nodeArrayT,d,f,&t);
		}	
	}
}

//print given data
void printData(nd* nodeArray[],int N){
	gives(" N - AdjList\n");
	int j;
	for (j=0;j<N;j++){
		adjNode * head = nodeArray[j]->adjHead;
		give(nodeArray[j]->id);gives("- ");
		while(head!=NULL){
			give(head->id);
			head=head->next;
		}
		gives("\n");
	}
}

int main ( int argc, char *argv[]){
	int E=0,i,j,N=4;
	FILE * fp=fopen(argv[1],"r");
	fscanf(fp,"%d",&N);
	// fscanf(fp,"%d",&E);
	nd** nodeArray = (nd**)malloc(N * sizeof(nd));
	nd** nodeArrayT = (nd**)malloc(N * sizeof(nd));
	int parentArray[N]; //every node can have one parent
	for (j=0;j<N;j++)
		parentArray[j] = -1;//set initial value to parent array

	for (j=0;j<N;j++){
		nodeArray[j] = createNode(j+1); //initialize the nodes of the graph
		nodeArrayT[j] = createNode(j+1); //initialize the nodes of the graph Transpose
	}

	int a,b;

	gives("Input read from file: \t");gives("Note: Nodes start from 1 here: \n");
	E=0;
	while(!feof(fp)){
		fscanf(fp,"%d %d",&a,&b); //scan a line of input
		E++;
		if(a<=N && b<=N){
			give(a+1);
			give(b+1);
			gives("\t");
			makeEdge(nodeArray[a],b+1);//Directed Graph this time - only one directional edge.
			makeEdge(nodeArrayT[b],a+1);
		}
		else {
			gives("Invalid ids-");give(a);give(b);gives("\n");
			return 0;
		}
	}
	fclose(fp);
	gives("\nRecorded edges: \n");
	printData(nodeArray,N);
	gives("\nRecorded Transpose edges: \n");
	printData(nodeArrayT,N);

//Classify every Edge-
	gives("\nGive Groups : \n");
	findSCCs(N,nodeArray,nodeArrayT);
	return 0;
}

