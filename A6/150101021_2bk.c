#include<stdio.h>
#include<stdlib.h>

//Below are some functions for convenience.
void give(int a){
	printf("%2d ",a);
}
void gives(char* a){
	printf("%s",a);
}
void giveA(int* A,int e){	int t=0,s=0;	for(t=s;t<e;t++)give(A[t]);gives("\n");}

typedef struct adjNode  {
	int id;
	struct adjNode * next;
}
adjNode ;

typedef struct node {
	int id,E,visit;
	adjNode * adjHead;
} nd;


typedef struct SCCnode {
	int id;
	int size; //no of elements in the SCC.
	int* group; //the group array
	adjNode * adjHead; //edges
} SCCnd;


SCCnd* createSCCNode(int id,int size,int * group){
	SCCnd* newNode = (SCCnd*)malloc(sizeof(SCCnd));
	newNode->id=id;
	newNode->size=size;
	newNode->group=group;
	newNode->adjHead = NULL;
	return newNode;
}

nd* createNode(int id){
	nd* newNode = (nd*)malloc(sizeof(nd));
	newNode->id=id;
	newNode->E=0;
	newNode->visit=0;
	newNode->adjHead = NULL;
	return newNode;
}

adjNode* createAdjNode(int id){
	adjNode* newNode = (adjNode*)malloc(sizeof(adjNode));
	newNode->id=id;
	newNode->next = NULL;
	return newNode;
}


void makeEdge(nd * Node,int id){
	//attaches ids of connected nodes
	adjNode * adjHead1 = Node->adjHead;
	if(adjHead1==NULL){
		Node->adjHead = createAdjNode(id);
	}
	else{
		while(adjHead1->next !=NULL)adjHead1 = adjHead1 -> next; //traverse to last id
		adjHead1 -> next = createAdjNode(id); // make new adjNode at end
	}

	Node->E++;
}

//reset all book keeping
void reset(nd* nodeArray[],int N,int d[],int f[],int* t){
	int j;
	*t=0;
	for (j=0;j<N;j++){
		d[j]= N+1; //set to infinity/sentinel
		f[j]= 0; //initial value
		nodeArray[j]->visit=0;
	}
}


//print given data
void printData(nd* nodeArray[],int N){
	gives(" N - AdjList -\tEdges\n");
	int j;
	for (j=0;j<N;j++){
		adjNode * head = nodeArray[j]->adjHead;
		give(nodeArray[j]->id);gives("| ");
		int counter=0;
		while(head!=NULL){
			give(head->id);
			head=head->next;
			counter++;
		}

		gives("\t(");give(counter);gives(")");
		gives("\n");
	}
}

//print given data of SCC
void printSCCData(SCCnd* nodeArray[],int N){
	gives(" SCC - AdjList -\tEdges\n");
	int j;
	for (j=0;j<N;j++){
		adjNode * head = nodeArray[j]->adjHead;
		give(nodeArray[j]->id);gives("| ");
		int counter=0;
		while(head!=NULL){
			give(head->id);
			head=head->next;
			counter++;
		}
		gives("\t(");give(counter);gives(")");
		gives("\n");
	}
}


void transposeGraph(nd* nodeArray[],nd* nodeArrayT[],int N){
	int j;
	for (j=0;j<N;j++) nodeArrayT[j] = createNode(j+1); //initialize the nodes of the graph

		int i;
	//for each vertex curr_node in graph,
	for ( i = 0; i < N; i++) {
		nd* curr_node = nodeArray[i];
		//traverse each node in its adjList & add curr_node in its list in the transpose graph
		adjNode * head = curr_node->adjHead;
		while(head!=NULL && curr_node->E>0){
			makeEdge(nodeArrayT[head->id-1],curr_node->id);
			head=head->next;
		}
	}

}

void DFS_visit(nd * curr_node,nd * nodeArray[],int d[],int f[],int* t){
	//set distance time color
	d[curr_node->id -1]= *t;
	*t = *t+1;
	curr_node->visit++; //makes gray
	give(curr_node->id);gives(" ");
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
	*t=*t + 1;
	f[curr_node->id-1] = *t;
	// gives("\t");give(curr_node->id);gives("f ");give(*t);
}

//this is just a modified version of DFS_visit above
void groupBySCC(nd * curr_node,nd * nodeArray[],int group[],int* i,int SCC[], int SCC_id){
//here you simply set SCC id and add node id to the group array.
	group[*i]=curr_node->id;
	SCC[curr_node->id-1]=SCC_id;
//time here is actually being referred as index of SCC group
	*i = *i+1;
	curr_node->visit++; //makes gray
	// give(curr_node->id);gives(" "); //we are also printing through the groups array.
	adjNode * head = curr_node->adjHead;//head points to current node's adj list
	//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];
		if(near_node->visit==0){//White
			groupBySCC(near_node,nodeArray,group,i,SCC,SCC_id);
		}
		head=head->next;
	}
	//at this point all neighbours are explored.
	curr_node->visit++;
}


