//Name - Udayraj Deshmukh 
//Roll - 150101021
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Below are some Functions for Convenience.
void swap(int*a,int*b){int t=*b;*b=*a;*a=t;}
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void give(int a){printf("%2d ",a);}
void gives(char* a){printf("%s ",a);}
void giveA(int* A,int e){int t=0;for(t=0;t<e;t++)give(A[t]);}
int findA(int key,int A[],int n){
	int i=0; for(i=0;i<n;i++)if(A[i]==key)return 1;
	return -1;
}
int rdm(int dgt){int mod=pow(10,dgt);return rand()%mod;}
/**********    Convenience functions  ******************/
void insertionSort(int A[],int n){ //as sorting is required to give distinct count in the differences
	int i;for(i=1;i<n;i++){
		int key=A[i];
		int j=i-1;
		while(j>=0 && key<A[j]){
			A[j+1]=A[j];
			j--;
		}
		A[j+1]=key;
	}
}

void uniqRandArray(int A[],int n,int dgt){
	int mod=pow(10,dgt);
	if(mod<n){
		gives("UniqArray Not possible.\n");
		return;
	}
	int i=0,key=0;
	for(i=0;i<n;i++){
		do {key=rdm(dgt);		}
		while(findA(key,A,n)==1 || (key*10)<mod);
		A[i]=key;
	}
}


/**********    BST code  ******************/
typedef struct node{
//title, author, year of publication, cost, and number of copies sold
	char* title,*author,*year;
	int cost,num_sold; 
	int prefix,regGrp,reg,publication,check;
	struct node *left, *right;
}nd;

int greaterThan(nd* n1,nd* n2){
	//first compare prefix then regGrp then reg then publication
	if(n1->prefix != n2->prefix)return n1->prefix > n2->prefix;
	else if(n1->regGrp != n2->regGrp)return n1->regGrp > n2->regGrp;
	else if(n1->reg != n2->reg)return n1->reg > n2->reg;
	else if(n1->publication != n2->publication)return n1->publication > n2->publication;
	else 
		//equal
		return -1; 
}
// using a Modulus 10 system with alternate weights of 1 and 3
int calcCheck(int prefix,int regGrp,int reg,int publication){
	 // • Assuming the digits are "abcdefghijkl-m" where m is the check digit. Then the check digit is computed by the following formula: 
	// m = ( [a b c d e f g h i j k l] * [1 3 1 3 1 3 1 3 1 3 1 3] ) mod 10 
	// 440 863 704 514 319
	int digit=1,w=1,chk=0;
	while(prefix>0) {
		w=(digit%2)?1:3;
		chk+= w*prefix%10;
		digit++;
		prefix/=10;
}
	
	while(regGrp>0) {
		w=(digit%2)?1:3;
		chk+= w*regGrp%10;
		digit++;
		regGrp/=10;
}

	while(reg>0) {
		w=(digit%2)?1:3;
		chk+= w*reg%10;
		digit++;
		reg/=10;
}
	
	while(publication>0) {
		w=(digit%2)?1:3;
		chk+= w*publication%10;
		digit++;
		publication/=10;
}
//(prefix%10)+3* (regGrp%10)+ (reg%10)+3* (publication%10)
	if(digit==13)
		return (chk)%10;
	else return -1;
}

nd* createNode(int cost,int num_sold,int prefix,int regGrp,int reg,int publication,char* title,char* author,char* year){
	nd* node=(nd*)malloc(sizeof(nd));
	node->cost=cost;
	node->num_sold=num_sold;
	node->prefix=prefix;
	node->regGrp=regGrp;
	node->reg=reg;
	node->publication=publication;
	node->title=title;
	node->author=author;
	node->year=year;
	node->check = calcCheck(prefix,regGrp,reg,publication);
	node->left=NULL;
	node->right=NULL;
	return node;
}

nd* insert(nd* newNode,nd* root){
	if(root==NULL){return newNode;} //every insertion is done at a leafnode.

	if(greaterThan(newNode,root)!=0) //checks part by part
		root->right = insert(newNode,root->right);//put duplicates into right trees	
	else 
		root->left = insert(newNode,root->left);

	return root; //return the same(unchanged) root for above two cases
}
nd* insert_main(int cost,int num_sold,int prefix,int regGrp,int reg,int publication,char* title,char* author,char* year,nd* root){
	nd* newNode = createNode(cost,num_sold,prefix,regGrp,reg,publication,title,author,year);
	insert(newNode,root);
	return root;
}

void print(nd* root){
	printf("(%d-%d-%d-%d-%d), ",root->prefix,root->regGrp,root->reg,root->publication,root->check);
}

void inorderPrint(nd *root){
	if(root == NULL)return;
    inorderPrint(root->left);//first print left bottommost number
    print(root);
    inorderPrint(root->right);
}


int main(){
	srand(time(NULL));
	int n=5,i;
	int prefix[n],regGrp[n],reg[n],publication[n];
	int prefix1=978,prefix2=979;
//eg of isbn : 978-0-306-40615
	int dgt_prefix=3,//always 3
	dgt_regGrp=1,
	dgt_reg=3,
	dgt_publication=12-( dgt_regGrp + dgt_reg + dgt_prefix);
	for(i=0;i<n;i++)
		prefix[i]=(rdm(1)%2)?prefix1:prefix2; //take current two possiblities, else uncomment below line
	// uniqRandArray(prefix,n,dgt_prefix);
	
	uniqRandArray(regGrp,n,dgt_regGrp);
	uniqRandArray(reg,n,dgt_reg);
	uniqRandArray(publication,n,dgt_publication);
	gives("\n");
	nd* nodeArray[n];
	int cost=50,num_sold=5;
	//int prefix,int regGrp,int reg,int publication
	char* title="title";char* author="author";char* year="year";
	for (i = 0; i < n; ++i) {
		nodeArray[i]=createNode(cost,num_sold,prefix[i],regGrp[i],reg[i],publication[i],title,author,year);
		print(nodeArray[i]);
	}
	

	
	gives("\n");
	return 0;
}
