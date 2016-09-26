//Name- Deshmukh Udayraj
//Roll - 150101021
#include<stdio.h>
#include<stdlib.h>

//Below are some functions for convenience.
void give(int a) {
	printf("%2d ",a);
}
void gives(char* a){
	printf("%s",a);
}

typedef struct adjNode  {
	int id;
	struct adjNode * next;
} adjNode ;

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
	if(adjHead1==NULL){ //If no edge yet, create First edge
		adjHead1 = (adjNode*)malloc(sizeof(adjNode)); // make new adjNode at end
		adjHead1 -> id = id;
		adjHead1 -> next =NULL; //set last one to NULL
		Node->adjHead=adjHead1;
	}
	else{//else Add new edge
		while(adjHead1->next !=NULL)adjHead1 = adjHead1 -> next; //traverse to last id
		adjHead1 -> next = (adjNode*)malloc(sizeof(adjNode)); // make new adjNode at end
		adjHead1 = adjHead1 -> next;
		adjHead1 -> id = id;
		adjHead1 -> next =NULL; //set last one to NULL
	}
	Node->E++;
}

//print given data
void printData(nd* nodeArray[],int N){
	gives(" N - AdjList\n");
	int j;
	for (j=0;j<N;j++){
		adjNode * head = nodeArray[j]->adjHead;
		give(nodeArray[j]->id);gives("| ");
		while(head!=NULL){
			give(head->id);
			head=head->next;
		}
		gives("\n");
	}
}

// resets the Colors, discovery times,etc for a new DFS search on the graph
void reset(nd* nodeArray[],int N,int d[],int* t){
	int j;
	*t=0;
	for (j=0;j<N;j++){
		d[j]= N+1; //set to infinity/sentinel
		nodeArray[j]->visit=0; //set visit to 0(white)
	}
}

/* THEORY FOR DETERMINING EDGES-
For edge u,v
1. If v is visited for the first time as we traverse the edge (u, v), then the edge is a tree edge.
2. Else, v has already been visited:
(a) If v is an ancestor of u, then edge (u, v) is a back edge.
(b) Else, if v is a descendant of u, then edge (u, v) is a forward edge.
(c) Else, if v is neither an ancestor or descendant of u, then edge (u, v) is a cross edge.
*/
void DFS_visit(nd * curr_node,nd * nodeArray[],int d[],int* t){
	//set distance-time-color
	d[curr_node->id -1]= *t;
	*t = *t+1;
	curr_node->visit++; //makes gray
	adjNode * head = curr_node->adjHead;//head points to current node's adj list

	//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];
		give(curr_node->id);gives("->");give(near_node->id);
		if(near_node->visit==1){//Gray
			gives("\t - Back edge\n");
		}
		else if(near_node->visit==2){//Black
                //Will be Forward if near_node is not discovered before curr_node, else its a Cross edge
			if(d[curr_node->id-1] < d[near_node->id-1]) gives("\t - Forward edge\n");
			else gives("\t - Cross edge\n");
		}
		else if(near_node->visit==0){//White => normal tree edge
			gives("\t - Tree edge\n");
			DFS_visit(near_node,nodeArray,d,t);
		}
		head=head->next;
	}
	//at this point all neighbours are explored.
	curr_node->visit++;
}

void classify(int N,nd * nodeArray[]){
	int t=0,d[N];
	reset(nodeArray,N,d,&t);
	int j;
	for (j=0;j<N;j++){
		nd* curr_node = nodeArray[j];
		if(curr_node->visit==0){
			gives("Traversing from : ");
			give(j+1);gives("\n");
			DFS_visit(curr_node,nodeArray,d,&t);
		}
	}
}

int main ( int argc, char *argv[]){

	gives("\t\tQ3 : Classify Edges On DFS Traversal of a graph: \n");

	int E=3,i,j,N=4;
	FILE * fp=fopen(argv[1],"r"); //make file pointer to read file input
	fscanf(fp,"%d",&N); //take first line to N
	fscanf(fp,"%d",&E);//take next line to E

	nd** nodeArray = (nd**)malloc(N * sizeof(nd));
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
			makeEdge(nodeArray[a-1],b);//Directed Graph this time - only one directional edge.
		}
		else {
			gives("Invalid ids-");give(a);give(b);gives("\n");
			gives("Please keep positive nodes inside new.txt");
			return 0;
		}
	}
	fclose(fp);

	gives("\nRecorded edges: \n");
//print Each Node with its adjacency list
	printData(nodeArray,N);

//Classify every Edge-
	gives("\nClassify Edges: \n");
	classify(N,nodeArray);
	return 0;
}

