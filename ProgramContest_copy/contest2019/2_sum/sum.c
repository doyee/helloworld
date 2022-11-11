#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    int a;
    char str[1024]={};
    scanf("%d", &a);
    if(a >= 30 || a <= 0){
        printf("error");
        return 0;
    }

    int* num1 = (int*)malloc(sizeof(int)*a);
    int* num2 = (int*)malloc(sizeof(int)*a);
    for(int i = 1; i <= a; i++){
        num1[i-1] = i;
        if(i == 1)
        {
            num2[i-1] = 2;
        }
        else
            num2[i-1] = num1[i-1] + num1[i - 2];
    }

    double res;

    for(int i = 0; i < a; i++){
       res += (double)num2[i]/(double)num1[i];
    }


    for(int i = 0; i < a; i++){
        char str1[1024];
        if(i == (a - 1)){
            snprintf(str1, sizeof(str1), "%d/%d = ", num2[i], num1[i]);
            strcat(str, str1);
        }
        else{
            snprintf(str1, sizeof(str1), "%d/%d+", num2[i], num1[i]);
            strcat(str, str1);
        }
    }
	printf("%s", str);
    printf("%f", res);

    return 0;
}
