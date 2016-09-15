//Name- Deshmukh Udayraj
//Roll - 150101021

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

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

void submitted()
{
    gives("Submitted! (Entry point + Exit point exactly 2 and at least one path from one point to another)\n");
}
void nopath()
{
    gives("Bad Luck! (No path from one point to another)\n");
}

int checkPath(int m,int n,int A[][n],int explored[][n],int i,int j,int x2,int y2)
{
    int up=0,down=0,left=0,right=0;

    up=(i-1)>=0?explored[i-1][j]:1;
    down=(i+1)<m?explored[i+1][j]:1;
    left=(j-1)>=0?explored[i][j-1]:1;
    right=(j+1)<n?explored[i][j+1]:1;

    if(up && down && left && right)return 0; //exit only if all explored
    else
    {

        if(up==0)  //either exists or unexplored
        {
            i--; //go up
            explored[i][j]=1;
            if(A[i][j]==1)//if its a L
            {
                if(i==y2 && j==x2)return 1;//if found x2,y2, stop searching
                if( checkPath(m,n,A,explored,i,j,x2,y2) ) return 1; //if zero, continue below.
            }
            //if its not a L OR its blocked, restart from previous point
            i++;//Go another direction from previous point.
            return checkPath(m,n,A,explored,i,j,x2,y2);
        }
        else if(down==0)  //either exists or unexplored
        {
            i++; //go down
            explored[i][j]=1;
            if(A[i][j]==1)
            {
                if(i==y2 && j==x2)return 1;//if found x2,y2, stop searching
                if( checkPath(m,n,A,explored,i,j,x2,y2) ) return 1; //if zero, continue below.
            }
            i--;//Go another direction from previous point.
            return checkPath(m,n,A,explored,i,j,x2,y2);
        }
        else if(right==0)  //either exists or unexplored
        {
            j++; //go right
            explored[i][j]=1;
            if(A[i][j]==1)
            {
                if(i==y2 && j==x2)return 1;//if found x2,y2, stop searching
                if( checkPath(m,n,A,explored,i,j,x2,y2) ) return 1; //if zero, continue below.
            }
            j--;//Go another direction from previous point.
            return checkPath(m,n,A,explored,i,j,x2,y2);
        }
        else if(left==0)   //either exists or unexplored
        {
            j--;//go left 
            explored[i][j]=1;
            if(A[i][j]==1)
            {
                if(i==y2 && j==x2)return 1;//if found x2,y2, stop searching
                if( checkPath(m,n,A,explored,i,j,x2,y2) ) return 1; //if zero, continue below.
            }
            j++;//Go another direction from previous point.
            return checkPath(m,n,A,explored,i,j,x2,y2);
        }
        //if all directions blocked
        else return 0;
    }
}
int main()
{
    gives("Enter dimensions of forest:\n ");
    int m,n;
    gives("Enter num rows : ");
    m=take();
    gives("Enter num cols : ");
    n=take();
    gives("Enter grid: L or T\n");
    int A[m][n];
    int explored[m][n];
    int i,j,t;
    char c;
    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf(" %c",&c);        //take input
            t= (c=='L' || c=='l');
            A[i][j]=t;          
            explored[i][j]=0;  // mark initially unexplored
        }
    }

//check if boundary has only two Ls
    int Lcount=0; //count of 'L's
    int X[m*n],Y[m*n]; // Store x & y of start & end. max sizes are m*n
    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i==0|| j==0 || i==m-1 || j==n-1) //check boundary once
            {
                if(A[i][j]==1)
                {
                    Y[Lcount]=i;        //check for L counts at boundary.
                    X[Lcount]=j;
                    Lcount++;
                }
            }
        }
    }

    if(Lcount==2)
    {
        //continue search
        if(checkPath(m,n,A,explored,Y[0],X[0],X[1],Y[1]))submitted();
        else nopath();
    }
    else
    { //no need to search.
        gives("Bad Luck! (Entry point + Exit point not exactly 2)\n");
    }

    return 0;
}
