#include<iostream>

using namespace std;

long long dp[40][3][3];
int vis[40][3][3];
int n;
int True;

long long back(int len,int last,int c)
{
    if(vis[len][last][c]==True) return dp[len][last][c];
    dp[len][last][c]=0;
    vis[len][last][c]=True;
    if(len==n)
    {
        if(last+c==1||last+c==0) dp[len][last][c]=1;

        return dp[len][last][c];
    }
    int l,l1,c1;
    if(last==1&&c==1)
    {
        c1=1;
        if(((0^last)^0)==0) dp[len][last][c]+=back(len+1,0,c1);
    }
    else if(last==1||c==1)
    {
        if(((0^last)^1)==0) dp[len][last][c]+=back(len+1,0,0);
    }
    else
    {
        if(((0^last)^0)==0) dp[len][last][c]+=back(len+1,0,0);
    }

    l=1+last+c;
    if(l==3)
    {
        if(((1^last)^1)==0) dp[len][last][c]+=back(len+1,1,1);
    }
    else if(l==2)
    {
        if(((1^last)^0)==0) dp[len][last][c]+=back(len+1,1,1);
    }
    else if(l==1)
    {
        if(((1^last)^1)==0) dp[len][last][c]+=back(len+1,1,0);
    }
    return dp[len][last][c];

}


int main()
{
    n=30;
    True++;
    cout<<back(0,0,0)<<endl;
    return 0;
}