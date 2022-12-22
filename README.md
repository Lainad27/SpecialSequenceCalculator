This is really messy :(

![alt text](https://github.com/Lainad27/SpecialSequenceCalculator/blob/main/How%20to%20compute%20a%20special%20sequence%20(ReadMe).PNG)

Written [here](http://mathb.in/51891)

Computational Remarks (regarding "main.c", the best version that needs less RAM):
1. In order to factorize the numbers, I kept a bitset where bitset[n] is false iff n is prime. Also, I kept an unsigned char array (0-256) of the prime gaps. from [Wikipedia](https://en.wikipedia.org/wiki/Prime_gap), we know that the largest prime gap before 303 billion is 500, and the prime gaps are always even, so we can divide every gap by 2 and store it in the array, sufficent to our unsigned char memory limit. Surprisingly enough, because there aren't that many primes (therefore there aren't that many prime gaps), We [know](https://en.wikipedia.org/wiki/Prime-counting_function) that the gaps unsigned char array uses less memory than the bitset.
2. We could improve the memory usage on the bitset by using [wheel factorization](https://en.wikipedia.org/wiki/Wheel_factorization). That is, because each prime is uneven (except 2), instead of defining, "a bitset where bitset[n] is false iff n is prime" we could store it in such a way where it is "a bitset where bitset[n] is false iff 2·n+1 is prime". This cuts off 50% of the memory cost. We can take this further. Because each prime is in the form of 6·n+1 or 6·n-1 (except 2,3), we can make two bitsets "bitset1[n] is false iff 6·n+1 is prime" and "bitset2[n] is false iff 6·n-1 is prime" (two bitsets). This cuts off 67% of memory usage. Again, surprisingly enough, we could do this until very high precentages (despite diminishing returns) to consume as little memory as we could computationaly afford.
3. If p^alpha divides n and p^alpha > sqrt(2n), we can rule out n.


Define b_n as a_n + n

b_n computed:

b_1 = 1

b_2 = 210

b_3 = 3478

b_4 = 8178

b_5 = 252970

b_6 = 3648841

b_7 = 72286099

b_8 = 159329615

b_9 = 2935782898

b_10  = 19295451546

So far all of those are [squarefree](https://en.wikipedia.org/wiki/Square-free_integer).
