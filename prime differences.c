#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h> /* for CHAR_BIT */

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)
const unsigned long long int a = 10;     // calculate this term in the sequence
#define MAX 11000000000                  // maximum value that will be checked
const unsigned long long int start = 10; // starting value that will be checked. notice that you must go a bit under where you actually want to start.
char arr[BITNSLOTS(MAX)]; // a bitset (bitset in C), where BITTEST(arr, i) is false iff i is prime.
unsigned char gaps[500000000]; // Prime gaps, in an array. because all of the prime gaps are even (ignore the first one), 
// and under 300 billion the gaps are smaller than 512 We can store them in a char array. the size of gaps should be more than the prime counting func of MAX.
int resqqq = 0; // this is just to check how many times the "check" function is used. unimportant.
unsigned long long int v(unsigned long long int p, unsigned long long int m) // this computes https://en.wikipedia.org/wiki/Legendre%27s_formula for m!
{
    unsigned long long int res = 0;
    unsigned long long int pi = p;
    while (pi < m)
    {
        res += floor(m / pi);
        pi *= p;
    }
    return res;
}
bool check(unsigned long long int n, unsigned long long int a) // This checks if the number completes the criteria. rarely used.
{
    resqqq++;

    for (unsigned long long int i = n; i < n + a + 1; ++i)
    {
        if (!BITTEST(arr, i))
        { // this isn't actually needed but why not, this function is rarely used.
            return 0;
        }
        unsigned long long int number = i;
        if (number % 2 == 0)
        {
            number /= 2;
            while (number % 2 == 0)
            {
                number /= 2;
            }
            if (v(2, n * 2) < 2 * v(2, a + n))
            {
                return 0;
            }
            else if (number == 1)
            {
                continue;
            }
            else if (!BITTEST(arr, number))
            {
                if (v(number, n * 2) < 2 * v(number, a + n))
                {
                    return 0;
                }
            }
        }
        unsigned long long int index = 3;
        while (true)
        {
            if (!BITTEST(arr, index) && number % index == 0)
            {
                number /= index;
                while (number % index == 0)
                {
                    number /= index;
                }
                if (v(index, n * 2) < 2 * v(index, a + n))
                {
                    return 0;
                }
                if (number == 1)
                {
                    break;
                }
                if (!BITTEST(arr, number))
                {
                    if (v(number, n * 2) < 2 * v(number, a + n))
                    {
                        return 0;
                    }
                    break;
                }
            }
            index += 2;
        }
    }

    return 1;
}
int main()
{

    unsigned long long int lat = 0; // This integer checks if a sequence met the "(2*i)!/(i+1)!^2 is an integer" criteria a times in a row. (variable a)

    for (unsigned long long i = 2; i * i < MAX; i++) // building arr, a bitset (bitset in C), where BITTEST(arr, i) is false iff i is prime.
    { 
        if (!BITTEST(arr, i))
        { // This could cost less mem. lets say !BITTEST(arr, i) if 2*i+1 is prime. then 2 bitsets and 6*i+1,6*i-1. Wheel factorization.
            for (unsigned long long j = i * i; j < MAX; j += i)
            {
                BITSET(arr, j);
            }
        }
    }
    unsigned long long int current = 3;
    unsigned long long int indi = 1;
    for (unsigned long long i = 5; i < MAX; i++) // building gaps, the prime gaps. uses the technique described earlier.
    { ////////////////////////////////////////////////////////////////////////////////
        if (!BITTEST(arr, i))
        { 
            gaps[indi] = (i - current) / 2;
            current = i;
            indi++;
        }
    }
    printf("Finding numbers \n", gaps[1], gaps[2], gaps[3]);
    for (unsigned long long int i = start; i < MAX - 1; ++i)
    {
        if (!BITTEST(arr, i + 1)) // If the number is prime, obviously (2*i)!/(i+1)!^2 is not an integer.
        {
            lat = 0; // reset the variable that counts the amount of numbers that matched the "(2*i)!/(i+1)!^2 is an integer" criteria is a row.
        }
        else
        {
            unsigned long long int number = i + 1;
            bool happenedTwo = false; //check if divisble by 2. if so check if the number meets the "(2*i)!/(i+1)!^2 is an integer" criteria for prime 2.
            if (number % 2 == 0)
            {
                number /= 2;
                while (number % 2 == 0)
                {
                    number /= 2;
                }
                if (v(2, i * 2) < 2 * v(2, i + 1))
                {
                    lat = -1;
                    happenedTwo = true;
                }
                else if (number == 1)
                {
                    happenedTwo = true;
                }
                else if (!BITTEST(arr, number))
                {
                    if (v(number, i * 2) < 2 * v(number, i + 1))
                    {
                        lat = -1;
                        happenedTwo = true;
                    }
                }
            }
            unsigned long int ind = 1;
            if (!happenedTwo)
            {
                unsigned long long int index = 3;
                while (true) //This is improved trial divison with gaps and arr, and for each factor found we eliminate it and check if i meets the "(2*i)!/(i+1)!^2 is an integer" criteria for the prime p.
                {
                    if (number % index == 0)
                    {
                        number /= index;
                        while (number % index == 0)
                        {
                            number /= index;
                        }
                        if (v(index, i * 2) < 2 * v(index, i + 1))
                        {
                            lat = -1;
                            break;
                        }
                        if (number == 1)
                        {
                            break;
                        }
                        if (!BITTEST(arr, number))
                        {
                            if (v(number, i * 2) < 2 * v(number, i + 1))
                            {
                                lat = -1;
                            }
                            break;
                        }
                    }
                    index += gaps[ind] * 2; // go to the next prime.
                    ind++;
                }
            }
            lat += 1; // if the counting variable did got reset to -1, it will now be 0. else, it will just got up by 1. 
        }

        if (lat >= a && check(i + 1 - a, a)) // if the numbers made the "(2*i)!/(i+1)!^2 is an integer" criteria a times in a row, check if i+1-a meets the "(2*k)!/(k+a)!^2 is an integer" criteria.
        {
            printf("We got : %llu\n", i + 1);
            break;
        }

        if (i % 10000000 == 0) // just to see how many numbers we passed.
        {
            printf("We loaded : %llu\n", i);
            printf("We made : %d\n", resqqq);
        }
    }
    printf("FINISHED : %d\n", resqqq);
    return 0;
}
