    #include <iostream>
    #include <vector>
    #include <math.h>
    #include <chrono>
	#include <algorithm>
	#include <bitset>  
		const unsigned long long int a = 10;
		const unsigned long long int MAX = 6000000000;
		const unsigned long long int start = 2935782098;
		std::bitset<MAX> arr;
std::vector<unsigned long long int> TrialDivision(unsigned long long int n) {
    std::vector<unsigned long long int> v; unsigned long long int f;
    f = 2;
    while (n % 2 == 0) { v.push_back(f); n /= 2; }
    f = 3;
    while (n % 3 == 0) { v.push_back(f); n /= 3; }
    f = 5;
    unsigned long long int ac = 9, temp = 16;
    do {
        ac += temp; // Assume addition does not cause overflow with U type
        if (ac > n) break; 
        if (n % f == 0) {
            v.push_back(f);
            n /= f;
            ac -= temp;
        }
        else { 
            f += 2;
            temp += 8;
        }
    } while (1);
    if (n != 1) v.push_back(n);
    return v;
}

    unsigned long long int v(unsigned long long int p,unsigned long long int m){
		unsigned long long int res = 0;
		unsigned long long int pi = p;
		while (pi<m){
			res += floor(m/pi);
			pi*=p;
		}
		return res;
	}
	bool check(unsigned long long int n, unsigned long long int a){
		
		for (unsigned long long int i = n ; i<n+a+1; ++i){
			
			if (arr[i] == 0){
				return false;
			}
			
			std::vector<unsigned long long int> ig = TrialDivision(i);
			for (auto j = ig.begin(); j != ig.end(); ++j){
				if (v(*j, 2*n) < 2*v(*j, a+n)){
					
					return false;
				}
			}
			
		}
		return true;
	}
    int main() {

    	unsigned long long int lat = 0;
    
    for (unsigned long long i = 2; i*i < MAX; i++) { ////////////////////////////////////////////////////////////////////////////////
        if (arr[i]==0){
            for (unsigned long long j = i * i; j < MAX; j+=i) {
                arr[j] = 1;
            }
        }
    }
    std::cout << "Finding numbers" << std::endl;
    	for (unsigned long long int i = start; i < MAX - 1; ++i) {
    		if (arr[i+1] == 0) {
    			lat = 0;
    		}
    		else {

				std::vector<unsigned long long int> ig = TrialDivision(i+1);//
				std::sort(ig.begin(), ig.end()); //
    			auto last = std::unique(ig.begin(), ig.end());
    			ig.erase(last, ig.end());
				std::reverse(ig.begin(),ig.end());
				auto start_time2 = std::chrono::steady_clock::now();//
    			for (auto j = ig.begin(); j != ig.end(); ++j){
    				if (v(*j, i*2) < 2*v((*j), i+1)){
						lat =-1;
						break;
					}
				}
				lat +=1;
    		}
			
			if (lat >= a && check( i + 1 - a, a)){
				std::cout << " We got " << i+1 <<std::endl;
				break;
			}
			
			if (i%100000000 == 0){
				std::cout << " We loaded " << i <<std::endl;
			}
    	}
		std::cout << "FINISHED. ";
    	return 0;
    }
