#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <vector>
#include <algorithm>

typedef __int64 int64;
struct timer
{
   double t;
   timer() { t=clock(); }
   ~timer() { printf("runtime %.3f secs\n", (clock()-t)/CLOCKS_PER_SEC); }
};

int gcd(int a, int b) //a>b
{ 
   int t;
   while (b!=0)
      t=b, b=a%b, a=t;
   return a;
}
namespace p309
{
   struct abc
   {
      int a,b/*,c*/;
      abc(int a,int b/*, int c*/) // a<b<c
      {
         this->a=a,this->b=b/*,this->c=c*/;
      }
   };
   struct lessByA : public std::binary_function<int, int, bool> 
   {
      abc* pabc;
      lessByA(abc* pabc) { this->pabc=pabc; }
      bool operator()(const int i1, const int i2) const
      {
         return pabc[i1].a < pabc[i2].a;
      }
   };
   struct lessByB : public std::binary_function<int, int, bool> 
   {
      abc* pabc;
      lessByB(abc* pabc) { this->pabc=pabc; }
      bool operator()(const int i1, const int i2) const
      {
         return pabc[i1].b < pabc[i2].b;
      }
   };
   void f309()
   {
      //const int MH=200;
      //const int MH=2501;
      const int MH=1000000;
      std::vector<abc> abcv_obj;
      abcv_obj.reserve(2*MH);
      int nt=0;
      int s=0,t;
      while (t=s, ++s)
      {
         int ss=s*s;
         while (t+=2)
         {
            if (gcd(s,t)>1)
               continue;
            int tt=t*t, c=tt+ss;
            if (c>=MH)
               break;
            int a=2*s*t, b=tt-ss;
            if (a<b)
            {
               int ax=a, bx=b, cx=c;
               do
                  abcv_obj.push_back( abc(ax, bx/*, cx*/) );
               while (ax+=a, bx+=b, cx+=c, cx<MH);
            }
            else
            {
               int ax=a, bx=b, cx=c;
               do
                  abcv_obj.push_back( abc(bx, ax/*, cx*/) );
               while (ax+=a, bx+=b, cx+=c, cx<MH);
            }
         }
         if (s+1==t)
            break;
      }
      s=abcv_obj.size();
      printf("size=%d\n", s);
      std::vector<int> av_obj;
      std::vector<int> bv_obj;
      av_obj.reserve(s);
      bv_obj.reserve(s);
      int i=-1;
      while (++i<s)
      {
         av_obj.push_back(i);
         bv_obj.push_back(i);
      }
      abc* pabc=&abcv_obj.front();
      std::sort(av_obj.begin(),av_obj.end(),lessByA(pabc));
      std::sort(bv_obj.begin(),bv_obj.end(),lessByB(pabc));
      int* pa=&av_obj.front();
      int* pb=&bv_obj.front();
      int j=0;
      i=-1;
      int amax=pabc[pa[s-1]].a;
      int bmax=pabc[pb[s-1]].b;
      printf("amax=%d bmax=%d\n", amax,bmax);
      while (++i<s)
      {
         int ib=pabc[pb[i]].b;
         if (ib>amax)
            break;
         while (pabc[pa[j]].a>=ib)
            --j;
         while (++j<s)
         {
            int ia=pabc[pa[j]].a;
            if (ia>ib)
               break;
            if (ia==ib) // found (a_j, b_j, c_j) (a_i, b_i, c_i) where a_j=b_i
            {

               int64 pay=(int64)pabc[pa[j]].b * (int64)pabc[pb[i]].a;
               int payda=pabc[pa[j]].b + pabc[pb[i]].a;
               if (!(pay%payda))
                     ++nt;
            }
         }
         if (j==s)
            --j;
      }
      i=0;
      while (++i<s)
      {
         int ia=pabc[pa[i]].a;
         if (pabc[pa[i-1]].a==ia) // found (a1, b1, c1) (a2, b2, c2) where a1=a2
         {
            int imax=i, ei=i-1;
            while (++imax<s && ia==pabc[pa[imax]].a)
               ;
            do
            {
               int ii=ei;
               do
               {
                  int64 pay=(int64)pabc[pa[ii]].b * (int64)pabc[pa[i]].b;
                  int payda=pabc[pa[ii]].b + pabc[pa[i]].b;
                  if (!(pay%payda))
                        ++nt;
               }
               while (++ii<i);
            }
            while (++i<imax);
         }
      }
      i=0;
      while (++i<s)
      {
         int ib=pabc[pb[i]].b;
         if (ib==pabc[pb[i-1]].b) // found (a1, b1, c1) (a2, b2, c2) where b1=b2
         {
            int imax=i, ei=i-1;
            while (++imax<s && ib==pabc[pb[imax]].b)
               ;
            do
            {
               int ii=ei;
               do
               {
                  int64 pay=(int64)pabc[pb[ii]].a * (int64)pabc[pb[i]].a;
                  int payda=pabc[pb[ii]].a + pabc[pb[i]].a;
                  if (!(pay%payda))
                        ++nt;
               }
               while (++ii<i);
            }
            while (++i<imax);
         }
      }
      printf("nt=%d\n",nt);
   }
}
int main(int argc, char**argv)
{
   timer t;
   p309::f309();
   return 0;
}