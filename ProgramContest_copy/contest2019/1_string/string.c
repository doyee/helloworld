#include<stdio.h>
#include<stdlib.h>

int main() {
    char s[1024];
    scanf("%s", s);
    int len = strlen(s);

    if(len <= 0 || len >= 100){
        printf("error");
        return 0;
    }

    deleteduplicatedletter(&s);

    deleteletter(&s);

    converletter(&s);

    sort(&s);

    printf("%s", s);

    return 0;
}


void deleteduplicatedletter(char * str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        for(int j = i+1; j < len; j++){
            if(str[i] == str[j]){
                for (int k = j; k < len; k++)
                {
                    str[k] = str[k+1];
                }
                
                j--;
                len--;
            }
        }
    }
}

void deleteletter(char * str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if(str[i] >= 'A' && str[i]  <= 'Z' || str[i] >= 'a' && str[i]  <= 'z' || str[i] >= '0' && str[i] <= '9'){
            continue;
        }
        else{
            for(int j = i ; j < len; j++){
                str[j] = str[j+1];
            }
            i--;
            len--;
        }
    }

}

void converletter(char * str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if(str[i] >= 'A' && str[i]  <= 'Z'){
            str[i] += 32;
        }
        else if(str[i] >= 'a' && str[i]  <= 'z'){
            str[i] -= 32;
        }
    }
}

void sort(char * str){
    int len = strlen(str);
    for(int i = 0; i< len; i++){
        for(int j = i+1; j< len; j++){
            if(str[i] < str[j]){
                char temp = str[j];
                str[j] = str[i];
                str[i] = temp;
            }
        }
    }
    
}