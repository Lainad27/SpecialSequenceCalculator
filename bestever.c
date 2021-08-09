#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h> /* for CHAR_BIT */
const int prime[5] = {2,3,5,7,11};
#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)
const unsigned long long int a = 10;      // calculate this term in the sequence
#define MAX 100000000000                    // maximum value that will be checked
const unsigned long long int start = 17000000000; // starting value that will be checked. notice that you must go a bit under where you actually want to start.
#define MAX2 1000000
char arr[BITNSLOTS(MAX2)];
#define differenciator 8
unsigned char gaps[100000];
int resqqq = 0; // this is just to check how many times the "check" function is used. unimportant.
int resqq = 0;
int resqqqq = 0;
int resqqqqq = 0;
int x =0;
long long mulmod(long long a, long long b, long long mod)
{
    long long x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/* 
 * modular exponentiation
 */
unsigned long long modulo(long long base, long long exponent, long long mod)
{
    long long x = 1;
    long long y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
 
/*
 * Miller-Rabin Primality test, iteration signifies the accuracy
 */
int Miller(long long p)
{
    resqqqq++;
    if (p==11 || p==7 || p==5 || p==3 || p==2){
        return 1;
    }
    int i;
    unsigned long long s;
    if (p < 2)
    {
        return 0;
    }
    if (p != 2 && p % 2==0)
    {
        return 0;
    }
     s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (i = 0; i < 5; i++)
    {
        unsigned long long a = prime[i], temp=s;
        unsigned long long mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return 0;
        }
    }
    return 1;
}

unsigned long long int v(unsigned long long int p, unsigned long long int m)
{
    unsigned long long int res = 0;
    unsigned long long int pi = p;
    while (pi <= m)
    {
        res += floor(m / pi);
        pi *= p;
    }
    return res;
}
bool check(unsigned long long int n, unsigned long long int a)
{
    resqqq++;

    for (unsigned long long int i = n+1; i < n + a + 1; ++i)
    {
        unsigned long long int number = i;
        unsigned long long int origi = i;
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
            else if (number < MAX2 && !BITTEST(arr, number))
            {
                if (v(number, n * 2) < 2 * v(number, a + n))
                {
                    return 0;
                }
                continue;
            }
        }
        unsigned long int ind = 1;
        int third = 0;
        unsigned long long int index = 3;
        while (true)
        {
            if (number % index == 0)
            {
                third = 1;
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
                if (number < MAX2 && !BITTEST(arr, number))
                {
                    if (v(number, n * 2) < 2 * v(number, a + n))
                    {
                        return 0;
                    }
                    break;
                }
            }
            index += gaps[ind] * 2; // Genereate short short ints (chars) for prime factors!
            ind++;
            if (index*index>number){
                if (v(number, n * 2) < 2 * v(number, a + n))
                {
                    return 0;
                }
                break;
            }
            if (index > 1000 && third==0&& index*index*index>number){
                third = 1;
                if  (Miller(number)){
                    resqqqqq++;
                    if (v(number, n * 2) < 2 * v(number, a + n))
                    {
                        return 0;
                    }
                    break;
                }
            }
            
        }
    }

    return 1;
}
int main()
{

    int lat = 0;

    for (unsigned long long i = 2; i * i < MAX2; i++)
    { ////////////////////////////////////////////////////////////////////////////////
        if (!BITTEST(arr, i))
        { // This could cost less mem. lets say !BITTEST(arr, i) if 2*i+1 is prime. then 2 bitsets and 6*i+1,6*i-1. Wheels!
            for (unsigned long long j = i * i; j < MAX2; j += i)
            {
                BITSET(arr, j);
            }
        }
    }
    unsigned long long int current = 3;
    unsigned long long int indi = 1;
    for (unsigned long long i = 5; i < MAX2; i++)
    { ////////////////////////////////////////////////////////////////////////////////
        if (!BITTEST(arr, i))
        { // This could cost less mem. lets say !BITTEST(arr, i) if 2*i+1 is prime. then 2 bitsets and 6*i+1,6*i-1. Wheels!
            gaps[indi] = (i - current) / 2;
            current = i;
            indi++;
        }
    }
    printf("Finding numbers \n", gaps[1], gaps[2], gaps[3]);
    if (check(72286092,7)){
        printf("Finding numbers %d \n", check(3648841-6,6));
    }
    for (unsigned long long int i = start; i < MAX - 1; i++)
    {
        bool flag = false;

        unsigned long long int number = i + 1;
        unsigned long long int origi = i + 1;
        bool happenedTwo = false;
        if (number % 2 == 0)
        {
            number /= 2;
            while (number % 2 == 0)
            {
                number /= 2;
            }
            if (v(2, i * 2) < 2 * v(2, i + 1))
            {
                lat = differenciator - 1;
                happenedTwo = true;
                flag = true;
            }
            else if (number == 1)
            {
                happenedTwo = true;
            }
            else if (number < MAX2 && !BITTEST(arr, number))
            {
                if (v(number, i * 2) < 2 * v(number, i + 1))
                {
                    lat = differenciator - 1;
                    flag = true;
                    happenedTwo = true;
                }
            }
        }
        unsigned long int ind = 1;
        int third = 0;
        if (!happenedTwo)
        {
            unsigned long long int index = 3;
            while (true)
            {
                if (number % index == 0)
                {
                    third=0;
                    number /= index;
                    while (number % index == 0)
                    {
                        number /= index;
                    }
                    if (v(index, i * 2) < 2 * v(index, i + 1))
                    {
                        lat = differenciator - 1;
                        flag = true;
                        break;
                    }
                    if (number == 1)
                    {
                        break;
                    }
                    if (number < MAX2 && !BITTEST(arr, number))
                    {
                        if (v(number, i * 2) < 2 * v(number, i + 1))
                        {
                            lat = differenciator - 1;
                            flag = true;
                        }
                        break;
                    }
                }
                index += gaps[ind] * 2; // Genereate short short ints (chars) for prime factors!
                ind++;
                if (index*index>number){
                    x++;
                    if (v(number, i * 2) < 2 * v(number, i + 1))
                    {
                        lat = differenciator - 1;
                        flag = true;
                    }
                    break;
                }
                if (index > 1000 && third==0 && index*index*index>number){
                    third = 1;
                    if  (Miller(number)){
                        resqqqqq++;
                        if (v(number, i * 2) < 2 * v(number, i + 1))
                        {
                            lat = differenciator - 1;
                            flag = true;
                        }
                        break;
                    } 
                }
                
            }
        }
        lat += 1;
        if (flag)
        {
            i += differenciator;
        }
        resqq++;
        if (lat >= a && check(i + 1 - a, a))
        {
            printf("We got : %llu\n", i + 1);
            break;
        }

        if (i % 100000000 < differenciator + 1)
        {
            printf("We loaded : %llu\n", i);
            printf("We made : %d %d %d %d\n",resqqqqq,resqqqq, resqqq, resqq);
        }
    }
    printf("FINISHED : %d %d %d %d %d\n",resqqqqq,resqqqq, resqqq, resqq,x);
    return 0;
}