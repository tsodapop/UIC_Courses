#include <stdio.h>
long fib(long n)
{
if (n==1)
        return 1;
else if(n<1)
        return 0;

else
        return(fib(n-1)+fib(n-2));

}

int main() 
{
int n = 6; 

printf("Fib of %ld is %ld\n",n,fib((long) n));

return 0;

}