#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>

#define MAX 5
int stack1[MAX];
int stack2[MAX];


int main()
{
    char operate[5];
    int top1=0,top2=0,n1=0,n2=0,n=0;
    int num=0;
    bool bExit=false;

    printf("COMMAND:PUSH,POP,EXIT,Please input one command!\n");
    
    while(!bExit)
    {
        scanf("%s",operate);
        if(strcmp(operate,"PUSH")==0)
        {
            scanf("%d",&num);
            stack1[top1++]=num;
            n = n1 = top1;

            if(n>MAX)
            {
                printf("stack is full\n");
            }
            else
            {
                top2 = 0;
                while(n)
                    stack2[top2++]=stack1[--n];

                n2 = top2;

                for(int i=0;i<n1;i++)
                {
                    //printf("stack1[%d]=%d\n",i,stack1[i]);

                }
                for(int i=0;i<n2;i++)
                {
                    printf("queue[%d]=%d\n",i,stack2[i]);
                }  
            }
  
        }
        else if(strcmp(operate,"POP")==0)
        {
            if(n2==0)
            {
                printf("queue is empty\n");
            }
            else
            {
                n2--;
                n1--;
                top1 = 0;
                n = n2;
                while(n)
                    stack1[top1++]=stack2[--n];

                for(int i=0;i<n1;i++)
                {
                    //printf("stack1[%d]=%d\n",i,stack1[i]);
                    
                }
                for(int i=0;i<n2;i++)
                {
                    printf("queue[%d]=%d\n",i,stack2[i]);
                    
                }
            }
        }
        else if(strcmp(operate,"EXIT")==0)
        {
           bExit=true;
        }
        else
        {
            printf("invalid input!try again\n");
           
        }
    }
    return 0;
}

