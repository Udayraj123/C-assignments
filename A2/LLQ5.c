//Name - DESHMUKH UDAYRAJ SHRIKANT
// Roll - 150101021
		#include<stdio.h>
		#include<stdlib.h>
		#include<time.h>
		#include<math.h>
//Some convenience functions-
void give(int x){printf("%d",x);}
void gives(char* x){printf("%s",x);}
void giveN(){printf("\n");}
void giveT(){printf("\t");}
void giveA(int A[],int n){int i=0;while(i<n)printf("%2d ",A[i++]);giveN();}
int take(){
	int n;
	scanf("%d",&n);
	return n;
}
	void randomInput(int A[],int n){//generates random numbers
		for(int t=0;t<n;t++)A[t]=random()%100+20; 			//for less space in terminal. remove if wanted.
	}
	void takeInput(int A[],int n){ //take User input
		gives("Enter elements -");for(int t=0;t<n;t++)A[t]=take();
	}
	void take2Inputs(int A[],int B[],int n){ //take User input
		gives("Enter row-wise data for each process :");giveN();
		gives("Arrv.Time<space>Exec.Time: ");giveN();
		for(int t=0;t<n;t++){A[t]=take();B[t]=take();}
	}

void Merge(int A[],int s,int mid,int e){
//make a new array to merge two halves into
	int *B=malloc(sizeof(int)*(e-s+1));
	int i=0,j=0,k=0;
	//Copy the smaller one first into new array
	for(i=s,j=mid+1; i<=mid && j<=e;){
		int L=A[i],R=A[j], key;
		if(L>R){ key=R;j++;}	else {key=L;i++;}
		B[k++]=key;
	}
//when one halve is exhausted-
	while(i<=mid){
		B[k++]=A[i++]; 
	}
	while(j<=e){
		B[k++]=A[j++]; 
	}
//copy back into original array.
	for(i=s,k=0;i<=e;i++){A[i]=B[k++]; }
}

void MergeSort(int A[],int s,int e){
if(s==e){return;}//0 1 | 2
int mid=(s+e)/2;// midKey=A[mid], nextToMid=A[mid+1];	
MergeSort(A,s,mid);
MergeSort(A,mid+1,e);
Merge(A,s,mid,e);
}


typedef struct list
{
	int time;  //stores the time remaining for process to complete
	int process;  //stores process number
	struct list *next;
}list;

list * create()
{
	list *temp;
	temp=(list*)malloc(sizeof(list));
    temp->next=NULL;
	return temp;
}

void printlist(list *start,int t)
{
	printf("Time %3d  Processess : ",t);
	while(start!=NULL)
	{
		printf("%d ",start->process);
		start=start->next;
	}
	printf("\n");
}

list * timeout(list *start,int i)  //function for when process is completed
{
	list *temp;
	temp=start;
	if(temp->next==NULL)  //for only one element remaining
    {
        start=NULL;
        printlist(start,i);
        return start;
    }
    temp=start->next;
    start->next=NULL;  //incrementing start to the next process
    printlist(temp,i);
	return temp;
}

list * timequantum(list *start,int i)  //function for when time quantum expires
{
	list *temp,*temp1;
	temp=start,temp1=start->next;
	if(temp1==NULL)
	    return start;
	while(temp->next!=NULL)  //find the last element
	    temp=temp->next;
	start->next=NULL;  //cut the start link else loop can be formed
	temp->next=start;  //linking the last element to start
	start=temp1;  //new start will be the second element
	printlist(start,i);
	return start;
}

list * arrival(list *start,int exe,int j,int i)  //function for adding new arrival at last im the list
{
	list *temp,*temp1;
	temp1=create();  //storing new element data
	temp1->time=exe;
	temp1->process=j;
	temp=start;
	if(temp==NULL)  //if empty
	{
	    start=temp1;
        printlist(start,i);
        return start;
	}
	while(temp->next!=NULL)//checking gor last element
	{
		temp=temp->next;
	}
	temp->next=temp1;  //appending to the last
	printlist(start,i);
	return start;
}

void roundrobin(int *arr,int *exe,int n,int t)  //round robin algorithm
{
	int l=0,i=0,j=0;
	list *start;
	start=NULL;
	while(i<=arr[n-1] || start!=NULL)  //check if process is over which would imply that start=null and time is greater than arrival time of last element
	{
	    if(start!=NULL)  //it is possible that start is null and arrival of one element is still left
        {
            int k=start->time;
            start->time=k-1;  //decrementing the remaining time of process left
        }
	    if(start!=NULL && start->time==0)  //if process time over
		{
	        l=i;  //storing when it ends as when it ends the next process starts. From that time to the next time quantum so that their subtraction is time quantum
	        start=timeout(start,i);
		}
		if((i-l)%t==0 && i>l && start!=NULL)  //if the time between last pocess terminating and now time is divisible by time quantum then it should be shifted back
		{
			start=timequantum(start,i);
		}
		if(i==arr[j] && j<n)  //if time of arrival has come
		{
			start=arrival(start,exe[j],j,i);  //funtion for appending the new element to last
			j++;
		}
		i++;
	}
}

void main()
{srand(time(NULL));
	int random=1,n=5;
	gives("\t\t Q5 Round-Robin CPU Time allocation");giveN();
	gives("Enter Number of the processes : ");n=take();
	int *arrival_times=malloc(sizeof(int)*n);
	int *execution_times=malloc(sizeof(int)*n);

	gives("Process Details: ");gives("Press 1 for Random Data, Press 0 for user : ");random=take(); 
	if(random){
		randomInput(arrival_times,n);
		randomInput(execution_times,n);
		MergeSort(arrival_times,0,n-1);
	}
	else {
		take2Inputs(arrival_times,execution_times,n);
	}
	giveN();
	gives("Arrival_times Array: ");giveT();giveA(arrival_times,n);giveN();
	gives("Execution_times Array: ");giveT();giveA(execution_times,n);giveN();
	int time_quantum=50;
gives("Enter TimeQuantum - ");giveT();time_quantum=take();
    int *p1,*p2;
    p1=&arrival_times[0];
    p2=&execution_times[0];
    roundrobin(p1,p2,n,time_quantum);
}