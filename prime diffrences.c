    #include <math.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <limits.h>		/* for CHAR_BIT */

	#define BITMASK(b) (1 << ((b) % CHAR_BIT))
	#define BITSLOT(b) ((b) / CHAR_BIT)
	#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
	#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
	#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
	#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)
	const unsigned long long int a = 9;
	#define  MAX 3000000000
	const unsigned long long int start = 2900000000;
	char arr[BITNSLOTS(MAX)];
	unsigned char gaps[144449587];
	int resqqq =0;
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
		resqqq++;
		
		for (unsigned long long int i = n ; i<n+a+1; ++i){
			if (!BITTEST(arr, i)){// this isn't actually needed but why not, this function is rarely used.
				return 0;
			}
			unsigned long long int number =i;
			if (number%2==0){
					number/=2;
					while (number%2==0){
						number/=2;
					}
					if (v(2, n*2) < 2*v(2, a+n)){
						return 0;
					}
					else if (number==1){continue;}
					else if (!BITTEST(arr, number)){
						if (v(number, n*2) < 2*v(number, a+n)){
						return 0;
						}
					}
				}
			unsigned long long int index =3;
					while (true){
						if (!BITTEST(arr, index) && number%index==0){
							number/=index;
							while (number%index==0){
								number/=index;
							}
							if (v(index, n*2) < 2*v(index, a+n)){
								return 0;
							}
							if (number==1){break;}
							if (!BITTEST(arr, number)){
								if (v(number, n*2) < 2*v(number, a+n)){
									return 0;
								}
								break;
							}
							}
						index+=2;
					}
			
		}
		
		return 1;
	}
    int main() {

    	unsigned long long int lat = 0;
    
    for (unsigned long long i = 2; i*i < MAX; i++) { ////////////////////////////////////////////////////////////////////////////////
        if (!BITTEST(arr, i)){ // This could cost less mem. lets say !BITTEST(arr, i) if 2*i+1 is prime. then 2 bitsets and 6*i+1,6*i-1. Wheels!
            for (unsigned long long j = i * i; j < MAX; j+=i) {
                BITSET(arr, j);
            }
        }
    }
	unsigned long long int current = 3;
	unsigned long long int indi = 1;
	for (unsigned long long i = 5; i < MAX; i++) { ////////////////////////////////////////////////////////////////////////////////
        if (!BITTEST(arr, i)){ // This could cost less mem. lets say !BITTEST(arr, i) if 2*i+1 is prime. then 2 bitsets and 6*i+1,6*i-1. Wheels!
            gaps[indi]=(i-current)/2;
			current=i;
			indi++;
        }
    }
    printf("Finding numbers %hhu %hhu %hhu \n",gaps[1],gaps[2],gaps[3]);
    	for (unsigned long long int i = start; i < MAX - 1; ++i) {
    		if (!BITTEST(arr, i+1)) {
    			lat = 0;
    		}
    		else {
				unsigned long long int number =i+1;
				bool happenedTwo = false;
				if (number%2==0){
					number/=2;
					while (number%2==0){
						number/=2;
					}
					if (v(2, i*2) < 2*v(2, i+1)){
						lat =-1;
						happenedTwo=true;
					}
					else if (number==1){happenedTwo=true;}
					else if (!BITTEST(arr, number)){
						if (v(number, i*2) < 2*v(number, i+1)){
						lat =-1;
						happenedTwo=true;
						}
					}
				}
				unsigned long int ind = 1;
				if (!happenedTwo){
					unsigned long long int index =3;
					while (true){
						if (number%index==0){
							number/=index;
							while (number%index==0){
								number/=index;
							}
							if (v(index, i*2) < 2*v(index, i+1)){
								lat =-1;
								break;
							}
							if (number==1){break;}
							if (!BITTEST(arr, number)){
								if (v(number, i*2) < 2*v(number, i+1)){
								lat =-1;
								break;
								}
								break;
							}
							}
						index+=gaps[ind]*2; // Genereate short short ints (chars) for prime factors!
						ind++;
					}
				}
				lat +=1;
    		}
			
			if (lat >= a && check( i + 1 - a, a)){
				printf("We got : %llu\n", i+1);
				break;
			}
			
			if (i%10000000 == 0){
				printf("We loaded : %llu\n", i);
				printf("We made : %d\n", resqqq);
			}
    	}
		printf("FINISHED : %d\n", resqqq);
    	return 0;
    }