void sortByF(int top[],int f[],int N){
	int max=0,prevMax=5*N,j,topIndex,i,prevTop;
	for (i=0;i<N;i++){
		max=0;
		topIndex=prevTop;
		for (j=0;j<N;j++){
			if(f[j] < prevMax  &&  f[j] > max){
				max=f[j];
				topIndex=j;
			}
		}
		prevMax=f[topIndex];
		top[i] = topIndex; //store node index
		prevTop = topIndex; //this can handle repetition
	}

}


void makeSCCEdge(SCCnd * Node,int id){
	//attaches ids of connected nodes
	adjNode * adjHead1 = Node->adjHead;
	if(adjHead1==NULL){
		Node->adjHead = createAdjNode(id);
	}
	else{
		while(adjHead1->next !=NULL)			adjHead1 = adjHead1 -> next; //traverse to last id
		if(adjHead1->id == id){
			return; //this will prevent duplicate edges being formed
		}
		adjHead1 -> next = createAdjNode(id); // make new adjNode at end
	}
}

void findSCCs(int N,nd * nodeArray[],nd * nodeArrayT[]){

	int t=0,d[N],f[N],top[N];
	reset(nodeArray,N,d,f,&t);

	gives("\n Normal DFS Traversal: \n");
	int i,j;
	for (j=0;j<N;j++){
		nd* curr_node = nodeArray[j];
		if(curr_node->visit==0){
			//1st traversal
			DFS_visit(curr_node,nodeArray,d,f,&t);
			gives("\n");
		}
	}
	sortByF(top,f,N);
	//reset after getting the order in finishing times
	reset(nodeArray,N,d,f,&t);
	reset(nodeArrayT,N,d,f,&t);
	gives("\n Strongly connected : \n");

	int SCC[N]; //stores the SCC_id of each node
	int SCC_id=0; //initialize first id of a SCC
	int group[N][N]; //contains the SCC nodes. max N SCC possible
	int size[N]; //contains the SCC size.
	int j2;
	for (j=0;j<N;j++){
		j2=top[j];
		nd* curr_node = nodeArrayT[j2];
		if(curr_node->visit==0){
			//2st traversal on transpose
			int i=0; //first index of current SCC group
			groupBySCC(curr_node,nodeArrayT,group[SCC_id],&i,SCC,SCC_id);
			size[SCC_id]=i; //check here for bugs
			SCC_id++;
		}
	}
int numSCC=SCC_id; //this is no of SCC groups
//NOw i have each SCC group (with their lengths)  //also I have an N array telling which SCC that belongs to.

//now create special nodes, with nodes array
SCCnd * SCCArray[numSCC];
for(j=0;j<numSCC;j++){
	SCCArray[j]=createSCCNode(j,size[j],group[j]);
}

giveA(SCC,N);
gives("\n");
for(j=0;j<numSCC;j++){
	giveA(group[j],size[j]);
	gives("\n");
}

//since each edge will be traversed once, this takes O(E) time
for(j=0;j<numSCC;j++){
	SCCnd* curr_SCC=SCCArray[j];
	int curr_id=j;
	for(i=0;i<size[j];i++){
		int v = group[j][i]; //ith vertex in current SCC
		//now for neighbours of v, check if they are from different SCC by their SCC_id
		nd* Node = nodeArrayT[v-1];
		adjNode * head = Node->adjHead;//head points to current node's adj list
		while(head!=NULL){//go thru the adjList of Node
			int id = SCC[head->id-1]; //starts from zero
			if(id != curr_id){
				//since we anyway traverse till end in following function,
				makeSCCEdge(curr_SCC,id); //this function adds only unique edges to SCCnode,
			}
			head=head->next;
		}
	}
}

printSCCData(SCCArray,numSCC);

}

int main ( int argc, char *argv[]){
	int E=3,i,j,N=4;
	FILE * fp=fopen("new.txt","r");
	//FILE * fp=fopen(argv[1],"r");
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

	//part A
	nd* nodeArrayT[N];
	transposeGraph(nodeArray,nodeArrayT,N);
	gives("\nTransposed Graph : \n");

	printData(nodeArrayT,N);	//print Each Node with its adjacency list
	//part B & part C
	findSCCs(N,nodeArray,nodeArrayT);
	// printData(nodeArrayT,N);	//print Each Node with its adjacency list


	return 0;
}
