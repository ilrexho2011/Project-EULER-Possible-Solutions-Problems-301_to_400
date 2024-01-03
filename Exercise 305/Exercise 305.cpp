#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
char chap[70000000]; int cn = 0;
LL tenInd[8];
LL tenPow[19];
int genLim;
LL startInd(LL n){
    LL ind = 0, ten = 10, l = 1;
    for(; ten<=n; ten*=10, ++l) ind += ten/10*9 * l;
    ind += l * (n-ten/10);
    return ind;
}
vector<LL> inside(LL n){
    vector<LL> ind;
    int lenN = 0;
    for(int c=n; c>0; c/=10) lenN++;
    for(LL length=1, ten=10; ind.size() < genLim; length++, ten*=10){
        LL pTen = ten/10;
        for(LL env=0; env<pTen; env++) {
            LL newN = n*tenPow[length] + env;
            ind.push_back(startInd(newN));
        }
        for(LL env=pTen; env<ten; env++){
            for(int left=0; left<=length; left++){
                int right=length-left;
                LL l = env/tenPow[right], r = env%tenPow[right];
                LL newN = r + n * tenPow[right] + l * tenPow[right + lenN];
                ind.push_back(startInd(newN)+left);
            }
        }
    }
    return ind;
}
vector<LL> consec(LL n){
    vector<LL> ind;
    int lenN=0;
    for(LL c=n; c>0; c/=10) lenN++;
    for(LL length=1, ten=10; ind.size()<genLim; length++, ten*=10){
        for(int left=1; left<lenN; left++){
            int right=lenN-left;
            LL l = n/tenPow[right], r = n%tenPow[right];
            if(r<tenPow[right-1]) continue;
            for(LL mid=0; mid<ten; mid++){
                LL newN = (l+1)%tenPow[left] + mid*tenPow[left] + r*tenPow[left+length];
                ind.push_back(startInd(newN) - left);
            }
        }
    }
    return ind;
}
LL getIndex(LL n, LL c){
    LL ten = 1, length = 0;
    while(ten<=n) ten*=10, length++;
    LL match = 0;
    for(int i=0; i<length; i++) match = 10*match + (int)(chap[i]-'0');
    for(int i=0; i<tenInd[length]; i++){
        if(match==n) if(--c == 0) return i+1; 
        match = (10*match + (int)(chap[i+length]-'0')) % ten;
    }
    if(length>1){
        genLim = 2*c;
        vector<LL> in = inside(n), out = consec(n);
        in.insert(in.end(), out.begin(), out.end());
        sort(in.begin(), in.end());
        return in[c-1]+1;
    }
    genLim = 2*c;
    vector<LL> in = inside(n);
    sort(in.begin(), in.end());
    return in[c-1]+1;
}
int main(){
    tenPow[0]=1; for(int i=1; i<19; i++) tenPow[i]=tenPow[i-1]*10;
    for(int i=1, ten=1, ti=0; i<10000010; i++){
        if(i==ten){
            tenInd[ti] = cn;
            ten *= 10;
            ti++;
        }
        cn += snprintf(chap+cn, 6000000, "%i", i);
    }
    LL ans = 0;
    for(LL i=0, three=3; i<13; i++,three*=3) ans += getIndex(three,three);;
    cout << ans;
}