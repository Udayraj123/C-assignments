//Name- Deshmukh Udayraj
//Roll - 150101021

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void swap(int*a,int*b)
{
    int t=*b;
    *b=*a;
    *a=t;
}

//Below are some functions for convenience.
void give(int a)
{
    printf("%2d ",a);
}
void gives(char* a)
{
    printf("%s",a);
}

int take()
{
    int n;
    scanf("%d",&n);
    return n;
}

typedef struct node {
    int val,row,col;
    struct node *down,*right;
} nd;

nd* createNode(int val,int row,int col){
    nd* newNode = (nd*)malloc(sizeof(nd));
    newNode->val=val;
    newNode->row=row;
    newNode->col=col;
    newNode->down=NULL;
    newNode->right=NULL;
}

void makeColHeads(nd * head,int row,int col){
    nd * head1 = head;
    int counter=1;
    while(counter != col){
        nd* new=createNode(0,row,counter++); //0 since initially 0 nonzero numbers
        head->right = new;
        new->right = head1;
        head = head -> right;
    }
}

void makeRowHeads(nd * head,int row,int col){
    nd * head1 = head;
    int counter=1;
    while(counter != row){
        nd* new=createNode(0,counter++,col); //0 since initially 0 nonzero numbers
        head->down = new;
        new->down = head1;
        head = head -> down;
    }
}

void insertDown(nd* cHead,int row,int col,int val){
     nd* element=cHead;
    nd * nextElement= element->down;
     while(element->down!=cHead && nextElement->row <= row){
        element=element->down;
        nextElement= nextElement->down;
    }
    nd* new=createNode(val,row,col); //0 since initially 0 nonzero numbers
        element->down = new;
        new->down = nextElement;
        head = head -> down;
}

void insertNode(int row,int col,nd* mainHeader,int val){
    nd *mainHeader1= mainHeader;
    int colCount=0;
    //reach its col Head
    for(colCount=0;colCount<col;colCount++){
        mainHeader=mainHeader->right;
    }
    nd* cHead = mainHeader; //store col
   
    insertDown(cHead,row,col,val); //insert in the vertical list.
    //now link to horiz list


}

int uniqueNZ(int r,int A[],int nonzeros){
    int i=0;
    for (i=0;i<nonzeros;i++){
        if(A[i]==r || r==0)return 0;
    }
    return 1;
}

int main()
{
    srand(time(NULL));
    gives("Enter dimensions of sparse matrix:\n ");
    int m,n,nonzeros;
    gives("Enter num rows : ");
    m=take();
    gives("Enter num cols : ");
    n=take();
    nonzeros=m*n;
    while(!(nonzeros<m && nonzeros<n)){gives("Enter nonzeros (less than rows or cols) : ");    nonzeros=take();}
    
    //make main Controller head
    nd* mainHeader=createNode(nonzeros,m,n);
    mainHeader->right=mainHeader; //initially loop to itself
    mainHeader->down=mainHeader; //initially loop to itself
    mainHeader->row=m;
    mainHeader->col=n;
    
    //make column heads & row heads
    makeRowHeads(mainHeader,m,n);       
    makeColHeads(mainHeader,m,n);       
    

    int i,j=0,r,c,X[nonzeros],Y[nonzeros];
    while(j<nonzeros){
        r=rand()%m;
        c=rand()%n;
        if(uniqueNZ(r,X,nonzeros) && uniqueNZ(c,Y,nonzeros)){ //check unique & nonzero
            Y[j]=r;
            X[j]=r;
            j++;
        }
    }
    // now random pairs ready

/******Orig in my room pc ****/

    insertNode(Y[i],X[i],mainHeader,rand()%100);


    return 0;
}
