#include <stdio.h>

#define MAXLEN 20

void replaceBlank(char *str,int length)
{
    int len1=0,space_num=0;
    
    while(str[len1]!='\0')
    {
        if(str[len1]==' ')
            space_num++;
        len1++;
    }

    printf("blank number =%d\n",space_num);


    if(len1>length)
    {
        printf("string length>MAX lenght(%d)\n",length);
        return;
    }
        
    len1--;

    while(len1>=0)
    {
        if(str[len1] ==' ')
        {
            str[len1]='_';
        }
        len1--;
    }
    printf("%s\n",str);
    return;
}


int main()
{

    char c,str[255];
    int i=0;
    while((c=getchar())!=EOF && c!='\n')
        str[i++]=c;
    str[i]='\0';
    replaceBlank(str,MAXLEN);

    return 0;

}