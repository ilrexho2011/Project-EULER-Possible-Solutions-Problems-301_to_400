#include <iostream>
#include <cmath>
#include <stdio.h>
#include <map>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

#define GR 200000

vector<int> prosti;
int suma=0, maxx=0, maks=0, br=0, zajebancija[GR];
map <set<int>, int > mapa;
map <set<int>, int >::iterator it;
set<int>::iterator aa;
pair<set<int>::iterator,bool> ret, ret1;

void init(){
      ifstream fajl("prosti.txt");
      __int64 pom;
      while (1){
          fajl>>pom;
          if (pom>GR) break;
          suma+=pom;
          prosti.push_back(pom);
      }
      fajl.close();
      set <int> x;
      mapa[x]=++suma;
      for (int i=0;i<GR;i++) zajebancija[i]=(i>=prosti[br])?br++:br-1;
}

void f(int a, int b, int gr, int najveci){
    if (najveci>gr) return;
    if (najveci>maxx) maxx=najveci;
    f(a,b,gr,najveci*a);
    return;
}

int main(){
    init();
    for (int i=0;i<8;i++){
        map <set<int>, int >pomocna;
        for (it=mapa.begin();it!=mapa.end();it++){
                f(prosti[i],prosti[i],GR,prosti[i]);
                for (int j=i;j<i+1;j++){
                    set <int> x=(*it).first;
                    ret=x.insert(prosti[i]), ret1.second=1;
                    if (ret.second&&ret1.second){
                        int k=mapa[(*it).first]+maxx-prosti[i]-((i==j)?0:prosti[j]);
                         if (k>pomocna[x]) pomocna[x]=k;
                         if (k>maks) maks=k;
                         maxx=0;
                    }
                }
                int pom=prosti[i];
                while (pom<sqrt(GR)){
                    for (int j=zajebancija[GR/pom];;j--){
                        set <int> x=(*it).first;
                        ret=x.insert(prosti[i]), ret1=x.insert(prosti[j]);
                        if (ret.second&&ret1.second){
                            f(prosti[i],prosti[j],GR,prosti[i]*prosti[j]);
                            int k=mapa[(*it).first]+maxx-prosti[i]-((i==j)?0:prosti[j]);
                            if (k>pomocna[x]) pomocna[x]=k;
                            if (k>maks) {maks=k; }
                            maxx=0;
                            break;
                        }
                    }
                    pom*=prosti[i];
                }
        }
        mapa.clear();
        for (it=pomocna.begin();it!=pomocna.end();it++) if (maks<=pomocna[(*it).first]) mapa[(*it).first]=pomocna[(*it).first];
    }

    for (int i=8;i<86;i++){
        bool q=false;
        map <set<int>, int >pomocna;
        for (it=mapa.begin();it!=mapa.end();it++){
                f(prosti[i],prosti[i],GR,prosti[i]);
                for (int j=i;j<i+1;j++){
                    set <int> x=(*it).first;
                    ret=x.insert(prosti[i]), ret1.second=1;
                    int k=mapa[(*it).first]+maxx-prosti[i]-((i==j)?0:prosti[j]);
                    if (k>pomocna[x]) pomocna[x]=k;
                    if (k>maks) {maks=k; }
                    maxx=0;
                }
                q=(i==51||i==52||i==68||i==69||(i>=73&&i<=77)||(i>=80&&i<=83)||i==84||i==85);
                for (int j=zajebancija[GR/prosti[i]];zajebancija[GR/prosti[i]]-j<5&&j>=86;j--){
                    set <int> x=(*it).first;
                    ret=x.insert(prosti[i]), ret1=x.insert(prosti[j]);
                    if (ret.second&&ret1.second){
                        f(prosti[i],prosti[j],GR,prosti[i]*prosti[j]);
                        int k=mapa[(*it).first]+maxx-prosti[i]-((i==j)?0:prosti[j]);
                        if (k>pomocna[x]) pomocna[x]=k;
                        if (k>maks) {maks=k;}
                        maxx=0;
                        if (!q) break;
                    }
                }
        }
        mapa.clear();
        for (it=pomocna.begin();it!=pomocna.end();it++) if (maks-((q)?8930:10)<pomocna[(*it).first]) mapa[(*it).first]=pomocna[(*it).first];
    }
    cout<<maks;
    return 0;
}