#include <stdio.h>
#include <stdlib.h>

#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b)   (a^=b,b^=a,a^=b)

/*
 * 冒泡排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void bubble_sort(int a[], int n)
{
     /* TODO: write code as below */
     int i,j;

     for (i=n-1; i>0; i--)
     {
        // 将a[0...i]中最大的数据放在末尾
          for (j=0; j<i; j++)
          {
               if (a[j] > a[j+1])
                    swap(a[j], a[j+1]);
          }
     }
}

int main()
{
     int i;
     int a[] = {80,79,99,18,20,39,28,10,59,43,78};
     int ilen = LENGTH(a);

     printf("before sort:");
     for (i=0; i<ilen; i++)
          printf("%d ", a[i]);
     printf("\n");

     bubble_sort(a, ilen);

     printf("after  sort:");
     for (i=0; i<ilen; i++)
          printf("%d ", a[i]);
     printf("\n");

     return 0;
}
