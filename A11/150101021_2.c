#include <stdio.h>
#include <stdlib.h>
void swap(int *a,int *b){int t=*a; *a=*b; *b=t; }
void give(int d){printf("%2d ",d);}
void gives(char* s){printf("%s",s); }
int take(){int n; scanf("%d",&n); return n; }

typedef struct sibTreeNode {
	int key;
	int depth;
	struct sibTreeNode *parent;
	struct sibTreeNode *firstChild;
	struct sibTreeNode *nextSibling;

}nd;

typedef struct sibTree {
	nd* root;
	int size,maxDepth;
}nT;

nT* createTree(){
	nT * newTree= malloc(sizeof(nT));
	newTree->size=0;
	newTree->maxDepth=0;
	newTree->root=NULL;	
	return newTree;
}

nd* createNode(int key){
	nd * newNode= malloc(sizeof(nd));
	newNode->key=key;
	newNode->depth=0;
	newNode->parent=NULL;
	newNode->firstChild=NULL;
	newNode->nextSibling=NULL;
	return newNode;
}

void printChildren(nd* root){
	nd* sibling=root->firstChild;
// if(sibling==NULL)gives("*");
	while(sibling!=NULL){
		give(sibling->key);
		sibling=sibling->nextSibling;
	}
	if(root->firstChild!=NULL)gives(" | ");
}
void printDepth(nd* root,int depth){
//base case
	if(root==NULL)return;
	
	if(root->depth>=depth)return;
	if(root->depth==depth-1){
	//print all childrens' siblings and return
		printChildren(root);
	}

//go broader
	printDepth(root->nextSibling,depth);
//go deeper
	printDepth(root->firstChild,depth);
}


void printTree(nT* tree){
	gives("Structure of the tree: \n");
	if(tree==NULL || tree->root==NULL)
		gives("Empty tree !\n");
	else{
		give((tree->root)->key);
		int i=0;
		for (i = 0; i <= tree->maxDepth; ++i){
			printDepth(tree->root,i);
			gives("\n");
		}
		printf("Size :%d, maxDepth : %d\n",tree->size,tree->maxDepth);
		gives("\n");
	}
}


nd* findKey(nd* root,int key){
//base case
	if(root==NULL || root->key==key) return root;

	//in children
	nd* child=findKey(root->firstChild,key);
	if(child!=NULL){
		//not null means found
		return child;
	}
	
	//in next sibling
	nd * sibling=findKey(root->nextSibling,key);
	if(sibling!=NULL){
		//not null means found
		return sibling;
	}
}
void removeLeaf(nd* root,int key){
//base case
	if(root==NULL) return;
	if(root->key==key && root->firstChild==NULL){
//update parent's child-
		if(root->parent)
			(root->parent)->firstChild=root->nextSibling;
		printf("deleted %d.\n",key);
		free(root);
		return;
	}
	if(root->nextSibling != NULL){
		nd *next=root->nextSibling;
		if(next->key==key && next->firstChild==NULL) {
			root->nextSibling=next->nextSibling;
			printf("deleted %d.\n",key);
			free(next);
			return;
		}
	}
	//in children
	removeLeaf(root->firstChild,key);
	//in next sibling
	removeLeaf(root->nextSibling,key);
}


void insertChild(nT* tree,int key1,int key2,int c){
	if(tree==NULL)return;
	nd* newNode=createNode(key2);

	if(tree->root==NULL) {
		newNode->depth=0;
		tree->size++;
		tree->root=newNode;
		return;
	}
	nd* found=findKey(tree->root,key1);
	if(found==NULL){
		return;
	}

	newNode->parent=found;
	newNode->depth=found->depth+1;

	nd* child=found->firstChild;
	if(child==NULL){
		found->firstChild=newNode;
		tree->maxDepth++;
	}
	else
	{
		while(child->nextSibling!=NULL && --c)
			child=child->nextSibling;
		//insert
		newNode->nextSibling=child->nextSibling;
		child->nextSibling=newNode;
	}
	tree->size++;
}

int main() {
	int i; 
//initially empty tree
	nT* tree=createTree();

/***** INTITIAL *******/
	insertChild(tree,1,1,5);
	insertChild(tree,1,2,5);
	insertChild(tree,1,3,5);
	insertChild(tree,1,4,5);
	insertChild(tree,1,5,5);
	insertChild(tree,2,6,5);
	insertChild(tree,2,7,5);
	insertChild(tree,2,8,5);
	insertChild(tree,4,9,5);
	insertChild(tree,9,12,5);
	insertChild(tree,5,10,5);
	insertChild(tree,5,11,5);

	printTree(tree); 
	getchar();
	gives("removes-\n");

/***** TEST *******/
	removeLeaf(tree->root,7);
	removeLeaf(tree->root,3);
	
	printTree(tree); 
	 getchar();
	gives("inserts-\n");
	insertChild(tree,2,99,2);
	insertChild(tree,9,44,2);
	insertChild(tree,5,88,1);
	insertChild(tree,7,22,1);
	printTree(tree); 
	getchar();
	gives("removes-\n");
	removeLeaf(tree->root,4);
	printTree(tree);


	// gives("Enter number of inserts: "); 
	// int n=take();
	// int key1,key2,c;
	// gives("Enter \tkey1 key2 c -\n");
	// for(i=0;i<n;i++){
	// 	printf("Node%d: \t",i+1);
	// 	key1=take();
	// 	key2=take();
	// 	c=take();
	// 	insertChild(tree,key1,key2,c);
	// 	printf("\nsize :%d, maxDepth : %d\n",tree->size,tree->maxDepth);
	// 	printTree(tree);
	// }

	return 0;
}