//Name - Udayraj Deshmukh
//Roll - 150101021
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define DEL -1
#define MOD 20


//Below are some functions for convenience.
int rdm(){
	int rdm=1;
	//always return > 1
	while(rdm <= 1){
		rdm=rand()%MOD;
	}
	return rdm;
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
void giveA(int* A,int e){ 
	int t=0,s=0;	for(t=s;t<e;t++)
	{
		if(A[t]!=DEL)
			give(A[t]);
		else 
			gives("_ ");
	}
	gives("\n");
}
/***********   Printing functions     *********/
void overflow(){
	gives("\t\t NO AVL POS! \n");	
}
void header(){
	gives(" \tKey\tKey\%m\tPos\tCollisions\n");
}


/***********   Hash functions     *********/
int h1(int k,int m){
	return k%m;
}

int h2(int k,int m){
	return 1+ k%(m-1);
}

int h_linear(int k,int i,int m){
//i is like an offset
	return (h1(k,m)+i)%m;
}

int h_quad(int k,int i,int m){
	int c1=1, c2=3;
	return (h1(k,m)+ c1*i + c2*i*i )%m;
}

int h_double(int k,int i,int m){
	return (h1(k,m)+ i*h2(k,m))%m;
}



/***********   Main functions     *********/

void insert(int A[], int k, int m, int method){
	int i=0, index;

	do{
		if (method == 0)
			index = h_linear(k,i,m);
		else 
			if (method == 1)
				index = h_quad(k,i,m);
			else 
				index = h_double(k,i,m);
			i++;
		}
		while(A[index] != DEL && i <= m );
	//i-1 is now number of collisions
		if(i>m){
			overflow();
			return;
		}

		A[index]=k;
		printf("\t%2d\t%2d\t%2d\t%2d \n",k,k%m,index,i-1);

	}
	void delete(int A[],int N,int k){
		int i=0;
		for (i = 0; i < N; ++i){
			if(A[i]==k){
				A[i]=DEL;
				break;
			}
		}
	}

	void clean(int A[],int N){
		while(N--)A[N]=DEL;
	}



/***********   Interface functions     *********/

	void makeHashTables(int HTable[],int HTable1[],int HTable2[],int keys[],int m,int n){
		int i;
		clean(HTable,m); // reset all values to a Sentinel
		clean(HTable1,m); // reset all values to a Sentinel
		clean(HTable2,m); // reset all values to a Sentinel
		
		gives("Linear Probing : \n");
		header();
		for (i = 0; i < n; ++i)
			insert(HTable,keys[i],m,0);gives("\n");

		gives("Quadratic Probing: \n");
		header();
		for (i = 0; i < n; ++i)
			insert(HTable1,keys[i],m,1);gives("\n");

		gives("Double hashing : \n");
		header();
		for (i = 0; i < n; ++i)
			insert(HTable2,keys[i],m,2);gives("\n");

		gives("Linear Probing :\t ");
		giveA(HTable,m);gives("\n");
		gives("Quadratic Probing:\t ");
		giveA(HTable1,m);gives("\n");
		gives("Double hashing :\t ");
		giveA(HTable2,m);gives("\n");

	}



/***********   Code for Part 1    *********/

	void part1(){
		int i; 
		gives("Enter Size of HTable m : "); int m=take();
		int HTable[m], HTable1[m], HTable2[m];
		int n;
		gives("Enter No of keys : "); 
		n=take();
		if(n>m){
			gives("No of keys will overflow. ");
			n=m;
		}
		gives("Taking input of ");give(n);gives("keys : ");
		int keys[n];
		for (i = 0; i < n; ++i) {
			keys[i]=take();
		}
		gives("\n");
		//this reuses the tables by cleaning them
		makeHashTables(HTable,HTable1,HTable2,keys,m,n);
	}


/***********   Code for Part 2     *********/

	void part2(){
		int i;
//part 2 
		int randM=rdm();
		int randN=rdm();
		gives("\n");
		gives("Random size of Table : ");give(randM);gives("\n");
		gives("Random No of keys : ");give(randN);gives("\n");

		int hTable[randM], hTable1[randM], hTable2[randM];
		int randKeys[randN];

		if(randN>randM){
			gives("No of keys will overflow.\n ");
			randN=randM;
		}
		gives("Random Input : ");give(randN);gives("keys : ");

		for (i = 0; i < randN; ++i)
			give(randKeys[i]=rdm());
		gives("\n");gives("\n");

		//this reuses the tables by cleaning them
		makeHashTables(hTable,hTable1,hTable2,randKeys,randM,randN);
	}

	int main(){
		srand(time(NULL));
		gives("Part 1 or Part 2 (0/1) "); int choice=take();
		if(choice==0)
			part1();
		else 
			part2();


		return 0;
	}