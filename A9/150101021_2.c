//Name - Udayraj Deshmukh
//Roll - 150101021
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define ALPHA 32767
//Below are some functions for convenience.
int rdm(){
	return rand()%100;
}

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

typedef struct node
{
	int key;
	int degree;
	int mark;
	struct node* parent;
	struct node* child;
	struct node* left;
	struct node* right;
}nd;

nd* createNode(int key){
	nd* newNode = (nd*) malloc(sizeof(nd));
	newNode->key=key;
	newNode->degree=0;
	newNode->mark=0;
	newNode->parent = NULL;
	newNode->child = NULL;
	newNode->left = newNode;
	newNode->right = newNode;

	return newNode;
}

nd* insert(int key,nd* min){
	nd* newNode = createNode(key);
	if(min==NULL) return newNode;
	//update new min
	nd* newMin = min;
	if(key < min->key)
		newMin=newNode;
	//also set its parent
	newNode->parent=min->parent;
	// 	 (newNode)
	// min  ^  next_to_min     <-- insert to right of min
	nd* next_min = min->right;
	newNode->left = min;
	newNode->right = next_min;
	min->right = newNode;
	next_min->left = newNode;

	return newMin;
}

nd* createRandList(int size){
	nd* start=createNode(rdm());
	while(--size)
		start= insert(rdm(),start);
	return start;
}

int countList(nd* min){
	if(min==NULL)
		return 0;

	nd* start=min;
	int counter=1;

	while(start->right!=min){
		counter++;
		start=start->right;
	}
	return counter;
}

//UNION
nd* concateLists(nd* min1,nd* min2){
	if(min1==NULL)return min2;
	if(min2==NULL)return min1;

	nd* newMin= ( min1->key < min2->key) ? min1 : min2;
	nd* switch1 = min1->left;
	nd* switch2 = min2->right;

	switch1 -> right = switch2;
	switch2 -> left = switch1;
	min1->left = min2;
	min2->right = min1;

	return newMin;
}


nd * getMin(nd* head){
	if(head==NULL)return NULL;
	nd* start=head;
	nd* min=head;
	do{
		if(head->key < min->key)
			min=head;
		head=head->right;
	}
	while(start!=head);
	return min;
}

nd* delete_node(nd* min){
	//also returns new min
	if(min==NULL || min->left==min)return NULL;
	(min->left)->right = min->right;
	(min->right)->left = min->left;
	return getMin(min->right);
}

void isolate(nd* y){
//requires atleast two elements
	if(y==NULL) return;
	nd* R = y->right;
	nd* L = y->left;
	L->right = R;
	R->left = L;
	y->right=y;
	y->left=y;
}

void goodPrint(nd* root,int depth, int last){
	// give(root->key);
	// give(depth); if(root->parent != NULL)give((root->parent)->key);

	int i;
	for(i=0;i<depth * 6 +4;i++)
		gives(" ");

	if(last){
		if(root->parent == NULL)//the last root node
			gives("\n");
		if(root->child != NULL) //still has children
			for(i=0;i<6;i++)
				gives(" ");
		}
		give(root->key);
	}


	void showHeap(nd* start,nd* root, int depth){
	if(root->right!=start)//first print along rights
		showHeap(start,root->right,depth);

	gives("\n");

	if((root->child != NULL) || (root->parent ==NULL))//if it is a root node & has a child
		goodPrint(root,depth,0);//print that root node
	else
		goodPrint(root,depth,1);//print newline if it has no children or if it has a parent

	if(root->child != NULL) {
		showHeap(root->child,root->child,depth+1); //recurse on child's right list
	}
}

void printHeap(nd* min,int printFlag){
	if(printFlag){
		if(min==NULL)
			gives("Empty Heap\n");
		else{
			gives("\n Structure of the Heap:\n");
			showHeap( min, min, 0 );
			gives("\n");
		}
	}
}


void putUp(nd* child){
	if(child==NULL)return;
	nd* start=child;
	while(child->right != start){
		child->parent=NULL;//put into the root list
		child=child->right;
	}
}

