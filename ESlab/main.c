#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MOD 1000000
#define ALPHA (MOD+1)
/******* UTILITY FUNCTIONS ************/
int rdm(){
	return rand()%MOD;
}

void seed(){
	int N=100000;
	printf("%d\n",N);
	while(N--)
		printf("%d\n",rdm());

}

/******* Main Structure ************/
typedef struct node
{
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;
}nd;

nd* createNode(int x){
	nd* newNode=malloc(sizeof(nd));
	newNode->key=x;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->parent=NULL;
	return newNode;
}

void swap(nd* a,nd* b){
	int t=a->key;
	a->key=b->key;
	b->key=t;
}
/******* Add Function ************/

nd* insert(nd* root,int x){
	if(root==NULL){
		return createNode(x);
	}
	if(x <= root->key){
		root->left=insert(root->left,x);
		(root->left)->parent=root;
	}
	else {
		root->right=insert(root->right,x);
		(root->right)->parent=root;
	}
	return root;
}

int gap(int a,int b){
	if(a>b)return a-b;
	else return b-a;
}

int findClosest(nd* root,int key,int minGap,int closest){ 
	int newGap;
	if(root==NULL)return -1;
	if(root->key==key)
		return root->key;
	
	if(key <= root->key){
		if(root->left !=NULL){
			newGap=gap(root->left->key,key);
			if(newGap<minGap){
				minGap=minGap;
				closest=root->left->key;
			}
			closest=findClosest(root->left,key,minGap,closest);
		}
	}
	else {
		if(root->right !=NULL){
			newGap=gap(root->right->key,key);
			if(newGap<minGap){
				minGap=minGap;
				closest=root->right->key;
			}
			closest=findClosest(root->right,key,minGap,closest);
		}
	}
	return closest;
}
/******* Remove Function ************/

void Remove(nd* mainRoot,nd* root,int key,int* deleted,int left){
	if(root==NULL){
		return;
	}
//update min,max pointers also.
	if( root->key == key){
		
		root->key=ALPHA; // set its value to infinity.
		nd* temp=root;

		while(temp!=NULL){
			if(temp->right==NULL && temp->left==NULL && temp->parent !=NULL){
			//at leaf node,
			//adjust parent's child pointer
				if(left==1)(temp->parent)->left=NULL;
				else (temp->parent)->right=NULL;
				//then free the found node
				printf("deleted.\n");
				free(temp);
				*deleted=1;
				break;
			}
				//swap with left if exists, else with right until temp is null.
			if(temp->left != NULL){
				swap(temp,temp->left);
				temp=temp->left;
				left=1;
			}
			else if(temp->right != NULL)
			{
				swap(temp,temp->right);
				temp=temp->right;
				left=0;
			}
		}
		return;
	}

	if(root->left==NULL && root->right==NULL){
		if(*deleted != 1){
		//give closest one here - 
			//along the search path, maintain the closest one.
			printf("closest : %d\n",findClosest(mainRoot,key,gap(root->key,key),mainRoot->key));
			return;
		}
	}

	if(key <= root->key)
		Remove(root,root->left,key,deleted,1); //left = 1
	else 
		Remove(root,root->right,key,deleted,0);//left = 0
}

/******* Searching Function ************/

nd* find(nd* root,int key){
	if(root==NULL || root->key==key)
		return root;
	if(key <= root->key)
		return find(root->left,key);
	else 
		return find(root->right,key);
}


int countN(nd* root,int key){
	int counter = 0 ;
	if(root==NULL )
		return 0;
	if(root->key==key)
		counter++;
	if(key >root->key)
		counter+=countN(root->right,key);
	else
		counter+=countN(root->left,key);

	return counter;
}

int findMax(nd* root){
	if(root==NULL)
		return -1;
	if(root->right==NULL)
		return root->key;
	return findMax(root->right); //the rightmost
}

int findMin(nd* root){
	if(root==NULL)
		return -1;
	if(root->left==NULL)
		return root->key;
	return findMin(root->left); //the leftmost
}

/******* Printing Function ************/

void inorderPrint(nd* root){
	if(root==NULL)return;
	inorderPrint(root->left);
	printf("%d ",root->key);
	inorderPrint(root->right);
}

void postorderPrint(nd* root){
	if(root==NULL)return;
	printf("%d ",root->key);
	postorderPrint(root->left);
	postorderPrint(root->right);
}


void showMenu(nd* root){
	int choice;
	printf("\nEnter your choice : \n 1.Insert\n 2.Remove\n 3.Count Same Salary\n 4.Min Salary\n 5.Max Salary\n 6.Inorder Print\n 7.postOrder Print\n 0.Exit\n choice: ");
	scanf("%d",&choice);
	int key,deleted=0;
	switch(choice){
		case 1: 
		printf("Enter key : "); scanf("%d",&key);
		insert(root,key);

		break;
		case 2: 
		printf("Enter key : "); scanf("%d",&key);
		Remove(root,root,key,&deleted,0);
		break;
		case 3: 
		printf("Enter key : "); scanf("%d",&key);
		printf("Count Key->%d\n", countN(root,key));
		break;
		case 4: 
		printf("Min->%d\n", findMin(root));
		break;
		case 5: 
		printf("Max->%d\n", findMax(root));
		break;
		case 6: 
		inorderPrint(root);printf("\n");
		break;
		case 7: 
		postorderPrint(root);printf("\n");
		break;
		case 0: 
		return;
		break;
		default:
		printf("Please enter correct choice\n");

		break;
	}
	showMenu(root);

}

int main(){
	srand(time(NULL));

// seed(); return 0; //initialize test file with random numbers

//Initialize Database from file-
	int t,N;
	nd* root=NULL;
	FILE * fp;
	int file;
	printf("Enter input file no (1/2) : "); scanf("%d",&file);

		//fp=fopen("new.txt","r");
	 if(file==1)
	 	fp=fopen("input1.txt","r");
	 else 
	 	fp=fopen("input2.txt","r");
	 	
	fscanf(fp,"%d",&N);
	while(!feof(fp) && N--){
		fscanf(fp,"%d",&t);	
		root = insert(root,t);
	}
	showMenu(root);

	return 0;
}