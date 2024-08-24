#include <iostream>
#include <vector>
#include <map>

typedef std::vector<long double> CLIST;
typedef std::map<size_t, long double> CMAP;

void pr2( const CLIST& l, size_t next_n )
{
        double single_ex = 0, single_ex2 = 0;
        double sum_ex=0, sum_ex2=0;
  for( size_t i=1; i<=next_n; i++ )
        {
          single_ex += i;
          single_ex2 += i*i;
        }
        single_ex/=next_n;
        single_ex2/=next_n;
  for( size_t i=1; i<l.size(); i++ )
        {
          double p = l[i];
                sum_ex += p*single_ex*i;
                sum_ex2 += p*single_ex2*i + p*single_ex*single_ex*i*(i-1);//...
        }
        std::cout << "VAR = " << sum_ex2-sum_ex*sum_ex << std::endl;
}

void norm( CLIST& l )
{
        double sum = 0;
        for( size_t i=1; i<l.size(); i++ )
        {
                sum += l[i];
        }
        if( sum == 0 )
                return;
        for( size_t i=1; i<l.size(); i++ )
        {
                l[i]/=sum;
        }
}

void norm( CMAP& m )
{
        double sum = 0;
        CMAP::const_iterator itr;
        for( itr=m.begin(); itr != m.end(); ++itr )
        {
          sum += itr->second;
        }
        if( sum==0 ) return;
        CMAP::iterator it;
        for( it=m.begin(); it != m.end(); ++it )
        {
          it->second /= sum;
        }
}

void step( const CLIST& in_list, unsigned int sides, CLIST& out_list )
{
        out_list.clear();
        if( in_list.empty() )
                return;
        size_t max_score = (in_list.size()-1) * sides;
        out_list.resize( max_score+1, 0 );

        for( size_t i=1; i<in_list.size(); i++ )
        {
                CMAP tmp0, tmp1;
                tmp0[0] = 1;
                for( size_t j=1; j<=i; j++ ) // jth die
                {
                        for( size_t k=1; k<=sides; k++ ) // kth side
                        {
                                CMAP::const_iterator it;
                                for( it = tmp0.begin(); it!= tmp0.end(); ++it )
                                {
                                        size_t score = it->first + k;
                                        if( tmp1.find(score) == tmp1.end() )
                                                tmp1[score] = it->second;
                                        else
                                                tmp1[score] += it->second;
                                }
                        }
                        tmp0 = tmp1;
                        tmp1.clear();
                }
                norm(tmp0);
                CMAP::const_iterator it;
                for( it = tmp0.begin(); it!= tmp0.end(); ++it )
                {
                        out_list[it->first] += in_list[i] * it->second;
                }
        }
        norm(out_list);
}

int main()
{
        std::cout.precision(30);
        std::cout << std::fixed;

        CLIST l0(2,0);
        l0[1] = 1;

        CLIST l1;
        step(l0,4,l1);

        CLIST l2;
        step( l1, 6, l2 );

        CLIST l3;
        step( l2, 8, l3 );

        CLIST l4;
        step( l3, 12, l4 );
        pr2(l4,20);

        // CLIST l5;
        // step( l4, 20, l5 );
}
