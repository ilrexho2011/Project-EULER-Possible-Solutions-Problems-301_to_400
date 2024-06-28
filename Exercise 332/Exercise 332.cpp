#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

double PI = atan(1) * 4;

class vector
{   
    public:
    double x , y , z;
    vector(){x=y=z=0;}
    vector(double _x , double _y , double _z){x=_x,y=_y,z=_z;}
    double operator *(vector u){return x*u.x + y*u.y + z*u.z;}
    double len(){return sqrt(x*x + y*y + z*z);}
    vector operator *(double m){return vector(x*m,y*m,z*m);}
    vector operator +(vector u){return vector(x+u.x,y+u.y,z+u.z);}
    vector operator -(vector u){return vector(x-u.x,y-u.y,z-u.z);}
    vector projection(vector u)
    {
        return u * (((*this)*u) / u.len() / u.len());
    }
    vector maketangent(vector u)
    {
        return (*this) - this->projection(u);
    }
    friend ostream& operator <<(ostream &ou , const vector&b)
    {
        return ou << b.x << " , " << b.y << " , " << b.z ;
    }
}P[1000001];

double getang(vector A , vector B , vector C)
{
    vector u = (B).maketangent(A);
    vector v = (C).maketangent(A);
    double cosalpha = u*v / u.len() / v.len();
    return acos(cosalpha);
}

double area(vector A , vector B , vector C)
{
    double r = A.len();
    double ang1 = getang(A , B , C);
    double ang2 = getang(B , A , C);
    double ang3 = getang(C , A , B);
    return r * r * (ang1 + ang2 + ang3 - PI);
}

double isZERO(vector a , vector b , vector c)
{
    b = b.maketangent(a);
    c = c.maketangent(a);
    c = c.maketangent(b);
    return c.len() < 1e-7;
}

double solve(int r)
{
    int counter = 0;
    for(int x = -r ; x <= r ; x++)
    for(int y = -r ; y <= r ; y++)
    for(int z = -r ; z <= r ; z++)
    {
        if(x*x + y*y + z*z == r*r)
            P[++counter] = vector((double)x , (double)y , (double)z);
    }
    double ret = 1e10;
    for(int i = 1 ; i <= counter ; i++)   
        for(int j = i + 1 ; j <= counter ; j++)
            for(int k = j + 1 ; k <= counter ; k++)
            {
                double a = area(P[i] , P[j] , P[k]);
                if(!isZERO(P[i] , P[j] , P[k]))
                    ret = min(ret , a);
            }
    return ret;
}

int main()
{
    cout << fixed << setprecision(6) << endl;
    double ans = 0;
    for(int i = 1 ; i <= 50 ; i++)
    {
        double thisone = solve(i);
        cout << i << " : " << thisone << endl;
        ans += thisone;
    }
    cout << endl;
    cout << ans << endl;
    system("pause");
    return 0;
}
