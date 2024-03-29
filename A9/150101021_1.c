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


void print(nd* min){
	gives("[");
	give(min->key); give(min->degree); give(min->mark);//[key,degree,mark]
	if(min->parent)give(min->parent->key); //parent
	else give(-1);
	gives("],");
}

void printList(nd* min){
	if(min==NULL){
		gives("empty List !\n");
		return;
	}
	nd* start=min;
	do{
		print(start);
		start=start->right;
	}while(start!=min);
	gives("\n");
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

//for lists
void createChild(nd* min1,nd* min2){
	if(min1==NULL || min2==NULL)return;
	nd* start=min2;
	do{
		start->parent=min1; //set each's parent as min(L1)
		start=start->right;
	}while(start!=min2);

	nd* child= min1->child;// could be null,but Concate handles it.
	child = concateLists(child,min2);
	min1->child=child;

	int size2 = countList(min2);
	min1->degree += size2;
}


void isolate(nd* y){
	if(y==NULL)
		return;
give("isolate");give(y->key);
//requires atleast two elements
	nd* R = y->right;
	nd* L = y->left;
	L->right = R;
	R->left = L;
	y->right=y;
	y->left=y;
}
nd* getNode(nd* min, int key){
	nd* y=NULL;
	if(min!=NULL){
		nd* start=min;
		do{
			if(start->key==key){
				y=start;
				break;
			}
			start=start->right;
		}while(start!=min);
	}
	return y;
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

nd* delete_node(nd* min){
	if(min->left==min)return NULL;
	(min->left)->right = min->right;
	(min->right)->left = min->left;
	return min;
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

nd* heap_link(nd* x,nd* y){
	if(y==NULL ||x==NULL || y->key < x->key){
gives("wrong link\n");
	return y; //y could be the min that has pointer to children
}
	isolate(y);
	y->parent = x;
	nd* child = x->child;
	// gives("X child : ");if(child)give(child->key);
	child = concateLists(y,child);
	child=getMin(child);
	x->child = child;
	// gives("X child : ");if(child)give(child->key);
	x->degree++;
	y->mark = 0;
	return x;
}

nd *extract_min(nd* min){
	nd* newMin=min;
	if(min==NULL || min->right==min){
		min=NULL;
		return NULL;
	}
// Step 1  :
	//make their parents NULL
	putUp(min->child);
// add its children besides the min // Concate the child to parent's child
	concateLists(min,min->child);
	newMin=min->right;
	delete_node(min);
	newMin=getMin(newMin);

//Step 2 : CONSOLIDATE
	//maintain auxillary array of pointers int * a[];
	int maxDeg= getMaxDeg(newMin) + 1;//countList(newMin); // This Has to change

	nd* aux[maxDeg];
	reset(aux,maxDeg);

	nd* head=newMin;
	int d,firstloop=1;
	nd* x,*y;

	return newMin;
	while (checkConflicts(head,maxDeg) ){
		d=head->degree;
		if(aux[d]!=NULL && aux[d]!=head){
			//conflict
			x=head; y=aux[d];
			if(y->key < x->key){
				head=head->right; // if x is vanishing from root list, move on
				//made sure newMin always stays in root list

				heap_link(y,x);//increases degree of parent by one
				
				// gives("\tDEBUG : checkConflicts : ");give(checkConflicts(head,maxDeg));
				printHeap(head,1);

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
	int choice;
	int N,key;
	gives("\nEnter your choice : \n 1.createHeap \n 2.Insert \n 3.extract_min\n4.createRandList\n 0.Quit\n");

	choice=take();
	switch(choice){
		case 1:
		start=NULL;
		break;

		case 9:
		gives("link last 2: ");
		start = heap_link(start->left,(start->right)->right);
		break;

		case 2:
		//insert
		gives("Enter key: "); key = take();
		start = insert(key,start);
		break;

		case 3:
		gives("Extract Min : ");
		if(start != NULL)
			give(start->key);
		else gives("No elements remaining !\n");
		gives("\n");
		start=extract_min(start); //returns to newMin
		break;

		case 4:
		gives("Enter number of elements N: ");
		N=take();
		start = createRandList(N);
		break;


		case 0:
		gives("Quit Program.\n");
		return;
		break;

		default:
		gives("Please Enter Valid Character First!.\n");
		break;
	}

	gives("\n");
	printHeap(start,printFlag);
	showMenu(start);
}
int main(){
	srand(time(NULL));
	nd* start=NULL;
	showMenu(start);
	return 0;
}
