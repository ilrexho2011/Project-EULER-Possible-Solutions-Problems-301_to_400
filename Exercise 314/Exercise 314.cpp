include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

#define SQR(x) (x)*(x)

typedef long long ll;

struct bxy {
  int x;
  int y;
  double a;
  double p;
  bxy(int x,int y,double a,double p) {
    this->x = x;
    this->y = y;
    this->a = a;
    this->p = p;
  }
};

vector<bxy> **tbst;
vector<bxy> **bbst;

double dist(int x1,int y1,int x2,int y2) {
  return sqrt(SQR(x1-x2)+SQR(y2-y1));
}

double area(int xy[][2],int l) {
  double a = 0;
  for(int i=0;i<l;i++) {
    int im1 = i > 0 ? i-1 : l-1;
    int ip1 = i < l-1 ? i+1 : 0;
    a += xy[i][0]*(xy[ip1][1]-xy[im1][1]);
  }
  if(a < 0) a = -a;
  return a/2;
}

void maximize(int hsize) {
  double maxratio = 0;
  int xy[4][2];
  for(int x=1;x<=hsize;x++) {
    for(int y=hsize;y>x;y--) {
      xy[0][0] = xy[1][1] = y;
      xy[0][1] = xy[1][0] = x;
      double ta = 0;
      double tp = 0;
      if(tbst[x][y].size() > 0) {
        ta = tbst[x][y][0].a;
        tp = tbst[x][y][0].p;
      }
      for(int x2=0;x2<x;x2++) {
        double ymin = (y-hsize)/x * x2 + hsize;
        for(int y2=hsize;y2>=y && y2 >= ymin;y2--) {
          xy[2][0] = x2;
          xy[2][1] = y2;
          xy[3][0] = y2;
          xy[3][1] = x2;
          double p,a;
          p = dist(x,y,x2,y2)+dist(y,x,y2,x2);
          a = area(xy,4);
          bxy &x2y2bbst = bbst[x2][y2][0];
          a += x2y2bbst.a;
          p += x2y2bbst.p;
          if(bbst[x][y].size() == 0) {
            bbst[x][y].push_back(bxy(x2,y2,a,p));
          }
          else {
            if((ta+a)*(tp+bbst[x][y][0].p) > (tp+p)*(ta+bbst[x][y][0].a)) {
              bbst[x][y].erase(bbst[x][y].begin(),bbst[x][y].end());
              bbst[x][y].push_back(bxy(x2,y2,a,p));
            }
            else if((ta+a)*(tp+bbst[x][y][0].p) == (tp+p)*(ta+bbst[x][y][0].a)) {
              bbst[x][y].push_back(bxy(x2,y2,a,p));
            }
          }
          if(x2 == 0) break;
        }
      }
    }
/*
    if(bbst[x][hsize].size() > 0) {
      bxy xybbst = bbst[x][hsize][0];
      double a = xybbst.a;
      double p = xybbst.p;
      double ratio = a/p;
      printf("%d %21.18f %21.18f %21.18f\n",x,a,p,ratio);
    }
*/
  }
  for(int x=hsize;x>0;x--) {
    for(int y=hsize;y>=x;y--) {
      xy[0][0] = xy[1][1] = x;
      xy[0][1] = xy[1][0] = y;
      double ba = 0;
      double bp = 0;
      if(bbst[x][y].size() > 0) {
        ba = bbst[x][y][0].a;
        bp = bbst[x][y][0].p;
      }
      for(int x2=x+1;x2<=y;x2++) {
        for(int y2=y;y2>=x2 && y2 > x+y-x2;y2--) {
          xy[2][0] = y2;
          xy[2][1] = x2;
          xy[3][0] = x2;
          xy[3][1] = y2;
          double p,a;
          double p2=0,a2=0;
          p = dist(x,y,x2,y2)+dist(y,x,y2,x2);
          if(x2==y2) {
            a = area(xy,3);
          }
          else {
            bxy &x2y2tbst = tbst[x2][y2][0];
            p2 = p+dist(x2,y2,y2,x2);
            a2 = area(xy,4);
            a = a2+x2y2tbst.a;
            p += x2y2tbst.p;
          }
          if(tbst[x][y].size() == 0) {
            if(a2*p > a*p2) {
              tbst[x][y].push_back(bxy(x2,y2,a2,p2));
            }
            else {
              tbst[x][y].push_back(bxy(x2,y2,a,p));
            }
          }
          else {
            if((ba+a)*(bp+tbst[x][y][0].p) > (bp+p)*(ba+tbst[x][y][0].a)) {
              tbst[x][y].erase(tbst[x][y].begin(),tbst[x][y].end());
              tbst[x][y].push_back(bxy(x2,y2,a,p));
            }
            else if((ba+a)*(bp+tbst[x][y][0].p) == (bp+p)*(ba+tbst[x][y][0].a)) {
              tbst[x][y].push_back(bxy(x2,y2,a,p));
            }
            else {
              if(a2 > 0) {
                if((ba+a2)*(bp+tbst[x][y][0].p) > (bp+p2)*(ba+tbst[x][y][0].a)) {
                  tbst[x][y].erase(tbst[x][y].begin(),tbst[x][y].end());
                  tbst[x][y].push_back(bxy(x,y,a2,p2));
                }
                else if((ba+a2)*(bp+tbst[x][y][0].p) == (bp+p2)*(ba+tbst[x][y][0].a)) {
                  tbst[x][y].push_back(bxy(x,y,a2,p2));
                }
              }
            }
          }
        }
      }
    }
    if(bbst[x][hsize].size() == 0) continue;
    bxy xybbst = bbst[x][hsize][0];
    double a = xybbst.a;
    double p = xybbst.p;
    if(tbst[x][hsize].size() > 0) {
      bxy xytbst = tbst[x][hsize][0];
      a += xytbst.a;
      p += xytbst.p;
      double ratio = a/p;
      if(maxratio <= ratio)
        maxratio = ratio;
      else
        break;
    }
  }
  printf("%11.8f\n",maxratio);
}

int main(int argc,char *argv[]) {
  int size = atoi(argv[1]);
  int hsize = size/2;
  tbst = new vector<bxy> *[hsize+1];
  bbst = new vector<bxy> *[hsize+1];
  for(int i=0;i<=hsize;i++) {
    tbst[i] = new vector<bxy>[hsize+1];
    bbst[i] = new vector<bxy>[hsize+1];
  }
  bbst[0][hsize].push_back(bxy(0,hsize,hsize*hsize*1./2,0));
  maximize(hsize);
}