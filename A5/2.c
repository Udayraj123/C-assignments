//Name- Deshmukh Udayraj
//Roll - 150101021
#include<stdio.h>
#include<stdlib.h>

//Below are some functions for convenience.
void give(int a){
	printf("%2d ",a);
}
void gives(char* a){
	printf("%s",a);
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

//acts on graph as per the name suggests
void resetVisits(nd* nodeArray[],int N){
	int j;
	for (j=0;j<N;j++){
		nodeArray[j]->visit=0;
	}
}

int DFS_find(int nd2,nd * nd1,nd * nodeArray[]){
	if(nd1->id==nd2)return 1;
	nd1->visit++;

	adjNode * head = nd1->adjHead;//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];
		if(near_node->visit==0){//unexplored
			if(DFS_find(nd2,near_node,nodeArray))return 1;
		}
		head=head->next;
	}
	//at this point all neighbours are explored.
	nd1->visit++;
	return 0;
}

void checkPath(int N,nd * nodeArray[]){
	int n1,n2;
	gives("\t");
	for(n2=1;n2<=N;n2++){give(n2);gives("\t");}
	gives("\n\n"); //print first row of matrix

//print matrix
for(n1=1;n1<=N;n1++){
		give(n1);gives("\t"); //print first col of matrix (node number)
		//from each node,
		//check if every other node can be reached
		for(n2=1;n2<=N;n2++){
			resetVisits(nodeArray,N);
			give(DFS_find(n2,nodeArray[n1-1],nodeArray));
			gives("\t");
		}
		gives("\n");
	}
}

int main ( int argc, char *argv[]){

	gives("\t\tQ2 : Print Transitive Closure Matrix Of A Graph: \n");

	int E=3,i,j,N=4;
	FILE * fp=fopen(argv[1],"r");
    fscanf(fp,"%d",&N); //take first line to N
	fscanf(fp,"%d",&E); //take next line to E

	nd** nodeArray = (nd**)malloc(N * sizeof(nd));
	for (j=0;j<N;j++)
		nodeArray[j] = createNode(j+1); //initialize the nodes of the graph

	int a,b;

	gives("Input read from file: \n");
	for (i=0;i<E;i++){
		fscanf(fp,"%d, %d",&a,&b);
		if(a<=N && b<=N && a*b>0){ //accept positive integers id less than N
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

//print given data
	gives("\nRecorded edges: \n");
	printData(nodeArray,N);	//print Each Node with its adjacency list

//check path between every pair-
	gives("\n Transitive Closure Matrix: \n");
	checkPath(N,nodeArray); //print the transitivity matrix

	return 0;
}

