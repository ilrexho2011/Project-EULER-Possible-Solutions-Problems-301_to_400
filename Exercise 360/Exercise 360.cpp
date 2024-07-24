#include<stdio.h>
#include<math.h>
#include<assert.h>
#define r 9765625ll
#define maxnp 10000

typedef struct{int x,y;} point;

int lf[2*r+1]={0}; // lowest factor
point x_y[2*r+1];

int cmp(const void *_a, const void *_b) {
  point *a=(point*)_a,*b=(point*)_b;
  return (a->x-b->x)?a->x-b->x:(a->y-b->y); 
}

point p[maxnp];
int np;

void generate(int now) {
  int a,b,c,d,x,y,i,j;
  c=x_y[now].x;
  d=x_y[now].y;
  assert(np*2<maxnp);  
  for(i=0;i<np;i++){
    a=p[i].x;
    b=p[i].y;
    x=b*d-a*c;
    y=a*d+b*c;
    p[i]=(x<y)?(point){x,y}:(point){y,x};
    x=a*d-b*c; if(x<0)x=-x;
    y=a*c+b*d;
    p[np+i]=(x<y)?(point){x,y}:(point){y,x};
  }
  np*=2;
  qsort(p,np,sizeof(point),cmp);
  for(i=1,j=1;j<np;j++)
    if(p[i-1].x!=p[j].x)
      p[i++]=p[j];
  np=i;
}

int proc(int n) {
  int now,last=1,power=0,prod=1;
  
  while(1){
    now=lf[n];
    if(now==last){power++;if(last%4!=1&&power%2==0)prod*=now;}
    else {
      if(last%4==3 && power%2) return 0;
      if(last==2 && power%2)generate(2);
      if(n==1) break;
      last=now;power=1;
    }
    n/=lf[now];
    if(now%4==1)generate(now);
  }
  return prod;
}

int main() {
  long long dsum=0;
  int x,y,z,d,i,j;
  int prod,sym;
  
  // lowest factor
  lf[0]=1;lf[1]=1;
  for(i=2;i*i<=2*r;i++) if(!lf[i])
    for(j=i;j<=2*r;j+=i) if(!lf[j]) lf[j]=i;
  for(;i<=2*r;i++) if(lf[i]==0)lf[i]=i;
  
  // solve primes
  x_y[2]=(point){1,1};
  for(x=1,x2=1;x2<=2*r;x2+=4*x+4,x+=2)
    for(y=2,d=x2+4;d<=2*r;d+=4*y+4,y+=2)
      if(lf[d]==d) x_y[d]=(x<y)?(point){x,y}:(point){y,x};

  dsum=0;
  for(z=0;3ll*z*z<r*r;z++) {    // y>=x>=z
    
    np=0;
    p[np++]=(point){0,1};

    if(prod=proc(r-z))if(prod*=proc(r+z)) {
      for(i=0;i<np;i++){
        if(p[i].x*prod<=z) continue;
        if(p[i].x>=p[i].y) break;
        sym=z?48:(p[i].x?24:6);
        dsum+=sym*(prod*(p[i].x+p[i].y)+z);
      }
    }
  }
  printf("dsum=%lld\n",dsum<<10);
}