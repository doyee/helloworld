
#include <stdio.h>
#include <stdlib.h>

//从键盘输入4个学生的有关数据，然后把他们转存到磁盘文件上去

#define SIZE 4
struct student_type
{
	char name[10];
	char ID[10];
	int age;
	char addr[15];
}stud[SIZE];

int main() {
	struct student_type * std = (struct student_type*)malloc(sizeof(struct student_type)*4);
	for(int i = 0; i < 4; i++){
		char s[10];
		char d[10];
		int a;
		char as[15];
		scanf("%s", s);
		scanf("%s", d);
		scanf("%d", &a);
		scanf("%s", as);
		if(strlen(s) >  10 || strlen(d) >  10 || strlen(as) >  15){
       		printf("error");
        	return 0;
    	}
		memcpy(std[i].name, s, strlen(s));
		memcpy(std[i].ID, d, strlen(d));
		memcpy(std[i].addr, as, strlen(as));
		std[i].age = a;
	}

	char filename[256];
	memset(&filename, 0, sizeof(char)*256);
	snprintf(filename, sizeof(filename), "/mnt/d/stu_list.txt");

	//printf("%s\n", filename);

	FILE *fp = fopen(filename, "w");
	fwrite(std, sizeof(struct student_type), 4, fp);
	fclose(fp);

	fp = fopen(filename, "r");

	struct student_type * std1 = (struct student_type*)malloc(sizeof(struct student_type)*4);
	fread(std1, sizeof(struct  student_type), 4, fp);
	fclose(fp);

	for(int i = 0; i < 4; i++){
		printf("%s %s %d %s\n", std1[i].name, std1[i].ID, std1[i].age, std1[i].addr);
	}

    return 0;
}
















