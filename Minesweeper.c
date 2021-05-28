#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 4
int a[N][N],b[N][N];
void printfun()
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(b[i][j])
                printf("%2d ",a[i][j]);
            else printf(" * ");
        }
        printf("\n");
    }
//    printf("\n");
}
void printA()
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%2d ",a[i][j]);
        }
        printf("\n");
    }
}
int fun(int i,int j)
{
    if(i<0||i==N||j<0||j==N)
        return 0;
    if(a[i][j]==-1)
        return 1;
    return 0;
}
int main(int argc, char ** argv)
{
    printf("This is a game! argc=%d\n", argc);
    for(int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    int i,j,coordinate,mine,sum,flag;
loop:
    mine=0;
    sum=N*N-1;
    srand((unsigned)time(0));
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(rand()%5==0)
            {
                a[i][j]=-1;
                mine++;
            }
            else a[i][j]=0;
            b[i][j]=0;
        }
    }
    if(mine==0)
    {
        a[rand()%N][rand()%N]=-1;
        mine++;
    }
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(a[i][j]==-1)
            {
                continue;
            }
            a[i][j]+=fun(i-1,j-1);
            a[i][j]+=fun(i-1,j);
            a[i][j]+=fun(i-1,j+1);
            a[i][j]+=fun(i,j+1);
            a[i][j]+=fun(i+1,j+1);
            a[i][j]+=fun(i+1,j);
            a[i][j]+=fun(i+1,j-1);
            a[i][j]+=fun(i,j-1);
        }
    }
    do
    {
        srand((unsigned)time(0));
        i=rand()%N;j=rand()%N;
    }while(a[i][j]==-1);
    b[i][j]=1;
   do
    {
        flag=0;
        do
        {
            system("clear");
            printf(" Number of mines:%d\n",mine);
            printfun();
            if(flag)
                printf("\nThe input is wrong, please re-enter!\n");
            printf("Please enter a two-digit integer for demining(E.g. 12):");
            scanf("%d",&coordinate);
            getchar();
            flag=1;
        }while(coordinate<11||coordinate>N*10+N);
        i=coordinate/10-1;
        j=coordinate%10-1;
            b[i][j]=1;
            sum--;
    }while(a[i][j]!=-1&&sum!=mine);
    printA();
    if(a[i][j]==-1)
        printf("\nBoom!-1 is a landmine!\n");
    else
        printf("\nSuccess! You have cleared all the mines\n");
    getchar();
    goto loop;
    return 0;
}
