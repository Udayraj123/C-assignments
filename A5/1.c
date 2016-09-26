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
	if(adjHead1==NULL){
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

void resetVisits(nd* nodeArray[],int N){
	int j;
	for (j=0;j<N;j++){
		nodeArray[j]->visit=0;
	}
}

void DFS_print(nd * curr_node,nd * nodeArray[]){

	give(curr_node->id);curr_node->visit++;

	adjNode * head = curr_node->adjHead; //head points to current node's adj list

	//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];

		if(near_node->visit==0){//unexplored
			DFS_print(near_node,nodeArray);
		}
		head=head->next;
	}
}

void printCycle(int childID,int parentID, int parentArray[])
{
	int c=childID;
	while (c != parentID && c!=-1)
	{
		give(c);gives("->");
		c = parentArray[c-1];
	}
	give(parentID);gives("->");
	give(childID);
	gives("\n");
}

int countCycles(int cycleHead[],nd * curr_node,nd * nodeArray[],int parentArray[]){
	int cycleCount=0;
	curr_node->visit++;

	adjNode * head = curr_node->adjHead; //head points to current node's adj list
	//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];

		if(near_node->visit==0){//unexplored
			parentArray[near_node->id-1]=curr_node->id;
			cycleCount += countCycles(cycleHead,near_node,nodeArray,parentArray);
		}

		else if(near_node->visit==1){//grey
		//if visited once only, check if it is not its parent, then it'd be a cycle.
			int parent = parentArray[curr_node->id-1];
			if( parent!= near_node->id && parent!=-1){
				cycleCount++;
			//print path
				printCycle(curr_node->id,near_node->id,parentArray);
			}
		}
		head=head->next;
	}
	//at this point all neighbours are explored.
	curr_node->visit++;
	return cycleCount;
}

void DFS_visit(nd * curr_node,nd * nodeArray[]){
	curr_node->visit++;

	adjNode * head = curr_node->adjHead;//head points to current node's adj list
	//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];

		if(near_node->visit==0){//unexplored
			DFS_visit(near_node,nodeArray);
		}

		head=head->next;
	}
	//at this point all neighbours are explored.
	curr_node->visit++;
}
void checkCycles(nd* nodeArray[],int N,int parentArray[]){
	int  v=0,j,k=0;
	int cycleHead[N]; //to store ids of heads of new cycle paths.

	resetVisits(nodeArray,N);
	gives("Cycles in the graph :\n");
	for (j=0;j<N;j++){
		nd* curr_node = nodeArray[j];
		if(curr_node->visit==0){
			v += countCycles(cycleHead,curr_node,nodeArray,parentArray); //caution : this adds 1 to visit index
		}
	}
	if(v==0){
		gives("No cycle found!\n");return;
	}gives("\n");
	gives("No of cycles :");give(v);gives("\n");
}


void connectedPaths(nd* nodeArray[],int N){
	int v=0,j;
	nd* paths[N]; //to store heads of new connected paths.
	resetVisits(nodeArray,N);

	for (j=0;j<N;j++){
		nd* curr_node = nodeArray[j];
		if(curr_node->visit==0){
			paths[v++]=curr_node; //increment on a new visit
			DFS_visit(curr_node,nodeArray); //caution : this adds 1 to visit index
		}
	}

	gives("\n");gives("No of connected components :");give(v);gives("\n");
	for (j=0;j<v;j++){
		resetVisits(nodeArray,N);
		gives("connected components ");give(j+1);gives(":\t");
		DFS_print(paths[j],nodeArray);//caution : this adds 1 to visit index
		gives("\n");
	}gives("\n");
}

int main ( int argc, char *argv[]){
	int E=3,i,j,N=4;
	FILE * fp=fopen(argv[1],"r");
	fscanf(fp,"%d",&N);
	fscanf(fp,"%d",&E);
	nd** nodeArray = (nd**)malloc(N * sizeof(nd));
	int parentArray[N]; //every node can have one parent
	for (j=0;j<N;j++)
		parentArray[j] = -1;//set initial value to parent array

	for (j=0;j<N;j++)
		nodeArray[j] = createNode(j+1); //initialize the nodes of the graph

	int a,b;

	gives("Input read from file: \n");
	for (i=0;i<E;i++){
		fscanf(fp,"%d, %d",&a,&b);
		if(a<=N && b<=N && a*b>0){
			give(a);
			give(b);
			gives("\t");
			makeEdge(nodeArray[a-1],b);
			makeEdge(nodeArray[b-1],a);
		}
		else {
			gives("Invalid ids-");give(a);give(b);gives("\n");
			return 0;
		}
	}
	fclose(fp);


	gives("\nRecorded edges: \n");
//print given data
	for (j=0;j<N;j++){
		adjNode * head = nodeArray[j]->adjHead;
		gives("Node");give(nodeArray[j]->id);gives("has edges with:\t ");
		while(head!=NULL){
			give(head->id);
			head=head->next;
		}
		gives("\n");
	}

//find number of connected components using DFS
	connectedPaths(nodeArray,N);

//find number of cycles using DFS
	checkCycles(nodeArray,N,parentArray);
	return 0;
}

