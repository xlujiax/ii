#include "wym.h"

Q int2_to_q(int u, int d)
{
 return (u << 16) + d;
}

int up(Q q)
{
     return q >> 16;
}
int down(Q q)
{
     int u = q >> 16;
     return q - ((long long int)u << 16);
}

int gcd(int m, int n)
 {
 while( m > 0 )
    {
     if( n > m )
       {
           int t = m; m = n; n = t;
       }
      m -= n;
    }
   return n;
 }
 
Q normalize(Q q)
{
 int g = gcd(up(q), down(q));
 return int2_to_q(up(q)/g, down(q)/g);
}

Q multiple(Q a, Q b)
{
        return normalize(int2_to_q(up(a)*up(b), down(a)*down(b)));
}

Q divide(Q a, Q b)
{
        return normalize(int2_to_q(up(a)*down(b), down(a)*up(b)));
}

Q plus(Q a, Q b)
{
        return normalize(int2_to_q(up(a)*down(b) + up(b)*down(a), down(a)*down(b)));
}

Q minus(Q a, Q b)
{
        return normalize(int2_to_q(up(a)*down(b) - up(b)*down(a), down(a)*down(b)));
}
Q read()
{
        int u, d;
        scanf("%d/%d", &u, &d);
        if(d <= 0)
        {
             printf("err: mianownik powinien byc dodatni\n");
             system("pause");
             exit(-1);
         }
        return normalize(int2_to_q(u, d));
}

void write(Q q)
{
     printf("%d/%d", up(q), down(q));
 }
