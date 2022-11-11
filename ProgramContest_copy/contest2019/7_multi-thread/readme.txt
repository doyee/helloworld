#Title: multi-thread operations

Given a "4160x3120.nv21" yuv image,
1. create 4 threads to run 4 tasks in parall
2. the 4 tasks will be
   suppose the yuv image left and top as (0,0),and right and bottom as��4160��3120��
   task 1, set the left and top corner area as black,from pixle(0��0��to (1440,1080)//ͼ�����Ͻ��ú� 
   task 2, set a black rect on the center with the rect size 1280x960               //ͼ�����Ļ��ڿ򣬴�С1280x960
   task 3, flip the right and bottom, the rectangle region is 1440x1080             //ͼ�����½�1440x1080ˮƽ���� 
   task 4, rotate 180��for the left and bottom area, the region is 1440x1080        //ͼ�����½���ת180��
3. save the final result to a new yuv image of 4160x3120_new.nv21

����1��5�֣�����2ÿ��taks��3�ֹ�12�֣�����3��3��(4��task��ȷ������һ����ȷ)

#Standard Input
 4160x3120.nv21 yuv image

#Constraints:
 create 4 threads to excute the task in parall

#Standard Output
 4160x3120_new.nv21 with the above modifications

#Sample
 none


Output
 You can use YUView to double check the crop and scale yuv imag

//////////////////////////
#NOTE:
a. compiling command: gcc thread.c -lpthread
b. running command: ./a.out
//////////////////////
