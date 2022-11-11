#include <stdio.h>


int Fibonacci(int n)
{
    int sum0=0,sum1=1,sum2=1;
    if(n<=0)
        return 0;
    else if(n<=1)
        return 1;
    else{
        for(int i=1;i<=n-1;i++){
            sum2=sum0+sum1;
            sum0=sum1;
            sum1=sum2;
        }
        return sum1;
    }	
    
}


int main()
{
    int n = 1;
    int ret = 0;

    ret = scanf("%d",&n);
    
    if(0==ret || n <=0 || n > 20)
    {   
        printf("ret=%d\n",ret);
        printf("input is not valid\n");
        return 0;
    }

    for(int j=1;j<=n;j++)
    {
        int x = Fibonacci(j);
        printf("%d\n",x);
    }
    
    return 0;

}