#include<stdio.h>
#include<stdlib.h>
//找出下面程序中的5处语法错误并修正，编译通过，并注释简述理由（不考虑编程风格问题）


int test(int i)//修改返回值类型
{
    float a = (float)1 / (float)2; //强制转换
    int b = i;
    int *c; 
      switch (b)
      {
        case 0:
             //*c = b; 
             c = &b; //指针指向b的地址
             break;            
        case 1 + 2:
             b = 3;
             break;        
        case 4:
             if (0.5 == a)
             {
                 //continue;//不能使用continue
             }
             break;             
        default:
             break;           
     }     
     //return &b;//不能return 局部变量地址
     return b;
}

int main(int i) {
   test(3);
   return 0;
}
