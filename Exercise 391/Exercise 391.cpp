#include "stdafx.h"
#include <iostream>
#include "math.h"
#include <time.h>
using namespace std;

// PROBLEM 391

int nBits1[65536];
int nBits1Of(int n) {
   int ret = 0;
   while (n>0) {
      if ((n&1)==1) ret++;
      n = n/2;
   }
   return ret;
}
int* s;
int pow2(int n) {
   int ret = 1;
   for (int i=0; i<n; i++) ret = 2*ret;
   return ret;
}
int M(int n){
   int goods, search;
   goods = pow2(n+1)-2;
   while (s[goods]>n) {
      search = goods-1;
      while (s[search]>=s[goods]-n) {
         search--;
      }
      goods = search;
   }
   return s[goods];
}
__int64 cube(int i){
   return (__int64)i*(__int64)i*(__int64)i;
}


int _tmain(int argc, _TCHAR* argv[])
{
	clock_t time = clock();


   int i;
   s = new int[18000000]; s[0] = 0; for (i=1; i<18000000; i++) s[i] = s[i-1] + nBits1Of(i);

   __int64 sum = 0;
   int cand[2001], iCand[2001], nCand;
   int n, min, minLoc, iGoto, sCand, incr, maxs=0, M=0;
   bool dif, found;

   for (n=1; n<=1000; n++) {

      // Initial candidates
      nCand = 0;
      i = 0;
      while (s[i] <= n) {
         cand[i] = i;
         iCand[i] = i;
         nCand++;
         i++;
      }

      // Iterate while there are different candidates
      dif = true;
      while (dif) {

         // find min(iCand) (the candidate that has advanced lest)
         min = iCand[0]; minLoc = 0;
         for (i=1; i<nCand; i++) if (iCand[i]<min) { min = iCand[i]; minLoc = i; }
         // See where cand[minLoc] would go if it was the right candidate
         sCand = s[iCand[minLoc]]+n;
         iGoto = iCand[minLoc]+1;
         while (s[iGoto]<=sCand) {
            iGoto++;
         }

         // if minLoc was the right move; if the other player moved to s[iCand[minLoc]+1],
         // I should still be able to go to s[iGoto]. If not, remove this possibility.
         if (s[iGoto] - s[iCand[minLoc]+1] > n) {
             cand[minLoc] =  cand[nCand-1];
            iCand[minLoc] = iCand[nCand-1];
            nCand--;
            continue;
         }

         // Could I force jumping onto s[iGoto+1] or even further?
         incr = 1;
         while (s[iCand[minLoc]+1]+n >= s[iGoto+incr]) {
            // Add this option (cand[minLoc],iGoto+incr) , if not already in the list
            found = false;
            for (i=0; i<nCand; i++) {
               if (cand[i]==cand[minLoc] && iCand[i]==iGoto+incr) found = true;
            }
            if (!found) {
               cand[nCand] = cand[minLoc];
               iCand[nCand] = iGoto+incr;
               nCand++;
            }
            incr++;
         }

         // So maybe minLoc is the right solution; advance
         iCand[minLoc] = iGoto;
         // See whether there are still different candidates
         dif = false; for (i=1; i<nCand; i++) if (cand[i] != cand[0]) dif = true;
      }
      for (i=0; i<nCand; i++) if (iCand[i]>maxs) maxs = iCand[i];

      M = s[cand[0]];
      sum = sum + M*M*M;
   }
   cout << "sum = " << sum << "\n";
   cout << "max s = " << maxs << "\n";

   time = clock() - time; cout << "time spent = " << time << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); return 0;
}