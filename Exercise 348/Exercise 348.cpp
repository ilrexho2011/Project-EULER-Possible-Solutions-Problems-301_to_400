#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "../tdn.hpp"
#define MAXN
#define INF 1<< 30
typedef unsigned long long ULL;
typedef long long LL;
using namespace std;

const LL N=1000000000;
const int D=digits(N,10).size();
const int A=pow(N,0.5)+5;
const int B=pow(N,0.333333)+5;

LL square[A], cube[B]; // te gjithe kubat deri ne N
vector <LL> pal;
vector <int> qq;

void f(LL &x){
	int a=0;
	int b=pal.size()-1;
	int m;
	while(a<b){
		m=(a+b)/2;
		if(x<=pal[m])b=m;
		else a=m+1;
	}
	if(pal[a]==x)qq[a]++;
}

int main(){
	for(LL i=2;i<A;i++)square[i-2]=i*i;
	for(LL i=2;i<B;i++)cube[i-2]=i*i*i;
	LL n=1;
	int d=1;
	vector <int> dd=digits(n,10);
	while(2*d-1<=D){
		LL m=n*intPow(10,d-1);
		for(int i=d-1;i>=1;i--)m+=(LL)intPow(10,d-1-i)*((LL)dd[i]);
		if(m<N)pal.push_back(m);
		if(2*d<=D){
			m=n*intPow(10,d);
			for(int i=d-1;i>=0;i--)m+=(LL)intPow(10,d-1-i)*((LL)dd[i]);
			if(m<N)pal.push_back(m);
		}
		
		n++;
		dd=digits(n,10);
		d=dd.size();
	}
	sort(pal.begin(), pal.end());
	qq.resize(pal.size());
	for(int i=0;i<int(qq.size());i++)qq[i]=0;
	cout << "Preprocessato\n";
	LL x;
	for(int i=0;i<A;i++)for(int j=0;j<B;j++){
		x=square[i]+cube[j];
		if(x>pal.back())break;
		f(x);
	}
	ULL res=0;
	//~ for(int i=0;i<int(qq.size());i++)cout << pal[i] << " " << qq[i] << "\n";
	for(int i=0;i<int(qq.size());i++)if(qq[i]==4){
		res+=pal[i];
		cout << pal[i] << "\n";
	}
	cout << "Rezultati= " << res << "\n";
}