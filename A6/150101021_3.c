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
int take(){
	int n;
	scanf("%d",&n);
	return n;
}


void makeEdge(int id1,int id2, int w,int N,int matrix[][N]){
	//attaches ids of connected nodes
	matrix[id1-1][id2-1]=w;
	matrix[id2-1][id1-1]=w;
}

//print given adjMatrix
void printData(int N, int matrix[][N]){
	int j,i;
	gives("\n Matrix Of weighted edges-\n");
	gives("\t");

//first line (node numbers)
	for (j=0;j<N;j++)give(j+1);gives("\n\n");
	for (j=0;j<N;j++){ //rest of rows
		give(j+1);
		gives("\t");
		for (i=0;i<N;i++)
			give(matrix[j][i]);
		gives("\n");
	}
}

//print calculated MST
void printMST(int N,int matrix[][N],int parent[]){
	int i,w,sum=0;
	gives("\nAn MST of the given graph is \n");
	gives("  Edge \t : Weight\n");
	for ( i = 1;i<N; i++) {// MST will have N-1 edges
		give(parent[i]+1);gives("-");give(i+1); //print parent & the current node
		gives("\t : ");
		w = matrix[i][parent[i]];
		give(w); //print weight of the edge
		sum+=w;
		gives("\n");
	}
	gives("Sum of weights = ");give(sum);gives("\n");
}

//this returns the minimum key vertex which is not in MST
int getMinNode(int N,int key[], int inMST[]) {
   // Initialize min value
	int min = 10000;
	int i,index;
	for (i = 0; i < N; i++){
	//traverse each node, which is not in MST and find whose key is minimum
		if (inMST[i] == 0 && key[i] < min){
			min = key[i];
			index = i;
		}
	}
	return index;
}

void findMST(int N,int matrix[][N],int key[],int parent[],int inMST[]){
	int i,j,w;
	key[0]=0; //Initialize root node, this is required for starting from node 0
	for ( i = 0;i<N-1; i++) { // MST will have N-1 edges
		//following will return the node outside MST & having min key

		int v = getMinNode(N, key, inMST); 							//starts from node 1 (whose key we set 0 above).
        inMST[v] = 1;    											 // Include the new node v in the current MST

        for ( j = 0; j < N; j++){
        	w= matrix[v][j];
       		// w > 0 will check if edge exists between node v and node j
        	if (w>0 && inMST[j] == 0 && w < key[j])								//Updates key values of neighbours of newly added node v-
        	{
        		parent[j] = v; 												//add that vertex to our MST
        		key[j] = w; 												//update the adj node's new key. //this will act like decrease_key as told in class.
        	}
        }
    }

}
void takeManual(int E,int N,int matrix[][N]){
	int i,a,b,w;
	gives("Enter data in the format - u,v,w\n");
	for (i=0;i<E;i++){
		scanf("%d, %d, %d",&a,&b,&w);
		if(a<=N && b<=N && a*w*b>0){ //accept positive integers id less than N
			makeEdge(a,b,w,N,matrix);
		}
		else{
			gives("Invalid numbers-");give(a);give(b);gives("\n");
			gives("Please enter positive ids-");
			i--;
		}
	}
}
int main ( int argc, char *argv[]){
	int E=3,i,j,N=4,fileInput=0;
	FILE * fp;
	if(argc>2)fp=fopen(argv[1],"r");
	else {
		gives("File input or Manual Input ? ( 1/0 ) : "); fileInput=take();
		if(fileInput){
			gives("Opening local input file- new2.txt\n");
			fp=fopen("new2.txt","r");
		}
		else {
			gives("Please enter N and E - ");
			N=take(); E=take();
		}
	}
	if(fileInput){
    	fscanf(fp,"%d",&N); //take first line to N
		fscanf(fp,"%d",&E); //take next line to E
	}

	int key[N], parent[N], inMST[N];
	int matrix[N][N];
	int alpha=100000; //max weight

	//initialize here
	for (i=0;i<N;i++)
	{
		key[i]=alpha;
		parent[i]= -1;
		inMST[i]=0;
		for (j=0;j<N;j++)matrix[i][j] = 0;
	}

if(!fileInput)takeManual(E,N,matrix);
else{
	int a,b,w;
	
	gives("Input read from file: \n");
	for (i=0;i<E;i++){
		fscanf(fp,"%d, %d, %d",&a,&b,&w);
		if(a<=N && b<=N && a*w*b>0){ //accept positive integers id less than N
			give(a); give(b); give(w);			gives(" - ");
			makeEdge(a,b,w,N,matrix);
		}
		else {
			gives("Invalid numbers-");give(a);give(b);gives("\n");
			gives("Please keep positive nodes inside new2.txt");
			gives("It shall have format -\nNo of nodes\nno of Edges\nnext E lines of the form - u,v,w (w is weight of edge(u,v)\n");
				return 0;
			}
		}
		gives(" \n ");
		fclose(fp);
	}

//print what data is read
	printData(N,matrix);
//find MST in O(V^2) time
	findMST(N,matrix,key,parent,inMST);
//print the MST
	printMST(N,matrix,parent);
	return 0;
}
