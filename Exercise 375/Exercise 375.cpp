#include <iostream>
#include <unordered_map>

using namespace std;

#define PRNG_MOD		50515093
#define S_0			290797
#define PRNG_CYCLE		6308948

unsigned s[PRNG_CYCLE] = {S_0};
unsigned rmq_j_v[PRNG_CYCLE] = {0};

unordered_map<unsigned,uint64_t> diff_cache;

unsigned s_idx(unsigned n) 
{
	return n%PRNG_CYCLE;
}

void calc_s(unsigned n)
{
	rmq_j_v[0] = s[0] = (uint64_t(S_0)*S_0)%PRNG_MOD;
	
	for(unsigned i = 1;i <= PRNG_CYCLE;i++) {
		s[i] = (uint64_t(s[i-1])*s[i-1])%PRNG_MOD;
	}
}


uint64_t m(unsigned n)
{
	calc_s(n);

	uint64_t a_s = 0;

	unsigned prev_j_j_val = s[0];
	uint64_t prev_sum = 0;
	
	for(unsigned j = 0;j < n;j++) 
	{
		uint64_t current_j_j_val = s[s_idx(j)];

		if(current_j_j_val < prev_j_j_val) 
		{	
			uint64_t orig_prev_sum = prev_sum;
			uint64_t t_prev_sum = prev_sum;
			unsigned m = 1;
			
			bool new_min = true;
			
			if(j > PRNG_CYCLE) {
				if(diff_cache.count(current_j_j_val)) {
					prev_sum = orig_prev_sum + diff_cache[current_j_j_val];
					a_s += prev_sum;
					prev_j_j_val = current_j_j_val;
					continue;
				}
			}
			
			for(signed k = j - 1;k >= 0;k--,m++) 
			{	
				if(rmq_j_v[s_idx(k)] < current_j_j_val)
				{
					prev_sum = t_prev_sum + current_j_j_val*m;
					a_s += prev_sum;
					rmq_j_v[s_idx(j)] = current_j_j_val;
					new_min = false;
					break;
				} else {
					t_prev_sum -= rmq_j_v[s_idx(k)];
					rmq_j_v[s_idx(k)] = current_j_j_val;
				}
			}

			if(new_min) {
				prev_sum = current_j_j_val*m;
				a_s += prev_sum;
				rmq_j_v[s_idx(j)] = current_j_j_val;
			}
			
			if(j > PRNG_CYCLE) {
				diff_cache[current_j_j_val] = (prev_sum - orig_prev_sum);
			}

		} else {
			a_s += prev_sum;
			a_s += current_j_j_val;
			
			prev_sum += current_j_j_val;
			rmq_j_v[s_idx(j)] = current_j_j_val;
		}

		prev_j_j_val = current_j_j_val;
	}
	
	return a_s;
}

int main()
{
//	cout << m(10) << endl;
//	cout << m(10000) << endl;
	cout << m(2000000000) << endl;
	return 0;
}