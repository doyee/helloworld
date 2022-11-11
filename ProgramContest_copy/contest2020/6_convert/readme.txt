#Title: YUV image operations, including crop and scale
题目：YUV图像操作

给定一张YUV（nv21）的图，做crop和缩放操作
1. 读取 *.nv21 image 到内存
2. 对输入图4160x3120.nv21做基于中心点的crop，要求fov是 2560*1920  
   并对这张crop图，进行缩放操作，缩放到640*480.
4. 保存结果图到 640*480.nv21
请参考 convert.jpg

#Standard Input
 4608x3456.nv21 yuv image

#Constraints:
 none

#Standard Output
 640x480.nv21 yuv image

#Sample
 none


Output
 可以使用YUV Viewer对图像进行查看

//////////////////////////
#NOTE:
a. compiling command: gcc convert.c
b. running command: ./a.out
//////////////////////
