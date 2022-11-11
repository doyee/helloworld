#include <stdio.h>
#include <stdlib.h>
int numberof1(int n)
{
    int count = 0;
    while(n)
    {
        ++count;
        n=(n-1) & n;
    }
    return count;
}
int main()
{
    int n;
    int ret = 0;

    ret = scanf("%d",&n);
    
    if(0==ret)
    {   
        printf("ret=%d\n",ret);
        printf("input is not valid\n");
        return 0;
    }

    printf("0x%x\n",n);
    printf("%d\n",numberof1(n));
    return 0;
}
