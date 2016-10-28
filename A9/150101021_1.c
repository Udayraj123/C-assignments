//Name - Udayraj Deshmukh
//Roll - 150101021
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

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
//later update the child of the newMin to currMin's
//also set its parent
	nd* newNode = createNode(key);
	if(min==NULL) return newNode;
	
	//update new min
	nd* newMin = min;
	if(key < min->key)
		newMin=newNode; 
	
	// 	 (newNode)
	// min  ^  next_min     <-- insert to right of min
	nd* next_min = min->right;
	newNode->left = min;
	newNode->right = next_min;
	min->right = newNode;
	next_min->left = newNode;

	return newMin;
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

nd* createRandList(int size){
	nd* start=createNode(rdm());
	
	while(--size)
		start= insert(rdm(),start);

	return start;
}

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
//requires atleast two elements
	nd* R = y->right;
	nd* L = y->left;
	L->right = R;
	R->left = L;
	y->right=y;
	y->left=y;
}
void heap_link(nd* L,nd* y,nd* x){
	if(L==NULL ||y==NULL ||x==NULL )return;

//y could be the min that has pointer to children
	isolate(y); 
	y->parent = x;
	nd* child = x->child;
	child = concateLists(y,child);
	x->child = child;
	x->degree++;
	y->mark = 0;
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
void showMenu(nd* start1,nd* start2){
	int choice;
	int N1,N2,listNo,key;
	nd* start;
	gives("\nEnter your choice : \n 1.createRandLists \n 2.Insert \n 3.countLists \n 4.concateLists\n 5.heap_link \n 6.createChild(L1,L2) \n 0.Quit\n");

	choice=take();	
	switch(choice){
		case 1:
		gives("Enter number of elements N1 & N2 : ");
		N1=take();
		N2=take();
		start1 = createRandList(N1);
		start2 = createRandList(N2);
		break;

		case 2:
		//insert
		gives("List 1 or List 2? (1/2)");
		listNo=take();
		key = take();
		if(listNo==1)
			start1 = insert(key,start1);
		else
			start2 = insert(key,start2);
		break;

		case 3:
		gives("\n");
		gives("\tCount of List 1: ");give(countList(start1));gives("\n");
		gives("\tCount of List 2: ");give(countList(start2));gives("\n");
		gives("\n");
		break;

		case 4:
		start=concateLists(start1,start2);
		break;


		case 5:
		gives("List 1 or List 2? (1/2): "); listNo=take();
		start= (listNo==1)?start1:start2;
		gives("\n From ");
		printList(start);
		gives("\nEnter x & y to heap_link : ");
		nd* X=getNode(start,take());
		nd* Y=getNode(start,take());

		if(X !=NULL && Y !=NULL)
			heap_link(start,Y,X);
		else
			gives("Not Found !\n");
		gives("\n");
		break;
		case 6:
		createChild(start1,start2);
		break;

		case 0:
		gives("Quit Program.\n");
		return; 
		break;

		default:
		gives("Please Enter Valid Character First!.\n");
		break;
	}
	gives("List 1: ");printList(start1);
	gives("\n");
	gives("List 2: ");printList(start2);

	showMenu(start1,start2);
}
int main(){
	srand(time(NULL));
	nd* start1=NULL;
	nd* start2=NULL;
	showMenu(start1,start2);
	return 0;
}