int getMaxDeg(nd* head){
	if(head==NULL)return 0;
	nd* start=head;
	int max=head->degree;
	do{
		if(head->degree > max)
			max=head->degree;
		head=head->right;
	}
	while(start!=head);
	return max;
}

void reset(nd* aux[],int N){
	while(N--)aux[N]=NULL;
}

nd* heap_link(nd* x,nd* y){
	if(y==NULL ||x==NULL || y->key < x->key){
		gives("wrong link\n");
		return y; //y could be the min that has pointer to children
	}
	isolate(y);
	y->parent = x;
	nd* child = x->child;
	child = concateLists(y,child);
	child= getMin(child);
	x->child = child;
	x->degree++;
	y->mark = 0;
	return x;
}
int checkConflicts(nd* head,int maxDeg){
	int d,degrees[maxDeg];
	for(d=0;d<maxDeg;d++)degrees[d]=0; //reset
		nd* start=head;
	do{
		d=head->degree;
		if(degrees[d]==1){
			return 1;//conflict
		}
		else degrees[d]=1;
		head=head->right;
	}
	while(start!=head);
	return 0;
}


nd *extract_min(nd* min){
	nd* newMin=min;
	if(min==NULL)
		return NULL;
	if(min->right==min && min->child==NULL)return NULL;
// Step 1  : //make their parents NULL
	putUp(min->child);
	// add its children besides the min // Concate the child to parent's child
	concateLists(min,min->child);//can be inserted anywhere
	newMin=delete_node(min);

//Step 2 : CONSOLIDATE
	int maxDeg= countList(newMin) + 1;// upper limit
	nd* aux[maxDeg];
	//maintain auxillary array of pointers int * a[];
	reset(aux,maxDeg);

	nd* head=newMin;
	int d;
	nd* x,*y;

	while (checkConflicts(head,maxDeg) ){
		d=head->degree;
		if(aux[d]!=NULL && aux[d]!=head){
			//if conflict
			x=head; y=aux[d];
			if(y->key < x->key){
				head=head->right; // if x is vanishing from root list, move on
				heap_link(y,x);//increases degree of parent by one
			}
			else{
				heap_link(x,y);
				head=head; //if x has updated, stay there
			}
		//update aux[d] & head
			aux[d]=NULL;
		}
		else {
		aux[d]=head;//occupy the NULL
		head=head->right;
	}

}
return newMin;
}


void showMenu(nd* start){
	static int printFlag=1;
	char choice;
	int N,key,shown=0;
	if(printFlag){
		gives("\nEnter your choice : \n S.Showheap \n c.Createheap\n r.createRandList\n i.Insert \n e.Extract Min \n +.Print On \n -.Print Off \n q.Quit\n");
	}
	else gives("\n");
	scanf("%c",&choice);
	switch(choice){
		case '-':
		gives("print flag off");
		printFlag=0;
		break;

		case '+':
		gives("print flag on");
		printFlag=1;
		break;

		case 'S':
		//print
		printHeap(start,1);
		shown=1;
		break;

		case 'c':
		//create empty heap
		gives("Created ");
		start = NULL;
		break;

		case 'i':
		//insert
		gives("Enter key: "); key = take();
		start = insert(key,start);
		break;

		case 'd':
		case 'e':
		//extractmin
		gives("\tExtract Min : ");
		if(start != NULL)
			give(start->key);
		else gives("No elements remaining !");
		gives("\n");
		start=extract_min(start); //returns to newMin
		break;

		case 'r':
		case 'R':
		gives("Enter number of elements N: ");
		N=take();
		start = createRandList(N);
		break;

		case 'q':
		gives("Quit Program.\n");
		return; //exit for other inputs
		break;

		default:
		gives("Please Enter Valid Character First(no numbers!).\n");
		gives("if persists, Try Entering a space before input\n");
		break;
	}
	// gives("\n");
	if(!shown)printHeap(start,printFlag);
	getchar();//to take enter. but may take space
	showMenu(start);
}
int main(){
	srand(time(NULL));
	nd* start=NULL;
	gives("\t\t Assignment 9 : Fibonacci Heap Implementation \n");
	showMenu(start);
	return 0;
}
