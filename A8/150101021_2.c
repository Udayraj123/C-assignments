//Name : Deshmukh Udayraj 
//Roll : 150101021
#include<stdio.h>
#include<stdlib.h>
#define alpha 32767
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

typedef struct node  {
	int key,degree;
	struct node * sibling, //goes right
	* parent,//goes up
	* leftMostChild;//goes down
}nd ;

nd* createHeap(int key){
	nd* newNode = (nd*)malloc(sizeof(nd));
	newNode->key = key;
	newNode->degree=0; // this is the k from Bk
	newNode->sibling = NULL;
	newNode->parent = NULL;
	newNode->leftMostChild = NULL;
	return newNode;
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
		if(root->leftMostChild != NULL) //still has children
			for(i=0;i<6;i++)
				gives(" ");
		}
		give(root->key);
	}

	void showHeap(nd* root, int depth){
	if(root->sibling!=NULL)//first print along siblings
		showHeap(root->sibling,depth);

	gives("\n");

	if((root->leftMostChild != NULL) || (root->parent ==NULL))//if it is a root node & has a child
		goodPrint(root,depth,0);//print that root node
	else
		goodPrint(root,depth,1);//print newline if it has no children or if it has a parent

	if(root->leftMostChild != NULL) {
		showHeap(root->leftMostChild,depth+1); //recurse on child's sibling list
	}
}

void printHeap(nd* root,int printFlag){
	if(printFlag){
		if(root==NULL)
			gives("Empty Heap\n");
		else{
			gives("\n Structure of the Heap:\n");
			showHeap( root, 0 );
		}
	}
}

nd* mergeBTs(nd* H1,nd* H2){
	if(H1==NULL)return H2;
	if(H2==NULL)return H1;
//merges two rootlists
	nd* newHead;
	if(H1->degree <= H2->degree){
		newHead=H1; H1=H1->sibling;
	}
	else{
		newHead=H2; H2=H2->sibling;
	}

	nd * returnHead=newHead; //we will return the root of the list at end.
	int d1,d2;
	while(H1!=NULL && H2!=NULL){
		d1=H1->degree;
		d2=H2->degree;
		if(d1<d2){
//add to the new merged list. (no change in degrees)
			newHead->sibling=H1;
			newHead=newHead->sibling;
			H1=H1->sibling;
		}
		else{
			newHead->sibling=H2;
			newHead=newHead->sibling;
			H2=H2->sibling;
		}
	}
//attach the remaining ones
	if(H1!=NULL)
		newHead->sibling=H1;
	if(H2!=NULL)
		newHead->sibling=H2;
	
	return returnHead; //either H1 or H2 whoever's 1st had lower degree
}

void makeChild(nd* parent,nd* child){
	parent->degree++; // manip degrees here.
	child->parent = parent;
	child->sibling = parent->leftMostChild; //ordering this way
	parent->leftMostChild = child;
}


nd* union_heap(nd* H1,nd* H2){
	if(H1==NULL)return H2;
	if(H2==NULL)return H1;
//step 1 ; take one from each heap acc to degrees, O(logn)
	nd * newH = mergeBTs(H1,H2);

//step 2 ; //combine while traversing root list (which has duplicates now) 
	nd* prev = NULL;
	nd* x = newH;
	nd* next_x = x->sibling;

	//we are looking at pairs x & next_x, so both shud exists
	while(next_x!=NULL){ 
		if ((x->degree != next_x->degree) 		//Case 1: Orders of x and next-x are not same, we simply move ahead
			|| ( (next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree)) 	// or Case 2 : next_next_x also has same degree as next_x & x, then move ahead
		{//move ahead
			prev = x;
			x = next_x;
		} 
		else {
			//Case 3 : If key of x is smaller than or equal to key of next-x,
			if(x->key<=next_x->key){
				x->sibling = next_x->sibling; //remove next_x from root list
				makeChild(x,next_x);
			}
			else{
				//Case 4 :x's key greater. here we are removing x from root list.
				if (prev == NULL)
					newH = next_x;
				else
					prev->sibling = next_x;
				//join x to next_x : 
				makeChild(next_x,x);
				x = next_x;
			}
		}
		next_x = x->sibling;
	}
	return newH;
}

nd* insert(nd* Head,int key){
	nd* x=createHeap(key);
	nd* newH = union_heap(Head,x); //min will stay in root list since we are inserting in root list
	return newH;
}


nd* reverseChildren(nd* child,nd** newRoot){
	if(child->sibling==NULL){
		*newRoot = child; //keep track of the last child as the newRoot
		return child;
	} 
		//backtrack method for reversing
	nd* counter_part = reverseChildren(child->sibling,newRoot);
	counter_part->sibling=child;
	return child;
}

int extractMin(nd** rootptr){
	if(*rootptr==NULL){
		return alpha;//defined using #define
	}
	nd* Head=*rootptr;
	nd* min=Head;
	nd* pre_min=NULL;
	//point to minimum & its previous node in rootlist
	while(Head->sibling!=NULL){
		if((Head->sibling)->key < min->key){
			pre_min=Head;
			min=Head->sibling;
		}
		Head=Head->sibling;
	}
	int minKey = min->key;
//remove min from rootList:
	if(pre_min!=NULL){
		pre_min->sibling=min->sibling;
	}
	else if(min== *rootptr){//if min was the first in rootlist
		*rootptr=min->sibling; //min->sibling could be null. in that case we get binHeap from min's children.
	}

	//make a binomial heap from children of min node
	//REVERSE CHILDREN we reverse the order of children as they are ordered from Bk-1 to B0
	nd* child = min->leftMostChild;
	if(child !=NULL){
		nd* newRoot;
		child = reverseChildren(child,&newRoot);
		child -> sibling = NULL;//since this is now the end of the list
		newRoot->parent=NULL; //since we are removing min
		*rootptr = union_heap(newRoot,*rootptr);	
	}
	free(min);
	return minKey;
}

void showMenu(nd* Head){
	char choice;
	static int printFlag=1;
	int key,min;
	nd* newRoot,*child;
	if(printFlag){	
		gives("\nEnter your choice : \n S.Showheap \t c.Createheap \t i.Insert \n e.Extract Min \t +.Print On \t -.Print Off \n q.Quit\n");
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
		printHeap(Head,1);
		break;

		case 'c':
		//create empty heap
		gives("Created ");
		Head = NULL;
		printHeap(Head,printFlag);
		break;

		//debug here - 
		case 'r':
		//reverse root list
		child = Head;
		child = reverseChildren(child,&newRoot);
		child -> sibling = NULL;//since this is now the end of the list
		printHeap(newRoot,printFlag);
		break;

		case 'i':
		//insert
		key = take();
		Head = insert(Head,key);
		printHeap(Head,printFlag);
		break;

		case 'd':
		case 'e':
		//extractmin
		gives("\tExtract Min : ");
		min=extractMin(&Head);
		if(min!=alpha)
			give(min);
		else 
			gives("No Nodes remaining to extract !");
		gives("\n");
		printHeap(Head,printFlag);
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

	getchar();//to wait
	showMenu(Head);
}

int main ( int argc, char *argv[]){
	gives("\t\t Assignment 8 : Binomial Heap Implementation \n");
	// Start the command based navigation-
	nd* Head=NULL;
	showMenu(Head);
	return 0;
}
